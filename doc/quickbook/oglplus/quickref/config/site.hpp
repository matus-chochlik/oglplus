/*
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_config_site_1
namespace oglplus {

#define OGLPLUS_OPENAL_FOUND <UNSPECIFIED> /*<
Indicates if __OpenAL__ is available and should be used.
>*/
#define OGLPLUS_PNG_FOUND <UNSPECIFIED> /*<
Indicates if __LibPNG__ was found and should be used.
>*/
#define OGLPLUS_PANGO_CAIRO_FOUND <UNSPECIFIED> /*<
Indicates if __Pango_Cairo__ was found and should be used.
>*/

#ifndef __OGLPLUS_LOW_PROFILE
#define __OGLPLUS_LOW_PROFILE <UNSPECIFIED> /*<
The low-profile mode can be set through the configuration script.
>*/
#endif

//]
//[oglplus_config_site_2

#ifndef OGLPLUS_USE_GLCOREARB_H /*<
Indicates that [^GL/glcorearb.h] + the GL binary library
should be used.
>*/
#define OGLPLUS_USE_GLCOREARB_H <UNSPECIFIED>
#endif
#ifndef OGLPLUS_USE_GL3_H /*<
Indicates that [^GL3/gl3.h] + the GL binary library
should be used.
>*/
#define OGLPLUS_USE_GL3_H <UNSPECIFIED>
#endif
#ifndef OGLPLUS_USE_GLEW /*<
Indicates that __GLEW__ should be used.
>*/
#define OGLPLUS_USE_GLEW <UNSPECIFIED>
#endif
#ifndef OGLPLUS_USE_GL3W /*<
Indicates that __GL3W__ should be used.
>*/
#define OGLPLUS_USE_GL3W <UNSPECIFIED>
#endif

//]
//[oglplus_config_site_3

#ifndef OGLPLUS_USE_BOOST_CONFIG
#define OGLPLUS_USE_BOOST_CONFIG <UNSPECIFIED>
#endif

} // namespace oglplus
//]

