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

class SpectraDocument
{
private:
	SpectraApp& parent_app;

	wxGLContext gl_context;

	wxString document_path;
public:
	class DocumentOpener
	{
	private:
		wxString document_path;
	public:
		DocumentOpener(const wxString& path);

		std::shared_ptr<SpectraDocument> operator()(
			SpectraApp& app,
			wxGLCanvas* canvas,
			wxGLContext* parent_ctxt
		) const;
	};

	SpectraDocument(
		SpectraApp& app,
		wxGLCanvas* canvas,
		wxGLContext* parent_ctxt,
		const wxString& doc_path
	);

	wxString GetName(void) const;

	wxGLContext& GLContext(void);
};

#endif // include guard
