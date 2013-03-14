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

SpectraSharedObjects& SpectraRenderer::Common(void)
{
	assert(shared_objects);
	return *shared_objects;
}

SpectraDocument& SpectraRenderer::Document(void)
{
	assert(document);
	return *document;
}

SpectraRenderer::SpectraRenderer(
	SpectraApp& app,
	const std::shared_ptr<SpectraSharedObjects>& sh_obj,
	const std::shared_ptr<SpectraDocument>& doc,
	wxGLCanvas* canvas
): parent_app(app)
 , shared_objects(sh_obj)
 , document(doc)
{
	assert(canvas);
	canvas->SetCurrent(Document().GLContext());
}

SpectraDefaultRenderer::SpectraDefaultRenderer(
	SpectraApp& app,
	const std::shared_ptr<SpectraSharedObjects>& sh_obj,
	const std::shared_ptr<SpectraDocument>& doc,
	wxGLCanvas* canvas
): SpectraRenderer(app, sh_obj, doc, canvas)
 , vis_cue_prog(Common().BuildProgram("default_vis_cue.prog"))
 , vis_cue_projection_matrix(vis_cue_prog, "ProjectionMatrix")
 , vis_cue_camera_matrix(vis_cue_prog, "CameraMatrix")
 , grid_vao(Common().UnitGrid().VAOForProgram(vis_cue_prog))
{
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
	gl.DepthMask(false);

	vis_cue_prog.Use();
	vis_cue_projection_matrix.Set(view.ProjectionMatrix());
	vis_cue_camera_matrix.Set(view.CameraMatrix());

	grid_vao.Bind();

	Common().UnitGrid().Draw();

	gl.DepthMask(false);
	gl.Disable(oglplus::Capability::Blend);
	gl.Disable(oglplus::Capability::LineSmooth);
}

void SpectraDefaultRenderer::Render(
	SpectraDocumentView& view,
	wxGLCanvas* canvas
)
{
	assert(canvas);
	canvas->SetCurrent(Document().GLContext());

	oglplus::Context gl;

	gl.ClearColor(0.0, 0.0, 0.0, 0.0);
	gl.ClearDepth(1.0f);

	gl.Clear().ColorBuffer().DepthBuffer();

	RenderVisualCues(view);
}
