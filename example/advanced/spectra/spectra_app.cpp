/*
 *  .file advanced/spectra/spectra_app.cpp
 *  .brief Implements the main application class
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/opt/application.hpp>
#include <oglplus/lib/oglplus.hpp>

#include <oalplus/al.hpp>
#include <oalplus/lib.hpp>

#include "spectra_app.hpp"
#include "main_frame.hpp"

IMPLEMENT_APP(SpectraApp)

wxString SpectraApp::MakeCommonErrorMessage(oglplus::Error& err)
{
	const wxString newline(wxT("\r\n"));
	wxString message;
	message.Append(wxString(err.what(), wxConvUTF8));
	message.Append(newline);
	message.Append(wxString::Format(
		wxGetTranslation(wxT("GL symbol: '%s'"), wxT("Error")),
		wxString(err.GLSymbol(), wxConvUTF8).c_str()
	));
	message.Append(newline);
	message.Append(wxString::Format(
		wxGetTranslation(wxT("Class: '%s'"), wxT("Error")),
		wxString(err.ClassName(), wxConvUTF8).c_str()
	));
	message.Append(newline);
	message.Append(wxString::Format(
		wxGetTranslation(wxT("Object: '%s'"), wxT("Error")),
		wxString(err.ObjectDescription().c_str(), wxConvUTF8).c_str()
	));
	message.Append(newline);
	message.Append(wxString::Format(
		wxGetTranslation(wxT("Binding point: '%s'"), wxT("Error")),
		wxString(err.BindTarget(), wxConvUTF8).c_str()
	));
	message.Append(newline);
	message.Append(wxString::Format(
		wxGetTranslation(wxT("File: '%s'"), wxT("Error")),
		wxString(err.File(), wxConvUTF8).c_str()
	));
	message.Append(newline);
	message.Append(wxString::Format(
		wxGetTranslation(wxT("Line: '%u'"), wxT("Error")),
		err.Line()
	));
	message.Append(newline);

	auto i = err.Properties().begin(), e = err.Properties().end();
	if(i != e)
	{
		message.Append(wxGetTranslation(wxT("Properties: "), wxT("Error")));
		message.Append(newline);

		while(i != e)
		{
			message.Append(wxString(i->first.c_str(), wxConvUTF8));
			message.Append(wxT(" = "));
			message.Append(wxString(i->second.c_str(), wxConvUTF8));
			message.Append(newline);
			++i;
		}
	}

	return message;
}

void SpectraApp::HandleError(
	oglplus::MissingFunction& err,
	wxWindow* parent
)
{
	wxString message;
	message.Append(MakeCommonErrorMessage(err));
	wxMessageBox(
		message,
		wxGetTranslation(wxT("Missing function"), wxT("Error")),
		wxOK | wxICON_ERROR,
		parent
	);
	err.Cleanup();
}

void SpectraApp::HandleError(
	oglplus::ProgramBuildError& err,
	wxWindow* parent
)
{
	wxString message;
	message.Append(MakeCommonErrorMessage(err));
	message.Append(wxGetTranslation(wxT("Build output: "), wxT("Error")));
	message.Append(wxString(err.Log().c_str(), wxConvUTF8));
	wxMessageBox(
		message,
		wxGetTranslation(wxT("Program build error"), wxT("Error")),
		wxOK | wxICON_ERROR,
		parent
	);
	err.Cleanup();
}

void SpectraApp::HandleError(
	oglplus::LimitError& err,
	wxWindow* parent
)
{
	wxString message;
	message.Append(MakeCommonErrorMessage(err));
	message.Append(wxString::Format(
		wxGetTranslation(
			wxT("Value %u exceeds implementation-dependent limit %u"),
			wxT("Error")
		),
		err.Value(),
		err.Limit()
	));
	wxMessageBox(
		message,
		wxGetTranslation(wxT("Limit exceeded"), wxT("Error")),
		wxOK | wxICON_ERROR,
		parent
	);
	err.Cleanup();
}

void SpectraApp::HandleError(
	oglplus::Error& err,
	wxWindow* parent
)
{
	wxMessageBox(
		MakeCommonErrorMessage(err),
		wxGetTranslation(wxT("OpenGL Error"), wxT("Error")),
		wxOK | wxICON_ERROR,
		parent
	);
	err.Cleanup();
}

void SpectraApp::HandleError(
	const std::exception& err,
	wxWindow* parent
)
{
	wxMessageBox(
		wxString(err.what(), wxConvUTF8),
		wxGetTranslation(wxT("Unspecified error"), wxT("Error")),
		wxOK | wxICON_ERROR,
		parent
	);
}

bool SpectraApp::OnInit(void)
{
	bool result = false;
	try
	{
		std::string arg0str(wxString(*argv).mb_str(wxConvUTF8));
		const char* arg0 = arg0str.c_str();
		oglplus::Application::ParseCommandLineOptions(argc, &arg0);
		SetTopWindow(new SpectraMainFrame(*this));
		result = true;
	}
	catch(oglplus::MissingFunction& mfe) { HandleError(mfe); }
	catch(oglplus::ProgramBuildError& pbe) { HandleError(pbe); }
	catch(oglplus::LimitError& le) { HandleError(le); }
	catch(oglplus::Error& err) { HandleError(err); }
	catch(const std::exception& se) { HandleError(se); }
	return result;
}

