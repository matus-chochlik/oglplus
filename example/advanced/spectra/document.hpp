/*
 *  .file advanced/spectra/document.hpp
 *  .brief Declares the document class.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_EXAMPLE_SPECTRA_DOCUMENT_HPP
#define OGLPLUS_EXAMPLE_SPECTRA_DOCUMENT_HPP

#include <oglplus/gl.hpp>

#include "spectra_app.hpp"
#include "document_canvas.hpp"

#include <wx/wx.h>
#include <wx/glcanvas.h>

#include <memory>
#include <functional>

struct SpectraDocument
{
	~SpectraDocument(void){ }

	virtual GLuint SamplesPerSecond(void) const = 0;

	virtual GLuint SpectrumSize(void) const = 0;

	virtual GLfloat MaxTime(void) const = 0;

	virtual wxString Name(void) const = 0;
};

extern std::unique_ptr<SpectraDocument> SpectraOpenTestDoc(void);

class SpectraDocumentVis
{
private:
	SpectraApp& parent_app;

	wxGLContext gl_context;

	std::unique_ptr<SpectraDocument> document;
public:
	SpectraDocumentVis(
		SpectraApp& app,
		wxGLCanvas* canvas,
		wxGLContext* parent_ctxt,
		std::unique_ptr<SpectraDocument>&& doc
	);

	wxGLContext& GLContext(void);

	SpectraDocument& Document(void);

	wxString Name(void);
};

#endif // include guard
