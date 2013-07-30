/**
 *  @file oglplus/ext/EXT_direct_state_access.hpp
 *  @brief Wrapper for a subset of the EXT_direct_state_access extension
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_EXT_EXT_DIRECT_STATE_ACCESS_1203031902_HPP
#define OGLPLUS_EXT_EXT_DIRECT_STATE_ACCESS_1203031902_HPP

#include <oglplus/extension.hpp>
#include <oglplus/ext/ARB_compatibility.hpp>
#include <oglplus/angle.hpp>
#include <oglplus/texture.hpp>
#include <oglplus/bitfield.hpp>

namespace oglplus {

#if OGLPLUS_DOCUMENTATION_ONLY || GL_EXT_direct_state_access

/// Wrapper around context direct state access operations
/**
 *  @note Do not use this class directly use EXT_direct_state_access instead.
 */
struct DSAContextEXT
{
	/// Resets specified client attribute group variables to default values
	/**
	 *  @glsymbols
	 *  @glfunref{ClientAttribDefaultEXT}
	 */
	static void ClientAttribDefault(
		Bitfield<CompatibilityClientAttributeGroup> attrib_groups
	)
	{
		OGLPLUS_GLFUNC(ClientAttribDefaultEXT)(
			GLbitfield(attrib_groups)
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(ClientAttribDefaultEXT));
	}

	/// Pushes specified client attribute group variables on the stack
	/**
	 *  @glsymbols
	 *  @glfunref{PushClientAttribDefaultEXT}
	 */
	static void PushClientAttribDefault(
		Bitfield<CompatibilityClientAttributeGroup> attrib_groups
	)
	{
		OGLPLUS_GLFUNC(PushClientAttribDefaultEXT)(
			GLbitfield(attrib_groups)
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(PushClientAttribDefaultEXT));
	}
};

/// Wrapper around matrix direct state access operations
/**
 *  @note Do not use this class directly use EXT_direct_state_access instead.
 */
struct DSAMatrixEXT
{
	/// Pushes a matrix on the stack specified by @p matrix_mode
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixPushEXT}
	 */
	static void MatrixPush(CompatibilityMatrixMode matrix_mode)
	{
		OGLPLUS_GLFUNC(MatrixPushEXT)(GLenum(matrix_mode));
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixPushEXT));
	}

	/// Pops a matrix from the stack specified by @p matrix_mode
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixPopEXT}
	 */
	static void MatrixPop(CompatibilityMatrixMode matrix_mode)
	{
		OGLPLUS_GLFUNC(MatrixPopEXT)(GLenum(matrix_mode));
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixPopEXT));
	}

	/// Loads a identity matrix
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixLoadIdentityEXT}
	 */
	static void MatrixLoadIdentity(CompatibilityMatrixMode matrix_mode)
	{
		OGLPLUS_GLFUNC(MatrixLoadIdentityEXT)(GLenum(matrix_mode));
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixLoadIdentityEXT));
	}

	/// Loads the specified @p matrix
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixLoadTransposeEXT}
	 */
	static void MatrixLoad(
		CompatibilityMatrixMode matrix_mode,
		const Mat4f& matrix
	)
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
	static void MatrixLoad(
		CompatibilityMatrixMode matrix_mode,
		const Mat4d& matrix
	)
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
	static void MatrixMult(
		CompatibilityMatrixMode matrix_mode,
		const Mat4f& matrix
	)
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
	static void MatrixMult(
		CompatibilityMatrixMode matrix_mode,
		const Mat4d& matrix
	)
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
	static void MatrixRotate(
		CompatibilityMatrixMode matrix_mode,
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
	static void MatrixRotate(
		CompatibilityMatrixMode matrix_mode,
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
	static void MatrixRotate(
		CompatibilityMatrixMode matrix_mode,
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
	static void MatrixScale(
		CompatibilityMatrixMode matrix_mode,
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
	static void MatrixScale(
		CompatibilityMatrixMode matrix_mode,
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
	static void MatrixScale(
		CompatibilityMatrixMode matrix_mode,
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
	static void MatrixTranslate(
		CompatibilityMatrixMode matrix_mode,
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
	static void MatrixTranslate(
		CompatibilityMatrixMode matrix_mode,
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
	static void MatrixTranslate(
		CompatibilityMatrixMode matrix_mode,
		const Vector<GLdouble, 3>& amount
	)
	{
		OGLPLUS_GLFUNC(MatrixTranslatedEXT)(
			GLenum(matrix_mode),
			amount.x(), amount.y(), amount.z()
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixTranslatedEXT));
	}

	/// Makes an ortho-matrix from the matrix specified by @p matrix_mode
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixOrthoEXT}
	 */
	static void MatrixOrtho(
		CompatibilityMatrixMode matrix_mode,
		GLdouble left,
		GLdouble right,
		GLdouble bottom,
		GLdouble top,
		GLdouble near_depth,
		GLdouble far_depth
	)
	{
		OGLPLUS_GLFUNC(MatrixOrthoEXT)(
			GLenum(matrix_mode),
			left,
			right,
			bottom,
			top,
			near_depth,
			far_depth
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixOrthoEXT));
	}

	/// Makes a frustum-matrix from the matrix specified by @p matrix_mode
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixFrustumEXT}
	 */
	static void MatrixFrustum(
		CompatibilityMatrixMode matrix_mode,
		GLdouble left,
		GLdouble right,
		GLdouble bottom,
		GLdouble top,
		GLdouble near_depth,
		GLdouble far_depth
	)
	{
		OGLPLUS_GLFUNC(MatrixFrustumEXT)(
			GLenum(matrix_mode),
			left,
			right,
			bottom,
			top,
			near_depth,
			far_depth
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixFrustumEXT));
	}
};

/// Wrapper for the EXT_direct_state_access extension
/**
 *  @glsymbols
 *  @glextref{EXT,direct_state_access}
 *
 *  @ingroup gl_extensions
 */
class EXT_direct_state_access
 : public DSAContextEXT
 , public DSAMatrixEXT
{
public:
	OGLPLUS_EXTENSION_CLASS(EXT, direct_state_access)
};
#endif

} // namespace oglplus

#endif // include guard
