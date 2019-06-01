/**
 *  @file oglplus/framebuffer.hpp
 *  @brief Framebuffer object wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_FRAMEBUFFER_1107121519_HPP
#define OGLPLUS_FRAMEBUFFER_1107121519_HPP

#include <oglplus/error/framebuffer.hpp>
#include <oglplus/framebuffer_attachment.hpp>
#include <oglplus/framebuffer_parameter.hpp>
#include <oglplus/framebuffer_status.hpp>
#include <oglplus/framebuffer_target.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/object/wrapper.hpp>
#include <oglplus/one_of.hpp>
#include <oglplus/texture_target.hpp>
#include <cassert>

namespace oglplus {

// NOTE: Xlib.h defines this symbol
// using the preprocessor.
#ifdef Status
#undef Status
#endif

/// Class wrapping framebuffer construction/destruction functions
/** @note Do not use this class directly, use Framebuffer instead.
 *
 *  @glsymbols
 *  @glfunref{GenFramebuffers}
 *  @glfunref{DeleteFramebuffers}
 *  @glfunref{IsFramebuffer}
 */
template <>
class ObjGenDelOps<tag::Framebuffer> {
protected:
    static void Gen(tag::Generate, GLsizei count, GLuint* names) {
        assert(names != nullptr);
        OGLPLUS_GLFUNC(GenFramebuffers)(count, names);
        OGLPLUS_CHECK_SIMPLE(GenFramebuffers);
    }
#if GL_VERSION_4_5 || GL_ARB_direct_state_access
    static void Gen(tag::Create, GLsizei count, GLuint* names) {
        assert(names != nullptr);
        OGLPLUS_GLFUNC(CreateFramebuffers)(count, names);
        OGLPLUS_CHECK_SIMPLE(CreateFramebuffers);
    }
#endif

    static void Delete(GLsizei count, GLuint* names) {
        assert(names != nullptr);
        OGLPLUS_GLFUNC(DeleteFramebuffers)(count, names);
        OGLPLUS_VERIFY_SIMPLE(DeleteFramebuffers);
    }

    static Boolean IsA(GLuint name) {
        Boolean result(OGLPLUS_GLFUNC(IsFramebuffer)(name), std::nothrow);
        OGLPLUS_VERIFY_SIMPLE(IsFramebuffer);
        return result;
    }
};

/// Framebuffer binding operations
template <>
class ObjBindingOps<tag::Framebuffer> {
private:
    static GLenum _binding_query(FramebufferTarget target);

protected:
    static GLuint _binding(FramebufferTarget target);

public:
    /// Framebuffer bind targets
    using Target = FramebufferTarget;

    /// Returns the current Framebuffer bound to specified @p target
    /**
     *  @glsymbols
     *  @glfunref{GetIntegerv}
     */
    static FramebufferName Binding(Target target) {
        return FramebufferName(_binding(target));
    }

    /// Binds the specified @p framebuffer to the specified @p target
    /**
     *  @glsymbols
     *  @glfunref{BindFramebuffer}
     */
    static void Bind(Target target, FramebufferName framebuffer) {
        OGLPLUS_GLFUNC(BindFramebuffer)(GLenum(target), GetGLName(framebuffer));
        OGLPLUS_VERIFY(BindFramebuffer, ObjectError, ObjectBinding(target));
    }
};

/// Common framebuffer operations
/** @note Do not use this class directly, use Framebuffer
 *  or DefaultFramebuffer instead.
 */
template <>
class ObjCommonOps<tag::Framebuffer>
  : public FramebufferName
  , public ObjBindingOps<tag::Framebuffer> {
protected:
    ObjCommonOps(FramebufferName name) noexcept
      : FramebufferName(name) {}

public:
    ObjCommonOps(ObjCommonOps&&) = default;
    ObjCommonOps(const ObjCommonOps&) = default;
    ObjCommonOps& operator=(ObjCommonOps&&) = default;
    ObjCommonOps& operator=(const ObjCommonOps&) = default;

    using ObjBindingOps<tag::Framebuffer>::Bind;

    /// Binds this framebuffer to the specified @p target
    /**
     *  @glsymbols
     *  @glfunref{BindFramebuffer}
     */
    void Bind(Target target) const {
        Bind(target, *this);
    }
};

/// Class wrapping framebuffer functions with explicit target selector
/** @note Do not use this class directly, use Framebuffer instead.
 */
template <>
class ObjectOps<tag::ExplicitSel, tag::Framebuffer>
  : public ObjZeroOps<tag::ExplicitSel, tag::Framebuffer> {
protected:
    ObjectOps(FramebufferName name) noexcept
      : ObjZeroOps<tag::ExplicitSel, tag::Framebuffer>(name) {}

public:
    ObjectOps(ObjectOps&&) = default;
    ObjectOps(const ObjectOps&) = default;
    ObjectOps& operator=(ObjectOps&&) = default;
    ObjectOps& operator=(const ObjectOps&) = default;

    /// Types related to Framebuffer
    struct Property {
        /// Buffer of default FB or attachment of a FBO
        using Buffer = OneOf<
          GLenum,
          std::tuple<
            FramebufferBuffer,
            FramebufferAttachment,
            FramebufferColorAttachment>>;

        /// Attachment of a Framebuffer
        using Attachment = OneOf<
          GLenum,
          std::tuple<FramebufferAttachment, FramebufferColorAttachment>>;

        /// Status of a Framebuffer
        using Status = FramebufferStatus;
    };

    /// Checks the status of the framebuffer
    /** Returns one of the values in the @c FramebufferStatus enumeration.
     *  For complete framebuffers this member function returns
     *  Status::Complete.
     *
     *  @see IsComplete
     *
     *  @glsymbols
     *  @glfunref{CheckFramebufferStatus}
     */
    static FramebufferStatus Status(Target target) {
        GLenum result = OGLPLUS_GLFUNC(CheckFramebufferStatus)(GLenum(target));
        if(result == 0)
            OGLPLUS_CHECK(
              CheckFramebufferStatus, ObjectError, ObjectBinding(target));
        return FramebufferStatus(result);
    }

    /// Returns true if the framebuffer is complete
    /**
     *  @see FramebufferStatus
     *  @see Status()
     *
     *  @glsymbols
     *  @glfunref{CheckFramebufferStatus}
     */
    static bool IsComplete(Target target) {
        return Status(target) == FramebufferStatus::Complete;
    }

    static void HandleIncompleteError(Target target, FramebufferStatus status);

    /// Throws an exception if the framebuffer is not complete
    static void Complete(Target target) {
        FramebufferStatus status = Status(target);
        if(status != FramebufferStatus::Complete) {
            HandleIncompleteError(target, status);
        }
    }

    /// Attach a @p renderbuffer to the @p attachment point of @p target
    /**
     *  @see AttachColorRenderbuffer
     *  @see AttachTexture
     *  @see AttachTextureLayer
     *  @see AttachTexture1D
     *  @see AttachTexture2D
     *  @see AttachTexture3D
     *  @see AttachColorTexture
     *
     *  @glsymbols
     *  @glfunref{FramebufferRenderbuffer}
     */
    static void AttachRenderbuffer(
      Target target,
      Property::Attachment attachment,
      RenderbufferName renderbuffer) {
        OGLPLUS_GLFUNC(FramebufferRenderbuffer)
        (GLenum(target),
         GLenum(attachment),
         GL_RENDERBUFFER,
         GetGLName(renderbuffer));
        OGLPLUS_CHECK(
          FramebufferRenderbuffer,
          ObjectPairError,
          Subject(renderbuffer).ObjectBinding(target));
    }

    /// Detach a @p renderbuffer from @p attachment point of @p target
    /**
     *  @see DetachColorRenderbuffer
     *  @see DetachTexture
     *  @see DetachTextureLayer
     *  @see DetachTexture1D
     *  @see DetachTexture2D
     *  @see DetachTexture3D
     *  @see DetachColorTexture
     *
     *  @glsymbols
     *  @glfunref{FramebufferRenderbuffer}
     */
    static void DetachRenderbuffer(
      Target target, Property::Attachment attachment) {
        OGLPLUS_GLFUNC(FramebufferRenderbuffer)
        (GLenum(target), GLenum(attachment), GL_RENDERBUFFER, 0);
        OGLPLUS_CHECK(
          FramebufferRenderbuffer, ObjectError, ObjectBinding(target));
    }

    /// Attach a @p renderbuffer to the color @p attachment_no of @p target
    /**
     *  @see AttachRenderbuffer
     *  @see AttachTexture
     *  @see AttachTextureLayer
     *  @see AttachTexture1D
     *  @see AttachTexture2D
     *  @see AttachTexture3D
     *  @see AttachColorTexture
     *
     *  @glsymbols
     *  @glfunref{FramebufferRenderbuffer}
     */
    static void AttachColorRenderbuffer(
      Target target,
      FramebufferColorAttachmentNumber attachment_no,
      RenderbufferName renderbuffer) {
        OGLPLUS_GLFUNC(FramebufferRenderbuffer)
        (GLenum(target),
         GL_COLOR_ATTACHMENT0 + GLuint(attachment_no),
         GL_RENDERBUFFER,
         GetGLName(renderbuffer));
        OGLPLUS_CHECK(
          FramebufferRenderbuffer,
          ObjectPairError,
          Subject(renderbuffer).ObjectBinding(target));
    }

    /// Detach a @p renderbuffer from color @p attachment_no of @p target
    /**
     *  @see DetachRenderbuffer
     *  @see DetachTexture
     *  @see DetachTextureLayer
     *  @see DetachTexture1D
     *  @see DetachTexture2D
     *  @see DetachTexture3D
     *  @see DetachColorTexture
     *
     *  @glsymbols
     *  @glfunref{FramebufferRenderbuffer}
     */
    static void DetachColorRenderbuffer(
      Target target, FramebufferColorAttachmentNumber attachment_no) {
        OGLPLUS_GLFUNC(FramebufferRenderbuffer)
        (GLenum(target),
         GL_COLOR_ATTACHMENT0 + GLuint(attachment_no),
         GL_RENDERBUFFER,
         0);
        OGLPLUS_CHECK(
          FramebufferRenderbuffer, ObjectPairError, ObjectBinding(target));
    }

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_2
    /// Attach a @p texture to the @p attachment point of @p target
    /**
     *  @see AttachRenderbuffer
     *  @see AttachColorRenderbuffer
     *  @see AttachTextureLayer
     *  @see AttachTexture1D
     *  @see AttachTexture2D
     *  @see AttachTexture3D
     *  @see AttachColorTexture
     *
     *  @glverreq{3,2}
     *  @glsymbols
     *  @glfunref{FramebufferTexture}
     */
    static void AttachTexture(
      Target target,
      Property::Attachment attachment,
      TextureName texture,
      GLint level) {
        OGLPLUS_GLFUNC(FramebufferTexture)
        (GLenum(target), GLenum(attachment), GetGLName(texture), level);
        OGLPLUS_CHECK(
          FramebufferTexture,
          ObjectPairError,
          Subject(texture).ObjectBinding(target).Index(level));
    }

    /// Detach a @p texture from @p attachment point of @p target
    /**
     *  @see DetachRenderbuffer
     *  @see DetachColorRenderbuffer
     *  @see DetachTextureLayer
     *  @see DetachTexture1D
     *  @see DetachTexture2D
     *  @see DetachTexture3D
     *  @see DetachColorTexture
     *
     *  @glverreq{3,2}
     *  @glsymbols
     *  @glfunref{FramebufferTexture}
     */
    static void DetachTexture(Target target, Property::Attachment attachment) {
        OGLPLUS_GLFUNC(FramebufferTexture)
        (GLenum(target), GLenum(attachment), 0, 0);
        OGLPLUS_CHECK(FramebufferTexture, ObjectError, ObjectBinding(target));
    }

    /// Attach a @p texture to the color @p attachment point of @p target
    /**
     *  @see AttachRenderbuffer
     *  @see AttachColorRenderbuffer
     *  @see AttachTexture1D
     *  @see AttachTexture2D
     *  @see AttachTexture3D
     *  @see AttachTexture
     *  @see AttachTextureLayer
     *
     *  @glsymbols
     *  @glfunref{FramebufferTexture}
     */
    static void AttachColorTexture(
      Target target,
      FramebufferColorAttachmentNumber attachment_no,
      TextureName texture,
      GLint level) {
        OGLPLUS_GLFUNC(FramebufferTexture)
        (GLenum(target),
         GL_COLOR_ATTACHMENT0 + GLenum(attachment_no),
         GetGLName(texture),
         level);
        OGLPLUS_CHECK(
          FramebufferTexture,
          ObjectPairError,
          Subject(texture).ObjectBinding(target).Index(level));
    }

    /// Detach a @p texture from color @p attachment point of @p target
    /**
     *  @see DetachRenderbuffer
     *  @see DetachColorRenderbuffer
     *  @see DetachTexture1D
     *  @see DetachTexture2D
     *  @see DetachTexture3D
     *  @see DetachTexture
     *  @see DetachTextureLayer
     *
     *  @glsymbols
     *  @glfunref{FramebufferTexture}
     */
    static void DetachColorTexture(
      Target target, FramebufferColorAttachmentNumber attachment_no) {
        OGLPLUS_GLFUNC(FramebufferTexture)
        (GLenum(target), GL_COLOR_ATTACHMENT0 + GLenum(attachment_no), 0, 0);
        OGLPLUS_CHECK(FramebufferTexture, ObjectError, ObjectBinding(target));
    }
#endif

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_0
    /// Attach a 1D @p texture to the @p attachment point of @p target
    /**
     *  @see AttachRenderbuffer
     *  @see AttachColorRenderbuffer
     *  @see AttachTexture2D
     *  @see AttachTexture3D
     *  @see AttachColorTexture
     *  @see AttachTexture
     *  @see AttachTextureLayer
     *
     *  @glsymbols
     *  @glfunref{FramebufferTexture1D}
     */
    static void AttachTexture1D(
      Target target,
      Property::Attachment attachment,
      TextureTarget textarget,
      TextureName texture,
      GLint level) {
        OGLPLUS_GLFUNC(FramebufferTexture1D)
        (GLenum(target),
         GLenum(attachment),
         GLenum(textarget),
         GetGLName(texture),
         level);
        OGLPLUS_CHECK(
          FramebufferTexture1D,
          ObjectPairError,
          Subject(texture).ObjectBinding(target).Index(level));
    }

    /// Detach a 1D @p texture from @p attachment point of @p target
    /**
     *  @see DetachRenderbuffer
     *  @see DetachColorRenderbuffer
     *  @see DetachTexture2D
     *  @see DetachTexture3D
     *  @see DetachColorTexture
     *  @see DetachTexture
     *  @see DetachTextureLayer
     *
     *  @glsymbols
     *  @glfunref{FramebufferTexture1D}
     */
    static void DetachTexture1D(
      Target target, Property::Attachment attachment) {
        OGLPLUS_GLFUNC(FramebufferTexture1D)
        (GLenum(target), GLenum(attachment), 0, 0, 0);
        OGLPLUS_CHECK(FramebufferTexture1D, ObjectError, ObjectBinding(target));
    }
#endif

    /// Attach a 2D @p texture to the @p attachment point of @p target
    /**
     *  @see AttachRenderbuffer
     *  @see AttachColorRenderbuffer
     *  @see AttachTexture1D
     *  @see AttachTexture3D
     *  @see AttachColorTexture
     *  @see AttachTexture
     *  @see AttachTextureLayer
     *
     *  @glsymbols
     *  @glfunref{FramebufferTexture2D}
     */
    static void AttachTexture2D(
      Target target,
      Property::Attachment attachment,
      TextureTarget textarget,
      TextureName texture,
      GLint level) {
        OGLPLUS_GLFUNC(FramebufferTexture2D)
        (GLenum(target),
         GLenum(attachment),
         GLenum(textarget),
         GetGLName(texture),
         level);
        OGLPLUS_CHECK(
          FramebufferTexture2D,
          ObjectPairError,
          Subject(texture).ObjectBinding(target).Index(level));
    }

    /// Detach a 2D @p texture from @p attachment point of @p target
    /**
     *  @see DetachRenderbuffer
     *  @see DetachColorRenderbuffer
     *  @see DetachTexture1D
     *  @see DetachTexture3D
     *  @see DetachColorTexture
     *  @see DetachTexture
     *  @see DetachTextureLayer
     *
     *  @glsymbols
     *  @glfunref{FramebufferTexture2D}
     */
    static void DetachTexture2D(
      Target target, Property::Attachment attachment) {
        OGLPLUS_GLFUNC(FramebufferTexture2D)
        (GLenum(target), GLenum(attachment), 0, 0, 0);
        OGLPLUS_CHECK(FramebufferTexture2D, ObjectError, ObjectBinding(target));
    }

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_0
    /// Attach a 3D @p texture to the @p attachment point of @p target
    /**
     *  @see AttachRenderbuffer
     *  @see AttachColorRenderbuffer
     *  @see AttachTexture1D
     *  @see AttachTexture2D
     *  @see AttachColorTexture
     *  @see AttachTexture
     *  @see AttachTextureLayer
     *
     *  @glsymbols
     *  @glfunref{FramebufferTexture3D}
     */
    static void AttachTexture3D(
      Target target,
      Property::Attachment attachment,
      TextureTarget textarget,
      TextureName texture,
      GLint level,
      GLint layer) {
        OGLPLUS_GLFUNC(FramebufferTexture3D)
        (GLenum(target),
         GLenum(attachment),
         GLenum(textarget),
         GetGLName(texture),
         level,
         layer);
        OGLPLUS_CHECK(
          FramebufferTexture3D,
          ObjectPairError,
          Subject(texture).ObjectBinding(target).Index(level));
    }

    /// Detach a 3D @p texture from @p attachment point of @p target
    /**
     *  @see DetachRenderbuffer
     *  @see DetachColorRenderbuffer
     *  @see DetachTexture1D
     *  @see DetachTexture2D
     *  @see DetachColorTexture
     *  @see DetachTexture
     *  @see DetachTextureLayer
     *
     *  @glsymbols
     *  @glfunref{FramebufferTexture3D}
     */
    static void DetachTexture3D(
      Target target, Property::Attachment attachment) {
        OGLPLUS_GLFUNC(FramebufferTexture3D)
        (GLenum(target), GLenum(attachment), 0, 0, 0, 0);
        OGLPLUS_CHECK(FramebufferTexture3D, ObjectError, ObjectBinding(target));
    }
#endif

    /// Attach a @p texture layer to the @p attachment point of @p target
    /**
     *  @see AttachRenderbuffer
     *  @see AttachColorRenderbuffer
     *  @see AttachTexture1D
     *  @see AttachTexture2D
     *  @see AttachTexture3D
     *  @see AttachColorTexture
     *  @see AttachTexture
     *
     *  @glsymbols
     *  @glfunref{FramebufferTextureLayer}
     */
    static void AttachTextureLayer(
      Target target,
      Property::Attachment attachment,
      TextureName texture,
      GLint level,
      GLint layer) {
        OGLPLUS_GLFUNC(FramebufferTextureLayer)
        (GLenum(target), GLenum(attachment), GetGLName(texture), level, layer);
        OGLPLUS_CHECK(
          FramebufferTextureLayer,
          ObjectPairError,
          Subject(texture).ObjectBinding(target).Index(level));
    }

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_3 || GL_ARB_invalidate_subdata
    /// Invalidates the specified attachments or buffers of the Framebuffer
    /**
     *  @glvoereq{4,3,ARB,invalidate_subdata}
     *  @glsymbols
     *  @glfunref{InvalidateFramebuffer}
     */
    static void Invalidate(
      Target target, const EnumArray<Property::Buffer>& buffers) {
        OGLPLUS_GLFUNC(InvalidateFramebuffer)
        (GLenum(target), GLsizei(buffers.Count()), buffers.Values());
        OGLPLUS_CHECK(
          InvalidateFramebuffer, ObjectError, ObjectBinding(target));
    }

    /// Invalidates the specified attachments or buffers of the Framebuffer
    /**
     *  @glvoereq{4,3,ARB,invalidate_subdata}
     *  @glsymbols
     *  @glfunref{InvalidateFramebuffer}
     */
    static void Invalidate(
      Target target, SizeType count, const Property::Buffer* buffers) {
        Invalidate(target, EnumArray<Property::Buffer>(count, buffers));
    }

    /// Invalidates parts of attachments or buffers of the Framebuffer
    /**
     *  @glvoereq{4,3,ARB,invalidate_subdata}
     *  @glsymbols
     *  @glfunref{InvalidateSubFramebuffer}
     */
    static void Invalidate(
      Target target,
      const EnumArray<Property::Buffer>& buffers,
      GLint x,
      GLint y,
      SizeType width,
      SizeType height) {
        OGLPLUS_GLFUNC(InvalidateSubFramebuffer)
        (GLenum(target),
         GLsizei(buffers.Count()),
         buffers.Values(),
         x,
         y,
         width,
         height);
        OGLPLUS_CHECK(
          InvalidateSubFramebuffer, ObjectError, ObjectBinding(target));
    }

    /// Invalidates parts of attachments or buffers of the Framebuffer
    /**
     *  @glvoereq{4,3,ARB,invalidate_subdata}
     *  @glsymbols
     *  @glfunref{InvalidateSubFramebuffer}
     */
    static void Invalidate(
      Target target,
      SizeType count,
      const Property::Buffer* buffers,
      GLint x,
      GLint y,
      SizeType width,
      SizeType height) {
        Invalidate(
          target,
          EnumArray<Property::Buffer>(count, buffers),
          x,
          y,
          width,
          height);
    }
#endif

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_3
    static GLint GetIntParam(Target target, FramebufferParameter query);

    /// Returns the default width of framebuffer bound to @p target
    /**
     *  @see DefaultHeight
     *  @see DefaultLayers
     *
     *  @glsymbols
     *  @glfunref{GetFramebufferParameter}
     *  @gldefref{FRAMEBUFFER_DEFAULT_WIDTH}
     */
    static SizeType DefaultWidth(Target target) {
        return MakeSizeType(
          GetIntParam(
            target, FramebufferParameter(GL_FRAMEBUFFER_DEFAULT_WIDTH)),
          std::nothrow);
    }

    /// Returns the default height of framebuffer bound to @p target
    /**
     *  @see DefaultWidth
     *  @see DefaultLayers
     *
     *  @glsymbols
     *  @glfunref{GetFramebufferParameter}
     *  @gldefref{FRAMEBUFFER_DEFAULT_HEIGHT}
     */
    static SizeType DefaultHeight(Target target) {
        return MakeSizeType(
          GetIntParam(
            target, FramebufferParameter(GL_FRAMEBUFFER_DEFAULT_HEIGHT)),
          std::nothrow);
    }

    /// Returns the default number of layers of FB bound to @p target
    /**
     *  @see DefaultWidth
     *  @see DefaultHeight
     *
     *  @glsymbols
     *  @glfunref{GetFramebufferParameter}
     *  @gldefref{FRAMEBUFFER_DEFAULT_LAYERS}
     */
    static SizeType DefaultLayers(Target target) {
        return MakeSizeType(
          GetIntParam(
            target, FramebufferParameter(GL_FRAMEBUFFER_DEFAULT_LAYERS)),
          std::nothrow);
    }

    /// Returns the number default samples of FB bound to @p target
    /**
     *  @see DefaultLayers
     *  @see DefaultFixedSampleLocations
     *
     *  @glsymbols
     *  @glfunref{GetFramebufferParameter}
     *  @gldefref{FRAMEBUFFER_DEFAULT_SAMPLES}
     */
    static SizeType DefaultSamples(Target target) {
        return MakeSizeType(
          GetIntParam(
            target, FramebufferParameter(GL_FRAMEBUFFER_DEFAULT_SAMPLES)),
          std::nothrow);
    }

    /// Returns the number default samples of FB bound to @p target
    /**
     *  @see DefaultSamples
     *
     *  @glsymbols
     *  @glfunref{GetFramebufferParameter}
     *  @gldefref{FRAMEBUFFER_DEFAULT_SAMPLES}
     */
    static SizeType DefaultFixedSampleLocations(Target target) {
        return MakeSizeType(
          GetIntParam(
            target,
            FramebufferParameter(
              GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS)),
          std::nothrow);
    }

    /// Returns the number samples of FB bound to @p target
    /**
     *
     *  @glsymbols
     *  @glfunref{GetFramebufferParameter}
     *  @gldefref{SAMPLES}
     */
    static SizeType Samples(Target target) {
        return MakeSizeType(
          GetIntParam(target, FramebufferParameter(GL_SAMPLES)), std::nothrow);
    }

    /// Returns the number sample buffers of FB bound to @p target
    /**
     *
     *  @glsymbols
     *  @glfunref{GetFramebufferParameter}
     *  @gldefref{SAMPLES}
     */
    static SizeType SampleBuffers(Target target) {
        return MakeSizeType(
          GetIntParam(target, FramebufferParameter(GL_SAMPLE_BUFFERS)),
          std::nothrow);
    }

    /// Indicates if doublebuffering is enabled
    /**
     *  @glsymbols
     *  @glfunref{GetFramebufferParameter}
     *  @gldefref{DOUBLEBUFFER}
     */
    static Boolean Doublebuffer(Target target) {
        return Boolean(
          GetIntParam(target, FramebufferParameter(GL_DOUBLEBUFFER)),
          std::nothrow);
    }

    /// Indicates if stereo mode is enabled
    /**
     *  @glsymbols
     *  @glfunref{GetFramebufferParameter}
     *  @gldefref{STEREO}
     */
    static Boolean Stereo(Target target) {
        return Boolean(
          GetIntParam(target, FramebufferParameter(GL_STEREO)), std::nothrow);
    }

    /// Sets the value of a framebuffer parameter
    /**
     *  @glsymbols
     *  @glfunref{FramebufferParameter}
    static void Parameter(
        Target target,
        FramebufferParameter parameter,
        GLint value
    )
    {
        OGLPLUS_GLFUNC(FramebufferParameteri)(
            GLenum(target),
            GLenum(parameter),
            value
        );
        OGLPLUS_CHECK(
            FramebufferParameteri,
            ObjectError,
            ObjectBinding(target)
        );
    }
     */

    /// Sets the default framebuffer width
    /**
     *  @glsymbols
     *  @glfunref{FramebufferParameter}
     *  @gldefref{FRAMEBUFFER_DEFAULT_WIDTH}
     */
    static void DefaultWidth(Target target, GLint width) {
        OGLPLUS_GLFUNC(FramebufferParameteri)
        (GLenum(target), GL_FRAMEBUFFER_DEFAULT_WIDTH, width);
        OGLPLUS_CHECK(
          FramebufferParameteri, ObjectError, ObjectBinding(target));
    }

    /// Sets the default framebuffer height
    /**
     *  @glsymbols
     *  @glfunref{FramebufferParameter}
     *  @gldefref{FRAMEBUFFER_DEFAULT_HEIGHT}
     */
    static void DefaultHeight(Target target, GLint height) {
        OGLPLUS_GLFUNC(FramebufferParameteri)
        (GLenum(target), GL_FRAMEBUFFER_DEFAULT_HEIGHT, height);
        OGLPLUS_CHECK(
          FramebufferParameteri, ObjectError, ObjectBinding(target));
    }

    /// Sets the default framebuffer layers
    /**
     *  @glsymbols
     *  @glfunref{FramebufferParameter}
     *  @gldefref{FRAMEBUFFER_DEFAULT_LAYERS}
     */
    static void DefaultLayers(Target target, GLint layers) {
        OGLPLUS_GLFUNC(FramebufferParameteri)
        (GLenum(target), GL_FRAMEBUFFER_DEFAULT_LAYERS, layers);
        OGLPLUS_CHECK(
          FramebufferParameteri, ObjectError, ObjectBinding(target));
    }

    /// Sets the default framebuffer samples
    /**
     *  @glsymbols
     *  @glfunref{FramebufferParameter}
     *  @gldefref{FRAMEBUFFER_DEFAULT_SAMPLES}
     */
    static void DefaultSamples(Target target, GLint samples) {
        OGLPLUS_GLFUNC(FramebufferParameteri)
        (GLenum(target), GL_FRAMEBUFFER_DEFAULT_SAMPLES, samples);
        OGLPLUS_CHECK(
          FramebufferParameteri, ObjectError, ObjectBinding(target));
    }

    /// Sets the default framebuffer fixed sample locations
    /**
     *  @glsymbols
     *  @glfunref{FramebufferParameter}
     *  @gldefref{FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS}
     */
    static void DefaultFixedSampleLocations(Target target, GLint locations) {
        OGLPLUS_GLFUNC(FramebufferParameteri)
        (GLenum(target),
         GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS,
         locations);
        OGLPLUS_CHECK(
          FramebufferParameteri, ObjectError, ObjectBinding(target));
    }
#endif
};

/// Framebuffer operations with explicit selector
using FramebufferOps = ObjectOps<tag::ExplicitSel, tag::Framebuffer>;

/// Helper class used with syntax-sugar operators
struct FramebufferComplete {};

// Helper class for syntax-sugar operators
struct FramebufferTargetAndAttch {
    FramebufferTarget target;

    using Attachment = FramebufferOps::Property::Attachment;
    Attachment attachment;

    FramebufferTargetAndAttch(FramebufferTarget& t, Attachment a)
      : target(t)
      , attachment(a) {}
};

// syntax sugar operators
inline FramebufferTargetAndAttch operator|(
  FramebufferTarget target, FramebufferOps::Property::Attachment attachment) {
    return FramebufferTargetAndAttch(target, attachment);
}

inline FramebufferTargetAndAttch operator<<(
  FramebufferTarget target, FramebufferOps::Property::Attachment attachment) {
    return FramebufferTargetAndAttch(target, attachment);
}

// Bind
inline FramebufferTarget operator<<(
  const FramebufferOps& fbo, FramebufferTarget target) {
    fbo.Bind(target);
    return target;
}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_2
// AttachTexture
inline FramebufferTarget operator<<(
  FramebufferTargetAndAttch taa, TextureName tex) {
    FramebufferOps::AttachTexture(taa.target, taa.attachment, tex, 0);
    return taa.target;
}
#endif

// AttachRenderbuffer
inline FramebufferTarget operator<<(
  FramebufferTargetAndAttch taa, RenderbufferName rbo) {
    FramebufferOps::AttachRenderbuffer(taa.target, taa.attachment, rbo);
    return taa.target;
}

// Complete
inline FramebufferTarget operator<<(
  FramebufferTarget target, FramebufferComplete) {
    FramebufferOps::Complete(target);
    return target;
}

/// An @ref oglplus_object encapsulating the default framebuffer functionality
/**
 *  @ingroup oglplus_objects
 */
using DefaultFramebuffer =
  ObjectZero<ObjZeroOps<tag::ExplicitSel, tag::Framebuffer>>;

inline FramebufferTarget operator<<(
  DefaultFramebuffer dfb, FramebufferTarget target) {
    dfb.Bind(target);
    return target;
}

/// An @ref oglplus_object encapsulating the framebuffer object functionality
/**
 *  @ingroup oglplus_objects
 */
using Framebuffer = Object<FramebufferOps>;

} // namespace oglplus

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/framebuffer.ipp>
#endif // OGLPLUS_LINK_LIBRARY

#endif // include guard
