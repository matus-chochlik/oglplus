/*
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_error
namespace oglplus {

class Error
 : public std::runtime_error
{
public:
	static const char* Message(GLenum error_code); /*<
	Returns a message for the specified [^error_code].
	>*/

	Error(const char* message); /*<
	Constructs a new instance of [^Error] with the specified
	error [^message].
	>*/

	~Error(void) throw() { }

	const char* SourceFile(void) const; /*<
	Returns the name of the source file where the error occured.

	The result of this function is also influenced by the
	__OGLPLUS_ERROR_NO_FILE preprocessor configuration option.
	If set to zero this function behaves as described above, otherwise it
	returns a [^nullptr].
	>*/

	const char* SourceFunc(void) const; /*<
	Returns the name of the function where the error occured.

	The result of this function is also influenced by the
	__OGLPLUS_ERROR_NO_FUNC preprocessor configuration option.
	If set to zero this function behaves as described above, otherwise it
	returns a [^nullptr].
	>*/

	unsigned SourceLine(void) const; /*<
	Returns the line of the source file where the error occured.

	The result of this function is also influenced by the
	__OGLPLUS_ERROR_NO_LINE preprocessor configuration option.
	If set to zero this function behaves as described above, otherwise it
	returns zero.
	>*/

	GLenum EnumParam(void) const; /*<
	Returns the value of the enumeration parameter related to the error.

	This function returns the value of the main enumeration
	parameter passed to the failed OpenGL function.
	The result of this function is also influenced by the
	__OGLPLUS_ERROR_NO_GL_SYMBOL preprocessor configuration option.
	If set to zero this function behaves as described above, otherwise it
	returns zero.
	>*/
};

} // namespace oglplus
//]

