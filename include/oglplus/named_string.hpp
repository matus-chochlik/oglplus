/**
 *  @file oglplus/named_string.hpp
 *  @brief NamedString wrapper class
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_NAMED_STRING_1202231207_HPP
#define OGLPLUS_NAMED_STRING_1202231207_HPP

#if OGLPLUS_DOCUMENTATION_ONLY || GL_ARB_shading_language_include

#include <oglplus/glfunc.hpp>
#include <oglplus/named_string_type.hpp>
#include <oglplus/string/ref.hpp>
#include <oglplus/string/def.hpp>

namespace oglplus {

/// Wrapper for GL NamedStrings
class NamedString
{
private:
	GLString _name;

	NamedString(const NamedString&);
public:
	/// Store the @p value, of the specified @p type under @p name
	static void Set(
		NamedStringType type,
		const GLCStrRef& name,
		const GLCStrRef& value
	)
	{
		OGLPLUS_GLFUNC(NamedStringARB)(
			GLenum(type),
			GLint(name.size()),
			name.data(),
			GLint(value.size()),
			value.data()
		);
		OGLPLUS_CHECK_SIMPLE(NamedStringARB);
	}

	/// Gets the value stored under @p name
	static GLString Get(const GLCStrRef& name)
	{
		GLint len = 0;
		OGLPLUS_GLFUNC(GetNamedStringivARB)(
			GLint(name.size()),
			name.data(),
			GL_NAMED_STRING_LENGTH_ARB,
			&len
		);
		OGLPLUS_CHECK_SIMPLE(GetNamedStringivARB);

		GLString result(len, '\0');
		OGLPLUS_GLFUNC(GetNamedStringARB)(
			GLint(name.size()),
			name.data(),
			len,
			&len,
			&result.front()
		);
		OGLPLUS_CHECK_SIMPLE(GetNamedStringARB);
		return std::move(result);

	}

	/// Deletes the value stored under @p name
	static void Delete(const GLCStrRef& name)
	{
		OGLPLUS_GLFUNC(DeleteNamedStringARB)(
			GLint(name.size()),
			name.data()
		);
		OGLPLUS_CHECK_SIMPLE(DeleteNamedStringARB);
	}

	/// Gets the type of the named string stored under @p name
	static NamedStringType Type(const GLCStrRef& name)
	{
		GLint result = 0;
		OGLPLUS_GLFUNC(GetNamedStringivARB)(
			GLint(name.size()),
			name.data(),
			GL_NAMED_STRING_TYPE_ARB,
			&result
		);
		OGLPLUS_CHECK_SIMPLE(GetNamedStringivARB);
		return NamedStringType(GLenum(result));
	}

	/// Checks if @p name is a stored string
	static bool IsA(const GLCStrRef& name)
	{
		GLboolean result = OGLPLUS_GLFUNC(IsNamedStringARB)(
			GLint(name.size()),
			name.data()
		);
		OGLPLUS_CHECK_SIMPLE(IsNamedStringARB);
		return result == GL_TRUE;
	}

	/// Sets the @p value of the specified @p type in this NamedString
	void Set(NamedStringType type, const GLCStrRef& value)
	{
		Set(type, _name, value);
	}

	/// Sets the @p value of this NamedString
	GLString Get(void) const
	{
		return Get(_name);
	}

	/// Move-construction
	NamedString(NamedString&& tmp)
	 : _name(std::move(tmp._name))
	{ }

	/// Store a string @p value of the specified type under @p name
	NamedString(
		NamedStringType type,
		GLString&& name,
		const GLCStrRef& value
	): _name(std::move(name))
	{
		Set(type, value);
	}

	/// Delete this named string
	~NamedString(void)
	{
		if(!_name.empty())
		{
			Delete(_name);
		}
	}
};

/// Specialization of NamedString for ShaderInclude type.
class ShaderInclude
 : public NamedString
{
public:
	/// Create a shader include with the specified name and value
	ShaderInclude(GLString&& name, const GLCStrRef& value)
	 : NamedString(
		NamedStringType::ShaderInclude,
		std::move(name),
		value
	){ }

	ShaderInclude(ShaderInclude&& tmp)
	 : NamedString(static_cast<NamedString&&>(tmp))
	{ }

	/// Set a new value for this shader include
	void Set(const GLCStrRef& value)
	{
		return NamedString::Set(NamedStringType::ShaderInclude, value);
	}
};

} // namespace oglplus

#endif // GL_ARB_shading_language_include

#endif // include guard
