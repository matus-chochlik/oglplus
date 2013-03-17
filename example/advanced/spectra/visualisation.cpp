/*
 *  .file advanced/spectra/visualisation.cpp
 *  .brief Implements the canvas responsible for document visualisation
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include "visualisation.hpp"

// SpectraVisualisation
SpectraVisualisation::SpectraVisualisation(
	SpectraApp& app,
	wxGLCanvas* canvas,
	wxGLContext* parent_ctxt,
	const std::shared_ptr<SpectraDocument>& doc
): parent_app(app)
 , gl_context(canvas, parent_ctxt)
 , document(doc)
{ }

wxGLContext& SpectraVisualisation::GLContext(void)
{
	return gl_context;
}

SpectraDocument& SpectraVisualisation::Document(void)
{
	assert(document);
	return *document;
}

wxString SpectraVisualisation::Name(void)
{
	return Document().Name();
}
