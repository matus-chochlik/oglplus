#!/bin/bash
#  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# defaults
oglplus_default_build_dir=_build
oglplus_without_glew=false
oglplus_no_examples=false
oglplus_no_screenshots=true
oglplus_no_docs=false

dry_run=false
from_scratch=false
quiet=false
build_and_install=false
#
function echoerror()
{
	echo "$@" 1>&2
}
# function for filesystem path normalization
function normalize_path()
{
	local normal_path="${1}"

	# make an absolute path
	case "${normal_path}" in
		/*);;
		~*) normal_path="${HOME}${normal_path:1}";;
		*)  normal_path="${PWD%/}/${normal_path}";;
	esac
	# translates '/./' -> '/'
	normal_path="${normal_path//\/.\///\/}"

	# removes 'dir/../'
	while [[ "${normal_path}" =~ ([^/][^/]*/\.\./) ]]
	do normal_path="${normal_path/${BASH_REMATCH[0]}/}"
	done

	# removes '/dir/..' from the end of the path
	if [[ "${normal_path}" =~ (/[^/][^/]*/\.\.) ]]
	then normal_path="${normal_path/${BASH_REMATCH[0]}/}"
	fi

	# removes '/.' from the end of the path
	echo ${normal_path%/.}
}
#
# function that finds the shortest path from $1 to $2
function shortest_path_from_to()
{
	local source_path="$(normalize_path ${1})"
	local target_path="$(normalize_path ${2})"

	# if the paths are equal after normalization
	if [ "${source_path}" == "${target_path}" ]
	then echo "." && exit
	fi

	local common_part="${source_path}/"
	local backtr_part=

	while [ "${target_path#${common_part}}" == "${target_path}" ]
	do
		common_part="$(dirname ${common_part})"
		backtr_part="../${backtr_part}"
	done

	local result_path="${backtr_part%/}${target_path#${common_part}}"

	if [ ${#result_path} -gt ${#target_path} ]
	then echo ${target_path%/}
	else echo ${result_path%/}
	fi
}

oglplus_src_root="$(normalize_path "${PWD%/}/$(dirname ${0})")"
#
unset oglplus_prefix
unset oglplus_build_dir
unset oglplus_cmake_options
unset header_search_paths
unset library_search_paths
#
# prints a short help screen
function print_short_help()
{
	echo "Unknown option '${1}'"
	echo "Use $(basename ${0}) --help to print a help screen."
	return 0
}
#
# prints a full help screen
function print_help()
{
	echo "$(basename ${0}): OGLplus cmake configuration script"
	echo
	echo "Synopsis:"
	echo "$(basename ${0}) [config-options] [<-|--cmake> [cmake-options]]"
	echo
	echo "All options after '-' or '--cmake' are passed verbatim to cmake"
	echo
	echo "config-options:"
	echo
	echo "  --help | -h:           Print this help screen."
	echo
	echo "  --prefix PREFIX:       Specifies the installation prefix. The path"
	echo "                         must be absolute or relative to the current"
	echo "                         working directory from which configure is"
	echo "                         invoked."
	echo
	echo "  --build-dir PATH:      Specifies the work directory for cmake,"
	echo "                         where the cached files, generated makefiles"
	echo "                         and the intermediate build files will be"
	echo "                         placed (default = '${oblplus_default_build_dir}')."
	echo "                         The specified path must be either absolute"
	echo "                         or relative to the current working directory"
	echo "                         from which configure is invoked."
	echo
	echo "  --include-dir PATH:    Specifies additional directory to search"
	echo "                         when looking for external headers like"
	echo "                         GL/glew.h or GL3/gl3.h.  The specified path"
	echo "                         must be absolute or relative to the current"
	echo "                         working directory from which configure is"
	echo "                         invoked."
	echo "                         This option may be specified multiple times"
	echo "                         to add multiple directories to the search list."
	echo
	echo "  --library-dir PATH:    Specifies additional directory to search"
	echo "                         when looking for compiled libraries like"
	echo "                         GL, GLEW, glut, png, etc. The specified path"
	echo "                         must be absolute or relative to the current"
	echo "                         working directory from which configure is"
	echo "                         invoked."
	echo "                         This option may be specified multiple times"
	echo "                         to add multiple directories to the search list."
	echo
	echo "  --cmake | -:           Everything following this option will be"
	echo "                         passed to cmake verbatim."
	echo
	echo "  --dry-run              Only print the commands that would be executed"
	echo "                         without actually executing them."
	echo
	echo "  --from-scratch         Remove any previous cached and intermediate files"
	echo "                         and run the configuration process from scratch."
	echo
	echo "  --without-glew         Do not use GLEW even if it is available."
	echo "                         This option requires GL3/gl3.h installed somewhere"
	echo "                         in the system include directories or in directories"
	echo "                         specified with --include-dir."
	echo
	echo "  --no-examples          Do not build the examples and the textures."
	echo
	echo "  --screenshots          Also make example screenshots for the documentation."
	echo "                         This is still experimental and currently works only"
	echo "                         with GL3/gl3.h + GLX."
	echo
	echo "  --no-docs              Do not build and install the documentation."
	echo
	echo "  --quiet                Do not print regular messages, errors are still"
	echo "                         printed to stderr. Also any cmake output is still"
	echo "                         printed."
	echo
	echo "  --build-and-install    If the configuration process is successful, also"
	echo "                         run the commands to build and install OGLplus"
	echo "                         automatically."
	echo
	return 0
}
#
# parses a path-specifying command-line option
function parse_path_spec_option()
{
	local option_tag=${1}
	local option=${2}
	local next_option=${3}

	unset option_path

	case "${option}" in
	--${option_tag}=*)
		option_path="$(normalize_path "${option#--${option_tag}=}")"
		return 0;;

	--${option_tag})
		option_path="$(normalize_path "${next_option}")"
		return 1;;
	*) echoerror "Parse error" && exit 1
	esac
}

#
# parse the command line options
while true
do
	case "${1}" in
	"") break;;
	-|--cmake)
		shift
		for arg
		do oglplus_cmake_options="${oglplus_cmake_options} '${arg}'"
		done
		break;;

	--prefix*)
		parse_path_spec_option prefix "${1}" "${2}" || shift
		oglplus_prefix=${option_path}
		unset option_path;;

	--build-dir*)
		parse_path_spec_option build-dir "${1}" "${2}" || shift
		oglplus_build_dir=${option_path}
		unset option_path;;

	--include-dir*)
		parse_path_spec_option include-dir "${1}" "${2}" || shift
		header_search_paths="${header_search_paths}${option_path};"
		unset option_path;;

	--library-dir*)
		parse_path_spec_option library-dir "${1}" "${2}" || shift
		library_search_paths="${library_search_paths}${option_path};"
		unset option_path;;

	--without-glew) oglplus_without_glew=true;;

	--no-examples) oglplus_no_examples=true;;
	--screenshots) oglplus_no_screenshots=false;;
	--no-docs) oglplus_no_docs=true;;

	--dry-run) dry_run=true;;
	--from-scratch) from_scratch=true;;
	--quiet) quiet=true;;
	--build-and-install) build_and_install=true;;

	-h|--help) print_help && exit 0;;
	*) print_short_help ${1} && exit 1;;
	esac
	shift
done
#
# use the defaults for params that were not
# set explicitly
if [ "${oglplus_build_dir}" == "" ]
then oglplus_build_dir="${oglplus_default_build_dir}"
fi

#
# check for prerequisities
#
# the directories
for oglplus_dir in "config" "doc" "include/oglplus" "example" "source" "utils" "xslt"
do
	if [ ! -d "${oglplus_src_root}/${oglplus_dir}" ]
	then echoerror "Missing the header directory" && exit 4
	fi
done
#
# the cmake executable
if [ ! -x "$(which cmake)" ]
then echoerror "cmake is required." && exit 5
fi
#
# let cmake dump some system information into a temp file
# in a form usable by bash
cmake_info_file=$(mktemp)
cmake ${oglplus_cmake_options} --system-information |
grep -e "CMAKE_BUILD_TOOL" -e "CMAKE_INSTALL_PREFIX" |
tr ' ' '=' > ${cmake_info_file}
#
# use the system information
source ${cmake_info_file} || exit $?
# remove the system info file
rm -f ${cmake_info_file}
#
#
# check the main cmake script
if [ ! -f "${oglplus_src_root}/CMakeLists.txt" ]
then echoerror "Missing the main cmake script." && exit 5
fi
#
# check the build tool
if [ "${CMAKE_BUILD_TOOL}" == "" ]
then echoerror "No build tool usable by cmake found." && exit 5
fi
#
if [ ! -x "${CMAKE_BUILD_TOOL}" ]
then echoerror "${CMAKE_BUILD_TOOL} is required." && exit 5
fi
#
# shorten the build tool command if possible
if [ "$(which $(basename ${CMAKE_BUILD_TOOL}))" == "${CMAKE_BUILD_TOOL}" ]
then CMAKE_BUILD_TOOL="$(basename ${CMAKE_BUILD_TOOL})"
fi

# pass the no-examples option
if [ "${oglplus_no_examples}" == "true" ]
then oglplus_cmake_options="'-DOGLPLUS_NO_EXAMPLES=On' ${oglplus_cmake_options}"
fi

# pass the no-screenshots option
if [ "${oglplus_no_screenshots}" == "true" ]
then oglplus_cmake_options="'-DOGLPLUS_NO_SCREENSHOTS=On' ${oglplus_cmake_options}"
fi

# pass the no-docs option
if [ "${oglplus_no_docs}" == "true" ]
then oglplus_cmake_options="'-DOGLPLUS_NO_DOCS=On' ${oglplus_cmake_options}"
fi

# pass the without-glew option to cmake
if [ "${oglplus_without_glew}" == "true" ]
then oglplus_cmake_options="'-DOGLPLUS_WITHOUT_GLEW=On' ${oglplus_cmake_options}"
fi

# pass the list of paths to search for libraries to cmake
if [ "${library_search_paths}" != "" ]
then oglplus_cmake_options="'-DLIBRARY_SEARCH_PATHS=${library_search_paths%;}' ${oglplus_cmake_options}"
fi

# pass the list of paths to search for headers to cmake
if [ "${header_search_paths}" != "" ]
then oglplus_cmake_options="'-DHEADER_SEARCH_PATHS=${header_search_paths%;}' ${oglplus_cmake_options}"
fi

# pass the install prefix to cmake
if [ "${oglplus_prefix}" != "" ]
then oglplus_cmake_options="'-DCMAKE_INSTALL_PREFIX=${oglplus_prefix}' ${oglplus_cmake_options}"
fi

# temporary file where the commands to be executed are stored
command_file=$(mktemp)
# make the configuration commands
(
	exec > ${command_file}
	if [ "${from_scratch}" == "true" ]
	then echo "rm -rf '${oglplus_build_dir##${PWD%/}/}' &&"
	fi
	echo "mkdir -p '${oglplus_build_dir##${PWD%/}/}' &&"
	echo "cd '${oglplus_build_dir##${PWD%/}/}' &&"
	echo "cmake ${oglplus_cmake_options} $(shortest_path_from_to "${oglplus_build_dir}" "${oglplus_src_root}")"
	echo "configure_result=\$?"
	echo "cd '${PWD}'"
)

if [ "${dry_run}" == false ]
then source ${command_file}
else cat ${command_file}
fi

rm -f ${command_file}

if [ "${dry_run}" != false ]
then exit
fi

if [ ${configure_result:-0} -eq 0 ]
then
	build_script=$(mktemp)
	(
		echo
		echo "# Configuration completed successfully."
		echo "# To build OGLplus do the following:"
		echo
		echo "cd $(shortest_path_from_to "${PWD}" "${oglplus_build_dir}") &&"
		echo "${CMAKE_BUILD_TOOL} &&"
		echo "${CMAKE_BUILD_TOOL} install"
		echo
		echo "# NOTE: installing may require administrative privilegues"
	) > ${build_script}

	if [ "${build_and_install}" == "true" ]
	then (source ${build_script})
	elif [ "${quiet}" != "true" ]
	then cat ${build_script}
	fi
	rm -f "${build_script}"
else
	echoerror "# Configuration failed with error code ${configure_result}."
	exit ${configure_result}
fi

exit
