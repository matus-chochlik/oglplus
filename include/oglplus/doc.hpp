/**
 *  @file oglplus/doc.hpp
 *  @brief Documentation-only declarations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_DOC_1107121519_HPP
#define OGLPLUS_DOC_1107121519_HPP

#include <oglplus/config.hpp>

#if OGLPLUS_DOCUMENTATION_ONLY

/// All definitions of OGLplus are nested in the oglplus namespace
namespace oglplus {

/** @mainpage OGLplus - a C++ wrapper for OpenGL® version 3 and higher.
 *
 *  @image html oglplus.png
 *
 *  OGLplus is a header-only library which implements
 *  a thin object-oriented facade over the OpenGL® (version 3 and higher)
 *  C-language API. It provides wrappers which automate
 *  the resource and object management and make the use of OpenGL
 *  in C++ safer and easier.
 *
 *  - @ref oglplus_features
 *    - @ref feat_auto_resource_management
 *    - @ref feat_type_safety
 *    - @ref feat_error_handling
 *    - @ref feat_interoperability_with_opengl
 *    - @ref feat_related_classes
 *  - @ref oglplus_what_it_is_not
 *  - @ref oglplus_screenshot_gallery
 *  - @ref oglplus_download
 *  - @ref oglplus_getting_started
 *  - @ref oglplus_getting_it_going
 *  - @ref oglplus_supported_compilers
 *  - @ref oglplus_example_rationale
 *  - @ref oglplus_object_description
 *
 *  @section oglplus_features Features
 *
 *  OGLplus adds the following functionality to the OpenGL® C API.
 *
 *  @subsection feat_auto_resource_management Automatic resource management
 *
 *  Applications using the OpenGL® library typically allocate and use, during their
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
 *  calls which are related to the resource managed by the particular
 *  class.
 *
 *  When several instances of the same resource type should be created
 *  and freed at the same time, the @ref oglplus::Array "Array" template provides
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
 *  basic OpenGL® API calls by functions accepting only parameters with matching
 *  enumerated types.
 *
 *  @subsection feat_error_handling Error handling and diagnostic
 *
 *  In cases where errors cannot be caught at compile-time by using
 *  the type system or by other means, OGLplus checks for errors after
 *  the calls to OpenGL and throws an exception if an error occurs.
 *  All exceptions are derived from the @ref oglplus::Error "Error" class
 *  which provides information about the throw site of the exception
 *  (source file, line, OGLplus function name, the OpenGL® C API call,
 *  etc. where the error occured) and optionally also some properties
 *  (string key and value) attached at the throw site or during the propagation
 *  of the exception. If the error is related to a
 *  @ref oglplus_object_description "described" object, then the object description
 *  can also be obtained for a more precise diagnostic.
 *
 *  @subsection feat_interoperability_with_opengl Interoperability with OpenGL® C API
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
 *  Like the OpenGL® C API, OGLplus does not officially provide nor force you to use code
 *  related to creating of the default framebuffer. There are already
 *  several other libraries and frameworks which do it in both platform
 *  dependent and platform independent ways.
 *
 *  OGLplus also does not include header file(s) declaring the OpenGL® 3 (or higher)
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
 *
 *  To build the examples type
 *  @code
 *  make
 *  @endcode
 *  in the root of the source directory. If you downloaded the source package
 *  the textures and automatically generated header files used by the examples
 *  are pre-built and building the examples requires only a C++ compiler.
 *  If you use the plain sources (for example from the repository) you'll
 *  need the following:
 *  - @c doxygen (to parse the sources into a XML file)
 *  - @c xsltproc (to transform the parsed XML to the auto-generated headers)
 *  - @c inkscape (to convert the texture SVG "sources" to PNG bitmap images)
 *
 *  The library itself is however header-only, i.e. all an application using it
 *  has to do is to include the necessary header files. The library does not need to be
 *  built nor linked to.
 *
 *  To install the headers to @c /usr/local/include you can use the install script
 *  located in the main directory of the source tree.
 *  @code
 *  ./install.sh
 *  @endcode
 *
 *  To install to another location you can specify the prefix to the install script:
 *  @code
 *  ./install.sh --prefix=~/opt
 *  @endcode
 *
 *  which will install the headers in the @c ~/opt/include directory. In this
 *  case it is necessary to tell the compiler to search this directory for
 *  header files (usually with the @c -I directive).
 *
 *  One important thing that an application using OGLplus needs to take care of
 *  is to make sure that the OpenGL® 3 (or higher) function prototypes, typedefs,
 *  preprocessor symbols, etc. are defined before including any OGLplus header.
 *
 *  There are several different ways how to do this; one of the most convenient
 *  is to download the @c gl3.h header file from
 *  <A HREF="www.opengl.org/registry/api/gl3.h">www.opengl.org/registry/api/gl3.h</A>
 *  and place it to a directory implicitly searched by the compiler or to add the
 *  @c -I/path/to/include directive to your @c CXXFLAGS. If the OpengGL dynamic library
 *  or shared object is located in a nonstandard location also update the @c LDFLAGS.
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
 *  soon.
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
 *  related to OpenGL® and OGLplus usage. The examples are numbered and ordered
 *  roughly by their "difficulty", from the easiest to the most complex.
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
 *  of an application and they are intended for debugging purposes only, they can be compiled away
 *  by setting the value of the @c #OGLPLUS_NO_OBJECT_DESCS preprocessor symbol to
 *  a nonzero integer value.
 *
 */

/** @defgroup math_utils GC-related math utilities
 *
 *  This group contains classes and functions which do not directly deal with
 *  OpenGL, but are related to computer graphics, like angles, vectors, matrices,
 *  etc. The OGLplus example make use these classes, but the library does not
 *  force you to use them if you don't want to.
 */

/** @defgroup shader_variables Shader variable access
 *
 *  Classes in this group are used for access to the format and values of
 *  shading language program variables, like uniforms and vertex attributes or
 *  vertex attribute arrays.
 */

/** @defgroup enumerations Strongly typed enumerations
 *
 *  These enumerations tie the OpenGL constants (defined as preprocessor
 *  symbols) into logical groups and are then used as parameter types
 *  in OpenGL function call wrappers instead of just plain @c GLenum
 *  or @c GLbitfield. This brings additional type safety and robustness
 *  to the application code and helps avoid subtle hard to track errors.
 */

/** @defgroup utility_classes Utility classes
 */

/** @defgroup modifier_classes Modifier classes
 *
 *  Class templates in this group modify the usage or behavior of other
 *  classes, mostly @ref oglplus_object "objects". They for example
 *  allow to make temporary copies of objects which are only movable
 *  or to allocate and cleanup several instances of the same type
 *  at the same time.
 */

/// Wrapper class for all ranges that can be used for Element traversal
/** This class cannot be instantiated and used directly in end-user
 *  code. It is here for documentation purposes only.
 */
class Range
{
public:
	/// Copy constructor
	Range(const Range&);

	/// Returns true if the range is empty
	bool Empty(void) const;

	/// Returns the number of Elements in the range
	GLuint Size(void) const;

	/// Goes to the next element in the range. Synonym for StepFront
	/** The range must not be empty when calling Next, otherwise the
	 *  application will be aborted.
	 *
	 *  @see Empty
	 *  @see StepFront
	 */
	void Next(void);

	/// Moves the front of the range one step forward. Synonym for Next
	/** The range must not be empty when calling StepFront, otherwise the
	 *  application will be aborted.
	 *
	 *  @see Empty
	 *  @see Next
	 *  @see Front
	 */
	void StepFront(void);

	/// Returns the element at the front of the range
	/** The range must not be empty when calling Front, otherwise the
	 *  application will be aborted.
	 *
	 *  @see Empty
	 *  @see Next
	 *  @see StepFront
	 */
	const Element Front(void);
};

/** @page oglplus_screenshot_gallery Screenshot gallery
 *
 *  @htmlinclude gallery.html
 */

/** @page bound_objects Bound objects
 *
 *  Bound objects make the usage of @ref oglplus_object "objects" that
 *  can be bound to a OpenGL binding point or "target" easier.
 *  This includes objects like @ref oglplus::Buffer "Buffer,"
 *  @ref oglplus::Texture "Texture", @ref oglplus::Renderbuffer "Renderbuffer"
 *  or @ref oglplus::Framebuffer "Framebuffer"
 *  which have a target to which individual
 *  instances can be bound and operated on through the binding point.
 *  Generally @c Bound<Object> classes re-implement those functions of @c Object
 *  which have a @c target parameter of the @c Object::Target type. These
 *  re-implemented functions have all the other parameters of the original
 *  member functions, but lack the @c target parameter and supply it to the
 *  original function call automatically.
 *
 *  For example to setup a texture object one might need to do the following:
 *  @code
 *  // create the texture
 *  Texture tex;
 *  // the binding point we'll be using to setup the texture
 *  Texture::Target tex_tgt = Texture::Target::_2D;
 *  tex.Bind(tex_tgt);
 *  {
 *    Texture::Image2D(tex_tgt, ...);
 *    Texture::GenerateMipmap(tex_tgt);
 *    Texture::MinFilter(tex_tgt, TextureMinFilter::Linear);
 *    Texture::MagFilter(tex_tgt, TextureMagFilter::Linear);
 *    Texture::WrapS(tex_tgt, TextureWrap::Repeat);
 *    Texture::WrapT(tex_tgt, TextureWrap::Repeat);
 *    Texture::SwizzleG(tex_tgt, TextureSwizzle::Red);
 *    Texture::SwizzleB(tex_tgt, TextureSwizzle::Red);
 *  }
 *  @endcode
 *
 *  The @c Bound template class instantiated through the @c Bind function
 *  allows to do things more conveniently:
 *  @code
 *  // create the texture
 *  Texture tex;
 *  // start a block where the texture will be set-up
 *  {
 *    // make a wrapper for the texture bound to TEXTURE_2D
 *    auto bound_tex = Bind(tex, Texture::Target::_2D);
 *    bound_tex.Image2D(...);
 *    bound_tex.GenerateMipmap();
 *    bound_tex.MinFilter(TextureMinFilter::Linear);
 *    bound_tex.MagFilter(TextureMagFilter::Linear);
 *    bound_tex.WrapS(TextureWrap::Repeat);
 *    bound_tex.WrapT(TextureWrap::Repeat);
 *    bound_tex.SwizzleG(TextureSwizzle::Red);
 *    bound_tex.SwizzleB(TextureSwizzle::Red);
 *  }
 *  @endcode
 *
 *  The source code for the specializations of the @ref oglplus::Bound "Bound"
 *  template class is not included automatically by including oglplus/all.hpp.
 *  In order to be able to use @c Bound objects it is necessary to include
 *  the appropriate header:
 *
 *  @code
 *  #include <oglplus/bound/texture.hpp> // Bound<Texture>
 *  #include <oglplus/bound/buffer.hpp> // Bound<Buffer>
 *  #include <oglplus/bound/framebuffer.hpp> // Bound<Framebuffer>
 *  #include <oglplus/bound/renderbuffer.hpp> // Bound<Renderbuffer>
 *  @endcode
 */

/// Allows to handle objects which are used through a binding point conveniently
/** See @ref bound_object for more details.
 *
 *  @ingroup modifier_classes
 */
template <class Object>
class Bound;

} // namespace oglplus
#endif // OGLPLUS_DOCUMENTATION_ONLY

#endif // include guard
