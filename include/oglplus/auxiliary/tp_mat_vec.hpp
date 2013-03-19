/**
 *  @file oglplus/auxiliary/tp_mat_vec.hpp
 *  @brief Helper class wrapping third party matrix types
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_AUX_TP_MAT_VEC_1205181513_HPP
#define OGLPLUS_AUX_TP_MAT_VEC_1205181513_HPP

#include <cassert>

namespace oglplus {
namespace aux {

template <class TPVector>
struct ThirdPartyVectorBase;

template <class TPMatrix>
struct ThirdPartyMatrixBase;

} // namespace aux

template <typename T, size_t N>
class ThirdPartyVector
{
private:
	const T* _data;
public:
#if !OGLPLUS_NO_DELETED_FUNCTIONS
	ThirdPartyVector(void) = delete;
	ThirdPartyVector(const ThirdPartyVector&) = delete;
#else
private:
	ThirdPartyVector(void);
	ThirdPartyVector(const ThirdPartyVector&);
public:
#endif

	template <class TPVector>
	ThirdPartyVector(const TPVector& ref)
	 : _data(nullptr)
	{
		static_assert(
			std::is_same<
				T,
				typename aux::ThirdPartyVectorBase<TPVector>::Type
			>::value,
			"Invalid vector  element type for this adaptor type"
		);
		static_assert(
			aux::ThirdPartyVectorBase<TPVector>::N::value == N,
			"Invalid vector element count for this adaptor type"
		);
		_data = aux::ThirdPartyVectorBase<TPVector>::Data(ref);
		assert(_data != nullptr);
	}

	size_t Size(void) const
	{
		return N;
	}

	const T* Data(void) const
	{
		return _data;
	}
};

template <typename T, size_t Rows, size_t Cols>
class ThirdPartyMatrix
{
private:
	const T* _data;
	const bool _row_major;
public:
#if !OGLPLUS_NO_DELETED_FUNCTIONS
	ThirdPartyMatrix(void) = delete;
	ThirdPartyMatrix(const ThirdPartyMatrix&) = delete;
#else
private:
	ThirdPartyMatrix(void);
	ThirdPartyMatrix(const ThirdPartyMatrix&);
public:
#endif

	template <class TPMatrix>
	ThirdPartyMatrix(const TPMatrix& ref)
	 : _data(nullptr)
	 , _row_major(aux::ThirdPartyMatrixBase<TPMatrix>::IsRowMajor::value)
	{
		static_assert(
			std::is_same<
				T,
				typename aux::ThirdPartyMatrixBase<TPMatrix>::Type
			>::value,
			"Invalid matrix element type for this adaptor type"
		);
		static_assert(
			aux::ThirdPartyMatrixBase<TPMatrix>::Rows::value == Rows,
			"Invalid matrix row count for this adaptor type"
		);
		static_assert(
			aux::ThirdPartyMatrixBase<TPMatrix>::Cols::value == Cols,
			"Invalid matrix column count for this adaptor type"
		);
		_data = aux::ThirdPartyMatrixBase<TPMatrix>::Data(ref);
		assert(_data != nullptr);
	}

	size_t Size(void) const
	{
		return Rows*Cols;
	}

	const T* Data(void) const
	{
		return _data;
	}

	bool IsRowMajor(void) const
	{
		return _row_major;
	}
};

} // namespace oglplus

#endif // include guard
