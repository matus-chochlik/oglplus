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

#include <eglplus/bitfield.hpp>

#include <cassert>
#include <vector>

namespace eglplus {

/// Stores a finished attribute list create by AttributeList
template <typename AttribKind> // <- do not remove this is intentional
class FinishedAttributeList
{
private:
	std::vector<EGLint> _attribs;
public:
	FinishedAttributeList(const std::vector<EGLint>& attribs)
	 : _attribs(attribs)
	{
		if(!_attribs.empty() && (_attribs.back() != EGL_NONE))
		{
			_attribs.push_back(EGL_NONE);
		}

		assert(
			(_attribs.empty()) || (
				(_attribs.size() % 2 == 1) &&
				(_attribs.back() == EGL_NONE)
			)
		);
	}

	FinishedAttributeList(FinishedAttributeList&& tmp)
	 : _attribs(std::move(tmp._attribs))
	{ }

	/// Returns the terminated array of attribute/value pairs
	const EGLint* Get(void) const
	{
		return _attribs.data();
	}
};

/// Specifies the list of attribute values for configuration selection
template <typename AttribKind, class ValueToAttribMap>
class AttributeList
{
private:
	std::vector<EGLint> _attribs;
	ValueToAttribMap _value_to_attrib_map;
public:
	/// Creates an empty list of attributes
	AttributeList(void)
	{
		_attribs.reserve(2*10+1);
	}

	/// Adds a new attribute/value pair
	/**
	 *  @pre !Finished()
	 */
	AttributeList& Add(AttribKind attrib, EGLint value)
	{
		assert(!Finished());
		_attribs.push_back(EGLint(EGLenum(attrib)));
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
		_attribs.push_back(EGLint(EGLenum(attrib)));
		_attribs.push_back(value?EGL_TRUE:EGL_FALSE);
		return *this;
	}

	/// Adds a new enumerated attribute value
	/**
	 *  @pre !Finished()
	 */
	template <typename AttribValueType>
	AttributeList& Add(AttribValueType value)
	{
		return Add(
			_value_to_attrib_map(value),
			EGLint(EGLenum(value))
		);
	}

	template <typename AttribValueType>
	AttributeList& Add(Bitfield<AttribValueType> bits)
	{
		return Add(
			_value_to_attrib_map(AttribValueType()),
			EGLint(EGLenum(bits))
		);
	}

	/// Sets the attribute value value to don't care
	/**
	 *  @pre !Finished()
	 */
	AttributeList& DontCare(AttribKind attrib)
	{
		assert(!Finished());
		_attribs.push_back(EGLint(EGLenum(attrib)));
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

	/// Returns a finished attribute list
	/**
	 *  @note this function does not call the Finish function
	 *  on this attribute list
	 */
	FinishedAttributeList<AttribKind> Get(void) const
	{
		return FinishedAttributeList<AttribKind>(_attribs);
	}
};

} // namespace eglplus

#endif // include guard
