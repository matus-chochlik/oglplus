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

class SpectraTestDocument
 : public SpectraDocument
{
public:
	SpectraTestDocument(void)
	{ }

	GLuint SamplesPerSecond(void) const
	{
		return 1024;
	}

	GLuint SpectrumSize(void) const
	{
		return 256;
	}

	GLfloat MaxTime(void) const
	{
		return 4.7f;
	}

	wxString Name(void) const
	{
		return wxT("Test document");
	}
};

std::unique_ptr<SpectraDocument> SpectraOpenTestDoc(void)
{
	return std::unique_ptr<SpectraDocument>(
		new SpectraTestDocument()
	);
}

SpectraDocumentVis::SpectraDocumentVis(
	SpectraApp& app,
	wxGLCanvas* canvas,
	wxGLContext* parent_ctxt,
	std::unique_ptr<SpectraDocument>&& doc
): parent_app(app)
 , gl_context(canvas, parent_ctxt)
 , document(std::move(doc))
{ }

wxGLContext& SpectraDocumentVis::GLContext(void)
{
	return gl_context;
}

SpectraDocument& SpectraDocumentVis::Document(void)
{
	assert(document);
	return *document;
}

wxString SpectraDocumentVis::Name(void)
{
	return Document().Name();
}

