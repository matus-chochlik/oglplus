/*
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_config_site_1
namespace oglplus {

#define OGLPLUS_OPENAL_FOUND <UNSPECIFIED> /*<
Indicates if __OpenAL is available and should be used.
>*/
#define OGLPLUS_PNG_FOUND <UNSPECIFIED> /*<
Indicates if LibPNG was found and should be used.
>*/
#define OGLPLUS_PANGO_CAIRO_FOUND <UNSPECIFIED> /*<
Indicates if Pango/Cairo was found and should be used.
>*/

//]
//[oglplus_config_site_2

#ifndef OGLPLUS_USE_GLCOREARB_H
#define OGLPLUS_USE_GLCOREARB_H <UNSPECIFIED>
#endif
#ifndef OGLPLUS_USE_GL3_H
#define OGLPLUS_USE_GL3_H <UNSPECIFIED>
#endif
#ifndef OGLPLUS_USE_GLEW
#define OGLPLUS_USE_GLEW <UNSPECIFIED>
#endif
#ifndef OGLPLUS_USE_GL3W
#define OGLPLUS_USE_GL3W <UNSPECIFIED>
#endif

#define OGLPLUS_USE_BOOST_CONFIG 1

} // namespace oglplus
//]

