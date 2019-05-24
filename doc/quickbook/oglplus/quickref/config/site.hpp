/*
 *  Copyright 2014-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_config_site_1

#define OGLPLUS_OPENAL_FOUND                             \
    __UNSPECIFIED /*<                                    \
Indicates if __OpenAL__ is available and should be used. \
>*/
#define OGLPLUS_PNG_FOUND                             \
    __UNSPECIFIED /*<                                 \
Indicates if __LibPNG__ was found and should be used. \
>*/
#define OGLPLUS_PANGO_CAIRO_FOUND                          \
    __UNSPECIFIED /*<                                      \
Indicates if __Pango_Cairo__ was found and should be used. \
>*/

#ifndef __OGLPLUS_LOW_PROFILE
#define __OGLPLUS_LOW_PROFILE                                     \
    __UNSPECIFIED /*<                                             \
The low-profile mode can be set through the configuration script. \
>*/
#endif

//]
//[oglplus_config_site_2

#ifndef OGLPLUS_USE_GLCOREARB_H /*<                      \
Indicates that [^GL/glcorearb.h] + the GL binary library \
should be used.                                          \
>*/
#define OGLPLUS_USE_GLCOREARB_H __UNSPECIFIED
#endif
#ifndef OGLPLUS_USE_GL3_H /*<                       \
Indicates that [^GL3/gl3.h] + the GL binary library \
should be used.                                     \
>*/
#define OGLPLUS_USE_GL3_H __UNSPECIFIED
#endif
#ifndef OGLPLUS_USE_GLEW /*<            \
Indicates that __GLEW__ should be used. \
>*/
#define OGLPLUS_USE_GLEW __UNSPECIFIED
#endif
#ifndef OGLPLUS_USE_GL3W /*<            \
Indicates that __GL3W__ should be used. \
>*/
#define OGLPLUS_USE_GL3W __UNSPECIFIED
#endif

//]
//[oglplus_config_site_3

#ifndef OGLPLUS_USE_BOOST_CONFIG
#define OGLPLUS_USE_BOOST_CONFIG __UNSPECIFIED
#endif

//]
//[oglplus_config_site_4
#if !OGLPLUS_USE_BOOST_CONFIG

#ifndef OGLPLUS_NO_VARIADIC_MACROS /*<                         \
Indicates that preprocessor variadic macros are not supported. \
>*/
#define OGLPLUS_NO_VARIADIC_MACROS __UNSPECIFIED
#endif

#ifndef OGLPLUS_NO_UNIFIED_INITIALIZATION_SYNTAX /*<                   \
Indicates that C++11 unified initialization syntax is not implemented. \
>*/
#define OGLPLUS_NO_UNIFIED_INITIALIZATION_SYNTAX __UNSPECIFIED
#endif

#ifndef OGLPLUS_NO_FUNCTION_TEMPLATE_DEFAULT_ARGS /*<           \
Indicates that C++11 default template arguments cannot be used. \
>*/
#define OGLPLUS_NO_FUNCTION_TEMPLATE_DEFAULT_ARGS __UNSPECIFIED
#endif

//]
//[oglplus_config_site_5

#endif //! OGLPLUS_USE_BOOST_CONFIG
       //]
       //[oglplus_config_site_6

//]
