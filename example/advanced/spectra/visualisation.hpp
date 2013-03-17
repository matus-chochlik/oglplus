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

#include "spectra_app.hpp"
#include "document.hpp"

#include <wx/wx.h>
#include <wx/glcanvas.h>

#include <memory>
#include <functional>

class SpectraVisualisation
{
private:
	SpectraApp& parent_app;

	wxGLContext gl_context;

	std::shared_ptr<SpectraDocument> document;
public:
	SpectraVisualisation(
		SpectraApp& app,
		wxGLCanvas* canvas,
		wxGLContext* parent_ctxt,
		const std::shared_ptr<SpectraDocument>& doc
	);

	bool FinishLoading(void);

	wxGLContext& GLContext(void);

	SpectraDocument& Document(void);

	wxString Name(void);
};

#endif // include guard
