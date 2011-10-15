#!/bin/bash
# Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
# Software License, Version 1.0. (See accompanying file
# LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
glewpath=${1}
rootdir=${2:-${PWD}}
#
Exts="\(ARB\|EXT\|INTEL\|AMD\|ATI\|NV\|NVIDIA\|GLX\|SGI\|SGIX\|HP\|3Dlabs\|IBM\|PGI\|MS\|SUN\|Mesa\|3Dfx\|S3\)"
#
# get the OpenGL functions that OGLplus is using
# in its headers
$(dirname $0)/_get_ogl_funs.sh ${rootdir} |
while read Function
do
	# whether we found the Function we are looking for
	foundfun=0
	# whether we found an extension alternative for Function
	foundalt=0
	# filter glew header, try to find Function
	sed -n \
		-e "s/^\s*#define\s\+\(\<gl${Function}${Exts}\?\>\).*$/\1/p;"\
		-e "s/.*GLAPIENTRY\s\+\(\<gl${Function}\>\).*$/\1/p;"\
		${glewpath} |
	while read AltFunction
	do
		# if we found the same function
		if [ "gl${Function}" == "${AltFunction}" ]
		then foundfun=1
		# if we found an alternative extenstion
		else
			if [ ${foundfun} -eq 0 -a ${foundalt} -eq 0 ]
			then
				foundalt=1
				echo "#define gl${Function} ${AltFunction}"
			fi
		fi
	done
done
#
# get the OpenGL constants that OGLplus is using
# in its headers
$(dirname $0)/_get_ogl_defs.sh ${rootdir} |
while read Define
do
	# whether we found the Define we are looking for
	founddef=0
	# whether we found an extension alternative for Define
	foundalt=0
	# filter glew header, try to find Define
	sed -n \
		-e "s/^\s*#define\s\+\(\<GL_${Define}\(_${Exts}\)\?\>\).*$/\1/p;"\
		${glewpath} |
	while read AltDefine
	do
		# if we found the same define
		if [ "GL_${Define}" == "${AltDefine}" ]
		then founddef=1
		# if we found an alternative extenstion
		else
			if [ ${founddef} -eq 0 -a ${foundalt} -eq 0 ]
			then
				foundalt=1
				echo "#define GL_${Define} ${AltDefine}"
			fi
		fi
	done
done
