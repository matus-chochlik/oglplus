/**
 *  @file oglplus/transform_feedback.hpp
 *  @brief TransformFeedback object wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_TRANSFORM_FEEDBACK_1107121519_HPP
#define OGLPLUS_TRANSFORM_FEEDBACK_1107121519_HPP

#include <oglplus/config.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>
#include <oglplus/object.hpp>
#include <oglplus/friend_of.hpp>
#include <oglplus/auxiliary/binding_query.hpp>
#include <cassert>

namespace oglplus {

/// The mode used to capture the varying variables in TF
/**
 *  @ingroup enumerations
 */
enum class TransformFeedbackMode : GLenum
{
#include <oglplus/enums/transform_feedback_mode.ipp>
};

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_0 || GL_ARB_transform_feedback2


/// Wrapper for fransform feedback operations
/** @note Do not use this class directly, use TransformFeedback instead.
 *
 *  @glsymbols
 *  @glfunref{GenTransformFeedbacks}
 *  @glfunref{DeleteTransformFeedbacks}
 *  @glfunref{IsTransformFeedback}
 */
class TransformFeedbackOps
 : public Named
{
protected:
	static void _init(GLsizei count, GLuint& _name)
	{
		OGLPLUS_GLFUNC(GenTransformFeedbacks)(count, &_name);
		HandleIfError(OGLPLUS_ERROR_INFO(GenTransformFeedbacks));
	}

	static void _cleanup(GLsizei count, GLuint& _name)
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(DeleteTransformFeedbacks)(count, &_name);
	}

	static GLboolean _is_x(GLuint _name)
	{
		assert(_name != 0);
		return OGLPLUS_GLFUNC(IsTransformFeedback)(_name);
	}

	friend class FriendOf<TransformFeedbackOps>;
public:
	/// Transform feedback bind targets
	enum class Target : GLenum {
#include <oglplus/enums/transform_feedback_target.ipp>
	};
protected:
	static GLenum _binding_query(Target target)
	{
		switch(GLenum(target))
		{
#include <oglplus/enums/transform_feedback_target_bq.ipp>
			default:;
		}
		return 0;
	}
	friend class BindingQuery<TransformFeedbackOps>;
public:

	/// Transform feedback primitive modes
	enum class PrimitiveType : GLenum {
#include <oglplus/enums/transform_feedback_primitive_type.ipp>
	};

	/// Bind this transform feedback object
	/**
	 *  @glsymbols
	 *  @glfunref{BindTransformFeedback}
	 */
	void Bind(Target target = Target::TransformFeedback) const
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(BindTransformFeedback)(GLenum(target), _name);
		AssertNoError(OGLPLUS_ERROR_INFO(BindTransformFeedback));
	}

	/// Bind the default transform feedback object
	/**
	 *  @glsymbols
	 *  @glfunref{BindTransformFeedback}
	 */
	static void BindDefault(Target target = Target::TransformFeedback)
	{
		OGLPLUS_GLFUNC(BindTransformFeedback)(GLenum(target), 0);
		AssertNoError(OGLPLUS_ERROR_INFO(BindTransformFeedback));
	}

	/// Begin the transform feedback mode
	/** Consider using an instance of Activator class for more robustness.
	 *  @throws Error
	 *
	 *  @see Activator
	 *  @see End
	 *
	 *  @glsymbols
	 *  @glfunref{BeginTransformFeedback}
	 */
	static void Begin(PrimitiveType mode)
	{
		OGLPLUS_GLFUNC(BeginTransformFeedback)(GLenum(mode));
		AssertNoError(OGLPLUS_ERROR_INFO(BeginTransformFeedback));
	}

	/// End the transform feedback mode
	/** Consider using an instance of Activator class for more robustness.
	 *  @throws Error
	 *
	 *  @see Activator
	 *  @see Begin
	 *
	 *  @glsymbols
	 *  @glfunref{EndTransformFeedback}
	 */
	static void End(void)
	{
		OGLPLUS_GLFUNC(EndTransformFeedback)();
		AssertNoError(OGLPLUS_ERROR_INFO(EndTransformFeedback));
	}

	/// Pause the transform feedback mode
	/** Consider using an instance of Pauser class for more robustness.
	 *  @throws Error
	 *
	 *  @see Pauser
	 *  @see Resume
	 *
	 *  @glsymbols
	 *  @glfunref{PauseTransformFeedback}
	 */
	static void Pause(void)
	{
		OGLPLUS_GLFUNC(PauseTransformFeedback)();
		AssertNoError(OGLPLUS_ERROR_INFO(PauseTransformFeedback));
	}

	/// Resume the transform feedback mode
	/** Consider using an instance of Pauser class for more robustness.
	 *  @throws Error
	 *
	 *  @see Pauser
	 *  @see Pause
	 *
	 *  @glsymbols
	 *  @glfunref{ResumeTransformFeedback}
	 */
	static void Resume(void)
	{
		OGLPLUS_GLFUNC(ResumeTransformFeedback)();
		AssertNoError(OGLPLUS_ERROR_INFO(ResumeTransformFeedback));
	}

	/// Class lifetime of which controls the (de)activation of TFB
	/** This class activates transform feedback mode when it is
	 *  constructed and deactivates it in destructor. It is a more
	 *  robust and preferred mode of transform feedback activation
	 *  and deactivation.
	 *
	 *  @glsymbols
	 *  @glfunref{BeginTransformFeedback}
	 *  @glfunref{EndTransformFeedback}
	 */
	class Activator
	{
	private:
		bool _active;
	public:
		/// Begins transform feedback
		/**
		 *  @glsymbols
		 *  @glfunref{BeginTransformFeedback}
		 */
		Activator(PrimitiveType mode)
		 : _active(true)
		{
			OGLPLUS_GLFUNC(BeginTransformFeedback)(GLenum(mode));
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
		/**
		 *  @glsymbols
		 *  @glfunref{EndTransformFeedback}
		 */
		~Activator(void)
		{
			if(_active) OGLPLUS_GLFUNC(EndTransformFeedback)();
		}
	};

	/// Class lifetime of which controls the pausing/resuming of TFB
	/** This class pauses active transform feedback when it is
	 *  constructed and resumes it in destructor. It is a more
	 *  robust and preferred mode of transform feedback activation
	 *  and deactivation.
	 *
	 *  @glsymbols
	 *  @glfunref{PauseTransformFeedback}
	 *  @glfunref{ResumeTransformFeedback}
	 */
	class Pauser
	{
	private:
		bool _paused;
	public:
		/// Pauses transform feedback
		/**
		 *  @glsymbols
		 *  @glfunref{PauseTransformFeedback}
		 */
		Pauser(void)
		 : _paused(true)
		{
			OGLPLUS_GLFUNC(PauseTransformFeedback)();
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
		/**
		 *  @glsymbols
		 *  @glfunref{ResumeTransformFeedback}
		 */
		~Pauser(void)
		{
			if(_paused) OGLPLUS_GLFUNC(ResumeTransformFeedback)();
		}
	};
};


#if OGLPLUS_DOCUMENTATION_ONLY
/// An @ref oglplus_object encapsulating the OpenGL transform feedback functionality
/**
 *  @ingroup objects
 */
class TransformFeedback
 : public TransformFeedbackOps
{ };
#else
typedef Object<TransformFeedbackOps, true> TransformFeedback;
#endif

#endif // transform feedback 2

} // namespace oglplus

#endif // include guard
