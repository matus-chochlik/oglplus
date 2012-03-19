/**
 *  @file oglplus/ext/NV_path_rendering.hpp
 *  @brief Wrapper for the NV_path_rendering extension
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_EXT_NV_PATH_RENDERING_1203031902_HPP
#define OGLPLUS_EXT_NV_PATH_RENDERING_1203031902_HPP

#include <oglplus/extension.hpp>
#include <oglplus/object.hpp>
#include <oglplus/data_type.hpp>
#include <oglplus/string.hpp>
#include <oglplus/texture_unit.hpp>

namespace oglplus {

#if OGLPLUS_DOCUMENTNVON_ONLY || GL_NV_path_rendering

/// Path specification command enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glextref{NV,path_rendering}
 */
enum class PathNVCommand : GLubyte
{
#include <oglplus/enums/ext/nv_path_command.ipp>
};

inline const GLchar* EnumValueName(PathNVCommand value)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/ext/nv_path_command.ipp>
#endif
	return "";
}

/// Path specification string format enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glextref{NV,path_rendering}
 */
enum class PathNVFormat : GLenum
{
#include <oglplus/enums/ext/nv_path_format.ipp>
};

inline const GLchar* EnumValueName(PathNVFormat value)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/ext/nv_path_format.ipp>
#endif
	return "";
}

/// Path fill mode
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glextref{NV,path_rendering}
 */
enum class PathNVFillMode : GLenum
{
#include <oglplus/enums/ext/nv_path_fill_mode.ipp>
};

inline const GLchar* EnumValueName(PathNVFillMode value)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/ext/nv_path_fill_mode.ipp>
#endif
	return "";
}

/// Path fill covering mode
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glextref{NV,path_rendering}
 */
enum class PathNVFillCoverMode : GLenum
{
#include <oglplus/enums/ext/nv_path_fill_cover_mode.ipp>
};

inline const GLchar* EnumValueName(PathNVFillCoverMode value)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/ext/nv_path_fill_cover_mode.ipp>
#endif
	return "";
}

/// Path stroke covering move
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glextref{NV,path_rendering}
 */
enum class PathNVStrokeCoverMode : GLenum
{
#include <oglplus/enums/ext/nv_path_stroke_cover_mode.ipp>
};

inline const GLchar* EnumValueName(PathNVStrokeCoverMode value)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/ext/nv_path_stroke_cover_mode.ipp>
#endif
	return "";
}

/// Stroke line join style enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glextref{NV,path_rendering}
 */
enum class PathNVJoinStyle : GLenum
{
#include <oglplus/enums/ext/nv_path_join_style.ipp>
};

inline const GLchar* EnumValueName(PathNVJoinStyle value)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/ext/nv_path_join_style.ipp>
#endif
	return "";
}

/// Path cap mode enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glextref{NV,path_rendering}
 */
enum class PathNVCapStyle : GLenum
{
#include <oglplus/enums/ext/nv_path_cap_style.ipp>
};

inline const GLchar* EnumValueName(PathNVCapStyle value)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/ext/nv_path_cap_style.ipp>
#endif
	return "";
}

/// Path dash offset reset mode enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glextref{NV,path_rendering}
 */
enum class PathNVDashOffsetReset : GLenum
{
#include <oglplus/enums/ext/nv_path_dash_offset_reset.ipp>
};

inline const GLchar* EnumValueName(PathNVDashOffsetReset value)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/ext/nv_path_dash_offset_reset.ipp>
#endif
	return "";
}

/// Path color mode enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glextref{NV,path_rendering}
 */
enum class PathNVColor : GLenum
{
#include <oglplus/enums/ext/nv_path_color.ipp>
};

inline const GLchar* EnumValueName(PathNVColor value)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/ext/nv_path_color.ipp>
#endif
	return "";
}

/// Path color format enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glextref{NV,path_rendering}
 */
enum class PathNVColorFormat : GLenum
{
#include <oglplus/enums/ext/nv_path_color_format.ipp>
};

inline const GLchar* EnumValueName(PathNVColorFormat value)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/ext/nv_path_color_format.ipp>
#endif
	return "";
}

/// Path color and tex-coord generation mode enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glextref{NV,path_rendering}
 */
enum class PathNVGenMode : GLenum
{
#include <oglplus/enums/ext/nv_path_gen_mode.ipp>
};

inline const GLchar* EnumValueName(PathNVGenMode value)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/ext/nv_path_gen_mode.ipp>
#endif
	return "";
}

/// Path transform type enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glextref{NV,path_rendering}
 */
enum class PathNVTransformType : GLenum
{
#include <oglplus/enums/ext/nv_path_transform_type.ipp>
};

inline const GLchar* EnumValueName(PathNVTransformType value)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/ext/nv_path_transform_type.ipp>
#endif
	return "";
}

class PathNVOps
 : public Named
{
protected:
	static void _init(GLsizei count, GLuint* _name)
	{
		assert(_name != nullptr);
		*_name = OGLPLUS_GLFUNC(GenPathsNV)(count);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GenTextures));
	}

	static void _cleanup(GLsizei count, GLuint* _name)
	{
		assert(_name != nullptr);
		assert(*_name != 0);
		OGLPLUS_GLFUNC(DeletePathsNV)(count, *_name);
	}

	static GLboolean _is_x(GLuint _name)
	{
		assert(_name != 0);
		return OGLPLUS_GLFUNC(IsPathNV)(_name);
	}

	friend class FriendOf<PathNVOps>;
public:
	/// Specifies the path via a set of commands and coordinates
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
			(const GLubyte*)(commands),
			num_coords,
			GLenum(GetDataType<CoordType>()),
			static_cast<const void*>(coords)
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(PathCommandsNV));
	}

	/// Specifies the path via a set of coordinates
	/**
	 *  @glsymbols
	 *  @glfunref{PathCoordsNV}
	 */
	template <typename CoordType>
	void Coords(
		GLsizei num_coords,
		const CoordType* coords
	)
	{
		OGLPLUS_GLFUNC(PathCoordsNV)(
			this->_name,
			num_coords,
			GLenum(GetDataType<CoordType>()),
			static_cast<const void*>(coords)
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
			(const GLubyte*)(commands),
			num_coords,
			GLenum(GetDataType<CoordType>()),
			static_cast<const void*>(coords)
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
 *  @ingroup objects
 */
class PathNV
 : public PathNVOps
{ };
#else
typedef Object<PathNVOps, false> PathNV;
#endif


/// Wrapper for the NV_path_rendering extension
/**
 *  @glsymbols
 *  @glextref{NV,path_rendering}
 *
 *  @ingroup extensions
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
