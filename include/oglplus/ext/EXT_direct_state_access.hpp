/**
 *  @file oglplus/ext/EXT_direct_state_access.hpp
 *  @brief Wrapper for the EXT_direct_state_access extension
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_EXT_EXT_DIRECT_STATE_ACCESS_1203031902_HPP
#define OGLPLUS_EXT_EXT_DIRECT_STATE_ACCESS_1203031902_HPP

#include <oglplus/extension.hpp>
#include <oglplus/ext/ARB_compatibility.hpp>
#include <oglplus/angle.hpp>

namespace oglplus {
namespace context {

struct DSAMatrixEXT
{
	/// Pushes a matrix on the stack specified by @p matrix_mode
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixPushEXT}
	 */
	static void Push(MatrixMode matrix_mode)
	{
		OGLPLUS_GLFUNC(MatrixPushEXT)(GLenum(matrix_mode));
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixPushEXT));
	}

	/// Pops a matrix from the stack specified by @p matrix_mode
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixPopEXT}
	 */
	static void Pop(MatrixMode matrix_mode)
	{
		OGLPLUS_GLFUNC(MatrixPopEXT)(GLenum(matrix_mode));
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixPopEXT));
	}

	/// Loads a identity matrix
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixLoadIdentityEXT}
	 */
	static void LoadIdentity(MatrixMode matrix_mode)
	{
		OGLPLUS_GLFUNC(MatrixLoadIdentityEXT)(GLenum(matrix_mode));
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixLoadIdentityEXT));
	}

	/// Loads the specified @p matrix
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixLoadTransposeEXT}
	 */
	static void Load(MatrixMode matrix_mode, const Mat4f& matrix)
	{
		OGLPLUS_GLFUNC(MatrixLoadTransposefEXT)(
			GLenum(matrix_mode),
			Data(matrix)
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixLoadTransposefEXT));
	}

	/// Loads the specified @p matrix
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixLoadTransposeEXT}
	 */
	static void Load(MatrixMode matrix_mode, const Mat4d& matrix)
	{
		OGLPLUS_GLFUNC(MatrixLoadTransposedEXT)(
			GLenum(matrix_mode),
			Data(matrix)
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixLoadTransposedEXT));
	}

	/// Multiplies the current matrix by the specified @p matrix
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixMultTransposeEXT}
	 */
	static void Mult(MatrixMode matrix_mode, const Mat4f& matrix)
	{
		OGLPLUS_GLFUNC(MatrixMultTransposefEXT)(
			GLenum(matrix_mode),
			Data(matrix)
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixMultTransposefEXT));
	}

	/// Multiplies the current matrix by the specified @p matrix
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixMultTransposeEXT}
	 */
	static void Mult(MatrixMode matrix_mode, const Mat4d& matrix)
	{
		OGLPLUS_GLFUNC(MatrixMultTransposedEXT)(
			GLenum(matrix_mode),
			Data(matrix)
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixMultTransposedEXT));
	}

	/// Applies rotation to the matrix specified by @p matrix_mode
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixRotateEXT}
	 */
	static void Rotate(
		MatrixMode matrix_mode,
		Angle<GLfloat> angle,
		const GLfloat x,
		const GLfloat y,
		const GLfloat z
	)
	{
		OGLPLUS_GLFUNC(MatrixRotatefEXT)(
			GLenum(matrix_mode),
			angle.ValueInDegrees(),
			x, y, z
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixRotatefEXT));
	}

	/// Applies rotation to the matrix specified by @p matrix_mode
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixRotateEXT}
	 */
	static void Rotate(
		MatrixMode matrix_mode,
		Angle<GLfloat> angle,
		const Vector<GLfloat, 3>& axis
	)
	{
		OGLPLUS_GLFUNC(MatrixRotatefEXT)(
			GLenum(matrix_mode),
			angle.ValueInDegrees(),
			axis.x(), axis.y(), axis.z()
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixRotatefEXT));
	}

	/// Applies rotation to the matrix specified by @p matrix_mode
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixRotateEXT}
	 */
	static void Rotate(
		MatrixMode matrix_mode,
		Angle<GLdouble> angle,
		const Vector<GLdouble, 3>& axis
	)
	{
		OGLPLUS_GLFUNC(MatrixRotatedEXT)(
			GLenum(matrix_mode),
			angle.ValueInDegrees(),
			axis.x(), axis.y(), axis.z()
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixRotatedEXT));
	}

	/// Scales the matrix specified by @p matrix_mode
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixScaleEXT}
	 */
	static void Scale(
		MatrixMode matrix_mode,
		const GLfloat x,
		const GLfloat y,
		const GLfloat z
	)
	{
		OGLPLUS_GLFUNC(MatrixScalefEXT)(
			GLenum(matrix_mode),
			x, y, z
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixScalefEXT));
	}

	/// Scales the matrix specified by @p matrix_mode
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixScaleEXT}
	 */
	static void Scale(
		MatrixMode matrix_mode,
		const Vector<GLfloat, 3>& amount
	)
	{
		OGLPLUS_GLFUNC(MatrixScalefEXT)(
			GLenum(matrix_mode),
			amount.x(), amount.y(), amount.z()
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixScalefEXT));
	}

	/// Scales the matrix specified by @p matrix_mode
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixScaleEXT}
	 */
	static void Scale(
		MatrixMode matrix_mode,
		const Vector<GLdouble, 3>& amount
	)
	{
		OGLPLUS_GLFUNC(MatrixScaledEXT)(
			GLenum(matrix_mode),
			amount.x(), amount.y(), amount.z()
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixScaledEXT));
	}

	/// Applies translation to the matrix specified by @p matrix_mode
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixTranslateEXT}
	 */
	static void Translate(
		MatrixMode matrix_mode,
		const GLfloat x,
		const GLfloat y,
		const GLfloat z
	)
	{
		OGLPLUS_GLFUNC(MatrixTranslatefEXT)(
			GLenum(matrix_mode),
			x, y, z
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixTranslatefEXT));
	}

	/// Applies translation the matrix specified by @p matrix_mode
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixTranslateEXT}
	 */
	static void Translate(
		MatrixMode matrix_mode,
		const Vector<GLfloat, 3>& amount
	)
	{
		OGLPLUS_GLFUNC(MatrixTranslatefEXT)(
			GLenum(matrix_mode),
			amount.x(), amount.y(), amount.z()
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixTranslatefEXT));
	}

	/// Applies translation the matrix specified by @p matrix_mode
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixTranslateEXT}
	 */
	static void Translate(
		MatrixMode matrix_mode,
		const Vector<GLdouble, 3>& amount
	)
	{
		OGLPLUS_GLFUNC(MatrixTranslatedEXT)(
			GLenum(matrix_mode),
			amount.x(), amount.y(), amount.z()
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixTranslatedEXT));
	}

	/// Makes a ortho-matrix from the matrix specified by @p matrix_mode
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixOrthoEXT}
	 */
	static void Ortho(
		MatrixMode matrix_mode,
		GLdouble left,
		GLdouble right,
		GLdouble bottom,
		GLdouble top,
		GLdouble near,
		GLdouble far
	)
	{
		OGLPLUS_GLFUNC(MatrixOrthoEXT)(
			GLenum(matrix_mode),
			left,
			right,
			bottom,
			top,
			near,
			far
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixOrthoEXT));
	}

	/// Makes a frustum-matrix from the matrix specified by @p matrix_mode
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixFrustumEXT}
	 */
	static void Frustum(
		MatrixMode matrix_mode,
		GLdouble left,
		GLdouble right,
		GLdouble bottom,
		GLdouble top,
		GLdouble near,
		GLdouble far
	)
	{
		OGLPLUS_GLFUNC(MatrixFrustumEXT)(
			GLenum(matrix_mode),
			left,
			right,
			bottom,
			top,
			near,
			far
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixFrustumEXT));
	}
};

} // namespace context

#if OGLPLUS_DOCUMENTATION_ONLY || GL_EXT_direct_state_access
/// Wrapper for the EXT_direct_state_access extension
/**
 *  @glsymbols
 *  @glextref{EXT,direct_state_access}
 *
 *  @ingroup extensions
 */
class EXT_direct_state_access
{
public:
	OGLPLUS_EXTENSION_CLASS(EXT, direct_state_access)

	/// Returns the wrapper around matrix operations
	static oglplus::context::DSAMatrixEXT Matrix(void)
	{
		return oglplus::context::DSAMatrixEXT();
	}
};
#endif

} // namespace oglplus

#endif // include guard
