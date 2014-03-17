/**
 *  @file oglplus/ext/EXT_direct_state_acccess/matrix.hpp
 *  @brief Direct state access of compatibility matrix stack
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_EXT_DSA_MATRIX_1107121519_HPP
#define OGLPLUS_EXT_DSA_MATRIX_1107121519_HPP

#include <oglplus/fwd.hpp>
#include <oglplus/ext/ARB_compatibility.hpp>

namespace oglplus {

#if OGLPLUS_DOCUMENTATION_ONLY || GL_EXT_direct_state_access

/// Wrapper for direct-state-access compatibility matrix operations
/**
 *  @glextreq{EXT,direct_state_access}
 */
class DSAMatrixEXT
{
private:
	CompatibilityMatrixMode _mode;
public:
	/// The matrix mode enumeration
	typedef CompatibilityMatrixMode Mode;

	/// Constructs a new compatibility DSA matrix
	DSAMatrixEXT(Mode mode)
	 : _mode(mode)
	{ }

	/// Pushes a matrix on the stack
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixPushEXT}
	 */
	void Push(void)
	{
		OGLPLUS_GLFUNC(MatrixPushEXT)(GLenum(_mode));
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixPushEXT));
	}

	/// Pops a matrix from the stack
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixPopEXT}
	 */
	void Pop(void)
	{
		OGLPLUS_GLFUNC(MatrixPopEXT)(GLenum(_mode));
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixPopEXT));
	}

	/// Loads an identity matrix
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixLoadIdentityEXT}
	 */
	void LoadIdentity(void)
	{
		OGLPLUS_GLFUNC(MatrixLoadIdentityEXT)(GLenum(_mode));
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixLoadIdentityEXT));
	}

	/// Loads the specified @p matrix
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixLoadTransposeEXT}
	 */
	void Load(const Matrix<GLfloat, 4, 4>& matrix)
	{
		OGLPLUS_GLFUNC(MatrixLoadTransposefEXT)(
			GLenum(_mode),
			Data(matrix)
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixLoadTransposefEXT));
	}

	/// Loads the specified @p matrix
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixLoadTransposeEXT}
	 */
	void Load(const Matrix<GLdouble, 4, 4>& matrix)
	{
		OGLPLUS_GLFUNC(MatrixLoadTransposedEXT)(
			GLenum(_mode),
			Data(matrix)
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixLoadTransposedEXT));
	}

	/// Multiplies the current matrix by the specified @p matrix
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixMultTransposeEXT}
	 */
	void Mult(const Matrix<GLfloat, 4, 4>& matrix)
	{
		OGLPLUS_GLFUNC(MatrixMultTransposefEXT)(
			GLenum(_mode),
			Data(matrix)
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixMultTransposefEXT));
	}

	/// Multiplies the current matrix by the specified @p matrix
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixMultTransposeEXT}
	 */
	void Mult(const Matrix<GLdouble, 4, 4>& matrix)
	{
		OGLPLUS_GLFUNC(MatrixMultTransposedEXT)(
			GLenum(_mode),
			Data(matrix)
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixMultTransposedEXT));
	}

	/// Applies rotation by angle around axis <x,y,z> to the current matrix
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixRotateEXT}
	 */
	void Rotate(
		Angle<GLfloat> angle,
		const GLfloat x,
		const GLfloat y,
		const GLfloat z
	)
	{
		OGLPLUS_GLFUNC(MatrixRotatefEXT)(
			GLenum(_mode),
			Degrees(angle),
			x, y, z
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixRotatefEXT));
	}

	/// Applies rotation by angle around axis to the current matrix
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixRotateEXT}
	 */
	void Rotate(Angle<GLfloat> angle, const Vector<GLfloat, 3>& axis)
	{
		OGLPLUS_GLFUNC(MatrixRotatefEXT)(
			GLenum(_mode),
			Degrees(angle),
			At(axis, 0),
			At(axis, 1),
			At(axis, 2)
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixRotatefEXT));
	}

	/// Applies rotation by angle around axis to the current matrix
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixRotateEXT}
	 */
	void Rotate(Angle<GLdouble> angle, const Vector<GLdouble, 3>& axis)
	{
		OGLPLUS_GLFUNC(MatrixRotatedEXT)(
			GLenum(_mode),
			Degrees(angle),
			At(axis, 0),
			At(axis, 1),
			At(axis, 2)
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixRotatedEXT));
	}

	/// Scales the current matrix
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixScaleEXT}
	 */
	void Scale(const GLfloat x, const GLfloat y, const GLfloat z)
	{
		OGLPLUS_GLFUNC(MatrixScalefEXT)(GLenum(_mode), x, y, z);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixScalefEXT));
	}

	/// Scales the current matrix
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixScaleEXT}
	 */
	void Scale(const Vector<GLfloat, 3>& amount)
	{
		OGLPLUS_GLFUNC(MatrixScalefEXT)(
			GLenum(_mode),
			At(amount, 0),
			At(amount, 1),
			At(amount, 2)
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixScalefEXT));
	}

	/// Scales the current matrix
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixScaleEXT}
	 */
	void Scale(const Vector<GLdouble, 3>& amount)
	{
		OGLPLUS_GLFUNC(MatrixScalefEXT)(
			GLenum(_mode),
			At(amount, 0),
			At(amount, 1),
			At(amount, 2)
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixScaledEXT));
	}

	/// Translates the current matrix
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixTranslateEXT}
	 */
	void Translate(const GLfloat x, const GLfloat y, const GLfloat z)
	{
		OGLPLUS_GLFUNC(MatrixTranslatefEXT)(GLenum(_mode), x, y, z);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixTranslatefEXT));
	}

	/// Translates the current matrix
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixTranslateEXT}
	 */
	void Translate(const Vector<GLfloat, 3>& amount)
	{
		OGLPLUS_GLFUNC(MatrixTranslatefEXT)(
			GLenum(_mode),
			At(amount, 0),
			At(amount, 1),
			At(amount, 2)
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixTranslatefEXT));
	}

	/// Translates the current matrix
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixTranslateEXT}
	 */
	void Translate(const Vector<GLdouble, 3>& amount)
	{
		OGLPLUS_GLFUNC(MatrixTranslatefEXT)(
			GLenum(_mode),
			At(amount, 0),
			At(amount, 1),
			At(amount, 2)
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixTranslatedEXT));
	}

	/// Makes an ortho-matrix from the current matrix
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixOrthoEXT}
	 */
	void Ortho(
		GLdouble left,
		GLdouble right,
		GLdouble bottom,
		GLdouble top,
		GLdouble near_depth,
		GLdouble far_depth
	)
	{
		OGLPLUS_GLFUNC(MatrixOrthoEXT)(
			GLenum(_mode),
			left,
			right,
			bottom,
			top,
			near_depth,
			far_depth
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixOrthoEXT));
	}

	/// Makes a frustum-matrix from the current matrix
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixFrustumEXT}
	 */
	void Frustum(
		GLdouble left,
		GLdouble right,
		GLdouble bottom,
		GLdouble top,
		GLdouble near_depth,
		GLdouble far_depth
	)
	{
		OGLPLUS_GLFUNC(MatrixFrustumEXT)(
			GLenum(_mode),
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

/// Wrapper for direct-state-access compatibility modelview matrix operations
class DSAModelviewMatrixEXT
 : public DSAMatrixEXT
{
public:
	DSAModelviewMatrixEXT(void)
	 : DSAMatrixEXT(CompatibilityMatrixMode::Modelview)
	{ }
};

/// Wrapper for direct-state-access compatibility projection matrix operations
class DSAProjectionMatrixEXT
 : public DSAMatrixEXT
{
public:
	DSAProjectionMatrixEXT(void)
	 : DSAMatrixEXT(CompatibilityMatrixMode::Projection)
	{ }
};

#endif // GL_EXT_direct_state_access

} // namespace oglplus

#endif // include guard
