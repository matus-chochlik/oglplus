/*
 *  .file advanced/spectra/renderer.cpp
 *  .brief Implements the document renderer class.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/context.hpp>

#include "renderer.hpp"

#include <wx/settings.h>

SpectraSharedObjects& SpectraRenderer::Common(void)
{
	assert(shared_objects);
	return *shared_objects;
}

SpectraDocumentVis& SpectraRenderer::DocVis(void)
{
	assert(document_vis);
	return *document_vis;
}

SpectraRenderer::SpectraRenderer(
	SpectraApp& app,
	const std::shared_ptr<SpectraSharedObjects>& sh_obj,
	const std::shared_ptr<SpectraDocumentVis>& doc_vis,
	wxGLCanvas* canvas
): parent_app(app)
 , shared_objects(sh_obj)
 , document_vis(doc_vis)
{
	assert(canvas);
	canvas->SetCurrent(DocVis().GLContext());
}

void SpectraRenderer::ReinitStyle(void)
{
}

SpectraDefaultRenderer::SpectraDefaultRenderer(
	SpectraApp& app,
	const std::shared_ptr<SpectraSharedObjects>& sh_obj,
	const std::shared_ptr<SpectraDocumentVis>& doc_vis,
	wxGLCanvas* canvas
): SpectraRenderer(app, sh_obj, doc_vis, canvas)
 , doc_vis_prog(Common().BuildProgram("default_doc_vis.prog"))
 , doc_vis_projection_matrix(doc_vis_prog, "ProjectionMatrix")
 , doc_vis_camera_matrix(doc_vis_prog, "CameraMatrix")
 , doc_vis_stretch_matrix(doc_vis_prog, "StretchMatrix")
 , doc_vis_transf_matrix(doc_vis_prog, "TransfMatrix")
 , spectrum_plane_wrap(
	Common().SpectrumPlane(
		DocVis().Document().SamplesPerSecond(),
		DocVis().Document().SpectrumSize()
	)
), spectrum_plane_vao(spectrum_plane_wrap.VAOForProgram(doc_vis_prog))
 , vis_cue_prog(Common().BuildProgram("default_vis_cue.prog"))
 , vis_cue_projection_matrix(vis_cue_prog, "ProjectionMatrix")
 , vis_cue_camera_matrix(vis_cue_prog, "CameraMatrix")
 , vis_cue_stretch_matrix(vis_cue_prog, "StretchMatrix")
 , vis_cue_transf_matrix(vis_cue_prog, "TransfMatrix")
 , vis_cue_color(vis_cue_prog, "Color")
 , vis_cue_alpha(vis_cue_prog, "Alpha")
 , ground_grid_vao(Common().GroundUnitGrid().VAOForProgram(vis_cue_prog))
 , wall_grid_vao(Common().WallUnitGrid().VAOForProgram(vis_cue_prog))
{
	CacheBgColor();
}

void SpectraDefaultRenderer::CacheBgColor(void)
{
	GLfloat s = 1.0f/255.f;

	wxColor bg = wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW);
	clear_r = bg.Red()*s;
	clear_g = bg.Green()*s;
	clear_b = bg.Blue()*s;

	wxColor lc = wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT);
	color_r = lc.Red()*s;
	color_g = lc.Green()*s;
	color_b = lc.Blue()*s;
}

void SpectraDefaultRenderer::RenderSpectrum(SpectraDocumentView& view)
{
	doc_vis_prog.Use();
	doc_vis_projection_matrix.TrySet(view.ProjectionMatrix());
	doc_vis_camera_matrix.TrySet(view.CameraMatrix());
	doc_vis_stretch_matrix.TrySet(view.StretchMatrix());
	doc_vis_transf_matrix.TrySet(view.TransfMatrix());

	spectrum_plane_vao.Bind();
	spectrum_plane_wrap.Draw(view.SegmentCount());
}

void SpectraDefaultRenderer::RenderVisualCues(SpectraDocumentView& view)
{
	oglplus::Context gl;

	gl.Enable(oglplus::Capability::LineSmooth);
	gl.Enable(oglplus::Capability::Blend);
	gl.BlendFunc(
		oglplus::BlendFn::SrcAlpha,
		oglplus::BlendFn::OneMinusSrcAlpha
	);

	vis_cue_prog.Use();
	vis_cue_projection_matrix.TrySet(view.ProjectionMatrix());
	vis_cue_camera_matrix.TrySet(view.CameraMatrix());
	vis_cue_stretch_matrix.TrySet(view.StretchMatrix());
	vis_cue_transf_matrix.TrySet(view.TransfMatrix());
	vis_cue_color.TrySet(oglplus::Vec3f(color_r, color_g, color_b));
	vis_cue_alpha.TrySet(0.5f);

	gl.DepthMask(false);

	ground_grid_vao.Bind();
	Common().GroundUnitGrid().Draw(view.SegmentCount());

	wall_grid_vao.Bind();
	Common().WallUnitGrid().Draw(view.SegmentCount());

	gl.DepthMask(true);

	gl.Disable(oglplus::Capability::Blend);
	gl.Disable(oglplus::Capability::LineSmooth);
}

void SpectraDefaultRenderer::ReinitStyle(void)
{
	CacheBgColor();
}

void SpectraDefaultRenderer::Render(
	SpectraDocumentView& view,
	wxGLCanvas* canvas
)
{
	assert(canvas);
	canvas->SetCurrent(DocVis().GLContext());

	oglplus::Context gl;

	gl.Viewport(view.Width(), view.Height());

	gl.ClearColor(clear_r, clear_g, clear_b, 0.0);
	gl.ClearDepth(1.0f);

	gl.Clear().ColorBuffer().DepthBuffer();

	gl.Enable(oglplus::Capability::DepthTest);

	RenderSpectrum(view);
	RenderVisualCues(view);
}
