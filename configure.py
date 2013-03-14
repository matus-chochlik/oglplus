#!/usr/bin/python
# coding=utf-8
#  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
import os, sys, getopt, shutil, subprocess

# initial values for the configuration options

def parse_arguments():
	import argparse
	import datetime

	def BoolArgValue(arg):
		if(arg in ("True", "true", "Yes", "yes", "Y", "On", "1")):
			return True
		elif(arg in ("False", "false", "No", "no", "N", "Off", "0")):
			return False
		else:
			msg = "'%s' is not a valid boolean value" % str(arg)
			raise argparse.ArgumentTypeError(msg)



	argparser = argparse.ArgumentParser(
		prog="configure",
		description="Configuration script for the OGLplus library",
		epilog="""
			Copyright (c) 2008 - %(year)d Matúš Chochlík.
			Permission is granted to copy, distribute and/or modify this document
			under the terms of the Boost Software License, Version 1.0.
			(See a copy at http://www.boost.org/LICENSE_1_0.txt)
		""" % {"year": datetime.datetime.now().year}
	)
	argparser.add_argument(
		"--prefix",
		dest="install_prefix",
		type=os.path.abspath,
		action="store",
		help="""
			Specifies the installation prefix. The path must be absolute or
			relative to the current working directory from which %(prog)s is
			invoked.
		"""
	)
	argparser.add_argument(
		"--build-dir",
		type=os.path.abspath,
		default="_build",
		action="store",
		help="""
			Specifies the work directory for cmake, where the cached files,
			generated makefiles and the intermediate build files will be
			placed. The specified path must be either absolute or
			relative to the current working directory from which %(prog)s
			is invoked (default = '%(default)s').
		"""
	)
	argparser.add_argument(
		"--include-dir", "-I",
		dest="include_dirs",
		type=os.path.abspath,
		action="append",
		default=list(),
		help="""
			Specifies additional directory to search when looking for external
			headers like GL/glew.h or GL3/gl3.h. The specified path
			must be absolute or relative to the current working directory
			from which %(prog)s is invoked. This option may be specified
			multiple times to add multiple directories to the search list.
		"""
	)
	argparser.add_argument(
		"--library-dir", "-L",
		dest="library_dirs",
		type=os.path.abspath,
		action="append",
		default=list(),
		help="""
			Specifies additional directory to search when looking for compiled
			libraries like GL, GLEW, glut, png, etc. The specified
			path must be absolute or relative to the current working directory
			from which configure is invoked. This option may be specified
			multiple times to add multiple directories to the search list.
		"""
	)
	argparser.add_argument(
		"--use-cxxflags",
		default=False,
		action="store_true",
		help="""
			Uses the directories specified by the -I options
			in CXXFLAGS (if available) and adds them
			to the values specified by --include-dir.
		"""
	)
	argparser.add_argument(
		"--use-ldflags",
		default=False,
		action="store_true",
		help="""
			Uses the directories specified by the -L options
			in LDFLAGS (if available) and adds them
			to the values specified by --library-dir.
		"""
	)
	argparser.add_argument(
		"--low-profile",
		dest="low_profile",
		type=BoolArgValue,
		choices=[True, False],
		action="store",
		default=None,
		help="""
			Enables or disables the low profile mode (see the documentation
			for the OGLPLUS_LOW_PROFILE compile-time switch).
			If this option is used, then the specified value is written to
			the oglplus/site_config.hpp file, otherwise it is set to the default
			value in oglplus/config.hpp and may be overriden in sources by
			defining this preprocessor symbol or by using the appropriate
			compiler command-line switch or build environment setting.
		"""
	)
	argparser_build_examples_group = argparser.add_mutually_exclusive_group()
	argparser_build_examples_group.add_argument(
		"--build-examples",
		dest="build_examples",
		type=BoolArgValue,
		choices=[True, False],
		action="store",
		default=True,
		help="""
			Determines whether the examples should be built (default = %(default)s).
		"""
	)
	argparser_build_examples_group.add_argument(
		"--no-examples",
		dest="build_examples",
		action="store_false",
		help="""
			Do not build the examples and the textures.
			Equivalent to --build-examples=False.
		"""
	)
	argparser_build_docs_group = argparser.add_mutually_exclusive_group()
	argparser_build_docs_group.add_argument(
		"--build-docs",
		dest="build_docs",
		type=BoolArgValue,
		choices=[True, False],
		action="store",
		default=True,
		help="""
			Determines whether the documentation should be built (default = %(default)s).
		"""
	)
	argparser_build_docs_group.add_argument(
		"--no-docs",
		dest="build_docs",
		action="store_false",
		help="""
			Do not build the documentation.
			Equivalent to --build-docs=False.
		"""
	)
	argparser_make_screenshots_group = argparser.add_mutually_exclusive_group()
	argparser_make_screenshots_group.add_argument(
		"--make-screenshots",
		dest="make_screenshots",
		type=BoolArgValue,
		choices=[True, False],
		action="store",
		default=False,
		help="""
			Determines whether screenshots from OGLplus examples should be
			made when building the documentation (default = %(default)s).
		"""
	)
	argparser_make_screenshots_group.add_argument(
		"--screenshots",
		dest="make_screenshots",
		action="store_true",
		help="""
			Equivalent to --make-screenshots=True.
		"""
	)
	argparser_gl_header_lib_group = argparser.add_mutually_exclusive_group()
	argparser_gl_header_lib_group.add_argument(
		"--use-gl-header-lib",
		dest="gl_header_lib",
		type=str,
		choices=["GLCOREARB_H", "GL3_H", "GLEW", "GL3W"],
		action="store",
		default=None,
		help="""
			Forces the use of a specific header or library which
			defines the GL symbols.
		"""
	)
	argparser_gl_header_lib_group.add_argument(
		"--use-glcorearb-h",
		dest="gl_header_lib",
		action="store_const",
		const="GLCOREARB_H",
		help="""
			Force use of the GL/glcorearb.h header. If this option is used,
			then this header must be installed somewhere in the system
			include directories or in directories specified with --include-dir.
			Equivalent to --use-gl-header-lib=GLCOREARB_H.
		"""
	)
	argparser_gl_header_lib_group.add_argument(
		"--use-gl3-h",
		dest="gl_header_lib",
		action="store_const",
		const="GL3_H",
		help="""
			Force use of the GL3/gl3.h header. If this option is used,
			then this header must be installed somewhere in the system
			include directories or in directories specified with --include-dir.
			Equivalent to --use-gl-header-lib=GL3_H.
		"""
	)
	argparser_gl_header_lib_group.add_argument(
		"--use-glew",
		dest="gl_header_lib",
		action="store_const",
		const="GLEW",
		help="""
			Force use of the GLEW library. If this option is used, then GLEW
			and the GL/glew.h header must be installed somewhere in the system
			include directories or in directories specified with
			--include-dir.
			Equivalent to --use-gl-header-lib=GLEW.
		"""
	)
	argparser_gl_header_lib_group.add_argument(
		"--use-gl3w",
		dest="gl_header_lib",
		action="store_const",
		const="GL3W",
		help="""
			Force use of the GL3W library. If this option is used, then GL3W
			and the GL/gl3w.h header must be installed somewhere in the system
			include directories or in directories specified with
			--include-dir.
			Equivalent to --use-gl-header-lib=GL3W.
		"""
	)
	argparser_gl_window_lib_group = argparser.add_mutually_exclusive_group()
	argparser_gl_window_lib_group.add_argument(
		"--use-gl-window-lib",
		dest="gl_window_lib",
		type=str,
		choices=["GLUT", "GLFW", "WXGL", "SDL", "GLX"],
		action="store",
		default=None,
		help="""
			Forces the use of a specific window library which
			initializes the default GL context. This option allows
			to force a specific example 'harness'.
		"""
	)
	argparser_gl_window_lib_group.add_argument(
		"--use-glut",
		dest="gl_window_lib",
		action="store_const",
		const="GLUT",
		help="""
			Equivalent to --use-gl-window-lib=GLUT.
		"""
	)
	argparser_gl_window_lib_group.add_argument(
		"--use-glfw",
		dest="gl_window_lib",
		action="store_const",
		const="GLFW",
		help="""
			Equivalent to --use-gl-window-lib=GLFW.
		"""
	)
	argparser_gl_window_lib_group.add_argument(
		"--use-wxgl",
		dest="gl_window_lib",
		action="store_const",
		const="WXGL",
		help="""
			Equivalent to --use-gl-window-lib=WXGL.
		"""
	)
	argparser_gl_window_lib_group.add_argument(
		"--use-sdl",
		dest="gl_window_lib",
		action="store_const",
		const="SDL",
		help="""
			Equivalent to --use-gl-window-lib=SDL.
		"""
	)
	argparser_gl_window_lib_group.add_argument(
		"--use-glx",
		dest="gl_window_lib",
		action="store_const",
		const="GLX",
		help="""
			Equivalent to --use-gl-window-lib=GLX.
		"""
	)

	argparser.add_argument(
		"--from-scratch",
		default=False,
		action="store_true",
		help="""
			Remove any previous cached and intermediate files and run the
			configuration process from scratch.
			Specifying this option causes the build directory to be deleted
			and recreated.
		"""
	)
	argparser.add_argument(
		"--quiet",
		default=False,
		action="store_true",
		help="""
			Do not print regular messages, errors are still printed to
			stderr. Also any cmake output is still printed.
		"""
	)
	argparser.add_argument(
		"--quick",
		default=False,
		action="store_true",
		help="""
			Skips some optional steps in the configuration process.
		"""
	)
	argparser.add_argument(
		"--build",
		default=False,
		action="store_true",
		help="""
			If possible, after running cmake also invoke the build tool
			and build the project. This is currently supported only
			for certain build tools.
		"""
	)
	argparser.add_argument(
		"--with-tests",
		default=False,
		action="store_true",
		help="""
			Configure the testsuite.
		"""
	)
	argparser.add_argument(
		"--cmake",
		dest="cmake_options",
		nargs=argparse.REMAINDER,
		default=list(),
		help="""Everything following this option will be passed to cmake verbatim."""
	)

	return argparser.parse_args()

# returns the common valid prefix for the specified paths
def common_path_prefix(paths):
	prefix = os.path.commonprefix(paths)
	for path in paths:
		if prefix != path:
			suffix = path[len(prefix):]
			if not suffix.startswith(os.path.sep):
				return op.path.dirname(prefix)
	return prefix


# returns the shortest path from the directory
# at source_path to the directory at target_path
def shortest_path_from_to(source_path, target_path):
	source_path = os.path.abspath(source_path)
	target_path = os.path.abspath(target_path)

	if source_path == target_path:
		return os.path.curdir

	common_prefix = common_path_prefix([
		source_path,
		target_path
	])
	backtrace = os.path.curdir
	while source_path != common_prefix:
		source_path = os.path.dirname(source_path)
		backtrace = os.path.join(os.path.pardir, backtrace)
	backtrace = os.path.normpath(backtrace)

	relative_path = target_path[len(common_prefix):]
	if relative_path.startswith(os.path.sep):
		relative_path = relative_path[len(os.path.sep):]
	relative_path = os.path.normpath(os.path.join(
		backtrace,
		relative_path
	))
	if len(relative_path) < len(target_path):
		return relative_path
	else: return target_path

# shortens a full command path to a command name only
# if possible
def shorten_command(command_path):
	def is_exe(filepath):
		return os.path.isfile(filepath) and os.access(filepath, os.X_OK)

	command_dir, command = os.path.split(command_path)

	for path_dir in os.environ["PATH"].split(os.pathsep):
		if command_dir == path_dir and is_exe(command_path):
			return command
	return command_path


# applies CXXFLAGS to the options for cmake if possible
def search_cxxflags():
	cxxflags_include_dirs = list()
	try:
		import shlex

		flagiter = iter(shlex.split(os.environ.get("CXXFLAGS")))
		for flag in flagiter:
			if flag == "-I":
				cxxflags_include_dirs.append(flagiter.next())
			elif flag.startswith("-I"):
				cxxflags_include_dirs.append(flag[2:])
	except: pass
	return cxxflags_include_dirs


# applies LDFLAGS to the options for cmake if possible
def search_ldflags():
	ldflags_library_dirs = list()
	try:
		import shlex

		flagiter = iter(shlex.split(os.environ.get("LDFLAGS")))
		for flag in flagiter:
			if flag == "-L":
				ldflags_library_dirs.append(flagiter.next())
			elif flag.startswith("-L"):
				ldflags_library_dirs.append(flag[2:])
	except: pass
	return ldflags_library_dirs

# get some useful information from cmake
def cmake_system_info(cmake_args):
	command = ["cmake", "--system-information"] + cmake_args
	try:
		proc = subprocess.Popen(
			command,
			stdin=None,
			stdout=subprocess.PIPE,
			stderr=None
		)
	except OSError as os_error:
		print("Failed to execute '%(cmd)s': %(error)s" % {
			"cmd": command,
			"error": os_error
		})
		sys.exit(2)

	result = dict()

	try:
		import shlex
		for line in proc.stdout.readlines():
			try:
				words = shlex.split(line)
				if(words[0] in (
					"CMAKE_BUILD_TOOL",
					"CMAKE_INSTALL_PREFIX"
				)): result[words[0]] = words[1]
			except ValueError:
				pass
			except IndexError:
				pass
	except: pass

	return result

# the main function
def main(argv):

	# parse and process the command-line arguments
	options = parse_arguments()

	# if we are in quiet mode we may also go to quick mode
	if options.quiet: options.quick = True

	# if we also want to build the project disable quick mode
	if options.build: options.quick = False

	# get the info from cmake if we are not in a hurry
	if not options.quick:
		cmake_info = cmake_system_info(options.cmake_options)
	else: cmake_info = list()

	# search the CXX and LD FLAGS if requested
	if(options.use_cxxflags): options.include_dirs += search_cxxflags()
	if(options.use_ldflags):  options.library_dirs += search_ldflags()

	# additional options for cmake
	cmake_options = list()

	# add the installation prefix if provided
	if(options.install_prefix):
		cmake_options.append(
			"-DCMAKE_INSTALL_PREFIX="+
			options.install_prefix
		)

	# set the low profile mode switch
	if(options.low_profile is not None):
		cmake_options.append("-DOGLPLUS_CONFIG_SET_LOW_PROFILE=On")
		if(options.low_profile):
			cmake_options.append("-DOGLPLUS_LOW_PROFILE=On")
		else:
			cmake_options.append("-DOGLPLUS_LOW_PROFILE=Off")

	# disable building the examples
	if(not options.build_examples):
		cmake_options.append("-DOGLPLUS_NO_EXAMPLES=On")

	# disable example screenshots in the docs
	if(not options.make_screenshots):
		cmake_options.append("-DOGLPLUS_NO_SCREENSHOTS=On")

	# disable building the docs
	if(not options.build_docs):
		cmake_options.append("-DOGLPLUS_NO_DOCS=On")

	# force the GL header to be used
	if(options.gl_header_lib):
		cmake_options.append("-DOGLPLUS_FORCE_"+options.gl_header_lib+"=On")

	# force the GL initialization library to be used
	if(options.gl_window_lib):
		cmake_options.append("-DOGLPLUS_FORCE_"+options.gl_window_lib+"=On")

	# add paths for header lookop
	if(options.include_dirs):
		cmake_options.append("-DHEADER_SEARCH_PATHS="+";".join(options.include_dirs))

	# add paths for library lookup
	if(options.library_dirs):
		cmake_options.append("-DLIBRARY_SEARCH_PATHS="+";".join(options.library_dirs))

	# remove the build dir if it was requested
	if(options.from_scratch and os.path.exists(options.build_dir)):
		shutil.rmtree(options.build_dir)

	# configure the test suite
	if(options.with_tests):
		cmake_options.append("-DOGLPLUS_WITH_TESTS=On")

	# create the build directory if necessary
	if(not os.path.isdir(options.build_dir)):
		os.makedirs(options.build_dir)

	# compose the command line for calling cmake
	workdir = os.path.abspath(os.path.dirname(sys.argv[0]))
	cmake_cmd_line = ["cmake"] + cmake_options + options.cmake_options + [workdir]

	# call cmake
	try: subprocess.call(cmake_cmd_line,cwd=options.build_dir)
	# handle errors
	except OSError as os_error:
		print( "# Configuration failed")
		print("# Failed to execute '%(cmd)s': %(error)s" % {
			"cmd": str(" ").join(cmake_cmd_line),
			"error": str(os_error)
		})
		sys.exit(3)

	# try to get the processor count (use below)
	try:
		import multiprocessing
		processor_count = multiprocessing.cpu_count()
	except: processor_count = None

	# print some info if not supressed
	if not options.quiet:
		print("# Configuration completed successfully.")

		cmake_build_tool = cmake_info.get("CMAKE_BUILD_TOOL")
		if(cmake_build_tool):
			cmake_build_tool = shorten_command(cmake_build_tool)
			path_to_build_dir = shortest_path_from_to(os.getcwd(), options.build_dir)

			if(not options.build):
				if(cmake_build_tool == "make"):
					print("# To build OGLplus do the following:")
					print(str())
					print("cd "+ path_to_build_dir)
					if processor_count:
						print("%(tool)s -j %(jobs)d" % {
							"tool": cmake_build_tool,
							"jobs": processor_count+1
						})
					else: print(cmake_build_tool)
					print(cmake_build_tool + " install")

	# if the user requested build after config is done
	if options.build:
		cmake_build_tool = cmake_info.get("CMAKE_BUILD_TOOL")

		if cmake_build_tool:
			build_tool_name = os.path.basename(cmake_build_tool)
		else:
			build_tool_name = str()

		if build_tool_name in ("make",):
			build_cmd_line = [cmake_build_tool];
			if processor_count:
				build_cmd_line += ["-j", str(processor_count+1)]
		elif build_tool_name in ("devenv.com", "devenv.exe"):
			build_cmd_line = [
				cmake_build_tool,
				os.path.join(options.build_dir, "OGLplus.sln"),
				"/Build",
				"Release"
			]
		else: build_cmd_line = None

		if build_cmd_line:
			try: subprocess.call(build_cmd_line,cwd=options.build_dir)
			except OSError as os_error:
				print( "# Build failed")
				print("# Failed to execute '%(cmd)s': %(error)s" % {
					"cmd": str(" ").join(build_cmd_line),
					"error": str(os_error)
				})
				sys.exit(4)
		else: print("# --build is not supported with the current build tool")


	# print additional info if not supressed
	if not options.quiet:

		if not options.install_prefix:
			options.install_prefix = cmake_info.get("CMAKE_INSTALL_PREFIX")

		if(options.install_prefix):

			if not os.access(options.install_prefix, os.W_OK):
				print(str())
				print("# NOTE: installing to '%(prefix)s' "\
					"may require administrative privilegues" % {
						"prefix": options.install_prefix
					}
				)

# run the main function
if __name__ == "__main__": main(sys.argv[1:])
