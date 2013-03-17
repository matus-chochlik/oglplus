/*
 *  .file advanced/spectra/calculator.cpp
 *  .brief Implements default signal spectrum calculators
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <oglplus/gl.hpp>
#include <oglplus/math.hpp>

#include "calculator.hpp"

#include <vector>
#include <cassert>

class SpectraDefaultMatrixTransf
 : public SpectraCalculator
{
protected:
	std::vector<double> mat;
	wxString name;
public:
	template <typename Generator>
	SpectraDefaultMatrixTransf(
		std::size_t size,
		const wxString& transf_name,
		Generator gen
	);

	std::size_t Size(void) const;

	wxString Name(void) const;

	void Transform(
		const float* input,
		float* output,
		std::size_t bufsize
	);
};

template <typename Generator>
SpectraDefaultMatrixTransf::SpectraDefaultMatrixTransf(
	std::size_t size,
	const wxString& transf_name,
	Generator gen
): mat(size*size)
 , name(transf_name)
{
	auto m = mat.begin();
	for(std::size_t row=0; row!=size; ++row)
	{
		for(std::size_t col=0; col!=size; ++col)
		{
			*m = gen(row, col, size);
			++m;
		}
	}
	assert(m == mat.end());
}

std::size_t SpectraDefaultMatrixTransf::Size(void) const
{
	return std::size_t(mat.size());
}

wxString SpectraDefaultMatrixTransf::Name(void) const
{
	return name;
}

void SpectraDefaultMatrixTransf::Transform(
	const float* input,
	float* output,
	std::size_t bufsize
)
{
	std::size_t n = mat.size();
	assert(bufsize >= n);

	float* o = output;
	for(std::size_t row=0; row!=n; ++row)
	{
		const float* i = input;
		auto m = mat.begin()+row*n;
		double sum = 0.0;
		for(std::size_t col=0; col!=n; ++col)
		{
			sum += (*m++) * (*i++);
		}
		*o++ = float(sum);
	}
}

struct SpectraFourierMatrixGen
{
	double operator()(std::size_t i, std::size_t k, std::size_t n) const
	{
		return std::cos((oglplus::math::TwoPi()*k*i)/double(n));
	}
};

std::shared_ptr<SpectraCalculator>
SpectraMakeDefaultFourierTransf(std::size_t size)
{
	return std::make_shared<SpectraDefaultMatrixTransf>(
		size,
		wxT("Fourier"),
		SpectraFourierMatrixGen()
	);
}
