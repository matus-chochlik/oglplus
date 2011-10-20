#!/bin/bash
# Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
# Software License, Version 1.0. (See accompanying file
# LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
gl3_h=${1:-$(locate gl3.h)}
Symbol=${2}
#
branch_stack=()
#
function push_branch()
{
	shift
	branch_stack=( "${branch_stack[@]}" "${*}" )
}
#
function pop_branch()
{
	if [ ${#branch_stack[*]} -gt 0 ]
	then unset branch_stack[${#branch_stack[@]}-1]
	fi
}
#
function get_branches()
{
	for b in ${branch_stack[@]}
	do
		case ${b} in
			GL_ARB*) echo ":$($0 ${gl3_h} ${b#GL_})";;
			GL_*) echo -n ":${b}";;
		esac
	done
}
#
function process_define()
{
	echo ${2}$(get_branches)
}
#
function process_function()
{
	echo ${4}$(get_branches)
}
#
function process_extension()
{
	echo GL_${Symbol}$(get_branches)
}
#
case ${Symbol} in
	ARB_*)
		cat "${gl3_h}" |
		while read line
		do
			case ${line} in
				"#if "*)    push_branch ${line};;
				"#ifdef"*)  push_branch ${line};;
				"#ifndef"*) push_branch ${line};;
				"#endif"*)  pop_branch;;
				"/* Reuse tokens from ${Symbol}"*) process_extension ${line};;
			esac
		done
	;;
	GL_*|gl*|*)
		cat "${gl3_h}" |
		while read line
		do
			case ${line} in
				"#if "*)    push_branch ${line};;
				"#ifdef"*)  push_branch ${line};;
				"#ifndef"*) push_branch ${line};;
				"#endif"*)  pop_branch;;
				"#define GL_${Symbol}"*) process_define ${line};;
				"GLAPI"*"APIENTRY gl${Symbol}"*) process_function ${line};;
			esac
		done
	;;
esac
