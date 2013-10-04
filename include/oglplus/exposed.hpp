/**
 *  @file oglplus/exposed.hpp
 *  @brief Special object wrapper for exposing Object's OpenGL name
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_EXPOSED_1107121519_HPP
#define OGLPLUS_EXPOSED_1107121519_HPP

#include <oglplus/config.hpp>
#include <oglplus/friend_of.hpp>
#include <oglplus/object.hpp>

namespace oglplus {

#if OGLPLUS_DOCUMENTATION_ONLY
/// This template class can ba used to get the OpenGL name of the Object
/** Exposing the object's name can be useful when calling an OpenGL function
 *  which is not wrapped by @OGLplus and which requires the name of an object.
 *
 *  @note The instance of Object from which the instance of Exposed<Object>
 *  was created must be kept alive at least as long as the instance of Exposed.
 *
 *  @see Managed
 *  @see Expose
 *
 *  @ingroup utility_classes
 */
template <class Object>
class Exposed
 : public Managed<Object>
{
public:
	Exposed(const Object& object);

	/// Returns the OpenGL name of the wrapped object
	GLuint Name(void) const;
};

#else
template <class ObjectOps_>
class Exposed
 : public Managed<ObjectOps_>
{
public:
	Exposed(const ObjectOps_& object)
	 : Managed<ObjectOps_>(object)
	{ }

	GLuint Name(void) const
	{
		return FriendOf<ObjectOps_>::GetName(*this);
	}
};
#endif

#if OGLPLUS_DOCUMENTATION_ONLY
/// Function that creates an Exposed wrapper for the object passed as argument
/** This function provides a more convenient way of exposing an Object's name
 *  than manually instantiating the Exposed class.
 *
 *  Example:
 *  @code
 *  Program program;
 *  // initialize program here
 *  glProgramParameteri(Expose(program).Name(), GL_PROGRAM_SEPARABLE, GL_TRUE);
 *  @endcode
 *  @see Exposed
 *
 *  @ingroup utility_classes
 */
template <class Object>
inline Exposed<Object> Expose(const Object& object)
#endif

template <class ObjectOps_>
inline Exposed<ObjectOps_> Expose(const Object<ObjectOps_>& object)
{
	return Exposed<ObjectOps_>(object);
}

template <class ObjectOps_>
inline Exposed<ObjectOps_> Expose(const Managed<Object<ObjectOps_> >& object)
{
	return Exposed<ObjectOps_>(object);
}

template <class ObjectOps_>
inline Exposed<ObjectOps_> Expose(const Managed<ObjectOps_>& object)
{
	return Exposed<ObjectOps_>(object);
}

} // namespace oglplus

#endif // include guard
