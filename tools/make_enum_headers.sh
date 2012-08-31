#!/bin/bash
# Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
# Software License, Version 1.0. (See accompanying file
# LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
RootDir=${1:-${PWD}}
InputDir="${RootDir}/source/enums"
InputFiles="${InputDir}/*.txt ${InputDir}/ext/*.txt"

function PrintFileHeader()
{
	echo "/*"
	echo " *  .file ${2}"
	echo " *"
	echo " *  Automatically generated header file. DO NOT modify manually,"
	echo " *  edit '${1##${RootDir}/}' instead."
	echo " *"
	echo " *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost"
	echo " *  Software License, Version 1.0. (See accompanying file"
	echo " *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)"
	echo " */"
	echo
}

ShortEnumTempDir=$(mktemp -d)

# Creates the following files:
#  oglplus/enums/${InputName}.ipp
#  oglplus/enums/${InputName}_ese.ipp
#  oglplus/enums/${InputName}_nse.ipp
for InputFile in ${InputFiles}
do
	InputName="${InputFile#${InputDir}/}"
	InputName=${InputName%.txt}

	OutputFile="oglplus/enums/${InputName}.ipp"
	OutputPath="${RootDir}/include/${OutputFile}"

	[[ ${InputFile} -ot ${OutputPath} ]] ||
	(
	echo "${InputName}" 1>&2
	mkdir -p $(dirname ${OutputPath})
	exec > ${OutputPath}
	PrintFileHeader ${InputFile} ${OutputFile}

	IFS=':'
	unset Comma
	echo "#if OGLPLUS_DOCUMENTATION_ONLY"
	grep -v -e '^\s*$' -e '^\s*#.*$' ${InputFile} |
	while read GL_DEF OGLPLUS_DEF AQ DOCUMENTATION BQ QN
	do
		if [ "${OGLPLUS_DEF}" == "" ]
		then OGLPLUS_DEF=$(echo ${GL_DEF} | sed 's/\([A-Z]\)\([A-Z0-9]*\)_\?/\1\L\2/g')
		fi

		echo "${Comma}"
		echo "/// ${GL_DEF}${DOCUMENTATION:+: }${DOCUMENTATION}"
		echo -n "${OGLPLUS_DEF}"
		Comma=","
	done
	echo
	echo
	echo "#else // !OGLPLUS_DOCUMENTATION_ONLY"
	echo
	echo "# if !OGLPLUS_NO_SCOPED_ENUMS"
	echo "// native scoped enums"
	echo "# include <oglplus/enums/${InputName}_nse.ipp>"
	echo "# else"
	echo "// emulated scoped enums"
	echo "# include <oglplus/enums/${InputName}_ese.ipp>"
	echo "# endif"
	echo
	echo "#endif"
	)
	git add ${OutputPath}

	#
	OutputFile="oglplus/enums/${InputName}_nse.ipp"
	OutputPath="${RootDir}/include/${OutputFile}"

	[[ ${InputFile} -ot ${OutputPath} ]] ||
	(
	exec > ${OutputPath}
	PrintFileHeader ${InputFile} ${OutputFile}

	echo "#ifdef OGLPLUS_LIST_NEEDS_COMMA"
	echo "# undef OGLPLUS_LIST_NEEDS_COMMA"
	echo "#endif"
	echo
	#
	IFS=':'
	grep -v -e '^\s*$' -e '^\s*#.*$' ${InputFile} |
	while read GL_DEF OGLPLUS_DEF X
	do
		if [ "${OGLPLUS_DEF}" == "" ]
		then OGLPLUS_DEF=$(echo ${GL_DEF} | sed 's/\([A-Z]\)\([A-Z0-9]*\)_\?/\1\L\2/g')
		fi

		echo "#if defined GL_${GL_DEF}"
		echo "# if OGLPLUS_LIST_NEEDS_COMMA"
		echo "   ,"
		echo "# endif"
		echo "  OGLPLUS_ENUM_CLASS_VALUE(${OGLPLUS_DEF}, GL_${GL_DEF})"
		echo "# ifndef OGLPLUS_LIST_NEEDS_COMMA"
		echo "#  define OGLPLUS_LIST_NEEDS_COMMA 1"
		echo "# endif"
		echo "#endif"
	done
	echo "#ifdef OGLPLUS_LIST_NEEDS_COMMA"
	echo "# undef OGLPLUS_LIST_NEEDS_COMMA"
	echo "#endif"
	echo
	)
	git add ${OutputPath}

	#
	OutputFile="oglplus/enums/${InputName}_ese.ipp"
	OutputPath="${RootDir}/include/${OutputFile}"

	[[ ${InputFile} -ot ${OutputPath} ]] ||
	(
	exec > ${OutputPath}
	PrintFileHeader ${InputFile} ${OutputFile}

	#
	IFS=':'
	grep -v -e '^\s*$' -e '^\s*#.*$' ${InputFile} |
	while read GL_DEF OGLPLUS_DEF X
	do
		if [ "${OGLPLUS_DEF}" == "" ]
		then OGLPLUS_DEF=$(echo ${GL_DEF} | sed 's/\([A-Z]\)\([A-Z0-9]*\)_\?/\1\L\2/g')
		fi

		echo "#if defined GL_${GL_DEF}"
		echo "# if defined ${OGLPLUS_DEF}"
		echo "#  pragma push_macro(\"${OGLPLUS_DEF}\")"
		echo "#  undef ${OGLPLUS_DEF}"
		echo "   OGLPLUS_ENUM_CLASS_VALUE(${OGLPLUS_DEF}, GL_${GL_DEF})"
		echo "#  pragma pop_macro(\"${OGLPLUS_DEF}\")"
		echo "# else"
		echo "   OGLPLUS_ENUM_CLASS_VALUE(${OGLPLUS_DEF}, GL_${GL_DEF})"
		echo "# endif"
		echo "#endif"
	done
	)
	git add ${OutputPath}

	OutputFile="oglplus/names/${InputName}.ipp"
	OutputPath="${RootDir}/include/${OutputFile}"

	[[ ${InputFile} -ot ${OutputPath} ]] ||
	(
	echo "${InputName}" 1>&2
	mkdir -p $(dirname ${OutputPath})
	exec > ${OutputPath}
	PrintFileHeader ${InputFile} ${OutputFile}
	#
	IFS=':'
	unset Comma
	echo "switch(value)"
	echo "{"
	grep -v -e '^\s*$' -e '^\s*#.*$' ${InputFile} |
	while read GL_DEF X
	do
		echo "#if defined GL_${GL_DEF}"
		echo "	case GL_${GL_DEF}: return StrLit(\"${GL_DEF}\");"
		echo "#endif"
	done
	echo "	default:;"
	echo "}"
	echo
	)

	git add ${OutputPath}
done

# Creates the oglplus/lib/enum_value_name.ipp file
(
OutputFile="oglplus/lib/enum_value_name.ipp"
OutputPath="${RootDir}/include/${OutputFile}"

mkdir -p $(dirname ${OutputPath})
exec > ${OutputPath}

PrintFileHeader "${RootDir}/source/enums/.*.txt" ${OutputFile}

for InputFile in ${InputFiles}
do
	InputName="${InputFile#${InputDir}/}"
	InputName=${InputName%.txt}

	EnumClass=$(sed -n -e 's|^#\([^@#]\+\)#$|\1|p' < ${InputFile})
	if [ "${EnumClass}" == "" ]
	then EnumClass=$(echo $(basename ${InputFile} .txt) | sed -e 's|^\([a-z]\)|\u\1|;s|_\([a-z]\)|\u\1|g')
	fi

	EnumBaseType=$(sed -n -e 's|^#@\([^@#]\+\)#$|\1|p' < ${InputFile})
	if [ "${EnumBaseType}" == "" ]
	then EnumBaseType="enum"
	fi

	echo "OGLPLUS_ENUM_CLASS_FWD(${EnumClass}, GL${EnumBaseType})"
	echo "StrLit EnumValueName(${EnumClass}*, GL${EnumBaseType} value)"
	echo "OGLPLUS_NOEXCEPT(true)"
	echo "{"
	echo "#if !OGLPLUS_NO_ENUM_VALUE_NAMES"
	echo "#include <oglplus/names/${InputName}.ipp>"
	echo "#else"
	echo "	OGLPLUS_FAKE_USE(value);"
	echo "#endif"
	echo "	return StrLit();"
	echo "}"
	echo
done
)

for InputFile in ${InputFiles}
do
(
	EnumClass=$(sed -n -e 's|^#\([^@#]\+\)#$|\1|p' < ${InputFile})
	if [ "${EnumClass}" == "" ]
	then EnumClass=$(echo $(basename ${InputFile} .txt) | sed -e 's|^\([a-z]\)|\u\1|;s|_\([a-z]\)|\u\1|g')
	fi

	IFS=':'

	grep -v -e '^\s*$' -e '^\s*#.*$' ${InputFile} |
	while read GL_DEF OGLPLUS_DEF X
	do
		if [ "${OGLPLUS_DEF}" == "" ]
		then OGLPLUS_DEF=$(echo ${GL_DEF} | sed 's/\([A-Z]\)\([A-Z0-9]*\)_\?/\1\L\2/g')
		fi

		mkdir -p ${ShortEnumTempDir}
		echo "${GL_DEF}:${EnumClass}" >> ${ShortEnumTempDir}/${OGLPLUS_DEF}
	done
)
done

(
	# first the real-deal
	OutputFile="oglplus/auxiliary/enum_shorteners.ipp"
	OutputPath="${RootDir}/include/${OutputFile}"

	mkdir -p $(dirname ${OutputPath})
	exec > ${OutputPath}
	PrintFileHeader "${RootDir}/source/enums/.*.txt" ${OutputFile}

	# the enumeration name shorteners
	find ${ShortEnumTempDir}/ -mindepth 1 -maxdepth 1 -type f |
	sort |
	while read InputFile
	do
		OGLPLUS_DEF=$(basename ${InputFile})

		echo -n "struct ${OGLPLUS_DEF} {"
		echo
		echo -n "template <typename Enum, Enum = Enum::${OGLPLUS_DEF}> operator Enum (void) const"
		echo -n "{ return Enum::${OGLPLUS_DEF}; }"
		echo
		echo -n "template <typename Enum> friend bool operator==(Enum value, ${OGLPLUS_DEF})"
		echo -n "{ return value == Enum::${OGLPLUS_DEF}; }"
		echo
		echo -n "template <typename Enum> friend bool operator!=(Enum value, ${OGLPLUS_DEF})"
		echo -n "{ return value != Enum::${OGLPLUS_DEF}; }"
		echo
		echo "};"
	done

	git add ${OutputPath}

	# now the documentation
	OutputFile="oglplus/auxiliary/enum_shorteners_doc.ipp"
	OutputPath="${RootDir}/include/${OutputFile}"

	mkdir -p $(dirname ${OutputPath})
	exec > ${OutputPath}
	PrintFileHeader "${RootDir}/source/enums/.*.txt" ${OutputFile}

	# the enumeration name shorteners
	find ${ShortEnumTempDir}/ -mindepth 1 -maxdepth 1 -type f |
	sort |
	while read InputFile
	do
		OGLPLUS_DEF=$(basename ${InputFile})

		echo "/// @ref oglplus_smart_enums \"Smart enum\" for enumerations with the @c ${OGLPLUS_DEF} value."
		echo "/**"
		for OGLPLUS_ENUM in $(cut -d':' -f2 < ${InputFile} | sort | uniq)
		do echo " *  @see @ref oglplus::${OGLPLUS_ENUM} \"${OGLPLUS_ENUM}\""
		done
		echo " *"
		echo " *  @glsymbols"
		for GL_DEF in $(cut -d':' -f1 < ${InputFile} | sort | uniq)
		do echo " *  @gldefref{${GL_DEF}}"
		done
		echo " *"
		echo " *  @ingroup smart_enums"
		echo " */"
		echo "struct ${OGLPLUS_DEF} {"
		echo
		echo "/// Conversion to any @p Enum type having the ${OGLPLUS_DEF} value."
		echo "/** Instances of the @ref oglplus::smart_enums::${OGLPLUS_DEF} \"${OGLPLUS_DEF}\""
		echo " *  type are convertible to instances of any enumeration type having"
		echo " *  the @c ${OGLPLUS_DEF} value."
		echo " */"
		echo "template <typename Enum, Enum = Enum::${OGLPLUS_DEF}> operator Enum (void) const;"
		echo
		echo "/// Equality comparison with any @p Enum type having the ${OGLPLUS_DEF} value."
		echo "/** Instances of the @c smart_enums::${OGLPLUS_DEF} type can be compared"
		echo " *  for equality to instances of any enumeration type having"
		echo " *  the @c ${OGLPLUS_DEF} value."
		echo " */"
		echo "template <typename Enum> friend bool operator==(Enum value, ${OGLPLUS_DEF});"
		echo
		echo "/// Non-equality comparison with any @p Enum type having the ${OGLPLUS_DEF} value."
		echo "/** Instances of the @c smart_enums::${OGLPLUS_DEF} type can be compared"
		echo " *  for non-equality to instances of any enumeration type having"
		echo " *  the @c ${OGLPLUS_DEF} value."
		echo " */"
		echo "template <typename Enum> friend bool operator!=(Enum value, ${OGLPLUS_DEF});"
		echo "};"
		echo
	done

	git add ${OutputPath}
)

rm -rf ${ShortEnumTempDir}


# the mapping of target def. to binding query def.
grep -c -e '^\([^:]*:\)\{4\}[^:]\+' ${InputFiles} |
grep -v -e ':0$' |
cut -d':' -f1 |
while read InputFile
do
	InputName="${InputFile#${InputDir}/}"
	InputName=${InputName%.txt}

	OutputFile="oglplus/enums/${InputName}_bq.ipp"
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
	while read GL_DEF OGL_DEF AQ DOC BINDING_QUERY_DEF X
	do
		if [ "${BINDING_QUERY_DEF}" != "" ]
		then
			echo "#if defined GL_${GL_DEF} && defined GL_${BINDING_QUERY_DEF}"
			echo "case GL_${GL_DEF}:"
			echo "	return GL_${BINDING_QUERY_DEF};"
			echo "#endif"
		fi
	done
	echo
	)

	git add ${OutputPath}
done

