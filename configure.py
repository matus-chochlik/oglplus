#!/usr/bin/python
#  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
import os, sys, getopt, shutil, subprocess

# initial values for the configuration options
oglplus_quiet_config=False
oglplus_quick_config=False
oglplus_install_prefix = None
oglplus_build_dir = os.path.abspath("_build")
oglplus_include_dirs = list()
oglplus_library_dirs = list()
oglplus_from_scratch = False
oglplus_use_cxxflags = False
oglplus_use_ldflags = False
oglplus_forced_gl_header=None
oglplus_forced_gl_init_lib=None
oglplus_no_examples=False
oglplus_no_screenshots=True
oglplus_framedump=False
oglplus_no_docs=False


# returns the shortest path from the directory
# at source_path to the directory at target_path
def shortest_path_from_to(source_path, target_path):
	source_path = os.path.abspath(source_path)
	target_path = os.path.abspath(target_path)

	if source_path == target_path:
		return os.path.curdir

	common_prefix = os.path.commonprefix([
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


# prints short usage screen
def print_short_usage():
	print "Use 'configure --help' for a full list of options"

# print the long usage screen
def print_long_usage():
	print "Usage:"
	print "configure [options]"
	# TODO: use the text formatted by groff

# parses the command line arguments
def parse_cmd_line(argv):
	try:
		shortopts = "hqQP:B:I:L:"
		longopts = [
			"help",
			"quiet",
			"quick",
			"from-scratch",
			"prefix=",
			"build-dir=",
			"include-dir=",
			"library-dir=",
			"use-cxxflags",
			"use-ldflags",
			"use-glcorearb-h",
			"use-gl3-h",
			"use-glew",
			"use-gl3w",
			"use-wxgl",
			"no-examples",
			"screenshots",
			"framedump",
			"no-docs"
		]
		return getopt.getopt(argv, shortopts, longopts)
	except getopt.GetoptError:
		print_short_usage()
		sys.exit(1)


# processes the configure options
def process_options(opts):
	global oglplus_quick_config
	global oglplus_quiet_config
	global oglplus_install_prefix
	global oglplus_build_dir
	global oglplus_include_dirs
	global oglplus_library_dirs
	global oglplus_from_scratch
	global oglplus_use_cxxflags
	global oglplus_use_ldflags
	global oglplus_forced_gl_header
	global oglplus_forced_gl_init_lib

	for opt, arg in opts:
		if opt in ("--help", "-h"):
			print_long_usage()
			sys.exit(0)
		elif opt in ("--quiet", "-q"):
			oglplus_quiet_config=True
		elif opt in ("--quick", "-Q"):
			oglplus_quick_config=True
		elif opt in ("--prefix", "-P"):
			oglplus_install_prefix = os.path.abspath(arg)
		elif opt in ("--build-dir", "-B"):
			oglplus_build_dir = os.path.abspath(arg)
		elif opt in ("--include-dir", "-I"):
			oglplus_include_dirs.append(os.path.abspath(arg))
		elif opt in ("--library-dir", "-B"):
			oglplus_library_dirs.append(os.path.abspath(arg))
		elif opt in ("--use-cxxflags"):
			oglplus_use_cxxflags = True
		elif opt in ("--use-ldflags"):
			oglplus_use_ldflags = True
		elif opt in ("--from-scratch"):
			oglplus_from_scratch = True
		elif opt in ("--use-glcorearb-h"):
			oglplus_forced_gl_header="GLCOREARB_H"
		elif opt in ("--use-gl3-h"):
			oglplus_forced_gl_header="GL3_H"
		elif opt in ("--use-glew"):
			oglplus_forced_gl_header="GLEW"
		elif opt in ("--use-gl3w"):
			oglplus_forced_gl_header="GL3W"
		elif opt in ("--use-wxgl"):
			oglplus_forced_gl_init_lib="WXGL"
		elif opt in ("--no-examples"):
			oglplus_no_examples=True
		elif opt in ("--screenshots"):
			oglplus_no_screenshots=False
		elif opt in ("--framedump"):
			oglplus_framedump=True
		elif opt in ("--no-docs"):
			oglplus_no_docs=True


# applies CXXFLAGS to the options for cmake if possible
def apply_cxxflags():
	global oglplus_include_dirs
	try:
		import shlex

		flagiter = iter(shlex.split(os.environ.get("CXXFLAGS")))
		for flag in flagiter:
			if flag == "-I":
				oglplus_include_dirs.append(flagiter.next())
			elif flag.startswith("-I"):
				oglplus_include_dirs.append(flag[2:])
	except: pass


# applies LDFLAGS to the options for cmake if possible
def apply_ldflags():
	global oglplus_library_dirs
	try:
		import shlex

		flagiter = iter(shlex.split(os.environ.get("LDFLAGS")))
		for flag in flagiter:
			if flag == "-L":
				oglplus_library_dirs.append(flagiter.next())
			elif flag.startswith("-L"):
				oglplus_library_dirs.append(flag[2:])
	except: pass

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
		print "Failed to execute '%(cmd)s': %(error)s" % {
			"cmd": command,
			"error": os_error
		}
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
	global oglplus_quiet_config
	global oglplus_quick_config
	global oglplus_install_prefix
	global oglplus_build_dir
	global oglplus_include_dirs
	global oglplus_library_dirs
	global oglplus_from_scratch
	global oglplus_use_cxxflags
	global oglplus_use_ldflags
	global oglplus_forced_gl_header
	global oglplus_forced_gl_init_lib
	global oglplus_no_examples
	global oglplus_no_screenshots
	global oglplus_framedump
	global oglplus_no_docs

	# parse and process the options
	options, init_cmake_options = parse_cmd_line(argv)
	process_options(options)

	if oglplus_quiet_config:
		oglplus_quick_config = True
	# get the info from cmake if we are not in a hurry
	if not oglplus_quick_config:
		cmake_info = cmake_system_info(init_cmake_options)
	else: cmake_info = list()

	# apply the CXX and LD FLAGS if requested
	if(oglplus_use_cxxflags): apply_cxxflags()
	if(oglplus_use_ldflags): apply_ldflags()

	# additional options for cmake
	cmake_options = list()

	# add the installation prefix if provided
	if(oglplus_install_prefix):
		cmake_options.append(
			"-DCMAKE_INSTALL_PREFIX="+
			oglplus_install_prefix
		)

	# disable building the examples
	if(oglplus_no_examples):
		cmake_options.append("-DOGLPLUS_NO_EXAMPLES=On")

	# disable example screenshots in the docs
	if(oglplus_no_screenshots):
		cmake_options.append("-DOGLPLUS_NO_SCREENSHOTS=On")

	# use the framedump harness for examples
	if(oglplus_framedump):
		cmake_options.append("-DOGLPLUS_FRAMEDUMP=On")

	# disable building the docs
	if(oglplus_no_docs):
		cmake_options.append("-DOGLPLUS_NO_DOCS=On")

	# force the GL header to be used
	if(oglplus_forced_gl_header):
		cmake_options.append("-DOGLPLUS_FORCE_"+oglplus_forced_gl_header+"=On")

	# force the GL initialization library to be used
	if(oglplus_forced_gl_init_lib):
		cmake_options.append("-DOGLPLUS_FORCE_"+oglplus_forced_gl_init_lib+"=On")

	# add paths for header lookop
	if(oglplus_include_dirs):
		cmake_options.append("-DHEADER_SEARCH_PATHS="+";".join(oglplus_include_dirs))

	# add paths for library lookup
	if(oglplus_library_dirs):
		cmake_options.append("-DLIBRARY_SEARCH_PATHS="+";".join(oglplus_library_dirs))

	# remove the build dir if it was requested
	if(oglplus_from_scratch and os.path.exists(oglplus_build_dir)):
		shutil.rmtree(oglplus_build_dir)

	# create the build directory if necessary
	if(not os.path.isdir(oglplus_build_dir)):
		os.makedirs(oglplus_build_dir)

	# compose the command line for calling cmake
	workdir = os.path.abspath(os.path.dirname(sys.argv[0]))
	cmake_cmd_line = ["cmake"] + cmake_options + init_cmake_options + [workdir]

	# call cmake
	try: subprocess.call(cmake_cmd_line,cwd=oglplus_build_dir)
	# handle errors
	except OSError as os_error:
		print "# Configuration failed"
		print "# Failed to execute '%(cmd)s': %(error)s" % {
			"cmd": str(" ").join(cmake_cmd_line),
			"error": str(os_error)
		}
		sys.exit(3)

	# print some info if not supressed
	if not oglplus_quiet_config:
		print "# Configuration completed successfully."

		cmake_build_tool = cmake_info.get("CMAKE_BUILD_TOOL")
		if(cmake_build_tool):
			cmake_build_tool = shorten_command(cmake_build_tool)
			path_to_build_dir = shortest_path_from_to(os.getcwd(), oglplus_build_dir)

			if(cmake_build_tool == "make"):
				try:
					import multiprocessing
					processor_count = multiprocessing.cpu_count()
				except: processor_count = None
				print "# To build OGLplus do the following:"
				print
				print "cd "+ path_to_build_dir
				if processor_count:
					print "%(tool)s -j %(jobs)d" % {
						"tool": cmake_build_tool,
						"jobs": processor_count+1
					}
				else: print cmake_build_tool
				print cmake_build_tool + " install"

		cmake_install_prefix = cmake_info.get("CMAKE_INSTALL_PREFIX")
		if(cmake_install_prefix):
			if not oglplus_install_prefix:
				oglplus_install_prefix = cmake_install_prefix

			if not os.access(oglplus_install_prefix, os.W_OK):
				print
				print "# NOTE: installing to '%(prefix)s' "\
					"may require administrative privilegues" % {
						"prefix": oglplus_install_prefix
					}

# run the main function
if __name__ == "__main__": main(sys.argv[1:])
