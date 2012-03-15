/**
 *  @file oglplus/ext/ARB_compatibility.hpp
 *  @brief Wrapper for the ARB_compatibility extension
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_EXT_ARB_COMPATIBILITY_1203031902_HPP
#define OGLPLUS_EXT_ARB_COMPATIBILITY_1203031902_HPP

#include <oglplus/extension.hpp>

namespace oglplus {

/// Compatibility primitive type enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{Begin}
 *  @glextref{ARB,compatibility}
 */
enum class CompatibilityPrimitiveType : GLenum
{
#include <oglplus/enums/ext/compat_prim_type.ipp>
};

/// Shorter name for CompatibilityPrimitiveType
typedef CompatibilityPrimitiveType CompatPrimType;

inline const GLchar* EnumValueName(CompatibilityPrimitiveType value)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/ext/compat_prim_type.ipp>
#endif
	return "";
}

/// Compatibility matrix mode enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{MatrixMode}
 *  @glextref{ARB,compatibility}
 */
enum class MatrixMode : GLenum
{
#include <oglplus/enums/ext/compat_matrix_mode.ipp>
};

inline const GLchar* EnumValueName(MatrixMode value)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/ext/compat_matrix_mode.ipp>
#endif
	return "";
}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_ARB_compatibility
/// Wrapper for the ARB_compatibility extension
/**
 *  @glsymbols
 *  @glextref{ARB,compatibility}
 *
 *  @ingroup extensions
 */
class ARB_compatibility
{
public:
	OGLPLUS_EXTENSION_CLASS(ARB, compatibility)

	/// Begins geometric object specification
	/**
	 *  @glsymbols
	 *  @glfunref{Begin}
	 */
	static void Begin(CompatibilityPrimitiveType mode)
	{
		OGLPLUS_GLFUNC(Begin)(GLenum(mode));
	}

	/// Ends geometric object specification
	/**
	 *  @glsymbols
	 *  @glfunref{End}
	 */
	static void End(void)
	{
		OGLPLUS_GLFUNC(End)();
		AssertNoError(OGLPLUS_ERROR_INFO(End));
	}

	/// Sets the matrix mode for the subsequent commands
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixMode}
	 */
	static void MatrixMode(oglplus::MatrixMode mode)
	{
		OGLPLUS_GLFUNC(MatrixMode)(GLenum(mode));
		AssertNoError(OGLPLUS_ERROR_INFO(MatrixMode));
	}

	/// Loads a identity matrix
	/**
	 *  @glsymbols
	 *  @glfunref{LoadIdentity}
	 */
	static void LoadIdentity(void)
	{
		OGLPLUS_GLFUNC(LoadIdentity)();
	}

private:
	static void _Vertex(GLint x, GLint y)
	{
		OGLPLUS_GLFUNC(Vertex2i)(x, y);
	}

	static void _Vertex(GLint x, GLint y, GLint z)
	{
		OGLPLUS_GLFUNC(Vertex3i)(x, y, z);
	}

	static void _Vertex(GLint x, GLint y, GLint z, GLint w)
	{
		OGLPLUS_GLFUNC(Vertex4i)(x, y, z, w);
	}

	static void _Vertex(GLfloat x, GLfloat y)
	{
		OGLPLUS_GLFUNC(Vertex2f)(x, y);
	}

	static void _Vertex(GLfloat x, GLfloat y, GLfloat z)
	{
		OGLPLUS_GLFUNC(Vertex3f)(x, y, z);
	}

	static void _Vertex(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
	{
		OGLPLUS_GLFUNC(Vertex4f)(x, y, z, w);
	}

	static void _Vertex(GLdouble x, GLdouble y)
	{
		OGLPLUS_GLFUNC(Vertex2d)(x, y);
	}

	static void _Vertex(GLdouble x, GLdouble y, GLdouble z)
	{
		OGLPLUS_GLFUNC(Vertex3d)(x, y, z);
	}

	static void _Vertex(GLdouble x, GLdouble y, GLdouble z, GLdouble w)
	{
		OGLPLUS_GLFUNC(Vertex4d)(x, y, z, w);
	}
public:
	/// Specifies vertex position x,y coordinates
	/**
	 *  @glsymbols
	 *  @glfunref{Vertex}
	 */
	template <typename Type>
	static void Vertex(Type x, Type y)
	{
		_Vertex(x, y);
	}

	/// Specifies vertex position x,y,z coordinates
	/**
	 *  @glsymbols
	 *  @glfunref{Vertex}
	 */
	template <typename Type>
	static void Vertex(Type x, Type y, Type z)
	{
		_Vertex(x, y, z);
	}

	/// Specifies vertex position x,y,z,w coordinates
	/**
	 *  @glsymbols
	 *  @glfunref{Vertex}
	 */
	template <typename Type>
	static void Vertex(Type x, Type y, Type z, Type w)
	{
		_Vertex(x, y, z, w);
	}

private:
	static void _Color(GLint r, GLint g, GLint b)
	{
		OGLPLUS_GLFUNC(Color3i)(r, g, b);
	}

	static void _Color(GLint r, GLint g, GLint b, GLint a)
	{
		OGLPLUS_GLFUNC(Color4i)(r, g, b, a);
	}

	static void _Color(GLfloat r, GLfloat g, GLfloat b)
	{
		OGLPLUS_GLFUNC(Color3f)(r, g, b);
	}

	static void _Color(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
	{
		OGLPLUS_GLFUNC(Color4f)(r, g, b, a);
	}

	static void _Color(GLdouble r, GLdouble g, GLdouble b)
	{
		OGLPLUS_GLFUNC(Color3d)(r, g, b);
	}

	static void _Color(GLdouble r, GLdouble g, GLdouble b, GLdouble a)
	{
		OGLPLUS_GLFUNC(Color4d)(r, g, b, a);
	}
public:
	/// Specifies vertex r,g,b color components
	/**
	 *  @glsymbols
	 *  @glfunref{Color}
	 */
	template <typename Type>
	static void Color(Type r, Type g, Type b)
	{
		_Color(r, g, b);
	}

	/// Specifies vertex r,g,b,a color components
	/**
	 *  @glsymbols
	 *  @glfunref{Color}
	 */
	template <typename Type>
	static void Color(Type r, Type g, Type b, Type a)
	{
		_Color(r, g, b, a);
	}
};
#endif

} // namespace oglplus

#endif // include guard
