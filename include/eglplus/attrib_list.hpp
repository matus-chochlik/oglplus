/**
 *  @file eglplus/attrib_list.hpp
 *  @brief EGL surface and configuration attribute list
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef EGLPLUS_ATTRIB_LIST_1303292057_HPP
#define EGLPLUS_ATTRIB_LIST_1303292057_HPP

#include <cassert>
#include <vector>

namespace eglplus {

/// Specifies the list of attribute values for configuration selection
template <typename AttribKind>
class AttributeList
{
private:
	std::vector<EGLint> _attribs;
public:
	/// Creates an empty list of attributes
	AttributeList(void)
	{
		_attribs.reserve(2*10+1);
	}

	/// Creates a list with a single attribute/value pair
	AttributeList(AttribKind attrib, EGLint value)
	{
		_attribs.reserve(2*10+1);
		Add(attrib, value);
	}

	/// Adds a new attribute/value pair
	/**
	 *  @pre !Finished()
	 */
	AttributeList& Add(AttribKind attrib, EGLint value)
	{
		assert(!Finished());
		_attribs.push_back(EGLint(attrib));
		_attribs.push_back(value);
		return *this;
	}

	/// Adds a new attribute/value pair
	/**
	 *  @pre !Finished()
	 */
	AttributeList& Add(AttribKind attrib, bool value)
	{
		assert(!Finished());
		_attribs.push_back(EGLint(attrib));
		_attribs.push_back(value?EGL_TRUE:EGL_FALSE);
		return *this;
	}

	/// Sets the attribute value value to don't care
	/**
	 *  @pre !Finished()
	 */
	AttributeList& DontCare(AttribKind attrib)
	{
		assert(!Finished());
		_attribs.push_back(EGLint(attrib));
		_attribs.push_back(EGL_DONT_CARE);
		return *this;
	}

	/// Returns true if the list of attributes has been finished
	/**
	 *  @see Finish()
	 */
	bool Finished(void) const
	{
		return _attribs.back() == EGL_NONE;
	}

	/// Finishes the list of attributes
	/**
	 *  @post Finished()
	 *  @see Get()
	 *  @see Finished()
	 */
	AttributeList& Finish(void)
	{
		if(!Finished()) _attribs.push_back(EGL_NONE);
		return *this;
	}

	/// Returns the terminated array of attribute/value pairs
	/**
	 *  @post Finished()
	 */
	const EGLint* Get(void)
	{
		Finish();
		return _attribs.data();
	}

	/// Returns the terminated array of attribute/value pairs
	/**
	 *  @pre Finished()
	 */
	const EGLint* Get(void) const
	{
		assert(Finished());
		return _attribs.data();
	}
};

typedef AttributeList<ConfigAttrib> ConfigAttribs;

} // namespace oglplus

#endif // include guard
