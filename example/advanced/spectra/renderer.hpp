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

	std::shared_ptr<SpectraDocument> document;

	SpectraDocument& Document(void);

	SpectraRenderer(
		SpectraApp& app,
		const std::shared_ptr<SpectraSharedObjects>& sh_obj,
		const std::shared_ptr<SpectraDocument>& doc,
		wxGLCanvas* canvas
	);
public:
	virtual void Render(
		SpectraDocumentView& view,
		wxGLCanvas* canvas
	) = 0;
};

class SpectraDefaultRenderer
 : public SpectraRenderer
{
private:
	oglplus::Program vis_cue_prog;
	oglplus::Uniform<oglplus::Mat4f> vis_cue_projection_matrix;
	oglplus::Uniform<oglplus::Mat4f> vis_cue_camera_matrix;
	oglplus::VertexArray grid_vao;

	void RenderVisualCues(SpectraDocumentView& view);
public:
	SpectraDefaultRenderer(
		SpectraApp& app,
		const std::shared_ptr<SpectraSharedObjects>& sh_obj,
		const std::shared_ptr<SpectraDocument>& doc,
		wxGLCanvas* canvas
	);

	void Render(
		SpectraDocumentView& view,
		wxGLCanvas* canvas
	);
};

#endif // include guard
