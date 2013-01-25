/**
 *  @file oglplus/auxiliary/uniform_typecheck.hpp
 *  @brief Helper base class templates used for uniform variable initialization
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_AUX_UNIFORM_TYPECHECK_1107121519_HPP
#define OGLPLUS_AUX_UNIFORM_TYPECHECK_1107121519_HPP

#include <oglplus/config.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>
#include <oglplus/auxiliary/glsl_to_cpp.hpp>

#include <vector>
#include <cstring>
#include <cassert>

namespace oglplus {
namespace aux {

class NoUniformTypecheck
{
public:
	inline NoUniformTypecheck(void)
	OGLPLUS_NOEXCEPT(true)
	{ }

	template <typename T>
	inline NoUniformTypecheck(T* /*selector*/)
	OGLPLUS_NOEXCEPT(true)
	{ }

	inline bool operator()(
		GLuint /*_program*/,
		GLint /*location*/,
		const GLchar* /*identifier*/
	) const
	OGLPLUS_NOEXCEPT(true)
	{
		return true;
	}
};

#if !OGLPLUS_NO_UNIFORM_TYPECHECK

class UniformTypecheckBase
{
protected:
	static GLenum _query_uniform_type(
		GLuint program,
		GLint /*location*/,
		const GLchar* identifier
	)
	{
		GLenum type, result = GL_NONE;
		GLint size;
		GLsizei length = 0;
		const GLsizei id_len = std::strlen(identifier);
		// The +2 is intentional
		// to distinguish between the searched identifier
		// and the udentifiers having the searched identifier
		// as prefix
		std::vector<GLchar> buffer(id_len+2);

		GLint active_uniforms = 0;
		OGLPLUS_GLFUNC(GetProgramiv)(
			program,
			GL_ACTIVE_UNIFORMS,
			&active_uniforms
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(GetProgramiv));

		for(GLint index=0; index!=active_uniforms; ++index)
		{
			OGLPLUS_GLFUNC(GetActiveUniform)(
				program,
				index,
				buffer.size(),
				&length,
				&size,
				&type,
				buffer.data()
			);
			OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(GetActiveUniform));
			if(id_len == length)
			{
				if(std::strncmp(
					identifier,
					buffer.data(),
					length
				) == 0)
				{
					result = type;
					break;
				}
			}
		}
		return result;
	}

	bool (*_uniform_type_match)(GLenum);
public:
	UniformTypecheckBase(bool (*uniform_type_match)(GLenum))
	 : _uniform_type_match(uniform_type_match)
	{ }

	bool operator()(
		GLuint program,
		GLint location,
		const GLchar* identifier
	) const
	{
		assert(_uniform_type_match);
		return _uniform_type_match(
			_query_uniform_type(
				program,
				location,
				identifier
			)
		);
	}
};

template <typename T>
struct DefaultGLSLtoCppTypeMatcher
{
	static bool _matches(GLenum /*sl_type*/)
	{
		return false;
	}
};

template <oglplus::SLDataType SLType>
struct DefaultGLSLtoCppTypeMatcher<oglplus::SLtoCpp<SLType> >
{
	static bool _matches(GLenum sl_type)
	{
		return sl_type == GLenum(SLType);
	}
};

template <>
struct DefaultGLSLtoCppTypeMatcher<bool>
{
	static bool _matches(GLenum sl_type)
	{
		return sl_type == GL_BOOL;
	}
};

template <>
struct DefaultGLSLtoCppTypeMatcher<GLint>
{
	static bool _matches(GLenum sl_type)
	{
		const GLenum allowed[] = {
			GL_INT,
			GL_BOOL,

#ifdef GL_IMAGE_1D
			GL_IMAGE_1D,
			GL_IMAGE_1D_ARRAY,
			GL_IMAGE_2D,
			GL_IMAGE_2D_ARRAY,
			GL_IMAGE_2D_MULTISAMPLE,
			GL_IMAGE_2D_MULTISAMPLE_ARRAY,
			GL_IMAGE_2D_RECT,
			GL_IMAGE_3D,
			GL_IMAGE_BUFFER,
			GL_IMAGE_CUBE,
#endif

#ifdef GL_INT_IMAGE_1D
			GL_INT_IMAGE_1D,
			GL_INT_IMAGE_1D_ARRAY,
			GL_INT_IMAGE_2D,
			GL_INT_IMAGE_2D_ARRAY,
			GL_INT_IMAGE_2D_MULTISAMPLE,
			GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY,
			GL_INT_IMAGE_2D_RECT,
			GL_INT_IMAGE_3D,
			GL_INT_IMAGE_BUFFER,
			GL_INT_IMAGE_CUBE,
#endif

#ifdef GL_UNSIGNED_INT_IMAGE_CUBE
			GL_UNSIGNED_INT_IMAGE_1D,
			GL_UNSIGNED_INT_IMAGE_1D_ARRAY,
			GL_UNSIGNED_INT_IMAGE_2D,
			GL_UNSIGNED_INT_IMAGE_2D_ARRAY,
			GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE,
			GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY,
			GL_UNSIGNED_INT_IMAGE_2D_RECT,
			GL_UNSIGNED_INT_IMAGE_3D,
			GL_UNSIGNED_INT_IMAGE_BUFFER,
			GL_UNSIGNED_INT_IMAGE_CUBE,
#endif

			GL_INT_SAMPLER_1D,
			GL_INT_SAMPLER_1D_ARRAY,
			GL_INT_SAMPLER_2D,
			GL_INT_SAMPLER_2D_ARRAY,
			GL_INT_SAMPLER_2D_MULTISAMPLE,
			GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY,
			GL_INT_SAMPLER_2D_RECT,
			GL_INT_SAMPLER_3D,
			GL_INT_SAMPLER_BUFFER,
			GL_INT_SAMPLER_CUBE,
			GL_INT_SAMPLER_CUBE_MAP_ARRAY,
			GL_UNSIGNED_INT_SAMPLER_1D,
			GL_UNSIGNED_INT_SAMPLER_1D_ARRAY,
			GL_UNSIGNED_INT_SAMPLER_2D,
			GL_UNSIGNED_INT_SAMPLER_2D_ARRAY,
			GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE,
			GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY,
			GL_UNSIGNED_INT_SAMPLER_2D_RECT,
			GL_UNSIGNED_INT_SAMPLER_3D,
			GL_UNSIGNED_INT_SAMPLER_BUFFER,
			GL_UNSIGNED_INT_SAMPLER_CUBE,
			GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY,
			GL_SAMPLER_1D,
			GL_SAMPLER_1D_ARRAY,
			GL_SAMPLER_1D_ARRAY_SHADOW,
			GL_SAMPLER_1D_SHADOW,
			GL_SAMPLER_2D,
			GL_SAMPLER_2D_ARRAY,
			GL_SAMPLER_2D_ARRAY_SHADOW,
			GL_SAMPLER_2D_MULTISAMPLE,
			GL_SAMPLER_2D_MULTISAMPLE_ARRAY,
			GL_SAMPLER_2D_RECT,
			GL_SAMPLER_2D_RECT_SHADOW,
			GL_SAMPLER_2D_SHADOW,
			GL_SAMPLER_3D,
			GL_SAMPLER_BUFFER,
			GL_SAMPLER_CUBE,
			GL_SAMPLER_CUBE_MAP_ARRAY,
			GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW,
			GL_SAMPLER_CUBE_SHADOW
		};
		std::size_t i=0, n=sizeof(allowed)/sizeof(allowed[0]);

		while(i != n) if(sl_type == allowed[i++]) return true;

		return false;
	}
};

template <>
struct DefaultGLSLtoCppTypeMatcher<GLuint>
{
	static bool _matches(GLenum sl_type)
	{
		const GLenum allowed[] = {
			GL_UNSIGNED_INT,
#ifdef GL_UNSIGNED_INT_ATOMIC_COUNTER
			GL_UNSIGNED_INT_ATOMIC_COUNTER,
#endif
			GL_BOOL
		};
		std::size_t i=0, n=sizeof(allowed)/sizeof(allowed[0]);

		while(i != n) if(sl_type == allowed[i++]) return true;

		return false;
	}
};

template <>
struct DefaultGLSLtoCppTypeMatcher<GLfloat>
{
	static bool _matches(GLenum sl_type)
	{
		return sl_type == GL_FLOAT;
	}
};

template <>
struct DefaultGLSLtoCppTypeMatcher<GLdouble>
{
	static bool _matches(GLenum sl_type)
	{
		return sl_type == GL_DOUBLE;
	}
};

template <typename T, std::size_t N>
struct DefaultGLSLtoCppTypeMatcher<oglplus::Vector<T, N> >
{
	static_assert(N <= 4, "Invalid vector size");

	static std::size_t _type_idx(bool*) { return 0; }
	static std::size_t _type_idx(GLint*) { return 1; }
	static std::size_t _type_idx(GLuint*) { return 2; }
	static std::size_t _type_idx(GLfloat*) { return 3; }
	static std::size_t _type_idx(GLdouble*) { return 4; }

	static T* _type_sel(void) { return nullptr; }

	static bool _matches(GLenum sl_type)
	{
		const GLenum allowed[5][4] = {
			{
				GL_BOOL,
				GL_BOOL_VEC2,
				GL_BOOL_VEC3,
				GL_BOOL_VEC4
			}, {
				GL_INT,
				GL_INT_VEC2,
				GL_INT_VEC3,
				GL_INT_VEC4
			}, {
				GL_UNSIGNED_INT,
				GL_UNSIGNED_INT_VEC2,
				GL_UNSIGNED_INT_VEC3,
				GL_UNSIGNED_INT_VEC4
			}, {
				GL_FLOAT,
				GL_FLOAT_VEC2,
				GL_FLOAT_VEC3,
				GL_FLOAT_VEC4
			}, {
				GL_DOUBLE,
				GL_DOUBLE_VEC2,
				GL_DOUBLE_VEC3,
				GL_DOUBLE_VEC4
			}
		};
		return sl_type == allowed[_type_idx(_type_sel())][N-1];
	}
};

template <typename T, std::size_t Rows, std::size_t Cols>
struct DefaultGLSLtoCppTypeMatcher<oglplus::Matrix<T, Rows, Cols> >
{
	static_assert(Rows >= 2, "Invalid matrix size");
	static_assert(Cols >= 2, "Invalid matrix size");

	static_assert(Rows <= 4, "Invalid matrix size");
	static_assert(Cols <= 4, "Invalid matrix size");

	static std::size_t _type_idx(GLfloat*) { return 0; }
	static std::size_t _type_idx(GLdouble*) { return 1; }

	static T* _type_sel(void) { return nullptr; }

	static bool _matches(GLenum sl_type)
	{
		const GLenum allowed[2][3][3] = {
			{
				{
					GL_FLOAT_MAT2,
					GL_FLOAT_MAT3x2,
					GL_FLOAT_MAT4x2
				}, {
					GL_FLOAT_MAT2x3,
					GL_FLOAT_MAT3,
					GL_FLOAT_MAT4x3
				}, {
					GL_FLOAT_MAT2x4,
					GL_FLOAT_MAT3x4,
					GL_FLOAT_MAT4
				}
			}, {
				{
					GL_DOUBLE_MAT2,
					GL_DOUBLE_MAT3x2,
					GL_DOUBLE_MAT4x2
				}, {
					GL_DOUBLE_MAT2x3,
					GL_DOUBLE_MAT3,
					GL_DOUBLE_MAT4x3
				}, {
					GL_DOUBLE_MAT2x4,
					GL_DOUBLE_MAT3x4,
					GL_DOUBLE_MAT4
				}
			}
		};
		return sl_type==allowed[_type_idx(_type_sel())][Rows-2][Cols-2];
	}
};

class DefaultUniformTypecheck
 : public UniformTypecheckBase
{
public:
	template <typename TypeSel>
	DefaultUniformTypecheck(TypeSel* /*type_sel*/)
	 : UniformTypecheckBase(&DefaultGLSLtoCppTypeMatcher<TypeSel>::_matches)
	{ }
};
#endif // !OGLPLUS_NO_UNIFORM_TYPECHECK

class UniformInitTypecheckUtils
{
protected:
	template <typename Typechecker>
	GLint _typecheck(
		Typechecker& type_ok,
		GLuint program,
		GLint location,
		const GLchar* identifier
	)
	{
		if(!type_ok(program, location, identifier))
		{
			Error::PropertyMapInit props;
			Error::AddPropertyValue(
				props,
				"identifier",
				identifier
			);
			Error::AddPropertyValue(
				props,
				"program",
				aux::ObjectDescRegistry<ProgramOps>::
						_get_desc(program)
			);
			HandleShaderVariableError(
				GL_INVALID_OPERATION,
				location,
				"Uniform type mismatch",
				OGLPLUS_ERROR_INFO_STR("Uniform"),
				std::move(props)
			);
		}
		return location;
	}
};

} // namespace aux

typedef aux::NoUniformTypecheck NoTypecheck;

#if !OGLPLUS_NO_UNIFORM_TYPECHECK
typedef aux::DefaultUniformTypecheck DefaultTypecheck;
#else
typedef aux::NoUniformTypecheck DefaultTypecheck;
#endif

} // namespace oglplus

#endif // include guard
