/**
 *  @file oglplus/transform_feedback.hpp
 *  @brief TransformFeedback object wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_TRANSFORM_FEEDBACK_1107121519_HPP
#define OGLPLUS_TRANSFORM_FEEDBACK_1107121519_HPP

#include <oglplus/error.hpp>
#include <oglplus/object.hpp>

namespace oglplus {

class TransformFeedbackOps
{
protected:
	GLuint _name;

	TransformFeedbackOps(void)
	{ }

	static void _init(GLsizei count, GLuint& _name)
	{
		::glGenTransformFeedbacks(count, &_name);
		ThrowOnError();
	}

	static void _cleanup(GLsizei count, GLuint& _name)
	{
		::glDeleteTransformFeedbacks(count, &_name);
	}
public:
	TransformFeedbackOps(GLuint _n)
	 : _name(_n)
	{ }

	enum class Kind {
		Default = GL_TRANSFORM_FEEDBACK
	};

	void Bind(Kind target = Kind::Default) const
	{
		::glBindTransformFeedback(GLenum(target), _name);
	}
};

typedef Object<TransformFeedbackOps> TransformFeedback;

} // namespace oglplus

#endif // include guard
