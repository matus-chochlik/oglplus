/**
 *  @file oglplus/doc.hpp
 *  @brief Documentation-only declarations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_DOC_1107121519_HPP
#define OGLPLUS_DOC_1107121519_HPP

#ifdef OGLPLUS_DOCUMENTATION_ONLY

/// All definitions of OGLplus are nested in the oglplus namespace
namespace oglplus {

/// Wrapper class for all ranges that can be used for Element traversal
/** This class cannot be instantiated and used directly in end-user
 *  code. It is here for documentation purposes only.
 */
class Range
{
public:
	/// Copy constructor
	Range(const Range&);

	/// Returns true if the range is empty
	bool Empty(void) const;

	/// Returns the number of Elements in the range
	GLuint Size(void) const;

	/// Goes to the next element in the range. Synonym for StepFront
	/** The range must not be empty when calling Next, otherwise the
	 *  application will be aborted.
	 *
	 *  @see Empty
	 *  @see StepFront
	 */
	void Next(void);

	/// Moves the front of the range one step forward. Synonym for Next
	/** The range must not be empty when calling StepFront, otherwise the
	 *  application will be aborted.
	 *
	 *  @see Empty
	 *  @see Next
	 *  @see Front
	 */
	void StepFront(void);

	/// Returns the element at the front of the range
	/** The range must not be empty when calling Front, otherwise the
	 *  application will be aborted.
	 *
	 *  @see Empty
	 *  @see Next
	 *  @see StepFront
	 */
	const Element Front(void);
};

} // namespace oglplus
#endif // OGLPLUS_DOCUMENTATION_ONLY

#endif // include guard
