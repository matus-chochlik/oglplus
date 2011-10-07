/**
 *  .file oglplus/auxiliary/prog_pl_stages.hpp
 *  .brief Helper class used by ProgramPipeline::UseStages
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_AUX_PROG_PL_STAGES_1107121519_HPP
#define OGLPLUS_AUX_PROG_PL_STAGES_1107121519_HPP

#include <oglplus/error.hpp>

namespace oglplus {

class ProgramPipelineOps;

namespace aux {

class ProgPLUseStages
{
private:
	GLuint _pipeline, _program;
	GLbitfield _bits;

	GLbitfield _forward(void)
	{
		GLbitfield res = _bits;
		_bits = 0;
		return res;
	}

	friend class oglplus::ProgramPipelineOps;

	ProgPLUseStages(void) = delete;
	ProgPLUseStages(const ProgPLUseStages&) = delete;
	ProgPLUseStages(GLuint pipeline, GLuint program, GLbitfield bits)
	 : _pipeline(pipeline)
	 , _program(program)
	 , _bits(bits)
	{ }

	inline ProgPLUseStages _make(GLbitfield bit)
	{
		return ProgPLUseStages(_pipeline, _program, _forward() | bit);
	}
public:
	inline ProgPLUseStages Vertex(void)
	{
		return _make(GL_VERTEX_SHADER_BIT);
	}

	inline ProgPLUseStages TessControl(void)
	{
		return _make(GL_TESS_CONTROL_SHADER_BIT);
	}

	inline ProgPLUseStages TessEvaluation(void)
	{
		return _make(GL_TESS_EVALUATION_SHADER_BIT);
	}

	inline ProgPLUseStages Geometry(void)
	{
		return _make(GL_GEOMETRY_SHADER_BIT);
	}

	inline ProgPLUseStages Fragment(void)
	{
		return _make(GL_FRAGMENT_SHADER_BIT);
	}

	inline ProgPLUseStages All(void)
	{
		return _make(GL_ALL_SHADER_BITS);
	}

	inline ProgPLUseStages(ProgPLUseStages&& temp)
	 : _pipeline(temp._pipeline)
	 , _program(temp._program)
	 , _bits(temp._forward())
	{ }

	inline ~ProgPLUseStages(void)
	{
		if(_bits)
		{
			assert(_pipeline);
			assert(_program);
			::glUseProgramStages(_pipeline, _bits, _program);
			AssertNoError(OGLPLUS_ERROR_INFO(UseProgramStages));
		}
	}
};

} // namespace aux

} // namespace oglplus

#endif // include guard
