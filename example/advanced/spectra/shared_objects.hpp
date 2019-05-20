/*
 *  .file advanced/spectra/shared_objects.hpp
 *  .brief Declares a class wrapping shared (GL) objects.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_EXAMPLE_SPECTRA_SHARED_OBJECTS_HPP
#define OGLPLUS_EXAMPLE_SPECTRA_SHARED_OBJECTS_HPP

#include <oglplus/gl.hpp>

#include <oglplus/program.hpp>
#include <oglplus/shader.hpp>
#include <oglplus/shapes/wrapper.hpp>
#include <oglplus/uniform.hpp>

#include "calculator.hpp"

#include <wx/glcanvas.h>
#include <wx/wx.h>

#include <map>

class SpectraSharedObjects {
private:
    wxGLContext* gl_context;
    wxGLCanvas* gl_canvas;

    oglplus::shapes::ShapeWrapper ground_unit_grid, wall_unit_grid;

    typedef std::map<std::pair<GLuint, GLuint>, oglplus::shapes::ShapeWrapper>
      spectrum_plane_map;

    spectrum_plane_map spectrum_planes;

    typedef std::map<std::size_t, std::shared_ptr<SpectraCalculator>>
      spectrum_calculator_map;

    spectrum_calculator_map spectrum_calculators;

public:
    SpectraSharedObjects(wxGLContext* context, wxGLCanvas* canvas);

    wxGLContext* GLContext();
    wxGLCanvas* GLCanvas();

    oglplus::Program BuildProgramWithXFB(
      const char* prog_name,
      const char** xfb_varyings,
      std::size_t xfb_var_count,
      bool separate_attrib = true);
    oglplus::Program BuildProgramWithXFB(
      const char* prog_name,
      const char* xfb_varying,
      bool separate_attrib = true);
    oglplus::Program BuildProgram(const char* prog_name);

    const oglplus::shapes::ShapeWrapper& GroundUnitGrid();
    const oglplus::shapes::ShapeWrapper& WallUnitGrid();
    const oglplus::shapes::ShapeWrapper& SpectrumPlane(
      GLuint samples_per_sec, GLuint spectrum_size);

    std::shared_ptr<SpectraCalculator> SpectrumCalculator(
      std::size_t spectrum_size);
};

#endif // include guard
