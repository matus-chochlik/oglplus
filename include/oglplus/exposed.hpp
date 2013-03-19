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
template <class ObjectOps>
class Exposed
 : public Managed<ObjectOps>
{
public:
	Exposed(const ObjectOps& object)
	 : Managed<ObjectOps>(object)
	{ }

	GLuint Name(void) const
	{
		return FriendOf<ObjectOps>::GetName(*this);
	}
};
#endif

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
template <class ObjectOps>
inline Exposed<ObjectOps> Expose(const Object<ObjectOps>& object)
{
	return Exposed<ObjectOps>(object);
}

template <class ObjectOps>
inline Exposed<ObjectOps> Expose(const Managed<Object<ObjectOps> >& object)
{
	return Exposed<ObjectOps>(object);
}

template <class ObjectOps>
inline Exposed<ObjectOps> Expose(const Managed<ObjectOps>& object)
{
	return Exposed<ObjectOps>(object);
}

} // namespace oglplus

#endif // include guard
