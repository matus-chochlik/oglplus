/**
 *  @file oglplus/context/blending.hpp
 *  @brief Wrappers for blending operations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_CONTEXT_BLENDING_1201040722_HPP
#define OGLPLUS_CONTEXT_BLENDING_1201040722_HPP

#include <oglplus/glfunc.hpp>
#include <oglplus/blend_function.hpp>

#ifdef RGB
#undef RGB
#endif

namespace oglplus {
namespace context {

struct BlendEquationSeparate
{
	GLint _v[2];

	BlendEquationSeparate(void)
	OGLPLUS_NOEXCEPT(true)
	{ }

	BlendEquationSeparate(BlendEquation rgb, BlendEquation alpha)
	OGLPLUS_NOEXCEPT(true)
	{
		_v[0] = GLint(GLenum(rgb));
		_v[1] = GLint(GLenum(alpha));
	}

	BlendEquation RGB(void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return BlendEquation(GLenum(_v[0]));
	}

	BlendEquation Alpha(void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return BlendEquation(GLenum(_v[1]));
	}

	bool Separate(void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return _v[0] != _v[1];
	}

	friend
	bool operator == (
		const BlendEquationSeparate& a,
		const BlendEquationSeparate& b
	) OGLPLUS_NOEXCEPT(true)
	{
		return (a._v[0] == b._v[0]) && (a._v[1] == b._v[1]);
	}

	friend
	bool operator != (
		const BlendEquationSeparate& a,
		const BlendEquationSeparate& b
	) OGLPLUS_NOEXCEPT(true)
	{
		return (a._v[0] != b._v[0]) || (a._v[1] != b._v[1]);
	}
};

/// Wrapper for blending operations
/**
 *  @ingroup ogl_context
 */
class BlendingOps
{
public:

#if OGLPLUS_DOCUMENTATION_ONLY || GL_KHR_blend_equation_advanced
	/// Specified boundaries between blending passes
	/**
	 *  @glsymbols
	 *  @glfunref{BlendBarrierKHR}
	 */
	static void BlendBarrier(void)
	{
		OGLPLUS_GLFUNC(BlendBarrierKHR)();
		OGLPLUS_VERIFY_SIMPLE(BlendBarrierKHR);
	}
#endif
};

/// Wrapper for blending operations
/**
 *  @ingroup ogl_context
 */
class BlendingState
{
public:
	/// Sets the blend equation
	/**
	 *  @glsymbols
	 *  @glfunref{BlendEquation}
	 */
	static void BlendEquation(
		OneOf<
			GLenum,
			std::tuple<
				oglplus::BlendEquation,
				oglplus::BlendEquationAdvanced
			>
		> eq
	)
	{
		OGLPLUS_GLFUNC(BlendEquation)(GLenum(eq));
		OGLPLUS_VERIFY_SIMPLE(BlendEquation);
	}

	/// Sets the blend equation separate for RGB and alpha
	/**
	 *  @glsymbols
	 *  @glfunref{BlendEquationSeparate}
	 */
	static void BlendEquationSeparate(
		oglplus::BlendEquation eq_rgb,
		oglplus::BlendEquation eq_alpha
	)
	{
		OGLPLUS_GLFUNC(BlendEquationSeparate)(
			GLenum(eq_rgb),
			GLenum(eq_alpha)
		);
		OGLPLUS_VERIFY_SIMPLE(BlendEquationSeparate);
	}

	static void BlendEquationSeparate(
		const oglplus::context::BlendEquationSeparate& eq
	)
	{
		OGLPLUS_GLFUNC(BlendEquationSeparate)(
			GLenum(eq._v[0]),
			GLenum(eq._v[1])
		);
		OGLPLUS_VERIFY_SIMPLE(BlendEquationSeparate);
	}

	static oglplus::context::BlendEquationSeparate BlendEquationSeparate(void)
	{
		oglplus::context::BlendEquationSeparate result;
		OGLPLUS_GLFUNC(GetIntegerv)(
			GL_BLEND_EQUATION_RGB,
			&result._v[0]
		);
		OGLPLUS_VERIFY_SIMPLE(GetIntegerv);
		OGLPLUS_GLFUNC(GetIntegerv)(
			GL_BLEND_EQUATION_ALPHA,
			&result._v[1]
		);
		OGLPLUS_VERIFY_SIMPLE(GetIntegerv);
		return result;
	}

	static oglplus::BlendEquation BlendEquationRGB(void)
	{
		GLint result;
		OGLPLUS_GLFUNC(GetIntegerv)(GL_BLEND_EQUATION_RGB, &result);
		OGLPLUS_VERIFY_SIMPLE(GetIntegerv);
		return oglplus::BlendEquation(GLenum(result));
	}

	static oglplus::BlendEquation BlendEquationAlpha(void)
	{
		GLint result;
		OGLPLUS_GLFUNC(GetIntegerv)(GL_BLEND_EQUATION_ALPHA, &result);
		OGLPLUS_VERIFY_SIMPLE(GetIntegerv);
		return oglplus::BlendEquation(GLenum(result));
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_0
	/// Sets the blend equation for a particular draw @p buffer
	/**
	 *  @glverreq{4,0}
	 *  @glsymbols
	 *  @glfunref{BlendEquationi}
	 */
	static void BlendEquation(
		GLuint buffer,
		OneOf<
			GLenum,
			std::tuple<
				oglplus::BlendEquation,
				oglplus::BlendEquationAdvanced
			>
		> eq
	)
	{
		OGLPLUS_GLFUNC(BlendEquationi)(buffer, GLenum(eq));
		OGLPLUS_VERIFY(
			BlendEquationi,
			Error,
			Index(buffer)
		);
	}

	/// Sets the blend equation separate for RGB and alpha for a @p buffer
	/**
	 *  @glverreq{4,0}
	 *  @glsymbols
	 *  @glfunref{BlendEquationSeparatei}
	 */
	static void BlendEquationSeparate(
		GLuint buffer,
		oglplus::BlendEquation eq_rgb,
		oglplus::BlendEquation eq_alpha
	)
	{
		OGLPLUS_GLFUNC(BlendEquationSeparatei)(
			buffer,
			GLenum(eq_rgb),
			GLenum(eq_alpha)
		);
		OGLPLUS_VERIFY(
			BlendEquationSeparatei,
			Error,
			Index(buffer)
		);
	}

	static void BlendEquationSeparate(
		GLuint buffer,
		const oglplus::context::BlendEquationSeparate& eq
	)
	{
		OGLPLUS_GLFUNC(BlendEquationSeparatei)(
			buffer,
			GLenum(eq._v[0]),
			GLenum(eq._v[1])
		);
		OGLPLUS_VERIFY(
			BlendEquationSeparatei,
			Error,
			Index(buffer)
		);
	}

	static oglplus::context::BlendEquationSeparate
	BlendEquationSeparate(GLuint buffer)
	{
		oglplus::context::BlendEquationSeparate result;
		OGLPLUS_GLFUNC(GetIntegeri_v)(
			GL_BLEND_EQUATION_RGB,
			buffer,
			&result._v[0]
		);
		OGLPLUS_CHECK(
			GetIntegeri_v,
			Error,
			Index(buffer)
		);
		OGLPLUS_GLFUNC(GetIntegeri_v)(
			GL_BLEND_EQUATION_ALPHA,
			buffer,
			&result._v[1]
		);
		OGLPLUS_CHECK(
			GetIntegeri_v,
			Error,
			Index(buffer)
		);
		return result;
	}

	static oglplus::BlendEquation BlendEquationRGB(GLuint buffer)
	{
		GLint result;
		OGLPLUS_GLFUNC(GetIntegeri_v)(
			GL_BLEND_EQUATION_RGB,
			buffer,
			&result
		);
		OGLPLUS_CHECK(
			GetIntegeri_v,
			Error,
			Index(buffer)
		);
		return oglplus::BlendEquation(GLenum(result));
	}

	static oglplus::BlendEquation BlendEquationAlpha(GLuint buffer)
	{
		GLint result;
		OGLPLUS_GLFUNC(GetIntegeri_v)(
			GL_BLEND_EQUATION_ALPHA,
			buffer,
			&result
		);
		OGLPLUS_CHECK(
			GetIntegeri_v,
			Error,
			Index(buffer)
		);
		return oglplus::BlendEquation(GLenum(result));
	}
#endif

	/// Sets the blend function
	/**
	 *  @glsymbols
	 *  @glfunref{BlendFunc}
	 */
	static void BlendFunc(BlendFunction src, BlendFunction dst)
	{
		OGLPLUS_GLFUNC(BlendFunc)(GLenum(src), GLenum(dst));
		OGLPLUS_VERIFY_SIMPLE(BlendFunc);
	}

	/// Sets the blend function separate for RGB and alpha
	/**
	 *  @glsymbols
	 *  @glfunref{BlendFuncSeparate}
	 */
	static void BlendFuncSeparate(
		BlendFunction src_rgb,
		BlendFunction dst_rgb,
		BlendFunction src_alpha,
		BlendFunction dst_alpha
	)
	{
		OGLPLUS_GLFUNC(BlendFuncSeparate)(
			GLenum(src_rgb),
			GLenum(dst_rgb),
			GLenum(src_alpha),
			GLenum(dst_alpha)
		);
		OGLPLUS_VERIFY_SIMPLE(BlendFuncSeparate);
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_0
	/// Sets the blend function for a particular @p buffer
	/**
	 *  @glverreq{4,0}
	 *  @glsymbols
	 *  @glfunref{BlendFunci}
	 */
	static void BlendFunc(
		GLuint buffer,
		BlendFunction src,
		BlendFunction dst
	)
	{
		OGLPLUS_GLFUNC(BlendFunci)(buffer, GLenum(src), GLenum(dst));
		OGLPLUS_VERIFY(
			BlendFunci,
			Error,
			Index(buffer)
		);
	}

	/// Sets the blend function separate for RGB and alpha for a @p buffer
	/**
	 *  @glverreq{4,0}
	 *  @glsymbols
	 *  @glfunref{BlendFuncSeparatei}
	 */
	static void BlendFuncSeparate(
		GLuint buffer,
		BlendFunction src_rgb,
		BlendFunction dst_rgb,
		BlendFunction src_alpha,
		BlendFunction dst_alpha
	)
	{
		OGLPLUS_GLFUNC(BlendFuncSeparatei)(
			buffer,
			GLenum(src_rgb),
			GLenum(dst_rgb),
			GLenum(src_alpha),
			GLenum(dst_alpha)
		);
		OGLPLUS_VERIFY(
			BlendFuncSeparatei,
			Error,
			Index(buffer)
		);
	}
#endif

	/// Sets the blend color
	/**
	 *  @glsymbols
	 *  @glfunref{BlendColor}
	 */
	static void BlendColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a)
	{
		OGLPLUS_GLFUNC(BlendColor)(r, g, b, a);
		OGLPLUS_VERIFY_SIMPLE(BlendColor);
	}
};

} // namespace context
} // namespace oglplus

#endif // include guard
