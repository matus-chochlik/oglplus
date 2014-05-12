/**
 *  @file oglplus/ext/NV_path_rendering/path.hpp
 *  @brief Wrapper for the NV_path_rendering path class
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_EXT_NV_PATH_RENDERING_PATH_1203031902_HPP
#define OGLPLUS_EXT_NV_PATH_RENDERING_PATH_1203031902_HPP

#if OGLPLUS_DOCUMENTATION_ONLY || GL_NV_path_rendering

#include <oglplus/string/ref.hpp>
#include <oglplus/error/object.hpp>
#include <oglplus/object/wrapper.hpp>
#include <oglplus/data_type.hpp>

#include <oglplus/ext/NV_path_rendering/command.hpp>
#include <oglplus/ext/NV_path_rendering/format.hpp>
#include <oglplus/ext/NV_path_rendering/fill_mode.hpp>
#include <oglplus/ext/NV_path_rendering/fill_cover_mode.hpp>
#include <oglplus/ext/NV_path_rendering/stroke_cover_mode.hpp>
#include <oglplus/ext/NV_path_rendering/join_style.hpp>
#include <oglplus/ext/NV_path_rendering/cap_style.hpp>
#include <oglplus/ext/NV_path_rendering/dash_offset_reset.hpp>
#include <oglplus/ext/NV_path_rendering/transform_type.hpp>
#if !OGLPLUS_NO_VARIADIC_TEMPLATES
#include <oglplus/ext/NV_path_rendering/path_spec.hpp>
#endif

#include <vector>

namespace oglplus {

/// Class wrapping NV path construction/destruction functions
/** @note Do not use this class directly, use PathNV instead.
 *
 *  @glsymbols
 *  @glfunref{GenPathsNV}
 *  @glfunref{DeletePathsNV}
 *  @glfunref{IsPathNV}
 */
template <>
class ObjGenDelOps<tag::PathNV>
{
protected:
	static void Gen(GLsizei count, GLuint* names)
	{
		assert(names != nullptr);
		GLuint base = OGLPLUS_GLFUNC(GenPathsNV)(count);
		for(GLsizei i=0; i!=count; ++i)
			names[i] = base+i;
		OGLPLUS_CHECK_SIMPLE(GenPathsNV);
	}

	static void Delete(GLsizei count, GLuint* names)
	{
		assert(names != nullptr);
		OGLPLUS_GLFUNC(DeletePathsNV)(count, *names);
		OGLPLUS_VERIFY_SIMPLE(DeletePathsNV);
	}

	static GLboolean IsA(GLuint name)
	{
		assert(name != 0);
		GLboolean result = OGLPLUS_GLFUNC(IsPathNV)(name);
		OGLPLUS_VERIFY_SIMPLE(IsPathNV);
		return result;
	}
};

/// Class wrapping NV-path functions (with direct state access)
/** @note Do not use this class directly, use PathNV instead.
 */
template <>
class ObjectOps<tag::DirectState, tag::PathNV>
 : public ObjZeroOps<tag::DirectState, tag::PathNV>
{
protected:
	ObjectOps(void){ }
public:
	/// Specifies the path via a sequence of commands and coordinates
	/**
	 *  @glsymbols
	 *  @glfunref{PathCommandsNV}
	 */
	template <typename CoordType>
	ObjectOps& Commands(
		GLsizei num_commands,
		const PathNVCommand* commands,
		GLsizei num_coords,
		const CoordType* coords
	)
	{
		OGLPLUS_GLFUNC(PathCommandsNV)(
			this->_name,
			num_commands,
			(const GLubyte*)commands,
			num_coords,
			GLenum(GetDataType<CoordType>()),
			(const void*)coords
		);
		OGLPLUS_CHECK(
			PathCommandsNV,
			ObjectError,
			Object(*this)
		);
		return *this;
	}

	/// Specifies the path via a sequence of commands and coordinates
	/**
	 *  @glsymbols
	 *  @glfunref{PathCommandsNV}
	 */
	template <typename CoordType>
	ObjectOps& Commands(
		const std::vector<PathNVCommand>& commands,
		const std::vector<CoordType>& coords
	)
	{
		OGLPLUS_GLFUNC(PathCommandsNV)(
			this->_name,
			GLsizei(commands.size()),
			(const GLubyte*)commands.data(),
			GLsizei(coords.size()),
			GLenum(GetDataType<CoordType>()),
			(const void*)coords.data()
		);
		OGLPLUS_CHECK(
			PathCommandsNV,
			ObjectError,
			Object(*this)
		);
		return *this;
	}

#if OGLPLUS_DOCUMENTATION_ONLY || !OGLPLUS_NO_VARIADIC_TEMPLATES
	/// Specifies the path via the PathNVSpec class
	/**
	 *  @see PathNVSpec
	 *
	 *  @glsymbols
	 *  @glfunref{PathCommandsNV}
	 */
	template <typename CoordType>
	ObjectOps& Spec(const PathNVSpec<CoordType>& spec)
	{
		return Commands<CoordType>(spec._commands, spec._coords);
	}
#endif

	/// Specifies the path via a sequence of coordinates
	/**
	 *  @glsymbols
	 *  @glfunref{PathCoordsNV}
	 */
	template <typename CoordType>
	ObjectOps& Coords(GLsizei num_coords, const CoordType* coords)
	{
		OGLPLUS_GLFUNC(PathCoordsNV)(
			this->_name,
			num_coords,
			GLenum(GetDataType<CoordType>()),
			static_cast<const void*>(coords)
		);
		OGLPLUS_CHECK(
			PathCoordsNV,
			ObjectError,
			Object(*this)
		);
		return *this;
	}

	/// Specifies the path via a sequence of coordinates
	/**
	 *  @glsymbols
	 *  @glfunref{PathCoordsNV}
	 */
	template <typename CoordType>
	ObjectOps& Coords(const std::vector<CoordType>& coords)
	{
		OGLPLUS_GLFUNC(PathCoordsNV)(
			this->_name,
			GLsizei(coords.size()),
			GLenum(GetDataType<CoordType>()),
			(const void*)coords.data()
		);
		OGLPLUS_CHECK(
			PathCoordsNV,
			ObjectError,
			Object(*this)
		);
		return *this;
	}

	/// Replaces a part of the the path with new commands and coordinates
	/**
	 *  @glsymbols
	 *  @glfunref{PathSubCommandsNV}
	 */
	template <typename CoordType>
	ObjectOps& SubCommands(
		GLsizei command_start,
		GLsizei commands_to_delete,
		GLsizei num_commands,
		const PathNVCommand* commands,
		GLsizei num_coords,
		const CoordType* coords
	)
	{
		OGLPLUS_GLFUNC(PathSubCommandsNV)(
			this->_name,
			command_start,
			commands_to_delete,
			num_commands,
			(const GLubyte*)commands,
			num_coords,
			GLenum(GetDataType<CoordType>()),
			(const void*)coords
		);
		OGLPLUS_CHECK(
			PathSubCommandsNV,
			ObjectError,
			Object(*this)
		);
		return *this;
	}

	/// Replaces a part of the the path with new commands and coordinates
	/**
	 *  @glsymbols
	 *  @glfunref{PathSubCommandsNV}
	 */
	template <typename CoordType>
	ObjectOps& SubCommands(
		GLsizei command_start,
		GLsizei commands_to_delete,
		const std::vector<PathNVCommand>& commands,
		const std::vector<CoordType>& coords
	)
	{
		OGLPLUS_GLFUNC(PathSubCommandsNV)(
			this->_name,
			command_start,
			commands_to_delete,
			GLsizei(commands.size()),
			(const GLubyte*)commands.data(),
			GLsizei(coords.size()),
			GLenum(GetDataType<CoordType>()),
			(const void*)coords.data()
		);
		OGLPLUS_CHECK(
			PathSubCommandsNV,
			ObjectError,
			Object(*this)
		);
		return *this;
	}

#if OGLPLUS_DOCUMENTATION_ONLY || !OGLPLUS_NO_VARIADIC_TEMPLATES
	/// Replaces a part of the the path with new commands and coordinates
	/**
	 *  @glsymbols
	 *  @glfunref{PathCoordsNV}
	 */
	template <typename CoordType>
	ObjectOps& SubSpec(
		GLsizei command_start,
		GLsizei commands_to_delete,
		const PathNVSpec<CoordType>& spec
	)
	{
		return SubCommands<CoordType>(
			command_start,
			commands_to_delete,
			spec._commands,
			spec._coords
		);
	}
#endif

	/// Replaces some of the paths coordinates
	/**
	 *  @glsymbols
	 *  @glfunref{PathSubCoordsNV}
	 */
	template <typename CoordType>
	ObjectOps& SubCoords(
		GLsizei coord_start,
		GLsizei num_coords,
		const CoordType* coords
	)
	{
		OGLPLUS_GLFUNC(PathSubCoordsNV)(
			this->_name,
			coord_start,
			num_coords,
			GLenum(GetDataType<CoordType>()),
			static_cast<const void*>(coords)
		);
		OGLPLUS_CHECK(
			PathSubCoordsNV,
			ObjectError,
			Object(*this)
		);
		return *this;
	}

	/// Replaces some of the paths coordinates
	/**
	 *  @glsymbols
	 *  @glfunref{PathSubCoordsNV}
	 */
	template <typename CoordType>
	ObjectOps& SubCoords(
		GLsizei coord_start,
		const std::vector<CoordType>& coords
	)
	{
		OGLPLUS_GLFUNC(PathSubCoordsNV)(
			this->_name,
			coord_start,
			GLsizei(coords.size()),
			GLenum(GetDataType<CoordType>()),
			(const void*)coords
		);
		OGLPLUS_CHECK(
			PathSubCoordsNV,
			ObjectError,
			Object(*this)
		);
		return *this;
	}


	/// Specifies the path using a string
	/**
	 *  @glsymbols
	 *  @glfunref{PathStringNV}
	 */
	ObjectOps& PathString(
		PathNVFormat format,
		GLsizei length,
		const GLchar* path_string
	)
	{
		OGLPLUS_GLFUNC(PathStringNV)(
			this->_name,
			GLenum(format),
			length,
			static_cast<const void*>(path_string)
		);
		OGLPLUS_CHECK(
			PathStringNV,
			ObjectError,
			Object(*this)
		);
		return *this;
	}

	/// Specifies the path using an SVG string
	/**
	 *  @glsymbols
	 *  @glfunref{PathStringNV}
	 */
	ObjectOps& PathString(PathNVFormat format, StrCRef path_string)
	{
		OGLPLUS_GLFUNC(PathStringNV)(
			this->_name,
			GLenum(format),
			path_string.size(),
			static_cast<const void*>(path_string.c_str())
		);
		OGLPLUS_CHECK(
			PathStringNV,
			ObjectError,
			Object(*this)
		);
		return *this;
	}

	/// Specifies the path using an SVG string
	/**
	 *  @glsymbols
	 *  @glfunref{PathStringNV}
	 *  @gldefref{PATH_FORMAT_SVG_NV}
	 */
	ObjectOps& SVGString(GLsizei length, const GLchar* path_string)
	{
		PathString(PathNVFormat::SVG, length, path_string);
		return *this;
	}

	/// Specifies the path using an SVG string
	/**
	 *  @glsymbols
	 *  @glfunref{PathStringNV}
	 *  @gldefref{PATH_FORMAT_SVG_NV}
	 */
	ObjectOps& SVGString(StrCRef path_string)
	{
		PathString(PathNVFormat::SVG, path_string);
		return *this;
	}

	/// Specifies the path using a Postscript string
	/**
	 *  @glsymbols
	 *  @glfunref{PathStringNV}
	 *  @gldefref{PATH_FORMAT_PS_NV}
	 */
	ObjectOps& PSString(GLsizei length, const GLchar* path_string)
	{
		PathString(PathNVFormat::PS, length, path_string);
		return *this;
	}

	/// Specifies the path using a Postscript string
	/**
	 *  @glsymbols
	 *  @glfunref{PathStringNV}
	 *  @gldefref{PATH_FORMAT_PS_NV}
	 */
	ObjectOps& PSString(StrCRef path_string)
	{
		PathString(PathNVFormat::PS, path_string);
		return *this;
	}

	/// Checks if the specified point is in the path interior
	/**
	 *  @glsymbols
	 *  @glfunref{IsPointInFillPathNV}
	 */
	bool IsPointInFill(GLuint mask, GLfloat x, GLfloat y) const
	{
		GLboolean result = OGLPLUS_GLFUNC(IsPointInFillPathNV)(
			this->_name,
			mask,
			x, y
		);
		OGLPLUS_VERIFY(
			IsPointInFillPathNV,
			ObjectError,
			Object(*this)
		);
		return result == GL_TRUE;
	}

	/// Checks if the specified point is on the path outline
	/**
	 *  @glsymbols
	 *  @glfunref{IsPointInStrokePathNV}
	 */
	bool IsPointInStroke(GLfloat x, GLfloat y) const
	{
		GLboolean result = OGLPLUS_GLFUNC(IsPointInStrokePathNV)(
			this->_name,
			x, y
		);
		OGLPLUS_VERIFY(
			IsPointInStrokePathNV,
			ObjectError,
			Object(*this)
		);
		return result == GL_TRUE;
	}

	/// Returns the approximation of the length of the path
	/**
	 *  @glsymbols
	 *  @glfunref{GetPathLengthNV}
	 */
	GLfloat GetLength(GLsizei start_segment, GLsizei num_segments) const
	{
		GLfloat result = OGLPLUS_GLFUNC(GetPathLengthNV)(
			this->_name,
			start_segment,
			num_segments
		);
		OGLPLUS_CHECK(
			GetPathLengthNV,
			ObjectError,
			Object(*this)
		);
		return result;
	}

	/// Get a point along the specified segment of the path
	/**
	 *  @glsymbols
	 *  @glfunref{PointAlongPathNV}
	 */
	bool PointAlong(
		GLsizei start_segment,
		GLsizei num_segments,
		GLfloat distance,
		GLfloat& ref_x,
		GLfloat& ref_y,
		GLfloat& ref_tg_x,
		GLfloat& ref_tg_y
	) const
	{
		GLboolean result = OGLPLUS_GLFUNC(PointAlongPathNV)(
			this->_name,
			start_segment,
			num_segments,
			distance,
			&ref_x,
			&ref_y,
			&ref_tg_x,
			&ref_tg_y
		);
		OGLPLUS_CHECK(
			PointAlongPathNV,
			ObjectError,
			Object(*this)
		);
		return result == GL_TRUE;
	}

	/// Sets the stroke width value
	/**
	 *  @glsymbols
	 *  @glfunref{PathParameterNV}
	 *  @gldefref{PATH_STROKE_WIDTH_NV}
	 */
	ObjectOps& StrokeWidth(GLfloat width)
	{
		OGLPLUS_GLFUNC(PathParameterfNV)(
			this->_name,
			GL_PATH_STROKE_WIDTH_NV,
			width
		);
		OGLPLUS_CHECK(
			PathParameterfNV,
			ObjectError,
			Object(*this)
		);
		return *this;
	}

	/// Gets the stroke width value
	/**
	 *  @glsymbols
	 *  @glfunref{GetPathParameterNV}
	 *  @gldefref{PATH_STROKE_WIDTH_NV}
	 */
	GLfloat StrokeWidth(void)
	{
		GLfloat result;
		OGLPLUS_GLFUNC(GetPathParameterfvNV)(
			this->_name,
			GL_PATH_STROKE_WIDTH_NV,
			&result
		);
		OGLPLUS_VERIFY(
			GetPathParameterfvNV,
			ObjectError,
			Object(*this)
		);
		return result;
	}

	/// Sets the miter limit
	/**
	 *  @glsymbols
	 *  @glfunref{PathParameterNV}
	 *  @gldefref{PATH_MITER_LIMIT_NV}
	 */
	ObjectOps& MiterLimit(GLfloat width)
	{
		OGLPLUS_GLFUNC(PathParameterfNV)(
			this->_name,
			GL_PATH_MITER_LIMIT_NV,
			width
		);
		OGLPLUS_CHECK(
			PathParameterfNV,
			ObjectError,
			Object(*this)
		);
		return *this;
	}

	/// Gets the miter limit value
	/**
	 *  @glsymbols
	 *  @glfunref{GetPathParameterNV}
	 *  @gldefref{PATH_MITER_LIMIT_NV}
	 */
	GLfloat MiterLimit(void)
	{
		GLfloat result;
		OGLPLUS_GLFUNC(GetPathParameterfvNV)(
			this->_name,
			GL_PATH_MITER_LIMIT_NV,
			&result
		);
		OGLPLUS_VERIFY(
			GetPathParameterfvNV,
			ObjectError,
			Object(*this)
		);
		return result;
	}

	/// Sets the stroke join style
	/**
	 *  @glsymbols
	 *  @glfunref{PathParameterNV}
	 *  @gldefref{PATH_JOIN_STYLE_NV}
	 */
	ObjectOps& JoinStyle(PathNVJoinStyle style)
	{
		OGLPLUS_GLFUNC(PathParameterfNV)(
			this->_name,
			GL_PATH_JOIN_STYLE_NV,
			GLenum(style)
		);
		OGLPLUS_CHECK(
			PathParameterfNV,
			ObjectError,
			Object(*this)
		);
		return *this;
	}

	/// Sets the initial end cap style
	/**
	 *  @glsymbols
	 *  @glfunref{PathParameterNV}
	 *  @gldefref{PATH_INITIAL_END_CAP_NV}
	 */
	ObjectOps& InitialEndCap(PathNVCapStyle style)
	{
		OGLPLUS_GLFUNC(PathParameterfNV)(
			this->_name,
			GL_PATH_INITIAL_END_CAP_NV,
			GLenum(style)
		);
		OGLPLUS_CHECK(
			PathParameterfNV,
			ObjectError,
			Object(*this)
		);
		return *this;
	}

	/// Sets the terminal end cap style
	/**
	 *  @glsymbols
	 *  @glfunref{PathParameterNV}
	 *  @gldefref{PATH_TERMINAL_END_CAP_NV}
	 */
	ObjectOps& TerminalEndCap(PathNVCapStyle style)
	{
		OGLPLUS_GLFUNC(PathParameterfNV)(
			this->_name,
			GL_PATH_TERMINAL_END_CAP_NV,
			GLenum(style)
		);
		OGLPLUS_CHECK(
			PathParameterfNV,
			ObjectError,
			Object(*this)
		);
		return *this;
	}

	/// Sets the initial dash cap style
	/**
	 *  @glsymbols
	 *  @glfunref{PathParameterNV}
	 *  @gldefref{PATH_INITIAL_DASH_CAP_NV}
	 */
	ObjectOps& InitialDashCap(PathNVCapStyle style)
	{
		OGLPLUS_GLFUNC(PathParameterfNV)(
			this->_name,
			GL_PATH_INITIAL_DASH_CAP_NV,
			GLenum(style)
		);
		OGLPLUS_CHECK(
			PathParameterfNV,
			ObjectError,
			Object(*this)
		);
		return *this;
	}

	/// Sets the terminal dash cap style
	/**
	 *  @glsymbols
	 *  @glfunref{PathParameterNV}
	 *  @gldefref{PATH_TERMINAL_DASH_CAP_NV}
	 */
	ObjectOps& TerminalDashCap(PathNVCapStyle style)
	{
		OGLPLUS_GLFUNC(PathParameterfNV)(
			this->_name,
			GL_PATH_TERMINAL_DASH_CAP_NV,
			GLenum(style)
		);
		OGLPLUS_CHECK(
			PathParameterfNV,
			ObjectError,
			Object(*this)
		);
		return *this;
	}

	/// Sets the dash offset
	/**
	 *  @glsymbols
	 *  @glfunref{PathParameterNV}
	 *  @gldefref{PATH_DASH_OFFSET_NV}
	 */
	ObjectOps& DashOffset(GLfloat width)
	{
		OGLPLUS_GLFUNC(PathParameterfNV)(
			this->_name,
			GL_PATH_DASH_OFFSET_NV,
			width
		);
		OGLPLUS_CHECK(
			PathParameterfNV,
			ObjectError,
			Object(*this)
		);
		return *this;
	}

	/// Gets the dash offset value
	/**
	 *  @glsymbols
	 *  @glfunref{GetPathParameterNV}
	 *  @gldefref{PATH_DASH_OFFSET_NV}
	 */
	GLfloat DashOffset(void)
	{
		GLfloat result;
		OGLPLUS_GLFUNC(GetPathParameterfvNV)(
			this->_name,
			GL_PATH_DASH_OFFSET_NV,
			&result
		);
		OGLPLUS_VERIFY(
			GetPathParameterfvNV,
			ObjectError,
			Object(*this)
		);
		return result;
	}

	/// Sets the dash reset mode
	/**
	 *  @glsymbols
	 *  @glfunref{PathParameterNV}
	 *  @gldefref{PATH_DASH_OFFSET_RESET_NV}
	 */
	ObjectOps& DashOffsetReset(PathNVDashOffsetReset mode)
	{
		OGLPLUS_GLFUNC(PathParameterfNV)(
			this->_name,
			GL_PATH_DASH_OFFSET_RESET_NV,
			GLenum(mode)
		);
		OGLPLUS_CHECK(
			PathParameterfNV,
			ObjectError,
			Object(*this)
		);
		return *this;
	}

	/// Sets the path dash array
	/**
	 *  @glsymbols
	 *  @glfunref{PathDashArrayNV}
	 */
	ObjectOps& DashArray(GLsizei dash_count, const GLfloat* dash_array)
	{
		OGLPLUS_GLFUNC(PathDashArrayNV)(
			this->_name,
			dash_count,
			dash_array
		);
		OGLPLUS_CHECK(
			PathDashArrayNV,
			ObjectError,
			Object(*this)
		);
		return *this;
	}

#if OGLPLUS_DOCUMENTATION_ONLY || !OGLPLUS_NO_VARIADIC_TEMPLATES
	/// Sets the path dash array
	/**
	 *  @glsymbols
	 *  @glfunref{PathDashArrayNV}
	 */
	template <typename ... T>
	ObjectOps& Dashes(T ... dashes)
	{
		const std::size_t N = sizeof ... (dashes);
		const GLfloat dash_array[N] = { GLfloat(dashes)... };
		return DashArray(N, dash_array);
	}
#endif

	/// Sets the client length value
	/**
	 *  @glsymbols
	 *  @glfunref{PathParameterNV}
	 *  @gldefref{PATH_CLIENT_LENGTH_NV}
	 */
	ObjectOps& ClientLength(GLfloat value)
	{
		OGLPLUS_GLFUNC(PathParameterfNV)(
			this->_name,
			GL_PATH_CLIENT_LENGTH_NV,
			value
		);
		OGLPLUS_CHECK(
			PathParameterfNV,
			ObjectError,
			Object(*this)
		);
		return *this;
	}

	/// Returns the client length value
	/**
	 *  @glsymbols
	 *  @glfunref{GetPathParameterNV}
	 *  @gldefref{PATH_CLIENT_LENGTH_NV}
	 */
	GLfloat ClientLength(void)
	{
		GLfloat result;
		OGLPLUS_GLFUNC(GetPathParameterfvNV)(
			this->_name,
			GL_PATH_CLIENT_LENGTH_NV,
			&result
		);
		OGLPLUS_VERIFY(
			GetPathParameterfvNV,
			ObjectError,
			Object(*this)
		);
		return result;
	}


	/// Writes the path interior (fill) into the stencil buffer
	/**
	 *  @glsymbols
	 *  @glfunref{StencilFillPathNV}
	 */
	ObjectOps& StencilFill(PathNVFillMode mode, GLuint mask)
	{
		OGLPLUS_GLFUNC(StencilFillPathNV)(
			this->_name,
			GLenum(mode),
			mask
		);
		OGLPLUS_CHECK(
			StencilFillPathNV,
			ObjectError,
			Object(*this)
		);
		return *this;
	}

	/// Covers the stencilled path interior (fill)
	/**
	 *  @glsymbols
	 *  @glfunref{CoverFillPathNV}
	 */
	ObjectOps& CoverFill(PathNVFillCoverMode mode)
	{
		OGLPLUS_GLFUNC(CoverFillPathNV)(this->_name, GLenum(mode));
		OGLPLUS_CHECK(
			CoverFillPathNV,
			ObjectError,
			Object(*this)
		);
		return *this;
	}

	/// Writes the path stroke into the stencil buffer
	/**
	 *  @glsymbols
	 *  @glfunref{StencilStrokePathNV}
	 */
	ObjectOps& StencilStroke(GLint reference, GLuint mask)
	{
		OGLPLUS_GLFUNC(StencilStrokePathNV)(
			this->_name,
			reference,
			mask
		);
		OGLPLUS_CHECK(
			StencilStrokePathNV,
			ObjectError,
			Object(*this)
		);
		return *this;
	}

	/// Covers the stencilled path stroke
	/**
	 *  @glsymbols
	 *  @glfunref{CoverStrokePathNV}
	 */
	ObjectOps& CoverStroke(PathNVStrokeCoverMode mode)
	{
		OGLPLUS_GLFUNC(CoverStrokePathNV)(this->_name, GLenum(mode));
		OGLPLUS_CHECK(
			CoverStrokePathNV,
			ObjectError,
			Object(*this)
		);
		return *this;
	}

	/// Copy path
	/**
	 *  @glsymbols
	 *  @glfunref{CopyPathNV}
	 */
	static PathNVName Copy(
		PathNVName dest_path,
		PathNVName src_path
	)
	{
		OGLPLUS_GLFUNC(CopyPathNV)(
			GetGLName(dest_path),
			GetGLName(src_path)
		);
		OGLPLUS_CHECK(
			CopyPathNV,
			ObjectPairError,
			Subject(src_path).
			Object(dest_path)
		);
		return dest_path;
	}

	/// Interpolates between two paths
	/**
	 *  @glsymbols
	 *  @glfunref{InterpolatePathsNV}
	 */
	static PathNVName Interpolate(
		PathNVName dest_path,
		PathNVName path_a,
		PathNVName path_b,
		GLfloat weight
	)
	{
		OGLPLUS_GLFUNC(InterpolatePathsNV)(
			GetGLName(dest_path),
			GetGLName(path_a),
			GetGLName(path_b),
			weight
		);
		OGLPLUS_CHECK(
			InterpolatePathsNV,
			ObjectError,
			Object(dest_path)
		);
		return dest_path;
	}

	/// Transforms a path
	/**
	 *  @glsymbols
	 *  @glfunref{TransformPathNV}
	 */
	static PathNVName Transform(
		PathNVName dest_path,
		PathNVName src_path,
		PathNVTransformType transform_type,
		const GLfloat* transform_values
	)
	{
		OGLPLUS_GLFUNC(TransformPathNV)(
			GetGLName(dest_path),
			GetGLName(src_path),
			GLenum(transform_type),
			transform_values
		);
		OGLPLUS_CHECK(
			TransformPathNV,
			ObjectPairError,
			Subject(src_path).
			Object(dest_path)
		);
		return dest_path;
	}
};

/// PathNV operations with direct state access
typedef ObjectOps<tag::DirectState, tag::PathNV>
	PathNVOps;

/// An @ref oglplus_object encapsulating the nVidia path functionality
/**
 *  @ingroup oglplus_objects
 */
typedef Object<PathNVOps> PathNV;

} // namespace oglplus

#endif // NV_path_rendering

#endif // include guard
