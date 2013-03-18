/*
 *  .file advanced/spectra/visualisation.hpp
 *  .brief Declares the class handling document visualization.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_EXAMPLE_SPECTRA_VISUALISATION_HPP
#define OGLPLUS_EXAMPLE_SPECTRA_VISUALISATION_HPP

#include <oglplus/gl.hpp>
#include <oglplus/buffer.hpp>
#include <oglplus/texture.hpp>

#include "spectra_app.hpp"
#include "document.hpp"

#include <wx/wx.h>
#include <wx/glcanvas.h>

#include <memory>

class SpectraMainFrame;
class SpectraVisDataUploader;

class SpectraGLContext
 : public wxGLContext
{
public:
	SpectraGLContext(
		wxGLCanvas* canvas,
		wxGLContext* parent_ctxt
	);
};

class SpectraVisualisation
{
private:
	SpectraApp& parent_app;
	SpectraMainFrame* main_frame;

	SpectraGLContext gl_context;

	std::shared_ptr<SpectraDocument> document;

	oglplus::Buffer spectrum_data;
	oglplus::Texture spectrum_tex;

	std::weak_ptr<SpectraVisDataUploader> uploader_ref;
public:
	SpectraVisualisation(
		SpectraApp& app,
		SpectraMainFrame* frame,
		wxGLCanvas* canvas,
		wxGLContext* parent_ctxt,
		const std::shared_ptr<SpectraDocument>& doc
	);

	~SpectraVisualisation(void);

	bool FinishLoading(void);

	wxGLContext& GLContext(void);

	oglplus::Managed<oglplus::Texture> SpectrumTex(void);

	wxString Name(void);

	const SpectraDocument& Document(void) const;

	std::size_t SignalSpectrumSize(void) const;

	std::size_t SignalSamplesPerGrid(void) const;

	std::size_t SignalSamplesPerGridPatch(void) const;

	std::size_t GridSamples(void) const;
};

#endif // include guard
