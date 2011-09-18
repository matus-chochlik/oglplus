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
 *  The OGLplus (@c oglplus) library implements an object-oriented facade over
 *  the basic OpenGL 3 C-language API. It provides wrappers which automate
 *  the resource and OpenGL object management and make the use of OpenGL
 *  in C++ much easier.
 *
 *  @section oglplus_features Features
 *
 *  OGLplus adds the following functionality to the basic OpenGL C API.
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
 *  Like the OpenGL C API, OGLplus does not implement any functionality
 *  related to creating of the default framebuffer. There are already
 *  several other libraries and frameworks which do it in both platform
 *  dependent and platform independent ways.
 *
 *  OGLplus also does not include header file(s) declaring the OpenGL 3 (or higher)
 *  function prototypes and enumerated values. It is the responsibility of the
 *  application to do so. There are several ways how to do it, see
 *  @ref oglplus_getting_it_going for some suggestions.
 *
 *  @section oglplus_getting_it_going Getting it going
 *
 *  TODO
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
 *  TODO
 *
 *  @section oglplus_object_description Optional object description
 *
 *  TODO
 *
 */
#endif // include guard
