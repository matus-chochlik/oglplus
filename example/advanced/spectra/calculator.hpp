/*
 *  .file advanced/spectra/calculator.hpp
 *  .brief Declares interface for signal spectra calculator
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_EXAMPLE_SPECTRA_CALCULATOR_HPP
#define OGLPLUS_EXAMPLE_SPECTRA_CALCULATOR_HPP

#include <wx/string.h>

#include <cstdint>
#include <memory>

struct SpectraCalculator
{
	virtual ~SpectraCalculator(void) { }

	virtual wxString Name(void) const = 0;

	virtual std::size_t Size(void) const = 0;

	virtual void Transform(
		const float* input,
		float* output,
		std::size_t bufsize
	) = 0;
};

extern std::shared_ptr<SpectraCalculator>
SpectraMakeDefaultFourierTransf(std::size_t size);

#endif // include guard
