/*
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_dsa_renderbuffer_1
namespace oglplus {

template <>
class __ObjectOps<__tag_DirectState, __tag_Renderbuffer>
 : public __ObjZeroOps<__tag_DirectState, __tag_Renderbuffer> /*<
Indirectly inherits from __ObjCommonOps_Renderbuffer.
>*/
{
public:
	void Storage(
		__PixelDataInternalFormat internalformat,
		GLsizei width,
		GLsizei height
	); /*<
	Sets the storage parameters for [^this] renderbuffer.
	See [glfunc NamedRenderbufferStorage].
	>*/
	void Storage(const __images_ImageSpec& image_spec);

	void StorageMultisample(
		GLsizei samples,
		__PixelDataInternalFormat internalformat,
		GLsizei width,
		GLsizei height
	); /*<
	Sets multipsample storage parameters for [^this] renderbuffer.
	See [glfunc NamedRenderbufferStorageMultisample].
	>*/

	GLsizei Width(void) const; /*<
	Returns the width in pixels of [^this] renderbuffer.
	See [glfunc GetNamedRenderbufferParameter], [glconst RENDERBUFFER_WIDTH].
	>*/
	GLsizei Height(void) const; /*<
	Returns the height in pixels of [^this] renderbuffer.
	See [glfunc GetNamedRenderbufferParameter], [glconst RENDERBUFFER_HEIGHT].
	>*/

	GLsizei RedSize(void) const; /*<
	Returns the size in bits of the red component of [^this] renderbuffer.
	See [glfunc GetNamedRenderbufferParameter], [glconst RENDERBUFFER_RED_SIZE].
	>*/
	GLsizei GreenSize(void) const; /*<
	Returns the size in bits of the green component of [^this] renderbuffer.
	See [glfunc GetNamedRenderbufferParameter], [glconst RENDERBUFFER_GREEN_SIZE].
	>*/
	GLsizei BlueSize(void) const; /*<
	Returns the size in bits of the blue component of [^this] renderbuffer.
	See [glfunc GetNamedRenderbufferParameter], [glconst RENDERBUFFER_BLUE_SIZE].
	>*/
	GLsizei AlphaSize(void) const; /*<
	Returns the size in bits of the alpha component of [^this] renderbuffer.
	See [glfunc GetNamedRenderbufferParameter], [glconst RENDERBUFFER_ALPHA_SIZE].
	>*/
	GLsizei DepthSize(void) const; /*<
	Returns the size in bits of the depth component of [^this] renderbuffer.
	See [glfunc GetNamedRenderbufferParameter], [glconst RENDERBUFFER_DEPTH_SIZE].
	>*/
	GLsizei StencilSize(void) const; /*<
	Returns the size in bits of the stencil component of [^this] renderbuffer.
	See [glfunc GetNamedRenderbufferParameter], [glconst RENDERBUFFER_STENCIL_SIZE].
	>*/

	GLsizei Samples(void) const; /*<
	Returns the number of samples of [^this] renderbuffer.
	See [glfunc GetNamedRenderbufferParameter], [glconst RENDERBUFFER_SAMPLES].
	>*/
	__PixelDataInternalFormat InternalFormat(void) const; /*<
	Returns the internal format of [^this] renderbuffer.
	See [glfunc GetNamedRenderbufferParameter], [glconst RENDERBUFFER_INTERNAL_FORMAT].
	>*/
};
//]
//[oglplus_dsa_renderbuffer_def

typedef ObjectOps<__tag_DirectState, __tag_Renderbuffer>
	DSARenderbufferOps;

typedef __Object<DSARenderbufferOps> DSARenderbuffer;

//]
//[oglplus_dsa_renderbuffer_sugar

DSARenderbufferOps& operator << (
	DSARenderbufferOps& rbo,
	__RenderbufferTarget target
); /*<
Binds [^rbo] to the specified [^target].
>*/

DSARenderbufferOps& operator << (
	DSARenderbufferOps& rbo,
	const __images_ImageSpec& image_spec
); /*<
Sets the storage parameters from [^image_spec] to the renderbuffer
currently bound to the specified [^target].
>*/

} // namespace oglplus
//]

