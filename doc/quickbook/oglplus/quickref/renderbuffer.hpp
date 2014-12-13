/*
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_renderbuffer_common
namespace oglplus {

template <>
class __ObjCommonOps<__tag_Renderbuffer>
 : public __RenderbufferName
{
public:
	typedef __RenderbufferTarget Target; /*<
	Renderbuffer bind target.
	>*/

	static __RenderbufferName Binding(Target target); /*<
	Returns the renderbuffer currently bound to the specified [^target].
	See [glfunc GetIntegerv].
	>*/
	static void Bind(Target target, __RenderbufferName renderbuffer); /*<
	Binds the specified [^renderbuffer] to the specified [^target].
	See [glfunc BindRenderbuffer].
	>*/

	void Bind(Target target) const; /*<
	Binds [^this] renderbuffer to the specified [^target].
	See [glfunc BindRenderbuffer].
	>*/
};
//]
//[oglplus_renderbuffer_1
template <>
class __ObjectOps<__tag_ExplicitSel, __tag_Renderbuffer>
 : public __ObjZeroOps<__tag_ExplicitSel, __tag_Renderbuffer>
{
public:
	static void Storage(
		Target target,
		__PixelDataInternalFormat internalformat,
		GLsizei width,
		GLsizei height
	); /*<
	Sets the storage parameters for the renderbuffer currently
	bound to the specified [^target].
	See [glfunc RenderbufferStorage].
	>*/
	static void Storage(
		Target target,
		const __images_ImageSpec& image_spec
	);

	static void StorageMultisample(
		Target target,
		GLsizei samples,
		__PixelDataInternalFormat internalformat,
		GLsizei width,
		GLsizei height
	); /*<
	Sets multipsample storage parameters for the renderbuffer currently
	bound to the specified [^target].
	See [glfunc RenderbufferStorageMultisample].
	>*/

	static GLsizei Width(Target target); /*<
	Returns the width in pixels of the renderbuffer currently bound
	to the specified [^target].
	See [glfunc GetRenderbufferParameter], [glconst RENDERBUFFER_WIDTH].
	>*/
	static GLsizei Height(Target target); /*<
	Returns the height in pixels of the renderbuffer currently bound
	to the specified [^target].
	See [glfunc GetRenderbufferParameter], [glconst RENDERBUFFER_HEIGHT].
	>*/

	static GLsizei RedSize(Target target); /*<
	Returns the size in bits of the red component of the renderbuffer
	currently bound to the specified [^target].
	See [glfunc GetRenderbufferParameter], [glconst RENDERBUFFER_RED_SIZE].
	>*/
	static GLsizei GreenSize(Target target); /*<
	Returns the size in bits of the green component of the renderbuffer
	currently bound to the specified [^target].
	See [glfunc GetRenderbufferParameter], [glconst RENDERBUFFER_GREEN_SIZE].
	>*/
	static GLsizei BlueSize(Target target); /*<
	Returns the size in bits of the blue component of the renderbuffer
	currently bound to the specified [^target].
	See [glfunc GetRenderbufferParameter], [glconst RENDERBUFFER_BLUE_SIZE].
	>*/
	static GLsizei AlphaSize(Target target); /*<
	Returns the size in bits of the alpha component of the renderbuffer
	currently bound to the specified [^target].
	See [glfunc GetRenderbufferParameter], [glconst RENDERBUFFER_ALPHA_SIZE].
	>*/
	static GLsizei DepthSize(Target target); /*<
	Returns the size in bits of the depth component of the renderbuffer
	currently bound to the specified [^target].
	See [glfunc GetRenderbufferParameter], [glconst RENDERBUFFER_DEPTH_SIZE].
	>*/
	static GLsizei StencilSize(Target target); /*<
	Returns the size in bits of the stencil component of the renderbuffer
	currently bound to the specified [^target].
	See [glfunc GetRenderbufferParameter], [glconst RENDERBUFFER_STENCIL_SIZE].
	>*/

	static GLsizei Samples(Target target); /*<
	Returns the number of samples of the renderbuffer currently
	bound to the specified [^target].
	See [glfunc GetRenderbufferParameter], [glconst RENDERBUFFER_SAMPLES].
	>*/
	static __PixelDataInternalFormat InternalFormat(Target target); /*<
	Returns the internal format of the renderbuffer currently
	bound to the specified [^target].
	See [glfunc GetRenderbufferParameter], [glconst RENDERBUFFER_INTERNAL_FORMAT].
	>*/
};
//]
//[oglplus_renderbuffer_def

typedef ObjectOps<__tag_ExplicitSel, __tag_Renderbuffer>
	RenderbufferOps;

typedef __Object<RenderbufferOps> Renderbuffer;

typedef __ObjectZero<__ObjZeroOps<__tag_ExplicitSel, __tag_Renderbuffer>>
	NoRenderbuffer;
//]
//[oglplus_renderbuffer_sugar

__RenderbufferTarget operator << (
	const RenderbufferOps& rbo,
	__RenderbufferTarget target
); /*<
Binds [^rbo] to the specified [^target].
>*/

__RenderbufferTarget operator << (
	__RenderbufferTarget target,
	const __images_ImageSpec& image_spec
); /*<
Sets the storage parameters from [^image_spec] to the renderbuffer
currently bound to the specified [^target].
>*/

} // namespace oglplus
//]

