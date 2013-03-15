/*
 *  .file advanced/spectra/renderer.hpp
 *  .brief Declares the document renderer class.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_EXAMPLE_SPECTRA_RENDERER_HPP
#define OGLPLUS_EXAMPLE_SPECTRA_RENDERER_HPP

#include <oglplus/gl.hpp>
#include <oglplus/vertex_array.hpp>

#include "shared_objects.hpp"
#include "document_view.hpp"
#include "document.hpp"
#include "spectra_app.hpp"

#include <wx/wx.h>
#include <wx/glcanvas.h>

#include <memory>

class SpectraRenderer
{
protected:
	SpectraApp& parent_app;

	std::shared_ptr<SpectraSharedObjects> shared_objects;

	SpectraSharedObjects& Common(void);

	std::shared_ptr<SpectraDocumentVis> document_vis;

	SpectraDocumentVis& DocVis(void);

	SpectraRenderer(
		SpectraApp& app,
		const std::shared_ptr<SpectraSharedObjects>& sh_obj,
		const std::shared_ptr<SpectraDocumentVis>& doc_vis,
		wxGLCanvas* canvas
	);
public:
	virtual void ReinitStyle(void);

	virtual void Render(
		SpectraDocumentView& view,
		wxGLCanvas* canvas
	) = 0;
};

class SpectraDefaultRenderer
 : public SpectraRenderer
{
private:
	GLfloat clear_r, clear_g, clear_b;
	GLfloat color_r, color_g, color_b;

	oglplus::Program doc_vis_prog;
	oglplus::OptionalUniform<oglplus::Mat4f> doc_vis_projection_matrix;
	oglplus::OptionalUniform<oglplus::Mat4f> doc_vis_camera_matrix;
	oglplus::OptionalUniform<oglplus::Mat4f> doc_vis_stretch_matrix;
	oglplus::OptionalUniform<oglplus::Mat4f> doc_vis_transf_matrix;

	const oglplus::shapes::ShapeWrapper& spectrum_plane_wrap;
	oglplus::VertexArray spectrum_plane_vao;

	oglplus::Program vis_cue_prog;
	oglplus::OptionalUniform<oglplus::Mat4f> vis_cue_projection_matrix;
	oglplus::OptionalUniform<oglplus::Mat4f> vis_cue_camera_matrix;
	oglplus::OptionalUniform<oglplus::Mat4f> vis_cue_stretch_matrix;
	oglplus::OptionalUniform<oglplus::Mat4f> vis_cue_transf_matrix;
	oglplus::OptionalUniform<oglplus::Vec3f> vis_cue_color;
	oglplus::OptionalUniform<GLfloat> vis_cue_alpha;

	oglplus::VertexArray ground_grid_vao, wall_grid_vao;

	void CacheBgColor(void);
	void RenderSpectrum(SpectraDocumentView& view);
	void RenderVisualCues(SpectraDocumentView& view);
public:
	SpectraDefaultRenderer(
		SpectraApp& app,
		const std::shared_ptr<SpectraSharedObjects>& sh_obj,
		const std::shared_ptr<SpectraDocumentVis>& doc_vis,
		wxGLCanvas* canvas
	);

	void ReinitStyle(void);

	void Render(
		SpectraDocumentView& view,
		wxGLCanvas* canvas
	);
};

#endif // include guard
