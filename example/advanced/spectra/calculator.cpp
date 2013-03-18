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
	const std::size_t in_size, out_size;
	std::vector<double> mat;
	wxString name;
public:
	template <typename Generator>
	SpectraDefaultMatrixTransf(
		std::size_t in_sz,
		std::size_t out_sz,
		const wxString& transf_name,
		Generator gen
	);

	std::size_t InputSize(void) const;

	std::size_t OutputSize(void) const;

	wxString Name(void) const;

	void Transform(
		const float* input,
		std::size_t inbufsize,
		float* output,
		std::size_t outbufsize
	);
};

template <typename Generator>
SpectraDefaultMatrixTransf::SpectraDefaultMatrixTransf(
	std::size_t in_sz,
	std::size_t out_sz,
	const wxString& transf_name,
	Generator gen
): in_size(in_sz)
 , out_size(out_sz)
 , mat(in_size*out_size)
 , name(transf_name)
{
	auto m = mat.begin();
	for(std::size_t row=0; row!=out_size; ++row)
	{
		for(std::size_t col=0; col!=in_size; ++col)
		{
			*m = gen(col, row, in_size, out_size);
			++m;
		}
	}
	assert(m == mat.end());
}

std::size_t SpectraDefaultMatrixTransf::InputSize(void) const
{
	return in_size;
}

std::size_t SpectraDefaultMatrixTransf::OutputSize(void) const
{
	return out_size;
}

wxString SpectraDefaultMatrixTransf::Name(void) const
{
	return name;
}

void SpectraDefaultMatrixTransf::Transform(
	const float* input,
	std::size_t inbufsize,
	float* output,
	std::size_t outbufsize
)
{
	assert(inbufsize >= in_size);
	assert(outbufsize >= out_size);

	float* o = output;
	for(std::size_t row=0; row!=out_size; ++row)
	{
		const float* i = input;
		auto m = mat.begin()+row*out_size;
		double sum = 0.0;
		for(std::size_t col=0; col!=in_size; ++col)
		{
			sum += (*m++) * (*i++);
		}
		*o++ = float(sum);
	}
}

struct SpectraFourierMatrixGen
{
	double inv_n;
	double inv_sqrt_n;

	SpectraFourierMatrixGen(std::size_t n, std::size_t)
	 : inv_n(1.0/n)
	 , inv_sqrt_n(1.0/std::sqrt(double(n)))
	{ }

	double operator()(
		std::size_t i,
		std::size_t k,
		std::size_t /*n*/,
		std::size_t /*m*/
	) const
	{
		const double twopi = oglplus::math::TwoPi();
		if(k == 0) return inv_n;
		else if(k % 2 == 0)
			return std::cos(twopi*(k/2)*i*inv_n)*inv_sqrt_n;
		else return std::sin(twopi*(k/2)*i*inv_n)*inv_sqrt_n;
	}
};

std::shared_ptr<SpectraCalculator>
SpectraGetDefaultFourierTransf(std::size_t spectrum_size)
{
	// TODO: share instances
	assert(spectrum_size % 2 == 0);
	std::size_t in_size = spectrum_size-2;
	return std::make_shared<SpectraDefaultMatrixTransf>(
		in_size,
		spectrum_size,
		wxT("Discrete real Fourier"),
		SpectraFourierMatrixGen(in_size, spectrum_size)
	);
}
