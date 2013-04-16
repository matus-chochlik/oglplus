/*
 *  .file advanced/spectra/document_with_calc.cpp
 *  .brief Implements a base class for documents using a spectrum calculator
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include "document_with_calc.hpp"

#include <cassert>

SpectraDocumentWithCalculator::SpectraDocumentWithCalculator(
	const std::shared_ptr<SpectraCalculator>& calc
): spectra_calc(calc)
{
	assert(spectra_calc);
	assert(spectra_calc->MaxConcurrentTransforms() > 0);
	transform_ids.resize(spectra_calc->MaxConcurrentTransforms());
}


std::size_t SpectraDocumentWithCalculator::SpectrumRowsPerLoadHint(void) const
{
	return 256*spectra_calc->MaxConcurrentTransforms();
}

std::size_t SpectraDocumentWithCalculator::QuerySpectrumValues(
	float* buffer,
	std::size_t bufsize,
	std::size_t start_row,
	std::size_t end_row
)
{
	std::size_t spectrum_size = SpectrumSize();
	std::size_t n = end_row-start_row;
	std::size_t m = transform_ids.size();
	assert(bufsize >= n*spectrum_size);

	std::vector<float> signal(spectra_calc->InputSize()+n-1);

	QuerySignalSamples(
		signal.data(),
		signal.size(),
		start_row,
		end_row+spectra_calc->InputSize()-1
	);
	spectra_calc->BeginBatch();
	for(std::size_t i=0; i!=m; ++i)
	{
		transform_ids[i] = spectra_calc->BeginTransform(
			signal.data()+i,
			spectra_calc->InputSize(),
			buffer+i*spectrum_size,
			spectrum_size
		);
	}

	for(std::size_t i=0; i!=n; ++i)
	{
		spectra_calc->FinishTransform(
			transform_ids[i%m],
			buffer+i*spectrum_size,
			spectrum_size
		);
		std::size_t j=i+m;
		if(j<n)
		{
			transform_ids[i%m] = spectra_calc->BeginTransform(
				signal.data()+j,
				spectra_calc->InputSize(),
				buffer+j*spectrum_size,
				spectrum_size
			);
		}
	}
	spectra_calc->FinishBatch();
	return n;
}

