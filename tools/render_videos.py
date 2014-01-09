#!/usr/bin/python
# coding=utf-8
# Copyright 2014 Matus Chochlik. Distributed under the Boost
# Software License, Version 1.0. (See accompanying file
# LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
import os, sys

class FallbackUI:
	def __init__(self, title, work_dir, options):
		self.title = title
		self.work_dir = work_dir

	class SimpleProgress:
		def __init__(self, title): sys.stdout.write(title+" ... ")
		def __enter__(self): return self
		def __exit__(self, type, value, traceback):
			sys.stdout.write("Done\n")

	def simple_action(self, title):
		return FallbackUI.SimpleProgress(title)

	class FramedumpProgress:
		def __init__(self, title): print(title)
		def __enter__(self): return self
		def __exit__(self, type, value, traceback):
			print("Done")

		def update(self, frame_no, frame_path):
			print("Rendered frame: %d"%frame_no)

	def framedump(self, title):
		return FallbackUI.FramedumpProgress(title)

	class VideoEncProgress:
		def __init__(self, title): print(title)
		def __enter__(self): return self
		def __exit__(self, type, value, traceback):
			print("Done")

		def update(self, message):
			print(message)

	def videoenc(self, title):
		return FallbackUI.VideoEncProgress(title)



def create_ui(sample_label, work_dir, options):
	return FallbackUI(sample_label, work_dir, options)

def remove_dir(work_dir):
	from shutil import rmtree
	rmtree(work_dir)

def make_work_dir():
	from tempfile import mkdtemp
	return mkdtemp()

def parse_args(args):
	import argparse
	import datetime

	def FrameDimType(arg):

		try: dims = [int(dim) for dim in arg.split('x')]
		except: dims = list()

		def valid_coord(dim):
			return isinstance(dim, int) and dim > 0

		if (len(dims) == 2) and all(valid_coord(dim) for dim in dims):
			return dims
		else:
			msg = "'%s' is not a valid frame dimension specification" % str(arg)
			raise argparse.ArgumentTypeError(msg)


	argparser = argparse.ArgumentParser(
		prog=os.path.basename(args[0]),
		description="""Script for rendering videos from OGLplus examples""",
		epilog="""
			Copyright (c) 2008 - %(year)d Matúš Chochlík.
			Permission is granted to copy, distribute and/or modify this document
			under the terms of the Boost Software License, Version 1.0.
			(See a copy at http://www.boost.org/LICENSE_1_0.txt)
		""" % { "year": datetime.datetime.now().year }
	)

	argparser.add_argument(
		"--build-dir",
		help="""The name of the build directory""",
		default="_build",
		action="store",
		dest="build_dir"
	)

	argparser.add_argument(
		"--size",
		help="""
			The dimensions in pixels of the video frame,
			specified as WxH where W and H are positive integers.
		""",
		type=FrameDimType,
		dest="frame_size",
		action="store",
		default="852x480"
	)

	argparser.add_argument(
		"--hd",
		help="""Sets the dimensions of the output to 1280x720.""",
		dest="frame_size",
		action="store_const",
		const=[1280,720]
	)

	argparser.add_argument(
		"examples",
		help="""
		List of examples to render.
		The examples should be specified as paths to the example executables
		relative to the build directory.
		""",
		nargs="*"
	)

	return argparser.parse_args()

# checks if we have everything we need to run the example
def check_example(root_dir, example):

	if not os.path.isdir(root_dir):
		msg = "Could not find directory '%s'." % root_dir
		raise Exception(msg)

	example_path = os.path.join(root_dir, example)

	if not os.path.isfile(example_path) or not os.access(example_path, os.X_OK):
		msg = "Could not find example '%s'." % example
		raise Exception(msg)

	return example_path


# runs imagemagick convert
def run_convert(work_dir, args):
	import subprocess

	cmd_line = ['convert'] + args

	ret = subprocess.call(cmd_line,cwd=work_dir)
	if ret < 0:
		raise RuntimeError("Convert killed by signal %d" % -ret)
	elif ret > 0:
		raise RuntimeError("Convert failed with code %d" % ret)

# runs the example, dumps the frames, renders the video
def render_video(
	sample_id,
	example_path,
	work_dir,
	main_label_file,
	sample_label_file,
	logo_file,
	width,
	height,
	ui
):

	prefix = os.path.join(work_dir, 'frame')

	import subprocess
	try:
		cmd_line = [example_path,
			'--frame-dump', '%s-'%prefix,
			'--width', str(width),
			'--height', str(height)
		]
		proc = subprocess.Popen(
			cmd_line,
			stdin=subprocess.PIPE,
			stdout=subprocess.PIPE,
			stderr=None
		)
		proc.stdin.write('%s-\n'%prefix)


		with ui.framedump('Rendering frames') as progress:
			frame_no = 0
			prev_frame_path_pic = str()
			while True:
				frame_path_raw = proc.stdout.readline()
				if not frame_path_raw:
					break
				proc.stdin.write(frame_path_raw)

				frame_path_raw = frame_path_raw.translate(None, '\r\n');
				frame_path_pic = frame_path_raw.replace('.rgba', '.jpeg')

				try:
					run_convert(work_dir, [
						'-size', '%dx%d'%(width, height),
						'-depth', '8',
						frame_path_raw,
						'-flip',
						'-alpha', 'Off',
						'-gravity', 'SouthEast',
						main_label_file,
						'-composite',
						'-gravity', 'SouthEast',
						sample_label_file,
						'-composite',
						'-gravity', 'SouthEast',
						logo_file,
						'-composite',
						'-quality', '100',
						frame_path_pic
					])
				except RuntimeError:
					import shutil
					shutil.copy2(prev_frame_path_pic, frame_path_pic)

				prev_frame_path_pic = frame_path_pic

				progress.update(frame_no, frame_path_pic)
				frame_no += 1
	except OSError as os_error:
		print("Failed to execute '%(cmd)s': %(error)s" % {
			"cmd": str(' ').join(cmd_line),
			"error": os_error
		})
		sys.exit(1)


	try:
		cmd_line = ['avconv',
			'-loglevel', 'info',
			'-y', '-f', 'image2',
			'-i', prefix+'-%06d.jpeg',
			'-r', '25',
			'-vcodec', 'mpeg4',
			'-b', '8000k',
			prefix+'.avi'
		]
		proc = subprocess.Popen(
			cmd_line,
			stdin=None,
			stdout=subprocess.PIPE,
			stderr=None
		)
		with ui.videoenc('Encoding video') as progress:
			while True:
				message = proc.stdout.readline().translate(None, '\r\n')
				if not frame_path_raw:
					break
				progress.update(message)

   	except OSError as os_error:
		print("Failed to execute '%(cmd)s': %(error)s" % {
			"cmd": str(' ').join(cmd_line),
			"error": os_error
		})
		sys.exit(2)

	os.rename(prefix+'.avi', 'oglplus-'+sample_id+'.avi')



# renders a video for a single example
def render_example(root_dir, example, options):

	work_dir = make_work_dir()
	build_dir = os.path.join(root_dir, options.build_dir)

	example_path = check_example(build_dir, example)

	main_label = "http://oglplus.org/"
	sample_label = os.path.basename(example)

	main_label_file = os.path.join(work_dir, 'main_label.png')
	sample_label_file = os.path.join(work_dir, 'sample_label.png')
	logo_file = os.path.join(work_dir, 'logo.png')

	width = options.frame_size[0]
	height= options.frame_size[1]

	ui = create_ui(sample_label, work_dir, options)


	# render the main text label
	with ui.simple_action('Rendering main label') as progress:
		run_convert(work_dir, [
			'-size', '%dx28'%(width/2), 'xc:none',
			'-background', 'none',
			'-pointsize', '28',
			'-gravity', 'center',
			'-stroke', 'black',
			'-strokewidth', '8',
			'-annotate', '0', main_label,
			'-blur', '0x4',
			'-shadow', '%dx7+2+2'%width,
			'+repage',
			'-stroke', 'none',
			'-strokewidth', '1',
			'-fill', 'white',
			'-annotate', '0', main_label,
			main_label_file
		])

	# render the example name label
	with ui.simple_action('Rendering example label') as progress:
		run_convert(work_dir, [
			'-size', '%dx90'%(width/3+len(sample_label)*4), 'xc:none',
			'-background', 'none',
			'-pointsize', '16',
			'-gravity', 'center',
			'-stroke', 'black',
			'-strokewidth', '2',
			'-annotate', '0', sample_label,
			'-blur', '0x4',
			'-shadow', '%dx4+1+1'%(width/4),
			'+repage',
			'-stroke', 'none',
			'-strokewidth', '1',
			'-fill', 'white',
			'-annotate', '0', sample_label,
			sample_label_file
		])

	# render the logo
	with ui.simple_action('Rendering logo') as progress:
		run_convert(work_dir, [
			'-size', '144x144', 'xc:none',
			'-background', 'none',
			'-gravity', 'center',
			'-stroke', 'black',
			'-fill', 'black',
			'-draw', 'circle 72,72, 72,144',
			'-blur', '2x2',
			'-shadow', '%dx7'%width,
			'+repage',
			os.path.join(root_dir,'doc','logo','oglplus_circular.png'),
			'-composite',
			'-adaptive-resize', '72x72',
			'-border', '16x0',
			logo_file
		])

	# run the example and dump the frames
	render_video(
		sample_label,
		example_path,
		work_dir,
		main_label_file,
		sample_label_file,
		logo_file,
		width,
		height,
		ui
	)

	remove_dir(work_dir)

def main():

	options = parse_args(sys.argv)

	for example in options.examples:
		render_example(
			os.path.abspath(
				os.path.join(
					os.path.dirname(sys.argv[0]),
					os.path.pardir
				)
			),
			os.path.splitext(example)[0],
			options
		)


# run the main function
if __name__ == "__main__": main()
