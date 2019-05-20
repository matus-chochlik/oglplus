/*
 *  .file advanced/spectra/calculator.hpp
 *  .brief Declares interface for signal spectra calculator
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_EXAMPLE_SPECTRA_CALCULATOR_HPP
#define OGLPLUS_EXAMPLE_SPECTRA_CALCULATOR_HPP

#include <wx/string.h>

#include <complex>
#include <cstdint>
#include <memory>

struct SpectraCalculator {
    virtual ~SpectraCalculator() {}

    virtual const char* Name() const = 0;

    virtual std::size_t InputSize() const = 0;

    virtual std::size_t OutputSize() const = 0;

    virtual unsigned MaxConcurrentTransforms() const = 0;

    virtual void BeginBatch() = 0;

    virtual void FinishBatch() = 0;

    virtual unsigned BeginTransform(
      const float* input,
      std::size_t inbufsize,
      float* output,
      std::size_t outbufsize) = 0;

    virtual void FinishTransform(
      unsigned tid, float* output, std::size_t outbufsize) = 0;
};

class SpectraSharedObjects;

extern std::shared_ptr<SpectraCalculator> SpectraGetDefaultSignalTransform(
  SpectraSharedObjects& shared_objects, std::size_t spectrum_size);

struct SpectraFourierMatrixGen {
    double inv_n;
    std::complex<double> inv_sqrt_n;

    SpectraFourierMatrixGen(std::size_t n, std::size_t);

    std::complex<double> operator()(
      std::size_t i, std::size_t k, std::size_t n, std::size_t m) const;
};

#endif // include guard
