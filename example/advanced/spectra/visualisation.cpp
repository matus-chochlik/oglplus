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

#include <oglplus/gl.hpp>

#include "main_frame.hpp"
#include "visualisation.hpp"
#include "coroutine.hpp"

// SpectraVisDataUploader
class SpectraVisDataUploader
 : public SpectraCoroutine
{
private:
	wxGLContext* gl_context;
	std::shared_ptr<std::set<wxGLCanvas*>> gl_canvases;

	bool SetCurrent(void);

	std::shared_ptr<SpectraDocument> document;

	std::size_t spectrum_size;
	std::size_t current_row;
	std::size_t row_count;
	const std::size_t rows_per_load;

	oglplus::Buffer& spectrum_data;

	std::vector<GLfloat> data_buf;
public:
	SpectraVisDataUploader(
		wxGLContext* context,
		const std::shared_ptr<std::set<wxGLCanvas*>>& canvases,
		const std::shared_ptr<SpectraDocument>& doc,
		oglplus::Buffer& spect_data
	);

	wxString Description(void) const;

	void Cancel(void);

	bool DoWork(void);

	int PercentDone(void) const;
};

SpectraVisDataUploader::SpectraVisDataUploader(
	wxGLContext* context,
	const std::shared_ptr<std::set<wxGLCanvas*>>& canvases,
	const std::shared_ptr<SpectraDocument>& doc,
	oglplus::Buffer& spect_data
): gl_context(context)
 , gl_canvases(canvases)
 , document(doc)
 , current_row(0)
 , rows_per_load(document->SpectrumRowsPerLoadHint())
 , spectrum_data(spect_data)
{
	assert(gl_context);
	assert(gl_canvases);
	assert(document);

	spectrum_size = document->SpectrumSize();
	row_count = document->SignalSampleCount();

	if(row_count < spectrum_size)
		row_count = 0;
	else row_count -= spectrum_size;

	data_buf.resize(spectrum_size*rows_per_load);

	if(SetCurrent())
	{
		std::vector<GLfloat> init_data(spectrum_size*row_count, 0.0f);
		spectrum_data.Bind(oglplus::Buffer::Target::Texture);
		oglplus::Buffer::Data(oglplus::Buffer::Target::Texture, init_data);
	}
}

bool SpectraVisDataUploader::SetCurrent(void)
{
	assert(gl_canvases);
	if(gl_canvases->empty()) return false;
	wxGLCanvas* gl_canvas = *gl_canvases->begin();
	assert(gl_canvas);
	gl_canvas->SetCurrent(*gl_context);
	return true;
}

wxString SpectraVisDataUploader::Description(void) const
{
	return wxGetTranslation(wxT("Uploading spectrum data to GPU"));
}

void SpectraVisDataUploader::Cancel(void)
{
	current_row = row_count;
}

bool SpectraVisDataUploader::DoWork(void)
{
	if((current_row < row_count) && SetCurrent())
	{
		spectrum_data.Bind(oglplus::Buffer::Target::Texture);
		std::size_t n = rows_per_load;

		if(current_row+n > row_count)
			n = row_count - current_row;

		document->QuerySpectrumValues(
			data_buf.data(),
			data_buf.size(),
			current_row,
			current_row+n
		);

		spectrum_data.Bind(oglplus::Buffer::Target::Texture);
		oglplus::Buffer::SubData(
			oglplus::Buffer::Target::Texture,
			spectrum_size*current_row,
			spectrum_size*n,
			data_buf.data()
		);

		current_row += n;
		return false;
	}
	return true;
}

int SpectraVisDataUploader::PercentDone(void) const
{
	return int((current_row*100)/row_count);
}


// SpectraGLContext
SpectraGLContext::SpectraGLContext(
	wxGLCanvas* canvas,
	wxGLContext* parent_ctxt
): wxGLContext(canvas, parent_ctxt)
{
	canvas->SetCurrent(*this);
}

// SpectraVisualisation
SpectraVisualisation::SpectraVisualisation(
	SpectraApp& app,
	SpectraMainFrame* frame,
	wxGLCanvas* canvas,
	wxGLContext* parent_ctxt,
	const std::shared_ptr<SpectraDocument>& doc
): parent_app(app)
 , main_frame(frame)
 , selected_time(0.0f)
 , selection_begin(0.0f)
 , selection_end(1.0f)
 , gl_context(canvas, parent_ctxt)
 , gl_canvases(std::make_shared<std::set<wxGLCanvas*>>())
 , document(doc)
 , signal_samples_per_grid(1)
{
	std::size_t sps = Document().SamplesPerSecond();
	std::size_t max = 4096;
	if(sps / signal_samples_per_grid > max)
	{
		signal_samples_per_grid = 2;
		while(sps / signal_samples_per_grid > max)
			signal_samples_per_grid += 2;
	}

	assert(gl_canvases);
	gl_canvases->insert(canvas);

	std::shared_ptr<SpectraVisDataUploader> data_uploader(
		std::make_shared<SpectraVisDataUploader>(
			&gl_context,
			gl_canvases,
			document,
			spectrum_data
		)
	);
	uploader_ref = data_uploader;
	spectrum_tex.Bind(oglplus::Texture::Target::Buffer);
	oglplus::Texture::Buffer(
		oglplus::Texture::Target::Buffer,
		oglplus::PixelDataInternalFormat::R32F,
		spectrum_data
	);

	main_frame->StartCoroutine(data_uploader);
}

SpectraVisualisation::~SpectraVisualisation(void)
{
	if(!uploader_ref.expired())
	{
		std::shared_ptr<SpectraVisDataUploader>
			data_uploader(uploader_ref.lock());
		if(data_uploader) data_uploader->Cancel();
	}
}

void SpectraVisualisation::AddCanvas(wxGLCanvas* canvas)
{
	gl_canvases->insert(canvas);
}

void SpectraVisualisation::RemoveCanvas(wxGLCanvas* canvas)
{
	gl_canvases->erase(canvas);
}

wxGLContext& SpectraVisualisation::GLContext(void)
{
	return gl_context;
}

oglplus::Managed<oglplus::Texture> SpectraVisualisation::SpectrumTex(void)
{
	return spectrum_tex;
}

wxString SpectraVisualisation::Name(void)
{
	return Document().Name();
}

const SpectraDocument& SpectraVisualisation::Document(void) const
{
	assert(document);
	return *document;
}

void SpectraVisualisation::Play(void)
{
	assert(document);
	document->Play(SelectionBegin(), SelectionEnd());
}

std::size_t SpectraVisualisation::SignalSpectrumSize(void) const
{
	return Document().SpectrumSize();
}

std::size_t SpectraVisualisation::SignalSamplesPerGrid(void) const
{
	return Document().SamplesPerSecond();
}

std::size_t SpectraVisualisation::SignalSamplesPerGridPatch(void) const
{
	return signal_samples_per_grid;
}

std::size_t SpectraVisualisation::GridSamples(void) const
{
	return SignalSamplesPerGrid() / SignalSamplesPerGridPatch();
}

void SpectraVisualisation::SelectedTime(float time)
{
	selected_time = time;
}

float SpectraVisualisation::SelectedTime(void) const
{
	return selected_time;
}

void SpectraVisualisation::DragSelection(float time, float delta)
{
	float eps = (selection_end - selection_begin)*0.2;
	if(time-delta <= selection_begin+eps)
	{
		selection_begin = time;
	}
	else if(time-delta >= selection_end-eps)
	{
		selection_end = time;
	}
	else
	{
		selection_begin += delta;
		selection_end += delta;
	}
	if(selection_begin > selection_end)
		selection_begin = selection_end;
	if(selection_begin < 0.0f)
		selection_begin = 0.0f;
	if(selection_end > Document().MaxTime())
		selection_end = Document().MaxTime();
}

float SpectraVisualisation::SelectionBegin(void) const
{
	return selection_begin;
}

float SpectraVisualisation::SelectionEnd(void) const
{
	return selection_end;
}

