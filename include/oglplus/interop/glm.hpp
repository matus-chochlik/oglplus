/**
 *  @file oglplus/interop/glm.hpp
 *  @brief Interoperability with GLM matrices, vectors, etc.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_INTEROP_GLM_1205181555_HPP
#define OGLPLUS_INTEROP_GLM_1205181555_HPP

#include <oglplus/auxiliary/tp_mat_vec.hpp>
#include <glm/glm.hpp> //TODO: only pick what is necessary
#include <glm/gtc/type_ptr.hpp>
#include <type_traits>

namespace oglplus {
namespace aux {

#define OGLPLUS_HLPR_IMPL_GLM_VECTOR_ADAPTER(DIM) \
template <class T> \
struct ThirdPartyVectorBase<glm::tvec##DIM<T> > \
{ \
	typedef T Type; \
	typedef std::integral_constant<std::size_t, DIM> N; \
	static const T* Data(glm::tvec##DIM<T> const & v)\
	{ \
		return glm::value_ptr(v); \
	} \
};

OGLPLUS_HLPR_IMPL_GLM_VECTOR_ADAPTER(2)
OGLPLUS_HLPR_IMPL_GLM_VECTOR_ADAPTER(3)
OGLPLUS_HLPR_IMPL_GLM_VECTOR_ADAPTER(4)

#undef OGLPLUS_HLPR_IMPL_GLM_VECTOR_ADAPTER

#define OGLPLUS_HLPR_IMPL_GLM_MATRIX_ADAPTER(ROWS, COLS) \
template <class T> \
struct ThirdPartyMatrixBase<glm::tmat##COLS##x##ROWS<T> > \
{ \
	typedef T Type; \
	typedef std::integral_constant<std::size_t, ROWS> Rows; \
	typedef std::integral_constant<std::size_t, COLS> Cols; \
	typedef std::integral_constant<bool, false> IsRowMajor; \
	static const T* Data(glm::tmat##COLS##x##ROWS<T> const & m)\
	{ \
		return glm::value_ptr(m); \
	} \
};

OGLPLUS_HLPR_IMPL_GLM_MATRIX_ADAPTER(2, 2)
OGLPLUS_HLPR_IMPL_GLM_MATRIX_ADAPTER(2, 3)
OGLPLUS_HLPR_IMPL_GLM_MATRIX_ADAPTER(2, 4)
OGLPLUS_HLPR_IMPL_GLM_MATRIX_ADAPTER(3, 2)
OGLPLUS_HLPR_IMPL_GLM_MATRIX_ADAPTER(3, 3)
OGLPLUS_HLPR_IMPL_GLM_MATRIX_ADAPTER(3, 4)
OGLPLUS_HLPR_IMPL_GLM_MATRIX_ADAPTER(4, 2)
OGLPLUS_HLPR_IMPL_GLM_MATRIX_ADAPTER(4, 3)
OGLPLUS_HLPR_IMPL_GLM_MATRIX_ADAPTER(4, 4)

#undef OGLPLUS_HLPR_IMPL_GLM_MATRIX_ADAPTER

} // namespace aux
} // namespace oglplus

#endif // include guard
