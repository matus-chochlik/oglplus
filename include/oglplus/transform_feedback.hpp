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
#include <oglplus/friend_of.hpp>
#include <cassert>

namespace oglplus {

/// The mode used to capture the varying variables in TF
enum class TransformFeedbackMode : GLenum
{
	/// INTERLEAVED_ATTRIBS
	InterleavedAttribs = GL_INTERLEAVED_ATTRIBS,
	/// SEPARATE_ATTRIBS
	SeparateAttribs = GL_SEPARATE_ATTRIBS
};

class TransformFeedbackOps
 : public Named
{
protected:
	static void _init(GLsizei count, GLuint& _name)
	{
		::glGenTransformFeedbacks(count, &_name);
		ThrowOnError(OGLPLUS_ERROR_INFO(GenTransformFeedbacks));
	}

	static void _cleanup(GLsizei count, GLuint& _name)
	{
		assert(_name != 0);
		::glDeleteTransformFeedbacks(count, &_name);
	}

	static GLboolean _is_x(GLuint _name)
	{
		assert(_name != 0);
		return ::glIsTransformFeedback(_name);
	}

	friend class FriendOf<TransformFeedbackOps>;
public:
	/// Transform feedback bind targets
	enum class Target : GLenum {
		/// The default target (TRANSFORM_FEEDBACK)
		Default = GL_TRANSFORM_FEEDBACK
	};

	/// Transform feedback primitive modes
	enum class PrimitiveType : GLenum {
		/// TRIANGLES
		Triangles = GL_TRIANGLES,
		/// LINES
		Lines = GL_LINES,
		/// POINTS
		Points = GL_POINTS
	};

	/// Bind this transform feedback object
	void Bind(Target target = Target::Default) const
	{
		assert(_name != 0);
		::glBindTransformFeedback(GLenum(target), _name);
		AssertNoError(OGLPLUS_ERROR_INFO(BindTransformFeedback));
	}

	/// Bind the default transform feedback object
	static void BindDefault(Target target = Target::Default)
	{
		::glBindTransformFeedback(GLenum(target), 0);
		AssertNoError(OGLPLUS_ERROR_INFO(BindTransformFeedback));
	}

	/// Begin the transform feedback mode
	/** Consider using an instance of Activator class for more robustness.
	 *  @throws Error
	 *
	 *  @see Activator
	 *  @see End
	 */
	static void Begin(PrimitiveType mode)
	{
		::glBeginTransformFeedback(GLenum(mode));
		AssertNoError(OGLPLUS_ERROR_INFO(BeginTransformFeedback));
	}

	/// End the transform feedback mode
	/** Consider using an instance of Activator class for more robustness.
	 *  @throws Error
	 *
	 *  @see Activator
	 *  @see Begin
	 */
	static void End(void)
	{
		::glEndTransformFeedback();
		AssertNoError(OGLPLUS_ERROR_INFO(EndTransformFeedback));
	}

	/// Pause the transform feedback mode
	/** Consider using an instance of Pauser class for more robustness.
	 *  @throws Error
	 *
	 *  @see Pauser
	 *  @see Resume
	 */
	static void Pause(void)
	{
		::glPauseTransformFeedback();
		AssertNoError(OGLPLUS_ERROR_INFO(PauseTransformFeedback));
	}

	/// Resume the transform feedback mode
	/** Consider using an instance of Pauser class for more robustness.
	 *  @throws Error
	 *
	 *  @see Pauser
	 *  @see Pause
	 */
	static void Resume(void)
	{
		::glResumeTransformFeedback();
		AssertNoError(OGLPLUS_ERROR_INFO(ResumeTransformFeedback));
	}

	/// Class lifetime of which controls the (de)activation of TFB
	/** This class activates transform feedback mode when it is
	 *  constructed and deactivates it in destructor. It is a more
	 *  robust and preferred mode of transform feedback activation
	 *  and deactivation.
	 */
	class Activator
	{
	private:
		bool _active;
	public:
		/// Begins transform feedback
		Activator(PrimitiveType mode)
		 : _active(true)
		{
			::glBeginTransformFeedback(GLenum(mode));
			AssertNoError(OGLPLUS_ERROR_INFO(BeginTransformFeedback));
		}

		/// Copying is disabled
		Activator(const Activator&) = delete;

		Activator(Activator&& tmp)
		 : _active(tmp._active)
		{
			tmp._active = false;
		}

		/// Ends transform feedback
		~Activator(void)
		{
			if(_active) ::glEndTransformFeedback();
		}
	};

	/// Class lifetime of which controls the pausing/resuming of TFB
	/** This class pauses active transform feedback when it is
	 *  constructed and resumes it in destructor. It is a more
	 *  robust and preferred mode of transform feedback activation
	 *  and deactivation.
	 */
	class Pauser
	{
	private:
		bool _paused;
	public:
		/// Pauses transform feedback
		Pauser(void)
		 : _paused(true)
		{
			::glPauseTransformFeedback();
			AssertNoError(OGLPLUS_ERROR_INFO(PauseTransformFeedback));
		}

		/// Copying is disabled
		Pauser(const Pauser&) = delete;

		Pauser(Pauser&& tmp)
		 : _paused(tmp._paused)
		{
			tmp._paused = false;
		}

		/// Resumes transform feedback
		~Pauser(void)
		{
			if(_paused) ::glResumeTransformFeedback();
		}
	};
};


#ifdef OGLPLUS_DOCUMENTATION_ONLY
/// An @ref oglplus_object encapsulating the OpenGL transform feedback functionality
class TransformFeedback
 : public TransformFeedbackOps
{ };
#else
typedef Object<TransformFeedbackOps, true> TransformFeedback;
#endif

} // namespace oglplus

#endif // include guard
