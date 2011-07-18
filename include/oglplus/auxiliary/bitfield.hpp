/**
 *  .file oglplus/auxiliary/bitfield.hpp
 *  .brief OpenGL bitfield-related helpers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_AUX_BITFIELD_1107121519_HPP
#define OGLPLUS_AUX_BITFIELD_1107121519_HPP

#include <initializer_list>

namespace oglplus {
namespace aux {

template <typename Bit>
inline GLbitfield MakeBitfield(
	const std::initializer_list<Bit>& bits,
	GLbitfield bf = GLbitfield(0)
)
{
	for(auto i=bits.begin(),e=bits.end(); i!=e; ++i)
		bf |= GLbitfield(*i);
	return bf;
}

} // namespace aux
} // namespace oglplus

#endif // include guard
