#!/bin/bash
#  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
oglplus_src_root="$(dirname ${0})"
# the installation prefix
oglplus_prefix="/usr/local"
#
# prints a short help screen
function print_short_help()
{
	echo "Unknown option '${1}'"
	echo "Use install.sh --help to print a help screen."
	return 0
}
#
# prints a full help screen
function print_help()
{
	echo "install.sh: OGLplus installation script"
	echo "Command line options:"
	echo
	echo "  --help | -h:     Print this help screen"
	echo
	echo "  --prefix PREFIX: Set the installation prefix [${oglplus_prefix}]"
	echo
	return 0
}
#
# check the installation prefix
function prefix_ok()
{
	local prefix="${1}/${2}"
	if [ ! -d "${prefix}" ]
	then
		mkdir -p "${prefix}"
		if [ "$?" -ne "0" ]
		then
			echo "Cannot create directory '${prefix}'"
			return 1
		fi
	fi

	if [ ! -w "${prefix}" ]
	then
		echo "Directory '${prefix}' is not writable."
		return 1
	fi
	if [ "${2}" == "" ]
	then
		prefix_ok "${1}" include
	fi
	return 0
}
#
# parse the command line options
while true
do
	case "${1}" in
	"") break;;
	--prefix=~*) oglplus_prefix="${HOME}${1##--prefix=~}";;
	--prefix=*) oglplus_prefix="${1##--prefix=}";;
	--prefix) shift && oglplus_prefix="${1}";;
	-h|--help) print_help && exit 0;;
	*) print_short_help && exit 1;;
	esac
	shift
done

#
# check for prerequisities
#
# the prefix
prefix_ok "${oglplus_prefix}" || exit 2
#
# the Makefile
if [ ! -f "${oglplus_src_root}/Makefile" ]
then echo "Missing Makefile" && exit 3
fi
#
# the include directory
if [ ! -d "${oglplus_src_root}/include/oglplus" ]
then echo "Missing the header directory" && exit 4
fi
#
# try to make the automatically generated headers
make auto_headers
#
# the auto-generated header directory
if [ ! -d "${oglplus_src_root}/auto_header/include/oglplus" ]
then echo "Missing the auto-generated header directory" && exit 5
fi
#
# do the actuall installation
cp -R "${oglplus_src_root}/include/oglplus" "${oglplus_prefix}/include/" &&
cp -R "${oglplus_src_root}/auto_header/include/oglplus" "${oglplus_prefix}/include/"
#
# print the result
if [ "$?" -eq "0" ]
then echo "Installation completed successfully" && exit 0
else echo "Installation failed" && exit 1
fi
