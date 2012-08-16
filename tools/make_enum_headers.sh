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
	echo "switch(GLenum(value))"
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

for InputFile in ${InputFiles}
do
(
	EnumClass=$(sed -n -e 's|^#\(\w\+\)#$|\1|p' < ${InputFile})

	IFS=':'

	grep -v -e '^\s*$' -e '^\s*#.*$' ${InputFile} |
	while read GL_DEF OGLPLUS_DEF X
	do
		if [ "${OGLPLUS_DEF}" == "" ]
		then OGLPLUS_DEF=$(echo ${GL_DEF} | sed 's/\([A-Z]\)\([A-Z0-9]*\)_\?/\1\L\2/g')
		fi

		mkdir -p ${ShortEnumTempDir}
		echo "${GL_DEF}" >> ${ShortEnumTempDir}/${OGLPLUS_DEF}
	done
)
done

(
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

		#echo -n "#if"
		#for GL_DEF in $(cat ${InputFile} | sort | uniq)
		#do echo -n " defined(GL_${GL_DEF}) ||"
		#done
		#echo " false"
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
		#echo "#endif"
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

