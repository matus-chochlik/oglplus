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

for InputFile in ${InputFiles}
do
	InputName="${InputFile#${InputDir}/}"
	InputName=${InputName%.txt}

	OutputFile="oglplus/enums/${InputName}.ipp"
	OutputPath="${RootDir}/include/${OutputFile}"
	[[ ${InputFile} -nt ${OutputPath} ]] || continue
	echo "${InputName}" 1>&2
	(
	mkdir -p $(dirname ${OutputPath})
	exec > ${OutputPath}
	PrintFileHeader ${InputFile} ${OutputFile}
	#
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
	echo "#ifdef OGLPLUS_LIST_NEEDS_COMMA"
	echo "# undef OGLPLUS_LIST_NEEDS_COMMA"
	echo "#endif"
	echo
	#
	grep -v -e '^\s*$' -e '^\s*#.*$' ${InputFile} |
	while read GL_DEF OGLPLUS_DEF X
	do
		if [ "${OGLPLUS_DEF}" == "" ]
		then OGLPLUS_DEF=$(echo ${GL_DEF} | sed 's/\([A-Z]\)\([A-Z0-9]*\)_\?/\1\L\2/g')
		fi

		echo "#if defined GL_${GL_DEF}"
		echo "# if OGLPLUS_LIST_NEEDS_COMMA"
		echo ","
		echo "# endif"
		echo "${OGLPLUS_DEF} = GL_${GL_DEF}"
		echo "# ifndef OGLPLUS_LIST_NEEDS_COMMA"
		echo "#  define OGLPLUS_LIST_NEEDS_COMMA 1"
		echo "# endif"
		echo "#endif"
	done
	echo "#ifdef OGLPLUS_LIST_NEEDS_COMMA"
	echo "# undef OGLPLUS_LIST_NEEDS_COMMA"
	echo "#endif"
	echo
	echo "#endif // !OGLPLUS_DOCUMENTATION_ONLY"
	echo
	)

	git add ${OutputPath}

	OutputFile="oglplus/names/${InputName}.ipp"
	OutputPath="${RootDir}/include/${OutputFile}"
	[[ ${InputFile} -nt ${OutputPath} ]] || continue
	echo "${InputName}" 1>&2
	(
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
		echo "	case GL_${GL_DEF}: return \"${GL_DEF}\";"
		echo "#endif"
	done
	echo "	default:;"
	echo "}"
	echo
	)

	git add ${OutputPath}
done

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
