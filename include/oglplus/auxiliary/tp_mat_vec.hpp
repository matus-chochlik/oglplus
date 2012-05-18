/**
 *  @file oglplus/auxiliary/tp_mat_vec.hpp
 *  @brief Helper class wrapping third party matrix types
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_AUX_TP_MAT_VEC_1205181513_HPP
#define OGLPLUS_AUX_TP_MAT_VEC_1205181513_HPP

#include <cassert>

namespace oglplus {
namespace aux {

template <class TPMatrix>
struct ThirdPartyMatrixBase;

template <class TPMatrix>
class ThirdPartyMatrix
 : public ThirdPartyMatrixBase<TPMatrix>
{
private:
	friend struct ThirdPartyMatrixBase<TPMatrix>;
	const TPMatrix& _ref;
public:
	ThirdPartyMatrix(const TPMatrix& ref)
	 : _ref(ref)
	{ }
};

} // namespace aux
} // namespace oglplus

#endif // include guard
