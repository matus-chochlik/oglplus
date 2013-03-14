/*
 *  .file advanced/spectra/main_frame.hpp
 *  .brief Declares the main frame.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_EXAMPLE_SPECTRA_MAIN_FRAME_HPP
#define OGLPLUS_EXAMPLE_SPECTRA_MAIN_FRAME_HPP

#include <oglplus/gl.hpp>

#include "shared_objects.hpp"
#include "spectra_app.hpp"

#include <wx/wx.h>
#include <wx/glcanvas.h>

#include <memory>
#include <set>

class SpectraDocumentFrame;

class SpectraMainFrame
 : public wxFrame
{
private:
	friend class SpectraDocumentFrame;

	SpectraApp& parent_app;
	wxMenuBar* main_menu;

	wxStatusBar* status_bar;
	void SetStatus(const wxString& status_text);

	wxGLCanvas* tmp_canvas;
	wxGLContext gl_context;
	std::unique_ptr<oglplus::GLAPIInitializer> api_init;

	std::shared_ptr<SpectraSharedObjects> shared_objects;

	std::set<SpectraDocumentFrame*> doc_frames;

	wxStaticText* gl_vendor;
	wxStaticText* gl_renderer;
	wxStaticText* gl_version;
	wxStaticText* sl_version;

	void InitMainMenu(void);
	void InitComponents(void);
	void ConnectEventHandlers(void);

	void DoClose(wxCommandEvent&);
	void OnClose(wxCloseEvent&);

	void DoShowAboutDialog(wxCommandEvent&);

	void DoOpenDocument(wxCommandEvent&);
public:
	SpectraMainFrame(SpectraApp& app);
	~SpectraMainFrame(void);

	void ForgetDocument(SpectraDocumentFrame*);
};

#endif // include guard
