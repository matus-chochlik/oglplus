/*
 *  .file advanced/spectra/renderer.hpp
 *  .brief Declares the document renderer abstract base class.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_EXAMPLE_SPECTRA_RENDERER_HPP
#define OGLPLUS_EXAMPLE_SPECTRA_RENDERER_HPP

#include "document_view.hpp"
#include "shared_objects.hpp"
#include "spectra_app.hpp"
#include "visualisation.hpp"

#include <wx/glcanvas.h>
#include <wx/wx.h>

#include <memory>

class SpectraRenderer {
protected:
    SpectraApp& parent_app;

    std::shared_ptr<SpectraSharedObjects> shared_objects;

    SpectraSharedObjects& Common();

    std::shared_ptr<SpectraVisualisation> document_vis;

    SpectraVisualisation& DocVis();

    SpectraRenderer(
      SpectraApp& app,
      const std::shared_ptr<SpectraSharedObjects>& sh_obj,
      const std::shared_ptr<SpectraVisualisation>& doc_vis,
      wxGLCanvas* canvas);

public:
    virtual ~SpectraRenderer() {}

    virtual void ReinitStyle();

    virtual bool Interactive() = 0;

    virtual void Render(SpectraDocumentView& view, wxGLCanvas* canvas) = 0;
};

#endif // include guard
