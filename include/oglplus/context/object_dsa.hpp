/**
 *  @file oglplus/context/object_dsa.hpp
 *  @brief Functions giving direct state acess to OGLplus Objects
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_CONTEXT_OBJECT_DSA_1404232057_HPP
#define OGLPLUS_CONTEXT_OBJECT_DSA_1404232057_HPP

#include <oglplus/config_compiler.hpp>
#include <oglplus/fwd.hpp>

namespace oglplus {
namespace context {

/// Object direct state access operations
/**
 *  @ingroup ogl_context
 */
class ObjectDSA
{
public:
	/// Returns a direct state access wrapper for @p object
	template <typename Object>
	static Managed<
		typename NonDSAtoDSA<
			typename ObjectBaseOps<Object>::Type
		>::Type
	> Direct(const Object& object)
	{
		return Managed<
			typename NonDSAtoDSA<
				typename ObjectBaseOps<Object>::Type
			>::Type
		>(object);
	}

	/// Returns a direct state access wrapper for @p object
	template <typename Object>
	static Managed<
		typename NonDSAtoDSA<
			typename ObjectBaseOps<Object>::Type
		>::Type
	> Direct(typename Object::Target target, const Object& object)
	{
		Managed<
			typename NonDSAtoDSA<
				typename ObjectBaseOps<Object>::Type
			>::Type
		> result(object);
		result.target = target;
		return result;
	}
};

} // namespace context
} // namespace oglplus

#endif // include guard
