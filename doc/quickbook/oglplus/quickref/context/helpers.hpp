/*
 *  Copyright 2014-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_context_RGBAValue
namespace context {

struct RGBAValue /*<
Helper structure storing the RGBA color components.
>*/
{
    RGBAValue() noexcept;

    RGBAValue(GLfloat r, GLfloat g, GLfloat b, GLfloat a) noexcept;

    GLfloat Red() const noexcept;

    GLfloat Green() const noexcept;

    GLfloat Blue() const noexcept;

    GLfloat Alpha() const noexcept;
};

//]
//[oglplus_context_RGBAMask

struct RGBAMask /*<
Helper structure storing the color component mask.
>*/
{
    RGBAMask() noexcept;

    RGBAMask(__Boolean r, __Boolean g, __Boolean b, __Boolean a) noexcept;

    __Boolean Red() const noexcept;

    __Boolean Green() const noexcept;

    __Boolean Blue() const noexcept;

    __Boolean Alpha() const noexcept;
};

} // namespace context
//]
