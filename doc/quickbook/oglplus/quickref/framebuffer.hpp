/*
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_framebuffer_common
namespace oglplus {

template <>
class __ObjCommonOps<__tag_Framebuffer>
 : public __FramebufferName
{
public:
	typedef __FramebufferTarget Target; /*<
	Framebuffer bind target.
	>*/

	static __FramebufferName Binding(Target target); /*<
	Returns the framebuffer currently bound to the specified [^target].
	See [glfunc GetIntegerv].
	>*/
	static void Bind(Target target, __FramebufferName framebuffer); /*<
	Binds the specified [^framebuffer] to the specified [^target].
	See [glfunc BindFramebuffer].
	>*/

	void Bind(Target target) const; /*<
	Binds [^this] framebuffer to the specified [^target].
	See [glfunc BindFramebuffer].
	>*/
};
//]
//[oglplus_framebuffer_zero
template <>
class __ObjZeroOps<__tag_ExplicitSel, __tag_Framebuffer>
 : public __ObjCommonOps<__tag_Framebuffer>
{
public: /*<
There are no operations that can work explicitly on framebuffer
object zero besides binding, so this class just inherits from
the common framebuffer operations wrapper.
>*/
};
//]
//[oglplus_framebuffer_1
template <>
class __ObjectOps<__tag_ExplicitSel, __tag_Framebuffer>
 : public __ObjZeroOps<__tag_ExplicitSel, __tag_Framebuffer>
{
public:
	struct Property
	{
		typedef __OneOf<
			__FramebufferBuffer,
			__FramebufferAttachment,
			__FramebufferColorAttachment
		> Buffer; /*<
		Enumerations specifying framebuffer output buffer.
		>*/

		typedef __OneOf<
			__FramebufferAttachment,
			__FramebufferColorAttachment
		> Attachment; /*<
		Enumerations specifying framebuffer attachments.
		>*/

		typedef __FramebufferStatus Status;
	};

	static __FramebufferStatus Status(Target target); /*<
	Returns the status of the framebuffer currently bound
	to the specified [^target].
	>*/
	static bool IsComplete(Target target); /*<
	Returns true if the framebuffer currently bound to the specified
	[^target] is complete.
	>*/
	static void Complete(Target target); /*<
	Throws an __IncompleteFramebuffer exception if the framebuffer
	currently bound to the specified [^target] is not complete.
	>*/

	static void AttachRenderbuffer(
		Target target,
		Property::Attachment attachment,
		__RenderbufferName renderbuffer
	); /*<
	Attaches a [^renderbuffer] object as an [^attachment] to the framebuffer
	currently bound to the specified [^target].
	>*/
	static void AttachColorRenderbuffer(
		Target target,
		__FramebufferColorAttachmentNumber attachment_no,
		__RenderbufferName renderbuffer
	); /*<
	Attaches a [^renderbuffer] object as a color attachment with index
	specified by [^attachment_no] to the framebuffer currently bound
	to the specified [^target].
	>*/

#if GL_VERSION_3_2
	static void AttachTexture(
		Target target,
		Property::Attachment attachment,
		__TextureName texture,
		GLint level
	); /*<
	Attaches the specified [^texture] [^level] as an attachment
	to the framebuffer currently bound to the specified [^target].
	>*/
	static void AttachColorTexture(
		Target target,
		__FramebufferColorAttachmentNumber attachment_no,
		__TextureName texture,
		GLint level
	); /*<
	Attaches the specified [^texture] [^level] as a color attachment with
	index specified by [^attachment_no] to the framebuffer currently
	bound to the specified [^target].
	>*/
#endif

	static void AttachTexture1D(
		Target target,
		Property::Attachment attachment,
		__TextureTarget textarget,
		__TextureName texture,
		GLint level
	); /*<
	Attaches the [^level] (or [^level]'s [^layer]) of a 1D, 2D or 3D
	[^texture] with type specified by [^textarget], as an [^attachment]
	of the framebuffer currently bound to the specified [^target].
	>*/
	static void AttachTexture2D(
		Target target,
		Property::Attachment attachment,
		__TextureTarget textarget,
		__TextureName texture,
		GLint level
	);
	static void AttachTexture3D(
		Target target,
		Property::Attachment attachment,
		__TextureTarget textarget,
		__TextureName texture,
		GLint level,
		GLint layer
	);

	static void AttachTextureLayer(
		Target target,
		Property::Attachment attachment,
		__TextureName texture,
		GLint level,
		GLint layer
	); /*<
	Attaches the [^level] (or [^level]'s [^layer]) of a 1D, 2D or 3D
	[^texture] as an [^attachment] of the framebuffer currently bound
	to the specified [^target].
	>*/
//]
//[oglplus_framebuffer_2

#if GL_VERSION_4_3 || GL_ARB_invalidate_subdata
	static void Invalidate(
		Target target,
		const __EnumArray<Property::Buffer>& buffers
	); /*<
	Invalidates the specified attachments or [^buffers] of the framebuffer
	currently bound to the specified [^target].
	>*/
	static void Invalidate(
		Target target,
		GLsizei count,
		const Property::Buffer* buffers
	);

	static void Invalidate(
		Target target,
		const __EnumArray<Property::Buffer>& buffers,
		GLint x,
		GLint y,
		GLsizei width,
		GLsizei height
	); /*<
	Invalidates parts (specified by [^x], [^y], [^width] and [^height])
	of attachments or [^buffers] of the framebuffer currently bound to
	the specified [^target].
	>*/
	static void Invalidate(
		Target target,
		GLsizei count,
		const Property::Buffer* buffers,
		GLint x,
		GLint y,
		GLsizei width,
		GLsizei height
	);
#endif
};

} // namespace oglplus
//]

