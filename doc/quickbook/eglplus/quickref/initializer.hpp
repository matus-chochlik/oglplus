/*
 *  Copyright 2014-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[eglplus_initializer

class EGLInitializer {
public:
    EGLInitializer(); /*<
    Initializes EGL on the default display.
    See [eglfunc GetDisplay], [eglfunc Initialize],
    [eglconst DEFAULT_DISPLAY].
    >*/

    EGLInitializer(const __Display& display); /*<
    Initializes EGL on the specified display.
    See [eglfunc Initialize].
    >*/

    EGLInitializer(const EGLInitializer&) = delete;
    EGLInitializer(EGLInitializer&&);

    ~EGLInitializer(); /*<
    See [eglfunc Terminate].
    >*/

    const __Display& Disp() const; /*<
    Returns a reference to the associated display.
    >*/
    const __Display& AssociatedDisplay() const;

    EGLint VersionMajor() const; /*<
    Returns the major version number.
    >*/
    EGLint VersionMinor() const; /*<
    Returns the minor version number.
    >*/

    const char* QueryString(__StringQuery query) const; /*<
    Queries the specified EGL string.
    See [eglfunc QueryString].
    >*/

    const char* Vendor() const; /*<
    Returns the vendor name.
    See [eglfunc QueryString], [eglconst EGL_VENDOR].
    >*/

    const char* Version() const; /*<
    Returns the version string.
    See [eglfunc QueryString], [eglconst EGL_VERSION].
    >*/

    __Range<__String> ClientAPIs() const; /*<
    Returns a range of supported API name strings.
    See [eglfunc QueryString], [eglconst EGL_CLIENT_APIS].
    >*/

    __Range<__String> Extensions() const; /*<
    Returns a range of extension strings.
    See [eglfunc QueryString], [eglconst EGL_EXTENSIONS].
    >*/

    static bool HasClientExtensions(); /*<
    Returns true if the EGL implementation supports client extensions.
    See [eglfunc QueryString], [eglconst EGL_EXTENSIONS].
    >*/

    static __Range<__String> ClientExtensions(); /*<
    Returns a range of client extension strings.
    See [eglfunc QueryString], [eglconst EGL_EXTENSIONS].
    >*/

    static __Boolean ReleaseThread(); /*<
    Releases the current thread state.
    See [eglfunc ReleaseThread].
    >*/
};

//]
//[eglplus_initializer_alias

typedef __EGLInitializer LibEGL;

//]
