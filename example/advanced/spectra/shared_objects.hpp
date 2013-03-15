/*
 *  .file advanced/spectra/shared_objects.hpp
 *  .brief Declares a class wrapping shared (GL) objects.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_EXAMPLE_SPECTRA_SHARED_OBJECTS_HPP
#define OGLPLUS_EXAMPLE_SPECTRA_SHARED_OBJECTS_HPP

#include <oglplus/gl.hpp>

#include <oglplus/program.hpp>
#include <oglplus/uniform.hpp>
#include <oglplus/shapes/wrapper.hpp>

#include <wx/wx.h>
#include <wx/glcanvas.h>

#include <map>

class SpectraSharedObjects
{
private:
	oglplus::shapes::ShapeWrapper ground_unit_grid, wall_unit_grid;

	typedef std::map<
		std::pair<GLuint, GLuint>,
		oglplus::shapes::ShapeWrapper
	> spectrum_plane_map;

	spectrum_plane_map spectrum_planes;
public:
	oglplus::Program BuildProgram(const char* prog_name);

	SpectraSharedObjects(void);

	const oglplus::shapes::ShapeWrapper& GroundUnitGrid(void);
	const oglplus::shapes::ShapeWrapper& WallUnitGrid(void);
	const oglplus::shapes::ShapeWrapper& SpectrumPlane(
		GLuint samples_per_sec,
		GLuint spectrum_size
	);
};

#endif // include guard
