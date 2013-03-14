/*
 *  .file advanced/spectra/main_frame.cpp
 *  .brief Implements the main frame
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include "main_frame.hpp"
#include "document_frame.hpp"
#include "document.hpp"
#include "renderer.hpp"

#include <wx/stockitem.h>
#include <wx/aboutdlg.h>

void SpectraMainFrame::SetStatus(const wxString& status_text)
{
	status_bar->SetStatusText(status_text);
}

wxStaticText* AddKeyValue(
	wxWindow* parent,
	wxSizer* sizer,
	const wxString& label,
	const wxString& tool_tip,
	const wxString& value
)
{
	wxStaticText* name_label = new wxStaticText(
		parent,
		wxID_ANY,
		label,
		wxDefaultPosition,
		wxDefaultSize,
		wxALIGN_LEFT
	);
	wxFont name_font = name_label->GetFont();
	name_font.SetWeight(wxFONTWEIGHT_BOLD);
	name_label->SetFont(name_font);

	if(!tool_tip.empty()) name_label->SetToolTip(tool_tip);
	sizer->Add(name_label, 1, wxEXPAND);

	wxStaticText* value_label = new wxStaticText(
		parent,
		wxID_ANY,
		value,
		wxDefaultPosition,
		wxDefaultSize,
		wxALIGN_RIGHT
	);
	sizer->Add(value_label, 3, wxEXPAND);
	return value_label;
}

void SpectraMainFrame::InitMainMenu(void)
{
	wxMenu* file_menu = new wxMenu();
	file_menu->Append(wxID_OPEN);
	file_menu->AppendSeparator();
	file_menu->Append(wxID_EXIT);

	main_menu->Append(file_menu, wxGetStockLabel(wxID_FILE));

	wxMenu* help_menu = new wxMenu();
	help_menu->Append(wxID_ABOUT);

	main_menu->Append(help_menu, wxGetStockLabel(wxID_HELP));

	SetMenuBar(main_menu);
}

void SpectraMainFrame::ConnectEventHandlers(void)
{
	Connect(
		wxID_EXIT,
		wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(SpectraMainFrame::DoClose)
	);
	Connect(
		wxID_OPEN,
		wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(SpectraMainFrame::DoOpenDocument)
	);
	Connect(
		wxID_ABOUT,
		wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(SpectraMainFrame::DoShowAboutDialog)
	);
	Connect(
		wxEVT_CLOSE_WINDOW,
		wxCloseEventHandler(SpectraMainFrame::OnClose)
	);
}

void SpectraMainFrame::InitComponents(void)
{
	const int em = 5;
	const int em_2 = em/2;

	const wxString n_a(wxGetTranslation(wxT("N/A")));

	SetMinSize(wxSize(200, 300));

	wxBoxSizer* td_sizer = new wxBoxSizer(wxVERTICAL);
	td_sizer->AddSpacer(em);
	wxBoxSizer* lr_sizer = new wxBoxSizer(wxHORIZONTAL);
	lr_sizer->AddSpacer(em);

	wxPanel* main_panel = new wxPanel(this);
	wxBoxSizer* main_sizer = new wxBoxSizer(wxVERTICAL);

	wxPanel* info_panel = new wxPanel(main_panel);
	wxFlexGridSizer* info_sizer = new wxFlexGridSizer(0, 2, em_2, em);

	gl_vendor = AddKeyValue(
		info_panel,
		info_sizer,
		wxGetTranslation(wxT("GL Vendor")),
		wxGetTranslation(wxT("The name of the GL implementation vendor")),
		n_a
	);

	gl_renderer = AddKeyValue(
		info_panel,
		info_sizer,
		wxGetTranslation(wxT("GL Renderer")),
		wxGetTranslation(wxT("The name of the GL renderer")),
		n_a
	);

	gl_version = AddKeyValue(
		info_panel,
		info_sizer,
		wxGetTranslation(wxT("GL Version")),
		wxGetTranslation(wxT("The version of GL supported by the renderer")),
		n_a
	);

	sl_version = AddKeyValue(
		info_panel,
		info_sizer,
		wxGetTranslation(wxT("SL Version")),
		wxGetTranslation(wxT("The version of GLSL supported by the renderer")),
		n_a
	);


	info_panel->SetSizer(info_sizer);

	main_sizer->Add(info_panel, 0, wxEXPAND);
	main_panel->SetSizer(main_sizer);

	lr_sizer->Add(main_panel, 1, wxEXPAND);
	lr_sizer->AddSpacer(em);
	td_sizer->Add(lr_sizer, 1, wxEXPAND);
	td_sizer->AddSpacer(em);
	td_sizer->Add(status_bar, 0, wxEXPAND);

	td_sizer->SetSizeHints(this);
	SetSizer(td_sizer);
	Layout();
}

void SpectraMainFrame::DoClose(wxCommandEvent&)
{
	Close();
}

void SpectraMainFrame::OnClose(wxCloseEvent& event)
{
	if(!doc_frames.empty())
	{
		for(auto& frame : doc_frames)
		{
			frame->Close();
		}
		if(event.CanVeto())
		{
			event.Veto();
		}
		else Destroy();
	}
	Destroy();
}

void SpectraMainFrame::DoShowAboutDialog(wxCommandEvent&)
{
    wxAboutDialogInfo info;
    info.SetName(wxGetTranslation(wxT("OGLplus spectra")));
    info.SetVersion(wxGetTranslation(wxT("0.1.0 Beta")));
    info.SetDescription(wxGetTranslation(wxT("3D viewer of signal Fourier spectra.")));
    info.SetCopyright(wxGetTranslation(wxT("(C) 2013 Matus Chochlik")));
    info.SetWebSite(wxGetTranslation(wxT("http://oglplus.org/")));
    info.AddDeveloper(wxGetTranslation(wxT("Matus Chochlik")));

    wxAboutBox(info);
}

void SpectraMainFrame::DoOpenDocument(wxCommandEvent&)
{
	wxString doc_path(wxT("TODO: get document path"));
	doc_frames.insert(
		new SpectraDocumentFrame(
			parent_app,
			this,
			&this->gl_context,
			SpectraDocument::DocumentOpener(doc_path),
			std::make_shared<
				SpectraDefaultRenderer,
				SpectraApp&,
				const std::shared_ptr<SpectraSharedObjects>&,
				const std::shared_ptr<SpectraDocument>&,
				wxGLCanvas*
			>
		)
	);
}

void SpectraMainFrame::ForgetDocument(SpectraDocumentFrame* doc_frame)
{
	doc_frames.erase(doc_frame);
}

int* SpectraGLConfig(void)
{
	static int conf[] = {
		WX_GL_RGBA,
		WX_GL_DOUBLEBUFFER,
		WX_GL_DEPTH_SIZE, 24,
		WX_GL_STENCIL_SIZE, 8,
		0
	};
	return conf;
}

SpectraMainFrame::SpectraMainFrame(SpectraApp& app)
 : wxFrame(
	(wxWindow*)nullptr,
	wxID_ANY,
	wxT("OGLplus Spectra"),
	wxDefaultPosition,
	wxSize(300, 400)
), parent_app(app)
 , main_menu(new wxMenuBar())
 , status_bar(new wxStatusBar(this))
 , tmp_canvas(
	new wxGLCanvas(
		(wxWindow*)this,
		wxID_ANY,
		SpectraGLConfig(),
		wxDefaultPosition,
		wxDefaultSize
	)
), gl_context(tmp_canvas)
 , api_init(nullptr)
 , shared_objects(nullptr)
{
	InitMainMenu();
	InitComponents();
	Show();

	SetStatus(wxGetTranslation(wxT("Initializing GL"), wxT("Status")));

	gl_context.SetCurrent(*tmp_canvas);
	api_init.reset(new oglplus::GLAPIInitializer());
	delete tmp_canvas;
	tmp_canvas = nullptr;

	gl_vendor->SetLabel(wxString(
		(const char*)glGetString(GL_VENDOR),
		wxConvUTF8
	));
	gl_renderer->SetLabel(wxString(
		(const char*)glGetString(GL_RENDERER),
		wxConvUTF8
	));
	gl_version->SetLabel(wxString(
		(const char*)glGetString(GL_VERSION),
		wxConvUTF8
	));
	sl_version->SetLabel(wxString(
		(const char*)glGetString(GL_SHADING_LANGUAGE_VERSION),
		wxConvUTF8
	));

	SetStatus(wxGetTranslation(wxT("Creating shared objects"), wxT("Status")));

	shared_objects = std::make_shared<SpectraSharedObjects>();

	SetStatus(wxGetTranslation(wxT("Ready"), wxT("Status")));

	ConnectEventHandlers();

	SetStatus(wxGetTranslation(wxT("Running"), wxT("Status")));
}

SpectraMainFrame::~SpectraMainFrame(void)
{
}
