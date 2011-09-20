/**
 *  @file oglplus/all.hpp
 *  @brief All-in-one inclusion of everything in OGLplus
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_ALL_1107121519_HPP
#define OGLPLUS_ALL_1107121519_HPP

#include <oglplus/config.hpp>
#include <oglplus/fwd.hpp>
#include <oglplus/error.hpp>

#include <oglplus/array.hpp>

#include <oglplus/context.hpp>

#include <oglplus/data_type.hpp>
#include <oglplus/primitive_type.hpp>

#include <oglplus/exposed.hpp>

#include <oglplus/buffer.hpp>
#include <oglplus/uniform.hpp>
#include <oglplus/uniform_block.hpp>
#include <oglplus/vertex_attrib.hpp>
#include <oglplus/vertex_array.hpp>
#include <oglplus/texture.hpp>
#include <oglplus/sampler.hpp>
#include <oglplus/framebuffer.hpp>
#include <oglplus/renderbuffer.hpp>
#include <oglplus/transform_feedback.hpp>
#include <oglplus/program_pipeline.hpp>
#include <oglplus/query.hpp>

#include <oglplus/shader.hpp>
#include <oglplus/program.hpp>

#include <oglplus/angle.hpp>
#include <oglplus/vector.hpp>
#include <oglplus/matrix.hpp>

/** @mainpage OGLplus - a C++ wrapper for OpenGL version 3 and higher.
 *
 *  OGLplus (@c oglplus) is a header only library which implements
 *  a thin object-oriented facade over the OpenGL (version 3 and higher)
 *  C-language API. It provides wrappers which automate
 *  the resource and object management and make the use of OpenGL
 *  in C++ much easier.
 *
 *  - @ref oglplus_features
 *    - @ref feat_auto_resource_management
 *    - @ref feat_type_safety
 *    - @ref feat_error_handling
 *    - @ref feat_interoperability_with_opengl
 *    - @ref feat_related_classes
 *  - @ref oglplus_what_it_is_not
 *  - @ref oglplus_download
 *  - @ref oglplus_getting_started
 *  - @ref oglplus_getting_it_going
 *  - @ref oglplus_supported_compilers
 *  - @ref oglplus_example_rationale
 *  - @ref oglplus_object_description
 *
 *  @section oglplus_features Features
 *
 *  OGLplus adds the following functionality to the "basic" OpenGL C API.
 *
 *  @subsection feat_auto_resource_management Automatic resource management
 *
 *  Applications using the OpenGL library typically allocate and use, during their
 *  run-time, resources like buffers, queries, textures, shaders, programs,
 *  etc. from this library.
 *  OGLplus uses the RAII idiom to automatically manage the lifetime
 *  of these resources. Classes like @ref oglplus::Buffer "Buffer",
 *  @ref oglplus::Texture "Texture", @ref oglplus::Query "Query",
 *  @ref oglplus::Shader "Shader", @ref oglplus::Program "Program",
 *  @ref oglplus::Framebuffer "Framebuffer",
 *  @ref oglplus::Renderbuffer "Renderbuffer",
 *  etc. automatically get a new OpenGL name
 *  for the wrapped object when an instance is constructed and it is freed
 *  when the instance is destroyed. Besides this basic functionality,
 *  the individual classes also implement member functions wrapping those
 *  OpenGL calls which are related to the resource managed by the particular
 *  class.
 *
 *  When several instances of the same resource type should be created
 *  and freed at once, the @ref oglplus::Array "Array" template provides
 *  efficient means for doing so.
 *
 *  @subsection feat_type_safety Type safety
 *
 *  OpenGL uses the @c GLuint type as the namespace for instances of different
 *  types of resources (textures, shaders, programs, etc.) and thus it is very
 *  easy to make an error and use a name originally allocated for a shader
 *  as a parameter for a call expecting for example a name of a occlusion query,
 *  and such errors will not be caught by the compiler.
 *
 *  By implementing the wrapper classes OGLplus gives a special meaning
 *  to the unsigned integer names and by their encapsulating and hiding
 *  from the library client it allows to avoid such errors.
 *
 *  Similarly the various enumerations are again basically values of the @c GLenum
 *  type and are prone to the same kind of error. You can pass an incompatible
 *  enumerated value to a API function call. OGLplus again allows to avoid these
 *  errors by separating the values into strongly typed enums and wrapping the
 *  basic OpenGL API calls by functions accepting only parameters with matching
 *  enumerated types.
 *
 *  @subsection feat_error_handling Error handling and diagnostic
 *
 *  In cases where errors cannot be caught at compile-time by using
 *  the type system or by other means, OGLplus checks for errors after
 *  the calls to OpenGL and throws an exception if an error occurs.
 *  All exceptions are derived from the @ref oglplus::Error "Error" class
 *  which provides information about the throw site of the exception
 *  (source file, line, OGLplus function name, the OpenGL C API call,
 *  etc. where the error occured) and optionally also some properties
 *  (string key and value) attached at the throw site or during the propagation
 *  of the exception. If the error is related to a
 *  @ref oglplus_object_description "described" object, then the object description
 *  can also be obtained for a more precise diagnostic.
 *
 *  @subsection feat_interoperability_with_opengl Interoperability with "basic" OpenGL
 *
 *  As said above, OGLplus by default encapsulates and hides the OpenGL names
 *  assigned to various objects (resources allocated at the OpenGL server).
 *  There are however situations where it might be necessary to get this
 *  "raw" resource handle. This can be done via the @ref oglplus::Expose() "Expose"
 *  function.
 *
 *  @subsection feat_related_classes Additional CG related classes
 *
 *  Besides the classes wrapping OpenGL functionality OGLplus also provides
 *  several classes which are related to computer graphics and indirectly
 *  to OpenGL, like @ref oglplus::Angle "Angle", @ref oglplus::Vector "Vector",
 *  @ref oglplus::Matrix "Matrix", @ref oglplus::BezierCurves "BezierCurves",
 *  and several others, but does not force you to use them if you don't want to.
 *
 *  @section oglplus_what_it_is_not What OGLplus isn't
 *
 *  Like the OpenGL C API, OGLplus does not officially provide nor force you to use code
 *  related to creating of the default framebuffer. There are already
 *  several other libraries and frameworks which do it in both platform
 *  dependent and platform independent ways.
 *
 *  OGLplus also does not include header file(s) declaring the OpenGL 3 (or higher)
 *  function prototypes and enumerated values. It is the responsibility of the
 *  application to do so. There are several ways how to do it, see
 *  @ref oglplus_getting_it_going for some suggestions.
 *
 *  @section oglplus_download Source download and repository
 *
 *  The source code can be downloaded from SourceForge at the following URL:
 *  <A HREF="http://sourceforge.net/projects/oglplus/files/">http://sourceforge.net/projects/oglplus/files/</A>.
 *
 *  Git users can get anonymous read-only access to the source repository
 *  by using the following command:
 *  @code
 *  git clone git://oglplus.git.sourceforge.net/gitroot/oglplus/oglplus
 *  @endcode
 *
 *  @section oglplus_getting_started Getting started, tutorials, examples
 *
 *  One of the best ways how to get yourself acquainted with the library is to
 *  look at the examples and to browse through the reference. Many of the examples
 *  are thoroughly commented and in the future step-by-step tutorials will be added.
 *
 *  @section oglplus_getting_it_going Getting it going
 *
 *  OGLplus currently uses the GNU Make build system, to build the examples
 *  which may by replaced or supplemented
 *  in the future with CMake, Boost.Build or something similar.
 *  The library itself is however header-only, i.e. all an application using it
 *  has to do is to include the necessary header files. It does not need to be
 *  built nor linked to.
 *
 *  One important thing that an application using OGLplus needs to take care of
 *  is to make sure that the OpenGL 3 (or higher) function prototypes, typedefs,
 *  preprocessor symbols, etc. are defined before including any OGLplus header.
 *
 *  There are several different ways how to do this; one of the most convenient
 *  is to download the @c gl3.h header file from
 *  <A HREF="www.opengl.org/registry/api/gl3.h">www.opengl.org/registry/api/gl3.h</A>
 *  and place it to a directory implicitly searched by the compiler or to add the
 *  @c -I/path/to/include directive to your @c CXXFLAGS. If the OpengGL dynamic library
 *  or shader object is located in a nonstandard location also update the @c LDFLAGS.
 *
 *  On Linux and similar systems using Bash as shell you can for example put
 *  the following to your ~/.bashrc file:
 *
 *  @code
 *  # if GL3/gl3.h is in $HOME/include
 *  export CXXFLAGS="$CXXFLAGS -I$HOME/include"
 *  # if libGL.so is in $HOME/lib
 *  export LDFLAGS="$LDFLAGS -L$HOME/lib"
 *  @endcode
 *
 *  Some other alternatives include using GLEW or a similar library or framework
 *  which includes gl3.h or defines the necessary symbols itself.
 *
 *  @section oglplus_supported_compilers Supported compilers
 *
 *  OGLplus is known to work with the following compilers:
 *  - GCC (version 4.5.1)
 *
 *  Currently the limiting factor seems to be the support for C++11 features
 *  by the various compilers. Since C++11 is now an official standard
 *  we expect that the compiler vendors will implement these new features
 *  as soon as possible.
 *
 *  @section oglplus_example_rationale Example rationale
 *
 *  As already said above, OGLplus does not officially provide means for creating of the
 *  default framebuffer nor any code related to window-system or user-input.
 *  The example code is usually encapsulated in a class derived from the @c Example
 *  class and the build system selects and builds and links the piece of code doing
 *  the initial setup, cleanup and handling of events to the example code
 *  automatically.
 *  This way the examples are not too cluttered by things which are not directly
 *  related to OpenGL and OGLplus usage.
 *
 *  @section oglplus_object_description Optional object description
 *
 *  Objects with OpenGL names (unsigned integers) can optionally have a textual
 *  description. This is useful for diagnostic purposes, for example in an application
 *  with lots of different shaders it is easier to track the source of compilation,
 *  linking or validation errors when the individual shader or program objects
 *  have a human-readable description which is attached to the exception raised
 *  by the error.
 *
 *  The classes like @ref oglplus::Shader "Shader", @ref oglplus::Program "Program",
 *  @ref oglplus::Texture "Texture", @ref oglplus::Query "Query" and many others
 *  have one or more constructors allowing to assign a description to the object
 *  during construction.
 *
 *  If the overhead caused by the descriptions is unacceptable for release builds
 *  of an application and they are intended for debugging purposes only, it can be compiled-away
 *  by setting the value of the @c #OGLPLUS_NO_OBJECT_DESCS preprocessor symbol to
 *  a nonzero integer value.
 *
 */
#endif // include guard
