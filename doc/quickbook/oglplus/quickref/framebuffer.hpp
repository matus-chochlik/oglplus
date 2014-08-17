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
	typedef __FramebufferTarget Target;

	static __FramebufferName Binding(Target target);
	static void Bind(Target target, __FramebufferName framebuffer);

	void Bind(Target target) const;
};
//]
//[oglplus_framebuffer_zero
template <>
class __ObjZeroOps<__tag_ExplicitSel, __tag_Framebuffer>
 : public __ObjCommonOps<__tag_Framebuffer>
{
public:
};
//]
//[oglplus_framebuffer
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
		> Buffer;

		typedef __OneOf<
			__FramebufferAttachment,
			__FramebufferColorAttachment
		> Attachment;

		typedef __FramebufferStatus Status;
	};

	static __FramebufferStatus Status(Target target)
	static bool IsComplete(Target target);
	static void Complete(Target target);

	static void AttachRenderbuffer(
		Target target,
		Property::Attachment attachment,
		__RenderbufferName renderbuffer
	);
	static void AttachColorRenderbuffer(
		Target target,
		__FramebufferColorAttachmentNumber attachment_no,
		__RenderbufferName renderbuffer
	);

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_2
	static void AttachTexture(
		Target target,
		Property::Attachment attachment,
		__TextureName texture,
		GLint level
	);
	static void AttachColorTexture(
		Target target,
		__FramebufferColorAttachmentNumber attachment_no,
		__TextureName texture,
		GLint level
	);
#endif

	static void AttachTexture1D(
		Target target,
		Property::Attachment attachment,
		__TextureTarget textarget,
		__TextureName texture,
		GLint level
	);
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
	);

#if GL_VERSION_4_3 || GL_ARB_invalidate_subdata
	static void Invalidate(
		Target target,
		const __EnumArray<Property::Buffer>& buffers
	);
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
	);
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

// TODO
} // namespace oglplus
//]

