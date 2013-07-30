/**
 *  @file oglplus/ext/NV_path_rendering.hpp
 *  @brief Wrapper for the NV_path_rendering extension
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_EXT_NV_PATH_RENDERING_1203031902_HPP
#define OGLPLUS_EXT_NV_PATH_RENDERING_1203031902_HPP

#include <oglplus/extension.hpp>
#include <oglplus/object.hpp>
#include <oglplus/data_type.hpp>
#include <oglplus/string.hpp>
#include <oglplus/texture_unit.hpp>
#include <oglplus/bitfield.hpp>
#include <oglplus/enumerations.hpp>

#include <vector>

namespace oglplus {

#if OGLPLUS_DOCUMENTATION_ONLY || GL_NV_path_rendering

/// Path specification command enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glextref{NV,path_rendering}
 */
OGLPLUS_ENUM_CLASS_BEGIN(PathNVCommand, GLubyte)
#include <oglplus/enums/ext/nv_path_command.ipp>
OGLPLUS_ENUM_CLASS_END(PathNVCommand)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/ext/nv_path_command_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/ext/nv_path_command_range.ipp>
#endif

/// Path specification string format enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glextref{NV,path_rendering}
 */
OGLPLUS_ENUM_CLASS_BEGIN(PathNVFormat, GLenum)
#include <oglplus/enums/ext/nv_path_format.ipp>
OGLPLUS_ENUM_CLASS_END(PathNVFormat)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/ext/nv_path_format_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/ext/nv_path_format_range.ipp>
#endif

/// Path fill mode
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glextref{NV,path_rendering}
 */
OGLPLUS_ENUM_CLASS_BEGIN(PathNVFillMode, GLenum)
#include <oglplus/enums/ext/nv_path_fill_mode.ipp>
OGLPLUS_ENUM_CLASS_END(PathNVFillMode)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/ext/nv_path_fill_mode_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/ext/nv_path_fill_mode_range.ipp>
#endif

/// Path fill covering mode
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glextref{NV,path_rendering}
 */
OGLPLUS_ENUM_CLASS_BEGIN(PathNVFillCoverMode, GLenum)
#include <oglplus/enums/ext/nv_path_fill_cover_mode.ipp>
OGLPLUS_ENUM_CLASS_END(PathNVFillCoverMode)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/ext/nv_path_fill_cover_mode_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/ext/nv_path_fill_cover_mode_range.ipp>
#endif

/// Path stroke covering move
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glextref{NV,path_rendering}
 */
OGLPLUS_ENUM_CLASS_BEGIN(PathNVStrokeCoverMode, GLenum)
#include <oglplus/enums/ext/nv_path_stroke_cover_mode.ipp>
OGLPLUS_ENUM_CLASS_END(PathNVStrokeCoverMode)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/ext/nv_path_stroke_cover_mode_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/ext/nv_path_stroke_cover_mode_range.ipp>
#endif

/// Stroke line join style enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glextref{NV,path_rendering}
 */
OGLPLUS_ENUM_CLASS_BEGIN(PathNVJoinStyle, GLenum)
#include <oglplus/enums/ext/nv_path_join_style.ipp>
OGLPLUS_ENUM_CLASS_END(PathNVJoinStyle)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/ext/nv_path_join_style_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/ext/nv_path_join_style_range.ipp>
#endif

/// Path cap mode enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glextref{NV,path_rendering}
 */
OGLPLUS_ENUM_CLASS_BEGIN(PathNVCapStyle, GLenum)
#include <oglplus/enums/ext/nv_path_cap_style.ipp>
OGLPLUS_ENUM_CLASS_END(PathNVCapStyle)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/ext/nv_path_cap_style_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/ext/nv_path_cap_style_range.ipp>
#endif

/// Path dash offset reset mode enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glextref{NV,path_rendering}
 */
OGLPLUS_ENUM_CLASS_BEGIN(PathNVDashOffsetReset, GLenum)
#include <oglplus/enums/ext/nv_path_dash_offset_reset.ipp>
OGLPLUS_ENUM_CLASS_END(PathNVDashOffsetReset)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/ext/nv_path_dash_offset_reset_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/ext/nv_path_dash_offset_reset_range.ipp>
#endif

/// Path color mode enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glextref{NV,path_rendering}
 */
OGLPLUS_ENUM_CLASS_BEGIN(PathNVColor, GLenum)
#include <oglplus/enums/ext/nv_path_color.ipp>
OGLPLUS_ENUM_CLASS_END(PathNVColor)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/ext/nv_path_color_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/ext/nv_path_color_range.ipp>
#endif

/// Path color format enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glextref{NV,path_rendering}
 */
OGLPLUS_ENUM_CLASS_BEGIN(PathNVColorFormat, GLenum)
#include <oglplus/enums/ext/nv_path_color_format.ipp>
OGLPLUS_ENUM_CLASS_END(PathNVColorFormat)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/ext/nv_path_color_format_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/ext/nv_path_color_format_range.ipp>
#endif

/// Path color and tex-coord generation mode enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glextref{NV,path_rendering}
 */
OGLPLUS_ENUM_CLASS_BEGIN(PathNVGenMode, GLenum)
#include <oglplus/enums/ext/nv_path_gen_mode.ipp>
OGLPLUS_ENUM_CLASS_END(PathNVGenMode)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/ext/nv_path_gen_mode_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/ext/nv_path_gen_mode_range.ipp>
#endif

/// Path transform type enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glextref{NV,path_rendering}
 */
OGLPLUS_ENUM_CLASS_BEGIN(PathNVTransformType, GLenum)
#include <oglplus/enums/ext/nv_path_transform_type.ipp>
OGLPLUS_ENUM_CLASS_END(PathNVTransformType)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/ext/nv_path_transform_type_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/ext/nv_path_transform_type_range.ipp>
#endif

/// Path font target enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glextref{NV,path_rendering}
 */
OGLPLUS_ENUM_CLASS_BEGIN(PathNVFontTarget, GLenum)
#include <oglplus/enums/ext/nv_path_font_target.ipp>
OGLPLUS_ENUM_CLASS_END(PathNVFontTarget)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/ext/nv_path_font_target_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/ext/nv_path_font_target_range.ipp>
#endif

/// Path missing glyph action mode enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glextref{NV,path_rendering}
 */
OGLPLUS_ENUM_CLASS_BEGIN(PathNVMissingGlyph, GLenum)
#include <oglplus/enums/ext/nv_path_missing_glyph.ipp>
OGLPLUS_ENUM_CLASS_END(PathNVMissingGlyph)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/ext/nv_path_missing_glyph_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/ext/nv_path_missing_glyph_range.ipp>
#endif

/// Path list mode enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glextref{NV,path_rendering}
 */
OGLPLUS_ENUM_CLASS_BEGIN(PathNVListMode, GLenum)
#include <oglplus/enums/ext/nv_path_list_mode.ipp>
OGLPLUS_ENUM_CLASS_END(PathNVListMode)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/ext/nv_path_list_mode_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/ext/nv_path_list_mode_range.ipp>
#endif

/// Path font style bits enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glextref{NV,path_rendering}
 */
OGLPLUS_ENUM_CLASS_BEGIN(PathNVFontStyle, GLbitfield)
#include <oglplus/enums/ext/nv_path_font_style.ipp>
OGLPLUS_ENUM_CLASS_END(PathNVFontStyle)

OGLPLUS_MAKE_BITFIELD(PathNVFontStyle)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/ext/nv_path_font_style_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/ext/nv_path_font_style_range.ipp>
#endif

/// Path metric query bits enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glextref{NV,path_rendering}
 */
OGLPLUS_ENUM_CLASS_BEGIN(PathNVMetricQuery, GLbitfield)
#include <oglplus/enums/ext/nv_path_metric_query.ipp>
OGLPLUS_ENUM_CLASS_END(PathNVMetricQuery)

OGLPLUS_MAKE_BITFIELD(PathNVMetricQuery)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/ext/nv_path_metric_query_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/ext/nv_path_metric_query_range.ipp>
#endif

/// Text encoding type enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glextref{NV,path_rendering}
 */
OGLPLUS_ENUM_CLASS_BEGIN(PathNVTextEncoding, GLenum)
#include <oglplus/enums/ext/nv_path_text_encoding.ipp>
OGLPLUS_ENUM_CLASS_END(PathNVTextEncoding)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/ext/nv_path_text_encoding_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/ext/nv_path_text_encoding_range.ipp>
#endif

/// Wrapper for NV_path_rendering-related operations
/** @note Do not use this class directly, use PathNV instead.
 *
 *  @glsymbols
 *  @glfunref{GenPathsNV}
 *  @glfunref{DeletePathsNV}
 *  @glfunref{IsPathNV}
 */
class PathNVOps
 : public Named
 , public BaseObject<true>
{
protected:
	static void _init(GLsizei count, GLuint* _name)
	{
		assert(_name != nullptr);
		GLuint base = OGLPLUS_GLFUNC(GenPathsNV)(count);
		for(GLsizei i=0; i!=count; ++i)
			_name[i] = base+i;
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GenPathsNV));
	}

	static void _cleanup(GLsizei count, GLuint* _name)
	OGLPLUS_NOEXCEPT(true)
	{
		assert(_name != nullptr);
		assert(*_name != 0);
		try{OGLPLUS_GLFUNC(DeletePathsNV)(count, *_name);}
		catch(...){ }
	}

	static GLboolean _is_x(GLuint _name)
	OGLPLUS_NOEXCEPT(true)
	{
		assert(_name != 0);
		try{return OGLPLUS_GLFUNC(IsPathNV)(_name);}
		catch(...){ }
		return GL_FALSE;
	}

	friend class FriendOf<PathNVOps>;
public:
	/// Specifies the path via a sequence of commands and coordinates
	/**
	 *  @glsymbols
	 *  @glfunref{PathCommandsNV}
	 */
	template <typename CoordType>
	void Commands(
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
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(PathCommandsNV));
	}

	/// Specifies the path via a sequence of commands and coordinates
	/**
	 *  @glsymbols
	 *  @glfunref{PathCommandsNV}
	 */
	template <typename CoordType>
	void Commands(
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
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(PathCommandsNV));
	}

	/// Specifies the path via a sequence of coordinates
	/**
	 *  @glsymbols
	 *  @glfunref{PathCoordsNV}
	 */
	template <typename CoordType>
	void Coords(GLsizei num_coords, const CoordType* coords)
	{
		OGLPLUS_GLFUNC(PathCoordsNV)(
			this->_name,
			num_coords,
			GLenum(GetDataType<CoordType>()),
			static_cast<const void*>(coords)
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(PathCoordsNV));
	}

	/// Specifies the path via a sequence of coordinates
	/**
	 *  @glsymbols
	 *  @glfunref{PathCoordsNV}
	 */
	template <typename CoordType>
	void Coords(const std::vector<CoordType>& coords)
	{
		OGLPLUS_GLFUNC(PathCoordsNV)(
			this->_name,
			GLsizei(coords.size()),
			GLenum(GetDataType<CoordType>()),
			(const void*)coords.data()
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(PathCoordsNV));
	}

	/// Replaces a part of the the path with new commands and coordinates
	/**
	 *  @glsymbols
	 *  @glfunref{PathSubCommandsNV}
	 */
	template <typename CoordType>
	void SubCommands(
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
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(PathSubCommandsNV));
	}

	/// Replaces a part of the the path with new commands and coordinates
	/**
	 *  @glsymbols
	 *  @glfunref{PathSubCommandsNV}
	 */
	template <typename CoordType>
	void SubCommands(
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
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(PathSubCommandsNV));
	}

	/// Replaces some of the paths coordinates
	/**
	 *  @glsymbols
	 *  @glfunref{PathSubCoordsNV}
	 */
	template <typename CoordType>
	void SubCoords(
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
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(PathSubCoordsNV));
	}

	/// Replaces some of the paths coordinates
	/**
	 *  @glsymbols
	 *  @glfunref{PathSubCoordsNV}
	 */
	template <typename CoordType>
	void SubCoords(
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
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(PathSubCoordsNV));
	}


	/// Specifies the path using a string
	/**
	 *  @glsymbols
	 *  @glfunref{PathStringNV}
	 */
	void PathString(
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
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(PathStringNV));
	}

	/// Specifies the path using a string
	/**
	 *  @glsymbols
	 *  @glfunref{PathStringNV}
	 */
	void PathString(PathNVFormat format, const String& path_string)
	{
		OGLPLUS_GLFUNC(PathStringNV)(
			this->_name,
			GLenum(format),
			path_string.size(),
			static_cast<const void*>(path_string.c_str())
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(PathStringNV));
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
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(IsPointInFillPathNV));
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
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(IsPointInStrokePathNV));
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
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GetPathLengthNV));
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
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(PointAlongPathNV));
		return result == GL_TRUE;
	}

	/// Sets the stroke width value
	/**
	 *  @glsymbols
	 *  @glfunref{PathParameterNV}
	 *  @gldefref{PATH_STROKE_WIDTH_NV}
	 */
	void StrokeWidth(GLfloat width)
	{
		OGLPLUS_GLFUNC(PathParameterfNV)(
			this->_name,
			GL_PATH_STROKE_WIDTH_NV,
			width
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(PathParameterfNV));
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
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(GetPathParameterfvNV));
		return result;
	}

	/// Sets the miter limit
	/**
	 *  @glsymbols
	 *  @glfunref{PathParameterNV}
	 *  @gldefref{PATH_MITER_LIMIT_NV}
	 */
	void MiterLimit(GLfloat width)
	{
		OGLPLUS_GLFUNC(PathParameterfNV)(
			this->_name,
			GL_PATH_MITER_LIMIT_NV,
			width
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(PathParameterfNV));
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
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(GetPathParameterfvNV));
		return result;
	}

	/// Sets the stroke join style
	/**
	 *  @glsymbols
	 *  @glfunref{PathParameterNV}
	 *  @gldefref{PATH_JOIN_STYLE_NV}
	 */
	void JoinStyle(PathNVJoinStyle style)
	{
		OGLPLUS_GLFUNC(PathParameterfNV)(
			this->_name,
			GL_PATH_JOIN_STYLE_NV,
			GLenum(style)
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(PathParameterfNV));
	}

	/// Sets the initial end cap style
	/**
	 *  @glsymbols
	 *  @glfunref{PathParameterNV}
	 *  @gldefref{PATH_INITIAL_END_CAP_NV}
	 */
	void InitialEndCap(PathNVCapStyle style)
	{
		OGLPLUS_GLFUNC(PathParameterfNV)(
			this->_name,
			GL_PATH_INITIAL_END_CAP_NV,
			GLenum(style)
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(PathParameterfNV));
	}

	/// Sets the terminal end cap style
	/**
	 *  @glsymbols
	 *  @glfunref{PathParameterNV}
	 *  @gldefref{PATH_TERMINAL_END_CAP_NV}
	 */
	void TerminalEndCap(PathNVCapStyle style)
	{
		OGLPLUS_GLFUNC(PathParameterfNV)(
			this->_name,
			GL_PATH_TERMINAL_END_CAP_NV,
			GLenum(style)
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(PathParameterfNV));
	}

	/// Sets the initial dash cap style
	/**
	 *  @glsymbols
	 *  @glfunref{PathParameterNV}
	 *  @gldefref{PATH_INITIAL_DASH_CAP_NV}
	 */
	void InitialDashCap(PathNVCapStyle style)
	{
		OGLPLUS_GLFUNC(PathParameterfNV)(
			this->_name,
			GL_PATH_INITIAL_DASH_CAP_NV,
			GLenum(style)
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(PathParameterfNV));
	}

	/// Sets the terminal dash cap style
	/**
	 *  @glsymbols
	 *  @glfunref{PathParameterNV}
	 *  @gldefref{PATH_TERMINAL_DASH_CAP_NV}
	 */
	void TerminalDashCap(PathNVCapStyle style)
	{
		OGLPLUS_GLFUNC(PathParameterfNV)(
			this->_name,
			GL_PATH_TERMINAL_DASH_CAP_NV,
			GLenum(style)
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(PathParameterfNV));
	}

	/// Sets the dash offset
	/**
	 *  @glsymbols
	 *  @glfunref{PathParameterNV}
	 *  @gldefref{PATH_DASH_OFFSET_NV}
	 */
	void DashOffset(GLfloat width)
	{
		OGLPLUS_GLFUNC(PathParameterfNV)(
			this->_name,
			GL_PATH_DASH_OFFSET_NV,
			width
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(PathParameterfNV));
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
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(GetPathParameterfvNV));
		return result;
	}

	/// Sets the dash reset mode
	/**
	 *  @glsymbols
	 *  @glfunref{PathParameterNV}
	 *  @gldefref{PATH_DASH_OFFSET_RESET_NV}
	 */
	void DashOffsetReset(PathNVDashOffsetReset mode)
	{
		OGLPLUS_GLFUNC(PathParameterfNV)(
			this->_name,
			GL_PATH_DASH_OFFSET_RESET_NV,
			GLenum(mode)
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(PathParameterfNV));
	}

	/// Sets the path dash array
	/**
	 *  @glsymbols
	 *  @glfunref{PathDashArrayNV}
	 */
	void DashArray(GLsizei dash_count, const GLfloat* dash_array)
	{
		OGLPLUS_GLFUNC(PathDashArrayNV)(
			this->_name,
			dash_count,
			dash_array
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(PathDashArrayNV));
	}

	/// Sets the client length value
	/**
	 *  @glsymbols
	 *  @glfunref{PathParameterNV}
	 *  @gldefref{PATH_CLIENT_LENGTH_NV}
	 */
	void ClientLength(GLfloat value)
	{
		OGLPLUS_GLFUNC(PathParameterfNV)(
			this->_name,
			GL_PATH_CLIENT_LENGTH_NV,
			value
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(PathParameterfNV));
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
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(GetPathParameterfvNV));
		return result;
	}


	/// Writes the path interior (fill) into the stencil buffer
	/**
	 *  @glsymbols
	 *  @glfunref{StencilFillPathNV}
	 */
	void StencilFill(PathNVFillMode mode, GLuint mask)
	{
		OGLPLUS_GLFUNC(StencilFillPathNV)(
			this->_name,
			GLenum(mode),
			mask
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(StencilFillPathNV));
	}

	/// Covers the stencilled path interior (fill)
	/**
	 *  @glsymbols
	 *  @glfunref{CoverFillPathNV}
	 */
	void CoverFill(PathNVFillCoverMode mode)
	{
		OGLPLUS_GLFUNC(CoverFillPathNV)(this->_name, GLenum(mode));
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(CoverFillPathNV));
	}

	/// Writes the path stroke into the stencil buffer
	/**
	 *  @glsymbols
	 *  @glfunref{StencilStrokePathNV}
	 */
	void StencilStroke(GLint reference, GLuint mask)
	{
		OGLPLUS_GLFUNC(StencilStrokePathNV)(
			this->_name,
			reference,
			mask
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(StencilStrokePathNV));
	}

	/// Covers the stencilled path stroke
	/**
	 *  @glsymbols
	 *  @glfunref{CoverStrokePathNV}
	 */
	void CoverStroke(PathNVStrokeCoverMode mode)
	{
		OGLPLUS_GLFUNC(CoverStrokePathNV)(this->_name, GLenum(mode));
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(CoverStrokePathNV));
	}

	/// Copy path
	/**
	 *  @glsymbols
	 *  @glfunref{CopyPathNV}
	 */
	static void Copy(PathNVOps& dest_path, const PathNVOps& src_path)
	{
		OGLPLUS_GLFUNC(CopyPathNV)(dest_path._name, src_path._name);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(CopyPathNV));
	}

	/// Interpolates between two paths
	/**
	 *  @glsymbols
	 *  @glfunref{InterpolatePathsNV}
	 */
	static void Interpolate(
		PathNVOps& dest_path,
		const PathNVOps& path_a,
		const PathNVOps& path_b,
		GLfloat weight
	)
	{
		OGLPLUS_GLFUNC(InterpolatePathsNV)(
			dest_path._name,
			path_a._name,
			path_b._name,
			weight
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(InterpolatePathsNV));
	}

	/// Transforms a path
	/**
	 *  @glsymbols
	 *  @glfunref{TransformPathNV}
	 */
	static void Transform(
		PathNVOps& dest_path,
		const PathNVOps& src_path,
		PathNVTransformType transform_type,
		const GLfloat* transform_values
	)
	{
		OGLPLUS_GLFUNC(TransformPathNV)(
			dest_path._name,
			src_path._name,
			GLenum(transform_type),
			transform_values
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(TransformPathNV));
	}
};

#if OGLPLUS_DOCUMENTATION_ONLY
/// An @ref oglplus_object encapsulating the nVidia path functionality
/**
 *  @ingroup oglplus_objects
 */
class PathNV
 : public PathNVOps
{ };
#else
typedef Object<PathNVOps> PathNV;
#endif

/// Array of PathNV objects and related operations
class PathArrayNV
 : public Array<PathNV>
{
public:
	/// Creates a sequence of @p count paths
	PathArrayNV(GLsizei count)
	 : Array<PathNV>(count)
	{ }

	/// Creates a range of paths from specified font for specified chars
	/**
	 *  @glsymbols
	 *  @glfunref{PathGlyphsNV}
	 */
	template <typename CharType>
	void Glyphs(
		PathNVFontTarget font_target,
		const GLchar* font_name,
		Bitfield<PathNVFontStyle> font_style,
		GLsizei num_glyphs,
		const CharType* char_codes,
		PathNVMissingGlyph handle_missing_glyphs,
		GLuint parameter_template,
		GLfloat em_scale
	)
	{
		OGLPLUS_GLFUNC(PathGlyphsNV)(
			this->_names[0],
			GLenum(font_target),
			(const void*)font_name,
			GLbitfield(font_style),
			num_glyphs,
			GetDataType<CharType>(),
			(const void*)char_codes,
			GLenum(handle_missing_glyphs),
			parameter_template,
			em_scale
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(PathGlyphsNV));
	}

	/// Creates a range of paths from specified font for specified chars
	/**
	 *  @glsymbols
	 *  @glfunref{PathGlyphsNV}
	 */
	template <typename CharType>
	void Glyphs(
		PathNVFontTarget font_target,
		const GLchar* font_name,
		Bitfield<PathNVFontStyle> font_style,
		const std::vector<CharType>& char_codes,
		PathNVMissingGlyph handle_missing_glyphs,
		GLuint parameter_template,
		GLfloat em_scale
	)
	{
		OGLPLUS_GLFUNC(PathGlyphsNV)(
			this->_names[0],
			GLenum(font_target),
			(const void*)font_name,
			GLbitfield(font_style),
			GLsizei(char_codes.size()),
			GetDataType<CharType>(),
			(const void*)char_codes.data(),
			GLenum(handle_missing_glyphs),
			parameter_template,
			em_scale
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(PathGlyphsNV));
	}

	/// Creates a range of paths from specified font for specified chars
	/**
	 *  @glsymbols
	 *  @glfunref{PathGlyphsNV}
	 */
	void Glyphs(
		PathNVFontTarget font_target,
		const GLchar* font_name,
		Bitfield<PathNVFontStyle> font_style,
		const String& char_codes,
		PathNVMissingGlyph handle_missing_glyphs,
		GLuint parameter_template,
		GLfloat em_scale
	)
	{
		OGLPLUS_GLFUNC(PathGlyphsNV)(
			this->_names[0],
			GLenum(font_target),
			(const void*)font_name,
			GLbitfield(font_style),
			char_codes.size(),
			GL_UTF8_NV,
			(const void*)char_codes.c_str(),
			GLenum(handle_missing_glyphs),
			parameter_template,
			em_scale
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(PathGlyphsNV));
	}

	/// Creates a range of paths from specified font
	/**
	 *  @glsymbols
	 *  @glfunref{PathGlyphRangeNV}
	 */
	void GlyphRange(
		PathNVFontTarget font_target,
		const GLchar* font_name,
		Bitfield<PathNVFontStyle> font_style,
		GLuint first_glyph,
		GLsizei num_glyphs,
		PathNVMissingGlyph handle_missing_glyphs,
		GLuint parameter_template,
		GLfloat em_scale
	)
	{
		OGLPLUS_GLFUNC(PathGlyphRangeNV)(
			this->_names[0],
			GLenum(font_target),
			(const void*)font_name,
			GLbitfield(font_style),
			first_glyph,
			num_glyphs,
			GLenum(handle_missing_glyphs),
			parameter_template,
			em_scale
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(PathGlyphRangeNV));
	}

	/// Queries the glyph spacing for paths in the array
	/**
	 *  @glsymbols
	 *  @glfunref{GetPathSpacingNV}
	 */
	template <typename IndexType>
	void GetSpacing(
		PathNVListMode list_mode,
		GLsizei num_indices,
		const IndexType* indices,
		GLfloat advance_scale,
		GLfloat kerning_scale,
		PathNVTransformType transform_type,
		GLfloat* returned_values
	)
	{
		OGLPLUS_GLFUNC(GetPathSpacingNV)(
			GLenum(list_mode),
			num_indices,
			GLenum(GetDataType<IndexType>()),
			(const void*)indices,
			this->_names[0],
			advance_scale,
			kerning_scale,
			GLenum(transform_type),
			returned_values
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GetPathSpacingNV));
	}

	/// Queries the glyph spacing for paths in the array
	/**
	 *  @glsymbols
	 *  @glfunref{GetPathSpacingNV}
	 */
	template <typename IndexType>
	void GetSpacing(
		PathNVListMode list_mode,
		const std::vector<IndexType>& indices,
		GLfloat advance_scale,
		GLfloat kerning_scale,
		PathNVTransformType transform_type,
		std::vector<GLfloat>& returned_values
	)
	{
		OGLPLUS_GLFUNC(GetPathSpacingNV)(
			GLenum(list_mode),
			GLsizei(indices.size()),
			GLenum(GetDataType<IndexType>()),
			(const void*)indices.data(),
			this->_names[0],
			advance_scale,
			kerning_scale,
			GLenum(transform_type),
			returned_values.data()
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GetPathSpacingNV));
	}

	/// Queries the glyph spacing for paths in the array
	/**
	 *  @glsymbols
	 *  @glfunref{GetPathSpacingNV}
	 */
	void GetSpacing(
		PathNVListMode list_mode,
		const String& indices,
		GLfloat advance_scale,
		GLfloat kerning_scale,
		PathNVTransformType transform_type,
		std::vector<GLfloat>& returned_values
	)
	{
		OGLPLUS_GLFUNC(GetPathSpacingNV)(
			GLenum(list_mode),
			GLsizei(indices.size()+1), //include null terminator
			GL_UTF8_NV,
			(const void*)indices.c_str(),
			this->_names[0],
			advance_scale,
			kerning_scale,
			GLenum(transform_type),
			returned_values.data()
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GetPathSpacingNV));
	}

	/// Queries the glyph metrics associated with a sequence of path objects
	/**
	 *  @glsymbols
	 *  @glfunref{GetPathMetricsNV}
	 */
	template <typename IndexType>
	void GetMetrics(
		Bitfield<PathNVMetricQuery> query_mask,
		GLsizei num_indices,
		const IndexType* indices,
		GLsizei stride,
		GLfloat* returned_values
	)
	{
		OGLPLUS_GLFUNC(GetPathMetricsNV)(
			GLbitfield(query_mask),
			num_indices,
			GLenum(GetDataType<IndexType>()),
			(const void*)indices,
			this->_names[0],
			stride,
			returned_values
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GetPathMetricsNV));
	}

	/// Queries the glyph metrics associated with a sequence of path objects
	/**
	 *  @glsymbols
	 *  @glfunref{GetPathMetricsNV}
	 */
	template <typename IndexType>
	void GetMetrics(
		Bitfield<PathNVMetricQuery> query_mask,
		const std::vector<IndexType>& indices,
		GLsizei stride,
		GLfloat* returned_values
	)
	{
		OGLPLUS_GLFUNC(GetPathMetricsNV)(
			GLbitfield(query_mask),
			GLsizei(indices.size()),
			GLenum(GetDataType<IndexType>()),
			(const void*)indices.data(),
			this->_names[0],
			stride,
			returned_values
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GetPathMetricsNV));
	}

	/// Queries the glyph metrics associated with a sequence of path objects
	/**
	 *  @glsymbols
	 *  @glfunref{GetPathMetricsNV}
	 */
	void GetMetrics(
		Bitfield<PathNVMetricQuery> query_mask,
		const String& indices,
		GLsizei stride,
		GLfloat* returned_values
	)
	{
		OGLPLUS_GLFUNC(GetPathMetricsNV)(
			GLbitfield(query_mask),
			GLsizei(indices.size()+1),
			GL_UTF8_NV,
			(const void*)indices.c_str(),
			this->_names[0],
			stride,
			returned_values
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GetPathMetricsNV));
	}

	/// Queries the glyph metrics associated with a range of path objects
	/**
	 *  @glsymbols
	 *  @glfunref{GetPathMetricRangeNV}
	 */
	void GetMetricRange(
		Bitfield<PathNVMetricQuery> query_mask,
		GLsizei num_paths,
		GLsizei stride,
		GLfloat* returned_values
	)
	{
		OGLPLUS_GLFUNC(GetPathMetricRangeNV)(
			GLbitfield(query_mask),
			this->_names[0],
			num_paths,
			stride,
			returned_values
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GetPathMetricRangeNV));
	}

	/// Writes the path interiors (fill) into the stencil buffer
	/**
	 *  @glsymbols
	 *  @glfunref{StencilFillPathInstancedNV}
	 */
	template <typename IndexType>
	void StencilFillInstanced(
		GLsizei num_paths,
		const IndexType* paths,
		PathNVFillMode mode,
		GLuint mask,
		PathNVTransformType transform_type,
		const GLfloat* transform_values
	)
	{
		OGLPLUS_GLFUNC(StencilFillPathInstancedNV)(
			num_paths,
			GLenum(GetDataType<IndexType>()),
			(const void*)paths,
			this->_names[0],
			GLenum(mode),
			mask,
			GLenum(transform_type),
			transform_values
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(StencilFillPathInstancedNV));
	}

	/// Writes the path interiors (fill) into the stencil buffer
	/**
	 *  @glsymbols
	 *  @glfunref{StencilFillPathInstancedNV}
	 */
	template <typename IndexType>
	void StencilFillInstanced(
		const std::vector<IndexType>& paths,
		PathNVFillMode mode,
		GLuint mask,
		PathNVTransformType transform_type,
		const std::vector<GLfloat>& transform_values
	)
	{
		// TODO: check if enough transform values
		// are provided for transform type
		OGLPLUS_GLFUNC(StencilFillPathInstancedNV)(
			GLsizei(paths.size()),
			GLenum(GetDataType<IndexType>()),
			(const void*)paths.data(),
			this->_names[0],
			GLenum(mode),
			mask,
			GLenum(transform_type),
			transform_values.data()
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(StencilFillPathInstancedNV));
	}

	/// Writes the path interiors (fill) into the stencil buffer
	/**
	 *  @glsymbols
	 *  @glfunref{StencilFillPathInstancedNV}
	 */
	void StencilFillInstanced(
		const String& paths,
		PathNVFillMode mode,
		GLuint mask,
		PathNVTransformType transform_type,
		const std::vector<GLfloat>& transform_values
	)
	{
		// TODO: check if enough transform values
		// are provided for transform type
		OGLPLUS_GLFUNC(StencilFillPathInstancedNV)(
			GLsizei(paths.size()),
			GL_UTF8_NV,
			(const void*)paths.c_str(),
			this->_names[0],
			GLenum(mode),
			mask,
			GLenum(transform_type),
			transform_values.data()
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(StencilFillPathInstancedNV));
	}

	/// Covers the path interiors (fill)
	/**
	 *  @glsymbols
	 *  @glfunref{CoverFillPathInstancedNV}
	 */
	template <typename IndexType>
	void CoverFillInstanced(
		GLsizei num_paths,
		const IndexType* paths,
		PathNVFillCoverMode mode,
		PathNVTransformType transform_type,
		const GLfloat* transform_values
	)
	{
		OGLPLUS_GLFUNC(CoverFillPathInstancedNV)(
			num_paths,
			GLenum(GetDataType<IndexType>()),
			(const void*)paths,
			this->_names[0],
			GLenum(mode),
			GLenum(transform_type),
			transform_values
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(CoverFillPathInstancedNV));
	}

	/// Covers the path interiors (fill)
	/**
	 *  @glsymbols
	 *  @glfunref{CoverFillPathInstancedNV}
	 */
	template <typename IndexType>
	void CoverFillInstanced(
		const std::vector<IndexType>& paths,
		PathNVFillCoverMode mode,
		PathNVTransformType transform_type,
		const std::vector<GLfloat>& transform_values
	)
	{
		OGLPLUS_GLFUNC(CoverFillPathInstancedNV)(
			GLsizei(paths.size()),
			GLenum(GetDataType<IndexType>()),
			(const void*)paths.data(),
			this->_names[0],
			GLenum(mode),
			GLenum(transform_type),
			transform_values.data()
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(CoverFillPathInstancedNV));
	}

	/// Covers the path interiors (fill)
	/**
	 *  @glsymbols
	 *  @glfunref{CoverFillPathInstancedNV}
	 */
	void CoverFillInstanced(
		const String& paths,
		PathNVFillCoverMode mode,
		PathNVTransformType transform_type,
		const std::vector<GLfloat>& transform_values
	)
	{
		OGLPLUS_GLFUNC(CoverFillPathInstancedNV)(
			GLsizei(paths.size()),
			GL_UTF8_NV,
			(const void*)paths.c_str(),
			this->_names[0],
			GLenum(mode),
			GLenum(transform_type),
			transform_values.data()
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(CoverFillPathInstancedNV));
	}

	/// Writes the path interiors strokes to the stencil buffer
	/**
	 *  @glsymbols
	 *  @glfunref{StencilStrokePathInstancedNV}
	 */
	template <typename IndexType>
	void StencilStrokeInstanced(
		GLsizei num_paths,
		const IndexType* paths,
		GLint reference,
		GLuint mask,
		PathNVTransformType transform_type,
		const GLfloat* transform_values
	)
	{
		OGLPLUS_GLFUNC(StencilStrokePathInstancedNV)(
			num_paths,
			GLenum(GetDataType<IndexType>()),
			(const void*)paths,
			this->_names[0],
			reference,
			mask,
			GLenum(transform_type),
			transform_values
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(StencilStrokePathInstancedNV));
	}

	/// Writes the path interiors strokes to the stencil buffer
	/**
	 *  @glsymbols
	 *  @glfunref{StencilStrokePathInstancedNV}
	 */
	template <typename IndexType>
	void StencilStrokeInstanced(
		const std::vector<IndexType>& paths,
		GLint reference,
		GLuint mask,
		PathNVTransformType transform_type,
		const std::vector<GLfloat>& transform_values
	)
	{
		OGLPLUS_GLFUNC(StencilStrokePathInstancedNV)(
			GLsizei(paths.size()),
			GLenum(GetDataType<IndexType>()),
			(const void*)paths.data(),
			this->_names[0],
			reference,
			mask,
			GLenum(transform_type),
			transform_values.data()
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(StencilStrokePathInstancedNV));
	}

	/// Writes the path interiors strokes to the stencil buffer
	/**
	 *  @glsymbols
	 *  @glfunref{StencilStrokePathInstancedNV}
	 */
	void StencilStrokeInstanced(
		const String& paths,
		GLint reference,
		GLuint mask,
		PathNVTransformType transform_type,
		const std::vector<GLfloat>& transform_values
	)
	{
		OGLPLUS_GLFUNC(StencilStrokePathInstancedNV)(
			GLsizei(paths.size()),
			GL_UTF8_NV,
			(const void*)paths.c_str(),
			this->_names[0],
			reference,
			mask,
			GLenum(transform_type),
			transform_values.data()
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(StencilStrokePathInstancedNV));
	}

	/// Covers the path strokes
	/**
	 *  @glsymbols
	 *  @glfunref{CoverFillPathInstancedNV}
	 */
	template <typename IndexType>
	void CoverStrokeInstanced(
		GLsizei num_paths,
		const IndexType* paths,
		PathNVStrokeCoverMode mode,
		PathNVTransformType transform_type,
		const GLfloat* transform_values
	)
	{
		OGLPLUS_GLFUNC(CoverStrokePathInstancedNV)(
			num_paths,
			GLenum(GetDataType<IndexType>()),
			(const void*)paths,
			this->_names[0],
			GLenum(mode),
			GLenum(transform_type),
			transform_values
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(CoverStrokePathInstancedNV));
	}

	/// Covers the path strokes
	/**
	 *  @glsymbols
	 *  @glfunref{CoverFillPathInstancedNV}
	 */
	template <typename IndexType>
	void CoverStrokeInstanced(
		const std::vector<IndexType>& paths,
		PathNVStrokeCoverMode mode,
		PathNVTransformType transform_type,
		const std::vector<GLfloat>& transform_values
	)
	{
		OGLPLUS_GLFUNC(CoverStrokePathInstancedNV)(
			GLsizei(paths.size()),
			GLenum(GetDataType<IndexType>()),
			(const void*)paths.data(),
			this->_names[0],
			GLenum(mode),
			GLenum(transform_type),
			transform_values.data()
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(CoverStrokePathInstancedNV));
	}

	/// Covers the path strokes
	/**
	 *  @glsymbols
	 *  @glfunref{CoverFillPathInstancedNV}
	 */
	void CoverStrokeInstanced(
		const String& paths,
		PathNVStrokeCoverMode mode,
		PathNVTransformType transform_type,
		const std::vector<GLfloat>& transform_values
	)
	{
		OGLPLUS_GLFUNC(CoverStrokePathInstancedNV)(
			GLsizei(paths.size()),
			GL_UTF8_NV,
			(const void*)paths.c_str(),
			this->_names[0],
			GLenum(mode),
			GLenum(transform_type),
			transform_values.data()
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(CoverStrokePathInstancedNV));
	}
};

/// Wrapper for the NV_path_rendering extension
/**
 *  @glsymbols
 *  @glextref{NV,path_rendering}
 *
 *  @ingroup gl_extensions
 */
class NV_path_rendering
{
public:
	OGLPLUS_EXTENSION_CLASS(NV, path_rendering)

	/// Sets the depth @p function to be used with path cover functions
	/**
	 *  @glsymbols
	 *  @glfunref{PathCoverDepthFuncNV}
	 */
	static void CoverDepthFunc(CompareFunction function)
	{
		OGLPLUS_GLFUNC(PathCoverDepthFuncNV)(GLenum(function));
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(PathCoverDepthFuncNV));
	}

	/// Sets the depth offset for rendered paths
	/**
	 *  @glsymbols
	 *  @glfunref{PathStencilDepthOffsetNV}
	 */
	static void DepthOffset(GLfloat factor, GLint units)
	{
		OGLPLUS_GLFUNC(PathStencilDepthOffsetNV)(factor, units);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(PathStencilDepthOffsetNV));
	}

	/// Sets how colors are computed for path covering fragment operations
	/**
	 *  @glsymbols
	 *  @glfunref{PathColorGenNV}
	 */
	static void ColorGen(
		PathNVColor color,
		PathNVGenMode gen_mode,
		PathNVColorFormat color_format,
		const GLfloat* coeffs
	)
	{
		OGLPLUS_GLFUNC(PathColorGenNV)(
			GLenum(color),
			GLenum(gen_mode),
			GLenum(color_format),
			coeffs
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(PathColorGenNV));
	}

	/// Sets how tex-coords are computed for path covering fragment operations
	/**
	 *  @glsymbols
	 *  @glfunref{PathTexGenNV}
	 */
	static void TexGen(
		TextureUnitSelector tex_unit,
		PathNVGenMode gen_mode,
		GLint components,
		const GLfloat* coeffs
	)
	{
		OGLPLUS_GLFUNC(PathTexGenNV)(
			GLenum(GL_TEXTURE0 + GLuint(tex_unit)),
			GLenum(gen_mode),
			components,
			coeffs
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(PathTexGenNV));
	}
};
#endif

} // namespace oglplus

#endif // include guard
