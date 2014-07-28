/**
 *  @file oglplus/shapes/draw.ipp
 *  @brief Implementation of shape draw instructions
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/lib/incl_begin.ipp>
#include <oglplus/glfunc.hpp>
#include <oglplus/error/basic.hpp>
#include <oglplus/lib/incl_end.ipp>

namespace oglplus {
namespace shapes {

OGLPLUS_LIB_FUNC
void DrawOperation::SetupPrimitiveRestart_(void) const
{
#if GL_VERSION_3_1
	if(restart_index == NoRestartIndex())
	{
		OGLPLUS_GLFUNC(Disable)(GL_PRIMITIVE_RESTART);
		OGLPLUS_VERIFY_SIMPLE(Disable);
	}
	else
	{
		OGLPLUS_GLFUNC(Enable)(GL_PRIMITIVE_RESTART);
		OGLPLUS_VERIFY_SIMPLE(Enable);
		OGLPLUS_GLFUNC(PrimitiveRestartIndex)(restart_index);
		OGLPLUS_VERIFY_SIMPLE(PrimitiveRestartIndex);
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
		OGLPLUS_VERIFY_SIMPLE(Disable);
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
		case Method::DrawArrays:
		{
			return DrawArrays_(
				inst_count,
				base_inst
			);
		}

		case Method::DrawElements:
		{
			return DrawElements_(
				indices,
				index_data_type,
				inst_count,
				base_inst
			);
		}
	}
}


OGLPLUS_LIB_FUNC
void DrawOperation::DrawArrays_(GLuint inst_count, GLuint base_inst) const
{
	if(inst_count == 1)
	{
		OGLPLUS_GLFUNC(DrawArrays)(GLenum(mode), first, count);
		OGLPLUS_CHECK_SIMPLE(DrawArrays);
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
		OGLPLUS_CHECK_SIMPLE(DrawArraysInstanced);
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
		OGLPLUS_CHECK_SIMPLE(DrawArraysInstancedBaseInstance);
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
		OGLPLUS_CHECK_SIMPLE(DrawElements);
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
		OGLPLUS_CHECK_SIMPLE(DrawElementsInstanced);
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
		OGLPLUS_CHECK_SIMPLE(DrawElementsInstancedBaseInstance);
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

