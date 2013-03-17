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
#include "coroutine.hpp"
#include "document_frame.hpp"
#include "document.hpp"
#include "default_renderer.hpp"

#include <wx/stockitem.h>
#include <wx/aboutdlg.h>

// -- SpectraMainFrameDocumentLoader --
class SpectraMainFrameDocumentLoader
 : public SpectraCoroutine
{
private:
	SpectraMainFrame* main_frame;
	std::shared_ptr<SpectraDocument> document;
public:
	SpectraMainFrameDocumentLoader(
		SpectraMainFrame* frame,
		const std::shared_ptr<SpectraDocument>& doc
	);

	wxString Description(void) const;

	bool DoWork(void);

	int PercentDone(void);
};

SpectraMainFrameDocumentLoader::SpectraMainFrameDocumentLoader(
	SpectraMainFrame* frame,
	const std::shared_ptr<SpectraDocument>& doc
): main_frame(frame)
 , document(doc)
{
	assert(main_frame);
	assert(document);
}

wxString SpectraMainFrameDocumentLoader::Description(void) const
{
	return wxGetTranslation(wxT("Loading document"));
}

bool SpectraMainFrameDocumentLoader::DoWork(void)
{
	if(document->FinishLoading())
	{
		main_frame->OpenLoadedDocument(document);
		return true;
	}
	else return false;
}

int SpectraMainFrameDocumentLoader::PercentDone(void)
{
	return document->PercentLoaded();
}


//-- SpectraMainFrame --
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
	SetExtraStyle(wxWS_EX_PROCESS_IDLE);
	wxIdleEvent::SetMode(wxIDLE_PROCESS_SPECIFIED);
	Connect(
		wxEVT_IDLE,
		wxIdleEventHandler(SpectraMainFrame::OnIdle)
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

void SpectraMainFrame::OnIdle(wxIdleEvent& event)
{
	if(!coroutine_exec->DoWork())
		event.RequestMore();
	for(auto* doc_frame : doc_frames)
		doc_frame->OnIdle(event);
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
	try
	{
		//wxString doc_path(wxT("TODO: get document path"));
		coroutine_exec->Start(
			std::make_shared<SpectraMainFrameDocumentLoader>(
				this,
				SpectraOpenTestDoc(
					[](float x) -> float { return std::sin(x*x); },
					2200,
					256,
					4.71
				) //TODO
			),
			false
		);
	}
	catch(oglplus::MissingFunction& mfe) { parent_app.HandleError(mfe); }
	catch(oglplus::ProgramBuildError& pbe) { parent_app.HandleError(pbe); }
	catch(oglplus::LimitError& le) { parent_app.HandleError(le); }
	catch(oglplus::OutOfMemory& oom) { parent_app.HandleError(oom); }
	catch(oglplus::Error& err) { parent_app.HandleError(err); }
	catch(const std::exception& se) { parent_app.HandleError(se); }
}

void SpectraMainFrame::OpenLoadedDocument(const std::shared_ptr<SpectraDocument>& document)
{
	this->doc_frames.insert(
		new SpectraDocumentFrame(
			this->parent_app,
			this,
			&this->gl_context,
			document,
			SpectraMakeDefaultRenderer
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
 , coroutine_exec(nullptr)
{
	InitMainMenu();
	InitComponents();
	Show();

	coroutine_exec = std::make_shared<SpectraCoroutineExecutor>(
		parent_app,
		this //TODO progress panel + sizer
	);

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
