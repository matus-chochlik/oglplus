/*
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_context_RGBAValue
namespace oglplus {
namespace context {

struct RGBAValue /*<
Helper structure storing the RGBA color components.
>*/
{
	RGBAValue(void)
	noexcept;

	RGBAValue(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
	noexcept;

	GLfloat Red(void) const
	noexcept;

	GLfloat Green(void) const
	noexcept;

	GLfloat Blue(void) const
	noexcept;

	GLfloat Alpha(void) const
	noexcept;
};

//]
//[oglplus_context_RGBAMask

struct RGBAMask /*<
Helper structure storing the color component mask.
>*/
{
	RGBAMask(void)
	noexcept;

	RGBAMask(bool r, bool g, bool b, bool a)
	noexcept;

	bool Red(void) const
	noexcept;

	bool Green(void) const
	noexcept;

	bool Blue(void) const
	noexcept;

	bool Alpha(void) const
	noexcept;
};

} // namespace context
} // namespace oglplus
//]

