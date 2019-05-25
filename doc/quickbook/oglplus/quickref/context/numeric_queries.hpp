/*
 *  Copyright 2014-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_context_NumericQueries
namespace context {

class NumericQueries {
public:
    static GLint MajorVersion(); /*<
    Returns the GL major version.
    See [glfunc Get], [glconst MAJOR_VERSION].
    >*/
    static GLint MinorVersion(); /*<
    Returns the GL minor version.
    See [glfunc Get], [glconst MINOR_VERSION].
    >*/

#if GL_VERSION_3_3 || GL_ARB_timer_query
    static GLint64 Timestamp(); /*<
    Queries the current GL timestamp.
    See [glfunc Get], [glconst TIMESTAMP].
    >*/
#endif

#if GL_VERSION_3_2
    static __Bitfield<__ContextProfileBit> ProfileMask(); /*<
    Returns the GL context profile mask.
    See [glfunc Get], [glconst CONTEXT_PROFILE_MASK].
    >*/
    static __Bitfield<__ContextFlagBit> Flags(); /*<
    Returns the current context flags.
    See [glfunc Get], [glconst CONTEXT_FLAGS].
    >*/
#endif

#if GL_VERSION_4_5 || GL_KHR_context_flush_control
    static __ContextReleaseBehavior ReleaseBehavior(); /*<
    Returns the current context flush control reset behavior.
    See [glfunc Get], [glconst CONTEXT_RELEASE_BEHAVIOR].
    >*/
#endif

#if GL_VERSION_4_5
    static __ResetNotificationStrategy ResetNotificationStrategy(); /*<
    Returns the currently active context reset notification strategy.
    See [glfunc Get], [glconst RESET_NOTIFICATION_STRATEGY].
    >*/
    static __GraphicsResetStatus GraphicsResetStatus(); /*<
    Returns the current GL context reset status.
    See [glfunc GetGraphicsResetStatus].
    >*/
#endif
};

} // namespace context
//]
