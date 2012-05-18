/**
 *  @file oglplus/interop/glm.hpp
 *  @brief Interoperability with GLM matrices, vectors, etc.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_INTEROP_GLM_1205181555_HPP
#define OGLPLUS_INTEROP_GLM_1205181555_HPP

#include <oglplus/aux/tp_mat_vec.hpp>
#include <type_traits>

namespace oglplus {
namespace aux {

#define OGLPLUS_HLPR_IMPL_GLM_MATRIX_ADAPTER(ROWS, COLS) \
template <class T> \
struct ThirdPartyMatrixBase<glm::detail::tmat##COLS##x##ROWS##<T> > \
{ \
	typedef T Type; \
	typedef std::integral_constant<size_t, ROWS> Rows; \
	typedef std::integral_constant<size_t, COLS> Cols; \
	typedef std::false_type IsRowMajor; \
	static const T* Data(const ThirdPartyMatrix<glm::detail::tmat4x4<T>>&m)\
	{ \
		return glm::value_ptr(m._ref); \
	} \
};

OGLPLUS_HLPR_IMPL_GLM_MATRIX_ADAPTER(4, 4)
OGLPLUS_HLPR_IMPL_GLM_MATRIX_ADAPTER(3, 3)
OGLPLUS_HLPR_IMPL_GLM_MATRIX_ADAPTER(2, 2)

#undef OGLPLUS_HLPR_IMPL_GLM_MATRIX_ADAPTER

} // namespace aux
} // namespace oglplus

#endif // include guard
