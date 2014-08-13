#!/usr/bin/python
# coding=utf-8
#  Copyright 2014 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
import os, sys

def print_newline(options):
	options.out.write(os.linesep)

def print_line(options, line_str):
	options.out.write(line_str)
	options.out.write(os.linesep)

def print_comment(options, cs, line_str = str()):
	print_line(options, "%s%s" % (cs, line_str))

def print_header(options, cs):

	print_comment(options, cs, "  File %s" % options.rel_output)
	print_comment(options, cs)
	print_comment(options, cs, "  Automatically generated file, DO NOT modify manually.")
	if options.rel_input:
		print_comment(options, cs, "  Edit the source '%s'" % options.rel_input)
		print_comment(options, cs, "  or the '%s' script instead." % options.rel_self)
	else:
		print_comment(options, cs, "  Edit the enumeration source files in 'source/enums/%s'" % options.library)
		print_comment(options, cs, "  or the '%s' script instead." % options.rel_self)
	print_comment(options, cs)
	print_comment(options, cs, "  Copyright 2010-%d Matus Chochlik." % options.year)
	print_comment(options, cs, "  Distributed under the Boost Software License, Version 1.0.")
	print_comment(options, cs, "  See accompanying file LICENSE_1_0.txt or copy at")
	print_comment(options, cs, "  http://www.boost.org/LICENSE_1_0.txt")
	print_comment(options, cs)

def print_cpp_header(options):
	print_header(options, "//")

def print_scr_header(options):
	print_header(options, "#")

def parse_source(options, input_file = None):

	if not input_file:
		input_file = options.input[0]

	result = list()

	attribs = ["src_name", "dst_name", "aq", "doc", "bind_query", "prefix"]

	with open(input_file, "r") as f:
		for line in f:
			line = line.strip()
			if line and not line.startswith("#"):
				values = line.split(":")
				av = dict(zip(attribs, values))

				if not av.get("dst_name"):
					tmp = av["src_name"].split("_")
					tmp = [x.capitalize() for x in tmp]
					av["dst_name"] = str().join(tmp)

				if not av.get("prefix"):
					av["prefix"] = options.base_lib_prefix

				result.append(type("Item", (object,), av))
	return result

def action_info(options):
	print("Input: %s" % options.input)
	print("Output: %s" % options.output)

def action_qbk_hpp(options):

	items = parse_source(options)

	print_cpp_header(options)
	print_line(options, "//[oglplus_enums_%s" % options.output_id)
	print_line(options, "namespace %s {" % options.library)
	print_newline(options)
	print_line(options, "enum class %s : %s%s" % (
		options.enum_name,
		options.base_lib_prefix,
		options.enum_type
	))
	print_line(options, "{")

	max_len = 0
	for item in items:
		max_len = max(max_len, len(item.dst_name))

	def print_item(options, item, term):
		fmt = "\t%s%"+str(max_len-len(item.dst_name)+3)+"s%s_%s%s"
		print_line(options, fmt % (
			item.dst_name,
			" = ",
			item.prefix,
			item.src_name,
			term
		))


	for item in items[:-1]:
		print_item(options, item, str(","))
	for item in items[-1:]:
		print_item(options, item, str(""))

	print_line(options, "};")
	print_newline(options)
	print_line(options, "template <>")
	print_line(options, "__Range<%s> __EnumValueRange<%s>(void);" % (
		options.enum_name,
		options.enum_name
	))
	print_newline(options)
	print_line(options, "__StrCRef __EnumValueName(%s);" % options.enum_name)
	print_newline(options)

	if options.enum_type == "bitfield":
		print_line(
			options,
			"__Bitfield<%s> operator | (%s b1, %s b2);" % (
				options.enum_name,
				options.enum_name,
				options.enum_name
			)
		)
		print_newline(options)
	print_line(options, "} // namespace %s" % options.library)
	print_line(options, "//]")

def action_smart_enums_ipp(options):

	enum_values = set()

	for input_file in options.input:
		items = parse_source(options, input_file)
		for item in items:
			enum_values.add(item.dst_name)

	print_cpp_header(options)
	for enum_value in sorted(enum_values):
		evp = (enum_value, enum_value)
		print_line(options, "struct %s {" % enum_value)
		print_line(options, "template <typename Enum, Enum = Enum::%s> operator Enum (void) const{ return Enum::%s; }" % evp)
		print_line(options, "template <typename Enum> friend bool operator==(Enum value, %s){ return value == Enum::%s; }" % evp)
		print_line(options, "template <typename Enum> friend bool operator!=(Enum value, %s){ return value != Enum::%s; }" % evp)
		print_line(options, "};")

def action_smart_enum_values_ipp(options):

	enum_values = set()

	for input_file in options.input:
		items = parse_source(options, input_file)
		for item in items:
			enum_values.add(item.dst_name)

	print_cpp_header(options)
	for enum_value in sorted(enum_values):
		evp = (enum_value, enum_value)
		print_line(options, "OGLPLUS_CONSTEXPR oglplus::smart_enums::%s %s;" % evp);

actions = {
	"info":    action_info,
	"qbk_hpp": action_qbk_hpp,
	"smart_enums_ipp": action_smart_enums_ipp,
	"smart_enum_values_ipp": action_smart_enum_values_ipp
}

multi_file_actions = ["smart_enums_ipp", "smart_enum_values_ipp"]

def dispatch_action(options):
	if not options.action in multi_file_actions:
		print(options)
		if len(options.input) < 1:
			msg = "Missing input file for action '%s'!" % options.action
			raise RuntimeError(msg)
		if len(options.input) > 1:
			msg = "Too many input files for action '%s'!" % options.action
			raise RuntimeError(msg)
	if not options.output_id:
		raise RuntimeError("No output-id was specified!")

	actions[options.action](options)


def get_argument_parser():
	import argparse, datetime, sys

	root_dir = os.path.join(
		os.path.pardir,
		os.path.pardir,
		os.path.dirname(sys.argv[0])
	)

	argparser = argparse.ArgumentParser(
		prog="make_enum",
		description="""
			Helper script for generating various enum related source files.
		""",
		epilog="""
			Copyright (c) 2014 - %(year)d Matúš Chochlík.
			Permission is granted to copy, distribute and/or modify this document
			under the terms of the Boost Software License, Version 1.0.
			(See a copy at http://www.boost.org/LICENSE_1_0.txt)
		""" % { "year": datetime.datetime.now().year }
	)

	argparser.add_argument(
		"--root-dir",
		type=os.path.abspath,
		default=root_dir,
		action="store",
		help=""" Path to the OGLplus root directory. """
	)

	argparser.add_argument(
		"--library",
		action="store",
		help=""" The all-lowercase library name. """
	)

	argparser.add_argument(
		"--base-lib-prefix",
		action="store",
		help=""" The base library prefix. """
	)

	argparser.add_argument(
		"inputs",
		metavar="FILE",
		type=os.path.abspath,
		nargs="*",
		help="""Path to the input text file(s) to be processed. """
	)

	argparser.add_argument(
		"--input",
		type=os.path.abspath,
		default=list(),
		action="append",
		help=""" Path to the input text file to be processed. """
	)

	argparser.add_argument(
		"--output-id",
		action="store",
		help=""" The output id string. """
	)

	argparser.add_argument(
		"--output",
		type=os.path.abspath,
		action="store",
		help=""" Path to the output file. """
	)

	def ValidAction(arg):
		if actions.get(arg) is None:
			msg = "'%s' is not a valid action name" % str(arg)
			raise argparse.ArgumentTypeError(msg)
		return arg

	argparser.add_argument(
		"--action",
		type=ValidAction,
		default="Info",
		action="store",
		help=""" The action to be executed. """
	)

	return argparser

def get_options():

	argparser = get_argument_parser()
	options = argparser.parse_args()

	options.input += options.inputs
	options.inputs = None

	options.root_dir = os.path.abspath(options.root_dir)
	options.rel_self = os.path.relpath(sys.argv[0], options.root_dir)

	if options.output is None:
		options.out = sys.stdout
		options.rel_output = "N/A"
	else:
		options.out = open(options.output, "wt")
		options.rel_output = os.path.relpath(options.output, options.root_dir)

	if len(options.input) == 1:
		options.rel_input = os.path.relpath(options.input[0], options.root_dir)

		options.enum_name = None
		options.enum_type = "enum"
		with open(options.input[0], "r") as f:
			for line in f:
				line = line.strip()
				if line.startswith("#@"):
					options.enum_type = line[2:-1]
					break
				elif line.startswith("#") and line.endswith("#"):
					options.enum_name = line[1:-1]
					break
		if not options.enum_name:
			tmp = os.path.splitext(os.path.basename(options.input[0]))[0]
			tmp = [x.capitalize() for x in tmp.split("_")]
			options.enum_name = str().join(tmp)

	else:
		options.rel_input = None

	import datetime
	options.year = datetime.datetime.now().year

	return options


def main():
	dispatch_action(get_options())


if __name__ == "__main__": main()

