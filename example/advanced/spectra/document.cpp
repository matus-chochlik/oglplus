/*
 *  .file advanced/spectra/document.cpp
 *  .brief Implements the document canvas
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include "calculator.hpp"
#include "openal_document.hpp"

#include <wx/utils.h>

#include <cmath>
#include <vector>

class SpectraTestDocument : public SpectraDocument {
private:
    std::function<float(float)> signal_func;
    const std::size_t samples_per_second;
    const float max_time;

public:
    SpectraTestDocument(
      std::function<float(float)> sig_fn, std::size_t sps, float mt);

    bool FinishLoading();

    int PercentLoaded() const;

    std::size_t SamplesPerSecond() const;

    std::size_t SignalSampleCount() const;

    float MaxTime() const;

    wxString Name() const;

    std::size_t QuerySignalSamples(
      float* buffer, std::size_t bufsize, std::size_t start, std::size_t end);

    bool CanPlay() const;

    void Play(float from, float to);
};

SpectraTestDocument::SpectraTestDocument(
  std::function<float(float)> sig_fn, std::size_t sps, float mt)
  : signal_func(sig_fn)
  , samples_per_second(sps)
  , max_time(mt) {}

bool SpectraTestDocument::FinishLoading() {
    return true;
}

int SpectraTestDocument::PercentLoaded() const {
    return 100;
}

std::size_t SpectraTestDocument::SamplesPerSecond() const {
    return samples_per_second;
}

std::size_t SpectraTestDocument::SignalSampleCount() const {
    return std::size_t(max_time * samples_per_second);
}

float SpectraTestDocument::MaxTime() const {
    return max_time;
}

wxString SpectraTestDocument::Name() const {
    return wxT("Test document");
}

std::size_t SpectraTestDocument::QuerySignalSamples(
  float* buffer, std::size_t bufsize, std::size_t start, std::size_t end) {
    assert(bufsize >= end - start);

    float* b = buffer;
    std::size_t se = SignalSampleCount();
    if(se > end)
        se = end;
    if(start < se) {
        float d = 1.0f / float(samples_per_second);
        for(std::size_t s = start; s != se; ++s) {
            *b++ = signal_func(s * d);
        }
        for(std::size_t s = se; s != end; ++s) {
            *b++ = 0.0f;
        }
        assert(b == buffer + end - start);
        return se - start;
    }
    return 0;
}

bool SpectraTestDocument::CanPlay() const {
    return true;
}

void SpectraTestDocument::Play(float, float) {
    wxBell();
}

std::shared_ptr<SpectraDocument> SpectraOpenTestDoc(
  const std::function<float(float)>& signal_func,
  std::size_t samples_per_second,
  float max_time) {
    return std::shared_ptr<SpectraDocument>(
      new SpectraTestDocument(signal_func, samples_per_second, max_time));
}

std::shared_ptr<SpectraDocument> SpectraLoadDocFromFile(
  const wxString& file_path) {
    return SpectraOpenOpenALDoc(file_path);
}
