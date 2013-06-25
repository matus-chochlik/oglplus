#!/bin/bash
# Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
# Software License, Version 1.0. (See accompanying file
# LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
RootDir=${PWD}/$(dirname ${0})/..
InputDir="${RootDir}/source/enums"

function PrintFileHeader()
{
	echo "/*"
	echo " *  .file ${2}"
	echo " *"
	echo " *  Automatically generated header file. DO NOT modify manually,"
	echo " *  edit '${1##${RootDir}/}' instead."
	echo " *"
	echo " *  Copyright 2010-$(date +%Y) Matus Chochlik. Distributed under the Boost"
	echo " *  Software License, Version 1.0. (See accompanying file"
	echo " *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)"
	echo " */"
	echo
}

function MakeEnumClass()
{
	local EnumClass=$(sed -n -e 's|^#\([^@#]\+\)#$|\1|p' < ${1})
	if [ "${EnumClass}" == "" ]
	then EnumClass=$(echo $(basename ${1} .txt) | sed -e 's|^\([a-z]\)|\u\1|;s|_\([a-z]\)|\u\1|g')
	fi
	echo ${EnumClass}
}

function MakeEnumBaseType()
{
	local EnumBaseType=$(sed -n -e 's|^#@\([^@#]\+\)#$|\1|p' < ${1})
	if [ "${EnumBaseType}" == "" ]
	then EnumBaseType="enum"
	fi
	echo ${EnumBaseType}
}

ShortEnumTempDir=$(mktemp -d)

# Creates the following files:
#  ${LibName}/enums/${InputName}.ipp
#  ${LibName}/enums/${InputName}_def.ipp
#  ${LibName}/enums/${InputName}_names.ipp
function MakeEnumHeaders()
{
LibPrefixUC="${1}"
LibNameLC="${2}"
LibNameUC=${LibNameLC^^}
local InputFiles="${InputDir}/${LibNameLC}/*.txt"
shift 2
for SubDir
do InputFiles="${InputFiles} ${InputDir}/${LibNameLC}/${SubDir}/*.txt"
done

for InputFile in ${InputFiles}
do
	InputName="${InputFile#${InputDir}/${LibNameLC}/}"
	InputName=${InputName%.txt}

	OutputFile="${LibNameLC}/enums/${InputName}.ipp"
	OutputPath="${RootDir}/include/${OutputFile}"

	[[ ${InputFile} -ot ${OutputPath} ]] ||
	(
	echo "${InputName}" 1>&2
	mkdir -p $(dirname ${OutputPath})
	exec > ${OutputPath}
	PrintFileHeader ${InputFile} ${OutputFile}

	IFS=':'
	unset Comma
	echo "#if ${LibNameUC}_DOCUMENTATION_ONLY"
	grep -v -e '^\s*$' -e '^\s*#.*$' ${InputFile} |
	while read XL_DEF OXLPLUS_DEF AQ DOCUMENTATION BQ X
	do
		if [ "${OXLPLUS_DEF}" == "" ]
		then OXLPLUS_DEF=$(echo ${XL_DEF} | sed 's/\([A-Z]\)\([A-Z0-9]*\)_\?/\1\L\2/g')
		fi

		echo "${Comma}"
		echo "/// ${XL_DEF}${DOCUMENTATION:+: }${DOCUMENTATION}"
		echo -n "${OXLPLUS_DEF}"
		Comma=","
	done
	echo
	echo
	echo "#else // !${LibNameUC}_DOCUMENTATION_ONLY"
	echo
	echo "#include <${LibNameLC}/enums/${InputName}_def.ipp>"
	echo
	echo "#endif"
	)
	git add ${OutputPath}

	#
	OutputFile="${LibNameLC}/enums/${InputName}_def.ipp"
	OutputPath="${RootDir}/include/${OutputFile}"

	[[ ${InputFile} -ot ${OutputPath} ]] ||
	(
	exec > ${OutputPath}
	PrintFileHeader ${InputFile} ${OutputFile}

	echo "#ifdef ${LibNameUC}_LIST_NEEDS_COMMA"
	echo "# undef ${LibNameUC}_LIST_NEEDS_COMMA"
	echo "#endif"
	echo
	#
	IFS=':'
	grep -v -e '^\s*$' -e '^\s*#.*$' ${InputFile} |
	while read XL_DEF OXLPLUS_DEF AQ DOCUMENTATION BQ PREFIX X
	do
		if [ "${OXLPLUS_DEF}" == "" ]
		then OXLPLUS_DEF=$(echo ${XL_DEF} | sed 's/\([A-Z]\)\([A-Z0-9]*\)_\?/\1\L\2/g')
		fi

		LibPrefix=${PREFIX:-${LibPrefixUC}}
		echo "#if defined ${LibPrefix}_${XL_DEF}"
		echo "# if ${LibNameUC}_LIST_NEEDS_COMMA"
		echo "   ${LibNameUC}_ENUM_CLASS_COMMA"
		echo "# endif"

		echo "# if defined ${OXLPLUS_DEF}"
		echo "#  pragma push_macro(\"${OXLPLUS_DEF}\")"
		echo "#  undef ${OXLPLUS_DEF}"
		echo "   ${LibNameUC}_ENUM_CLASS_VALUE(${OXLPLUS_DEF}, ${LibPrefix}_${XL_DEF})"
		echo "#  pragma pop_macro(\"${OXLPLUS_DEF}\")"
		echo "# else"
		echo "   ${LibNameUC}_ENUM_CLASS_VALUE(${OXLPLUS_DEF}, ${LibPrefix}_${XL_DEF})"
		echo "# endif"

		echo "# ifndef ${LibNameUC}_LIST_NEEDS_COMMA"
		echo "#  define ${LibNameUC}_LIST_NEEDS_COMMA 1"
		echo "# endif"
		echo "#endif"
	done
	echo "#ifdef ${LibNameUC}_LIST_NEEDS_COMMA"
	echo "# undef ${LibNameUC}_LIST_NEEDS_COMMA"
	echo "#endif"
	echo
	)
	git add ${OutputPath}


	OutputFile="${LibNameLC}/enums/${InputName}_names.ipp"
	OutputPath="${RootDir}/include/${OutputFile}"

	[[ ${InputFile} -ot ${OutputPath} ]] ||
	(
	echo "${InputName}" 1>&2
	mkdir -p $(dirname ${OutputPath})
	exec > ${OutputPath}
	#
	PrintFileHeader ${InputFile} ${OutputFile}
	#
	EnumClass=$(MakeEnumClass ${InputFile})
	EnumBaseType=$(MakeEnumBaseType ${InputFile})
	#
	echo "namespace enums {"
	echo "${LibNameUC}_LIB_FUNC StrLit _ValueName("
	echo "	${EnumClass}*,"
	echo "	${LibPrefixUC}${EnumBaseType} value"
	echo ")"
	echo "#if (!${LibNameUC}_LINK_LIBRARY || defined(${LibNameUC}_IMPLEMENTING_LIBRARY)) && \\"
	echo "	!defined(${LibNameUC}_IMPL_EVN_${EnumClass^^})"
	echo "#define ${LibNameUC}_IMPL_EVN_${EnumClass^^}"
	echo "{"
	echo "switch(value)"
	echo "{"
	IFS=':'
	unset Comma
	grep -v -e '^\s*$' -e '^\s*#.*$' ${InputFile} |
	while read XL_DEF OXLPLUS_DEF AQ DOCUMENTATION BQ PREFIX X
	do
		LibPrefix=${PREFIX:-${LibPrefixUC}}
		echo "#if defined ${LibPrefix}_${XL_DEF}"
		echo "	case ${LibPrefix}_${XL_DEF}: return StrLit(\"${XL_DEF}\");"
		echo "#endif"
	done
	echo "	default:;"
	echo "}"
	echo "${LibNameUC}_FAKE_USE(value);"
	echo "return StrLit();"
	echo "}"
	echo "#else"
	echo ";"
	echo "#endif"
	echo "} // namespace enums"
	echo
	)

	git add ${OutputPath}

	OutputFile="${LibNameLC}/enums/${InputName}_range.ipp"
	OutputPath="${RootDir}/include/${OutputFile}"

	[[ ${InputFile} -ot ${OutputPath} ]] ||
	(
	echo "${InputName}" 1>&2
	mkdir -p $(dirname ${OutputPath})
	exec > ${OutputPath}
	#
	PrintFileHeader ${InputFile} ${OutputFile}
	#
	EnumClass=$(MakeEnumClass ${InputFile})
	EnumBaseType=$(MakeEnumBaseType ${InputFile})
	#
	echo "namespace enums {"
	echo "${LibNameUC}_LIB_FUNC aux::CastIterRange<"
	echo "	const ${LibPrefixUC}${EnumBaseType}*,"
	echo "	${EnumClass}"
	echo "> _ValueRange(${EnumClass}*)"
	echo "#if (!${LibNameUC}_LINK_LIBRARY || defined(${LibNameUC}_IMPLEMENTING_LIBRARY)) && \\"
	echo "	!defined(${LibNameUC}_IMPL_EVR_${EnumClass^^})"
	echo "#define ${LibNameUC}_IMPL_EVR_${EnumClass^^}"
	echo "{"
	echo "static const ${LibPrefixUC}${EnumBaseType} _values[] = {"
	IFS=':'
	unset Comma
	grep -v -e '^\s*$' -e '^\s*#.*$' ${InputFile} |
	while read XL_DEF OXLPLUS_DEF AQ DOCUMENTATION BQ PREFIX X
	do
		LibPrefix=${PREFIX:-${LibPrefixUC}}
		echo "#if defined ${LibPrefix}_${XL_DEF}"
		echo "${LibPrefix}_${XL_DEF},"
		echo "#endif"
	done
	echo "0"
	echo "};"
	echo "return aux::CastIterRange<"
	echo "	const ${LibPrefixUC}${EnumBaseType}*,"
	echo "	${EnumClass}"
	echo ">(_values, _values+sizeof(_values)/sizeof(_values[0])-1);"
	echo "}"
	echo "#else"
	echo ";"
	echo "#endif"
	echo "} // namespace enums"
	echo
	)

	git add ${OutputPath}
done
} # MakeEnumHeaders()

# Creates the ${LibName}/lib/enum_value_name.ipp file
function MakeEnumValueName()
{(
LibPrefixUC="${1}"
LibNameLC="${2}"
LibNameUC=${LibNameLC^^}
local InputFiles="${InputDir}/${LibNameLC}/*.txt"
shift 2
for SubDir
do InputFiles="${InputFiles} ${InputDir}/${LibNameLC}/${SubDir}/*.txt"
done

OutputFile="${LibNameLC}/lib/enum_value_name.ipp"
OutputPath="${RootDir}/include/${OutputFile}"

mkdir -p $(dirname ${OutputPath})
exec > ${OutputPath}

PrintFileHeader "${RootDir}/source/enums/${LibNameLC}/.*.txt" ${OutputFile}

echo "#if !${LibNameUC}_NO_ENUM_VALUE_NAMES"
for InputFile in ${InputFiles}
do
	InputName="${InputFile#${InputDir}/${LibNameLC}/}"
	InputName=${InputName%.txt}

	EnumClass=$(MakeEnumClass ${InputFile})
	EnumBaseType=$(MakeEnumBaseType ${InputFile})

	echo "${LibNameUC}_ENUM_CLASS_FWD(${EnumClass}, ${LibPrefixUC}${EnumBaseType})"
	echo "#include <${LibNameLC}/enums/${InputName}_names.ipp>"
	echo
done
echo "#endif"

git add ${OutputPath}
)} # MakeEnumValueName()

# Creates the ${1}/lib/enum_value_range.ipp file
function MakeEnumValueRange()
{(
LibPrefixUC="${1}"
LibNameLC="${2}"
LibNameUC=${LibNameLC^^}
local InputFiles="${InputDir}/${LibNameLC}/*.txt"
shift 2
for SubDir
do InputFiles="${InputFiles} ${InputDir}/${LibNameLC}/${SubDir}/*.txt"
done

OutputFile="${LibNameLC}/lib/enum_value_range.ipp"
OutputPath="${RootDir}/include/${OutputFile}"

mkdir -p $(dirname ${OutputPath})
exec > ${OutputPath}

PrintFileHeader "${RootDir}/source/enums/${LibNameLC}/.*.txt" ${OutputFile}

echo "#if !${LibNameUC}_NO_ENUM_VALUE_RANGES"
for InputFile in ${InputFiles}
do
	InputName="${InputFile#${InputDir}/${LibNameLC}/}"
	InputName=${InputName%.txt}

	EnumClass=$(MakeEnumClass ${InputFile})
	EnumBaseType=$(MakeEnumBaseType ${InputFile})

	echo "${LibNameUC}_ENUM_CLASS_FWD(${EnumClass}, ${LibPrefixUC}${EnumBaseType})"
	echo "#include <${LibNameLC}/enums/${InputName}_range.ipp>"
	echo
done
echo "#endif"

git add ${OutputPath}
)} # MakeEnumValueRange


# Creates the ${LibName}/auxiliary/enum_shorteners.ipp file
function MakeEnumShorteners()
{
LibPrefixUC="${1}"
LibNameLC="${2}"
LibNameUC=${LibNameLC^^}
local InputFiles="${InputDir}/${LibNameLC}/*.txt"
shift 2
for SubDir
do InputFiles="${InputFiles} ${InputDir}/${LibNameLC}/${SubDir}/*.txt"
done

for InputFile in ${InputFiles}
do
(
	EnumClass=$(MakeEnumClass ${InputFile})

	IFS=':'

	grep -v -e '^\s*$' -e '^\s*#.*$' ${InputFile} |
	while read XL_DEF OXLPLUS_DEF X
	do
		if [ "${OXLPLUS_DEF}" == "" ]
		then OXLPLUS_DEF=$(echo ${XL_DEF} | sed 's/\([A-Z]\)\([A-Z0-9]*\)_\?/\1\L\2/g')
		fi

		mkdir -p ${ShortEnumTempDir}
		echo "${XL_DEF}:${EnumClass}" >> ${ShortEnumTempDir}/${OXLPLUS_DEF}
	done
)
done

(
	# first the real-deal
	OutputFile="${LibNameLC}/auxiliary/enum_shorteners.ipp"
	OutputPath="${RootDir}/include/${OutputFile}"

	mkdir -p $(dirname ${OutputPath})
	exec > ${OutputPath}
	PrintFileHeader "${RootDir}/source/enums/${LibNameLC}/.*.txt" ${OutputFile}

	# the enumeration name shorteners
	find ${ShortEnumTempDir}/ -mindepth 1 -maxdepth 1 -type f |
	sort |
	while read InputFile
	do
		OXLPLUS_DEF=$(basename ${InputFile})

		echo -n "struct ${OXLPLUS_DEF} {"
		echo
		echo -n "template <typename Enum, Enum = Enum::${OXLPLUS_DEF}> operator Enum (void) const"
		echo -n "{ return Enum::${OXLPLUS_DEF}; }"
		echo
		echo -n "template <typename Enum> friend bool operator==(Enum value, ${OXLPLUS_DEF})"
		echo -n "{ return value == Enum::${OXLPLUS_DEF}; }"
		echo
		echo -n "template <typename Enum> friend bool operator!=(Enum value, ${OXLPLUS_DEF})"
		echo -n "{ return value != Enum::${OXLPLUS_DEF}; }"
		echo
		echo "};"
	done

	git add ${OutputPath}

	# now the documentation
	OutputFile="${LibNameLC}/auxiliary/enum_shorteners_doc.ipp"
	OutputPath="${RootDir}/include/${OutputFile}"

	mkdir -p $(dirname ${OutputPath})
	exec > ${OutputPath}
	PrintFileHeader "${RootDir}/source/enums/${LibNameLC}/.*.txt" ${OutputFile}

	# the enumeration name shorteners
	find ${ShortEnumTempDir}/ -mindepth 1 -maxdepth 1 -type f |
	sort |
	while read InputFile
	do
		OXLPLUS_DEF=$(basename ${InputFile})

		echo "/// @ref ${LibNameLC}_smart_enums \"Smart enum\" for enumerations with the @c ${OXLPLUS_DEF} value."
		echo "/**"
		for OXLPLUS_ENUM in $(cut -d':' -f2 < ${InputFile} | sort | uniq)
		do echo " *  @see @ref ${LibNameLC}::${OXLPLUS_ENUM} \"${OXLPLUS_ENUM}\""
		done
		echo " *"
		echo " *  @${LibPrefixUC,,}symbols"
		for XL_DEF in $(cut -d':' -f1 < ${InputFile} | sort | uniq)
		do echo " *  @${LibPrefixUC,,}defref{${XL_DEF}}"
		done
		echo " *"
		echo " *  @ingroup smart_enums"
		echo " */"
		echo "struct ${OXLPLUS_DEF} {"
		echo
		echo "/// Conversion to any @p Enum type having the ${OXLPLUS_DEF} value."
		echo "/** Instances of the @ref ${LibNameLC}::smart_enums::${OXLPLUS_DEF} \"${OXLPLUS_DEF}\""
		echo " *  type are convertible to instances of any enumeration type having"
		echo " *  the @c ${OXLPLUS_DEF} value."
		echo " */"
		echo "template <typename Enum, Enum = Enum::${OXLPLUS_DEF}> operator Enum (void) const;"
		echo
		echo "/// Equality comparison with any @p Enum type having the ${OXLPLUS_DEF} value."
		echo "/** Instances of the @c smart_enums::${OXLPLUS_DEF} type can be compared"
		echo " *  for equality to instances of any enumeration type having"
		echo " *  the @c ${OXLPLUS_DEF} value."
		echo " */"
		echo "template <typename Enum> friend bool operator==(Enum value, ${OXLPLUS_DEF});"
		echo
		echo "/// Non-equality comparison with any @p Enum type having the ${OXLPLUS_DEF} value."
		echo "/** Instances of the @c smart_enums::${OXLPLUS_DEF} type can be compared"
		echo " *  for non-equality to instances of any enumeration type having"
		echo " *  the @c ${OXLPLUS_DEF} value."
		echo " */"
		echo "template <typename Enum> friend bool operator!=(Enum value, ${OXLPLUS_DEF});"
		echo "};"
		echo
	done

	git add ${OutputPath}
)

rm -rf ${ShortEnumTempDir}
} # MakeEnumShorteners()


# the mapping of target def. to binding query def.
function MakeEnumBQHeaders()
{
LibPrefixUC="${1}"
LibNameLC="${2}"
LibNameUC=${LibNameLC^^}
local InputFiles="${InputDir}/${LibNameLC}/*.txt"
shift 2
for SubDir
do InputFiles="${InputFiles} ${InputDir}/${LibNameLC}/${SubDir}/*.txt"
done

grep -c -e '^\([^:]*:\)\{4\}[^:]\+' ${InputFiles} |
grep -v -e ':0$' |
cut -d':' -f1 |
while read InputFile
do
	InputName="${InputFile#${InputDir}/${LibNameLC}/}"
	InputName=${InputName%.txt}

	OutputFile="${LibNameLC}/enums/${InputName}_bq.ipp"
	OutputPath="${RootDir}/include/${OutputFile}"
	[[ ${InputFile} -nt ${OutputPath} ]] || continue
	echo "${InputName}" 1>&2
	(
	mkdir -p $(dirname ${OutputPath})
	exec > ${OutputPath}
	PrintFileHeader ${InputFile} ${OutputFile}
	#
	IFS=:
	grep -v -e '^\s*$' -e '^\s*#.*$' ${InputFile} |
	while read XL_DEF OXLPLUS_DEF AQ DOCUMENTATION BQ PREFIX X
	do
		if [ "${BINDING_QUERY_DEF}" != "" ]
		then
			LibPrefix=${PREFIX:-${LibPrefixUC}}
			echo "#if defined ${LibPrefix}_${XL_DEF} && defined ${LibPrefix}_${BINDING_QUERY_DEF}"
			echo "case ${LibPrefix}_${XL_DEF}:"
			echo "	return ${LibPrefix}_${BINDING_QUERY_DEF};"
			echo "#endif"
		fi
	done
	echo
	)

	git add ${OutputPath}
done
} # MakeEnumBQHeaders()

# specials
#
function MapGLSLtypeToCPPtype()
{
	LibPrefixUC="${1}"
	LibNameLC="${2}"
	shift 2
	case ${1} in
		NONE) echo "void";;

		BOOL) echo "${LibPrefixUC}boolean";;
		INT) echo "${LibPrefixUC}int";;
		UNSIGNED_INT) echo "${LibPrefixUC}uint";;
		FLOAT) echo "${LibPrefixUC}float";;
		DOUBLE) echo "${LibPrefixUC}double";;

		*_VEC[234])
			local ELEM=$(MapGLSLtypeToCPPtype ${LibPrefixUC} ${LibNameLC} ${1%_VEC[234]})
			local N=${1#*_VEC}
			echo "${LibNameLC}::Vector<${ELEM}, ${N}>";;

		*_MAT[234])
			local ELEM=$(MapGLSLtypeToCPPtype ${LibPrefixUC} ${LibNameLC} ${1%_MAT[234]})
			local N=${1#*_MAT}
			echo "${LibNameLC}::Matrix<${ELEM}, ${N}, ${N}>";;

		*_MAT[234]x[234])
			local ELEM=$(MapGLSLtypeToCPPtype ${LibPrefixUC} ${LibNameLC} ${1%_MAT[234]x[234]})
			local D=${1#*_MAT}
			local C=${D%x[234]}
			local R=${D#[234]x}
			echo "${LibNameLC}::Matrix<${ELEM}, ${R}, ${C}>";;

		*SAMPLER*) echo "${LibPrefixUC}int";;
		*IMAGE*) echo "${LibPrefixUC}int";;

		*) echo "${LibPrefixUC}uint";;
	esac
}
# sl_data_type -> C++ type mapping
function MakeGLSLtoCPPtypeHeader()
{
LibPrefixUC="${1}"
LibNameLC="${2}"
InputFile="${RootDir}/source/enums/${LibNameLC}/sl_data_type.txt"
OutputFile="${LibNameLC}/auxiliary/glsl_to_cpp.ipp"
OutputPath="${RootDir}/include/${OutputFile}"
(
	mkdir -p $(dirname ${OutputPath})
	exec > ${OutputPath}
	PrintFileHeader ${InputFile} ${OutputFile}
	#
	IFS=:

	grep -v -e '^\s*$' -e '^\s*#.*$' ${InputFile} |
	while read XL_DEF OXLPLUS_DEF AQ DOCUMENTATION BQ PREFIX X
	do
		if [ "${OXLPLUS_DEF}" == "" ]
		then OXLPLUS_DEF=$(echo ${XL_DEF} | sed 's/\([A-Z]\)\([A-Z0-9]*\)_\?/\1\L\2/g')
		fi

		LibPrefix=${PREFIX:-${LibPrefixUC}}
		TYPE=$(MapGLSLtypeToCPPtype ${LibPrefix} ${LibNameLC} ${XL_DEF})

		echo "#ifdef ${LibPrefix}_${XL_DEF}"
		echo "# ifdef ${OXLPLUS_DEF}"
		echo "# pragma push_macro(\"${OXLPLUS_DEF}\")"
		echo "# undef ${OXLPLUS_DEF}"
		echo "template <> struct GLSL2Cpp<"
		echo "	${LibNameUC}_CONST_ENUM_VALUE(SLDataType::${OXLPLUS_DEF})"
		echo "> { typedef ${TYPE} Type; };"
		echo "# pragma pop_macro(\"${OXLPLUS_DEF}\")"
		echo "# else"
		echo "template <> struct GLSL2Cpp<"
		echo "	${LibNameUC}_CONST_ENUM_VALUE(SLDataType::${OXLPLUS_DEF})"
		echo "> { typedef ${TYPE} Type; };"
		echo "# endif"
		echo "#endif // ${XL_DEF}"
		echo
	done
	echo
)
git add ${OutputPath}

} #MakeSLtoCPPtypeHeader()

if [ $# -eq 0 ] || [ "${1}" == "oglplus" ]
then
	MakeEnumHeaders GL oglplus ext
	MakeEnumValueName GL oglplus ext
	MakeEnumValueRange GL oglplus ext
	MakeEnumShorteners GL oglplus ext
	MakeEnumBQHeaders GL oglplus ext
	MakeGLSLtoCPPtypeHeader GL oglplus
fi

if [ $# -eq 0 ] || [ "${1}" == "oalplus" ]
then
	MakeEnumHeaders AL oalplus
	MakeEnumValueName AL oalplus
	MakeEnumValueRange AL oalplus
fi

if [ $# -eq 0 ] || [ "${1}" == "eglplus" ]
then
	MakeEnumHeaders EGL eglplus
	MakeEnumValueName EGL eglplus
	MakeEnumValueRange EGL eglplus
fi
