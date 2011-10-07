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

#ifdef OGLPLUS_DOCUMENTATION_ONLY

/// All definitions of OGLplus are nested in the oglplus namespace
namespace oglplus {

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
