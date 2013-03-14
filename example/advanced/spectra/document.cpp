/*
 *  .file advanced/spectra/document.cpp
 *  .brief Implements the document canvas
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include "document.hpp"

SpectraDocument::SpectraDocument(
	SpectraApp& app,
	wxGLCanvas* canvas,
	wxGLContext* parent_ctxt,
	const wxString& doc_path
): parent_app(app)
 , gl_context(canvas, parent_ctxt)
 , document_path(doc_path)
{
}

wxString SpectraDocument::GetName(void) const
{
	//TODO
	return document_path;
}

wxGLContext& SpectraDocument::GLContext(void)
{
	return gl_context;
}

// DocumentOpener
SpectraDocument::DocumentOpener::DocumentOpener(const wxString& path)
 : document_path(path)
{ }

std::shared_ptr<SpectraDocument> SpectraDocument::DocumentOpener::operator()(
	SpectraApp& app,
	wxGLCanvas* canvas,
	wxGLContext* parent_ctxt
) const
{
	return std::make_shared<SpectraDocument>(
		app,
		canvas,
		parent_ctxt,
		document_path
	);
}

