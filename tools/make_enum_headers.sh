#!/bin/bash
# Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
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
OutputPath="${RootDir}/implement/${OutputFile}"

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
OutputPath="${RootDir}/implement/${OutputFile}"

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
	OutputPath="${RootDir}/implement/${OutputFile}"
	[[ ${InputFile} -nt ${OutputPath} ]] || continue
	echo "${InputName}" 1>&2
	(
	mkdir -p $(dirname ${OutputPath})
	exec > ${OutputPath}
	PrintFileHeader ${InputFile} ${OutputFile}
	#
	IFS=:
	grep -v -e '^\s*$' -e '^\s*#.*$' ${InputFile} |
	while read XL_DEF OXLPLUS_DEF AQ DOCUMENTATION BINDING_QUERY_DEF PREFIX X
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
OutputFile="${LibNameLC}/detail/glsl_to_cpp.ipp"
OutputPath="${RootDir}/implement/${OutputFile}"
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
		echo "	SLDataType::${OXLPLUS_DEF}"
		echo "> { typedef ${TYPE} Type; };"
		echo "# pragma pop_macro(\"${OXLPLUS_DEF}\")"
		echo "# else"
		echo "template <> struct GLSL2Cpp<"
		echo "	SLDataType::${OXLPLUS_DEF}"
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
	MakeEnumValueName GL oglplus ext
	MakeEnumValueRange GL oglplus ext
	MakeEnumBQHeaders GL oglplus ext
	MakeGLSLtoCPPtypeHeader GL oglplus
fi

if [ $# -eq 0 ] || [ "${1}" == "oalplus" ]
then
	MakeEnumValueName AL oalplus
	MakeEnumValueRange AL oalplus
fi

if [ $# -eq 0 ] || [ "${1}" == "eglplus" ]
then
	MakeEnumValueName EGL eglplus
	MakeEnumValueRange EGL eglplus
fi
