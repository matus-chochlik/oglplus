/**
 *  @file oglplus/shapes/draw.ipp
 *  @brief Implementation of shape draw instructions
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace oglplus {
namespace shapes {

OGLPLUS_LIB_FUNC
void DrawOperation::SetupPrimitiveRestart_(void) const
{
#if GL_VERSION_3_1
	if(restart_index == NoRestartIndex())
	{
		OGLPLUS_GLFUNC(Disable)(GL_PRIMITIVE_RESTART);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(Disable));
	}
	else
	{
		OGLPLUS_GLFUNC(Enable)(GL_PRIMITIVE_RESTART);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(Enable));
		OGLPLUS_GLFUNC(PrimitiveRestartIndex)(restart_index);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(PrimitiveRestartIndex));
	}
#else
	assert(!
		"Primitive restarting required, "
		"but not supported by the used version of OpenGL!"
	);
#endif
}

OGLPLUS_LIB_FUNC
void DrawOperation::CleanupPrimitiveRestart_(void) const
{
	if(restart_index != NoRestartIndex())
	{
		OGLPLUS_GLFUNC(Disable)(GL_PRIMITIVE_RESTART);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(Disable));
	}
}

OGLPLUS_LIB_FUNC
void DrawOperation::Draw_(
	void* indices,
	DataType index_data_type,
	GLuint inst_count,
	GLuint base_inst
) const
{
	switch(method)
	{
		case OGLPLUS_CONST_ENUM_VALUE(
			Method::DrawArrays
		): return DrawArrays_(
			inst_count,
			base_inst
		);

		case OGLPLUS_CONST_ENUM_VALUE(
			Method::DrawElements
		): return DrawElements_(
			indices,
			index_data_type,
			inst_count,
			base_inst
		);
	}
}


OGLPLUS_LIB_FUNC
void DrawOperation::DrawArrays_(GLuint inst_count, GLuint base_inst) const
{
	if(inst_count == 1)
	{
		OGLPLUS_GLFUNC(DrawArrays)(GLenum(mode), first, count);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(DrawArrays));
	}
	else if(base_inst == 0)
	{
#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_1
		OGLPLUS_GLFUNC(DrawArraysInstanced)(
			GLenum(mode),
			first,
			count,
			inst_count
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(DrawArraysInstanced));
#else
		assert(!
			"DrawArraysInstanced required, "
			"but not supported by the used version of OpenGL!"
		);
#endif
	}
	else
	{
#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_2
		OGLPLUS_GLFUNC(DrawArraysInstancedBaseInstance)(
			GLenum(mode),
			first,
			count,
			inst_count,
			base_inst
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(
			DrawArraysInstancedBaseInstance
		));
#else
		assert(!
			"DrawArraysInstancedBaseInstance required, "
			"but not supported by the used version of OpenGL!"
		);
#endif
	}
}

OGLPLUS_LIB_FUNC
void DrawOperation::DrawElements_(
	void* indices,
	DataType index_data_type,
	GLuint inst_count,
	GLuint base_inst
) const
{
	SetupPrimitiveRestart_();
	if(inst_count == 1)
	{
		OGLPLUS_GLFUNC(DrawElements)(
			GLenum(mode),
			count,
			GLenum(index_data_type),
			indices
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(DrawElements));
	}
	else if(base_inst == 0)
	{
#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_1
		OGLPLUS_GLFUNC(DrawElementsInstanced)(
			GLenum(mode),
			count,
			GLenum(index_data_type),
			indices,
			inst_count
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(
			DrawElementsInstanced
		));
#else
		assert(!
			"DrawElementsInstanced required, "
			"but not supported by the used version of OpenGL!"
		);
#endif
	}
	else
	{
#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_2
		OGLPLUS_GLFUNC(DrawElementsInstancedBaseInstance)(
			GLenum(mode),
			count,
			GLenum(index_data_type),
			indices,
			inst_count,
			base_inst
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(
			DrawElementsInstancedBaseInstance
		));
#else
		assert(!
			"DrawElementsInstancedBaseInstance required, "
			"but not supported by the used version of OpenGL!"
		);
#endif
	}
	CleanupPrimitiveRestart_();
}

} // shapes
} // oglplus

