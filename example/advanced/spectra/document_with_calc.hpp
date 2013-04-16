/*
 *  .file advanced/spectra/document_with_calc.hpp
 *  .brief Declares a base class for documents using a spectrum calculator
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_EXAMPLE_SPECTRA_DOCUMENT_WITH_CALC_HPP
#define OGLPLUS_EXAMPLE_SPECTRA_DOCUMENT_WITH_CALC_HPP

#include "document.hpp"
#include "calculator.hpp"

#include <vector>
#include <memory>

class SpectraDocumentWithCalculator
 : public SpectraDocument
{
private:
	std::shared_ptr<SpectraCalculator> spectra_calc;
	std::vector<unsigned> transform_ids;
public:
	SpectraDocumentWithCalculator(
		const std::shared_ptr<SpectraCalculator>& calc
	);

	std::size_t SpectrumRowsPerLoadHint(void) const;

	std::size_t QuerySpectrumValues(
		float* buffer,
		std::size_t bufsize,
		std::size_t start_row,
		std::size_t end_row
	);
};

#endif // include guard
