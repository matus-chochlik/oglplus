/**
 *  @file oglplus/ext/EXT_direct_state_access.hpp
 *  @brief Wrapper for a subset of the EXT_direct_state_access extension
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_EXT_EXT_DIRECT_STATE_ACCESS_1203031902_HPP
#define OGLPLUS_EXT_EXT_DIRECT_STATE_ACCESS_1203031902_HPP

#include <oglplus/extension.hpp>
#include <oglplus/ext/ARB_compatibility.hpp>
#include <oglplus/angle.hpp>
#include <oglplus/texture.hpp>
#include <oglplus/bitfield.hpp>

namespace oglplus {

#if OGLPLUS_DOCUMENTATION_ONLY || GL_EXT_direct_state_access

/// Wrapper around context direct state access operations
/**
 *  @note Do not use this class directly use EXT_direct_state_access instead.
 */
struct DSAContextEXT
{
	/// Resets specified client attribute group variables to default values
	/**
	 *  @glsymbols
	 *  @glfunref{ClientAttribDefaultEXT}
	 */
	static void ClientAttribDefault(
		Bitfield<CompatibilityClientAttributeGroup> attrib_groups
	)
	{
		OGLPLUS_GLFUNC(ClientAttribDefaultEXT)(
			GLbitfield(attrib_groups)
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(ClientAttribDefaultEXT));
	}

	/// Pushes specified client attribute group variables on the stack
	/**
	 *  @glsymbols
	 *  @glfunref{PushClientAttribDefaultEXT}
	 */
	static void PushClientAttribDefault(
		Bitfield<CompatibilityClientAttributeGroup> attrib_groups
	)
	{
		OGLPLUS_GLFUNC(PushClientAttribDefaultEXT)(
			GLbitfield(attrib_groups)
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(PushClientAttribDefaultEXT));
	}
};

/// Wrapper around matrix direct state access operations
/**
 *  @note Do not use this class directly use EXT_direct_state_access instead.
 */
struct DSAMatrixEXT
{
	/// Pushes a matrix on the stack specified by @p matrix_mode
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixPushEXT}
	 */
	static void MatrixPush(MatrixMode matrix_mode)
	{
		OGLPLUS_GLFUNC(MatrixPushEXT)(GLenum(matrix_mode));
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixPushEXT));
	}

	/// Pops a matrix from the stack specified by @p matrix_mode
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixPopEXT}
	 */
	static void MatrixPop(MatrixMode matrix_mode)
	{
		OGLPLUS_GLFUNC(MatrixPopEXT)(GLenum(matrix_mode));
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixPopEXT));
	}

	/// Loads a identity matrix
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixLoadIdentityEXT}
	 */
	static void MatrixLoadIdentity(MatrixMode matrix_mode)
	{
		OGLPLUS_GLFUNC(MatrixLoadIdentityEXT)(GLenum(matrix_mode));
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixLoadIdentityEXT));
	}

	/// Loads the specified @p matrix
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixLoadTransposeEXT}
	 */
	static void MatrixLoad(MatrixMode matrix_mode, const Mat4f& matrix)
	{
		OGLPLUS_GLFUNC(MatrixLoadTransposefEXT)(
			GLenum(matrix_mode),
			Data(matrix)
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixLoadTransposefEXT));
	}

	/// Loads the specified @p matrix
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixLoadTransposeEXT}
	 */
	static void MatrixLoad(MatrixMode matrix_mode, const Mat4d& matrix)
	{
		OGLPLUS_GLFUNC(MatrixLoadTransposedEXT)(
			GLenum(matrix_mode),
			Data(matrix)
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixLoadTransposedEXT));
	}

	/// Multiplies the current matrix by the specified @p matrix
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixMultTransposeEXT}
	 */
	static void MatrixMult(MatrixMode matrix_mode, const Mat4f& matrix)
	{
		OGLPLUS_GLFUNC(MatrixMultTransposefEXT)(
			GLenum(matrix_mode),
			Data(matrix)
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixMultTransposefEXT));
	}

	/// Multiplies the current matrix by the specified @p matrix
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixMultTransposeEXT}
	 */
	static void MatrixMult(MatrixMode matrix_mode, const Mat4d& matrix)
	{
		OGLPLUS_GLFUNC(MatrixMultTransposedEXT)(
			GLenum(matrix_mode),
			Data(matrix)
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixMultTransposedEXT));
	}

	/// Applies rotation to the matrix specified by @p matrix_mode
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixRotateEXT}
	 */
	static void MatrixRotate(
		MatrixMode matrix_mode,
		Angle<GLfloat> angle,
		const GLfloat x,
		const GLfloat y,
		const GLfloat z
	)
	{
		OGLPLUS_GLFUNC(MatrixRotatefEXT)(
			GLenum(matrix_mode),
			angle.ValueInDegrees(),
			x, y, z
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixRotatefEXT));
	}

	/// Applies rotation to the matrix specified by @p matrix_mode
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixRotateEXT}
	 */
	static void MatrixRotate(
		MatrixMode matrix_mode,
		Angle<GLfloat> angle,
		const Vector<GLfloat, 3>& axis
	)
	{
		OGLPLUS_GLFUNC(MatrixRotatefEXT)(
			GLenum(matrix_mode),
			angle.ValueInDegrees(),
			axis.x(), axis.y(), axis.z()
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixRotatefEXT));
	}

	/// Applies rotation to the matrix specified by @p matrix_mode
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixRotateEXT}
	 */
	static void MatrixRotate(
		MatrixMode matrix_mode,
		Angle<GLdouble> angle,
		const Vector<GLdouble, 3>& axis
	)
	{
		OGLPLUS_GLFUNC(MatrixRotatedEXT)(
			GLenum(matrix_mode),
			angle.ValueInDegrees(),
			axis.x(), axis.y(), axis.z()
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixRotatedEXT));
	}

	/// Scales the matrix specified by @p matrix_mode
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixScaleEXT}
	 */
	static void MatrixScale(
		MatrixMode matrix_mode,
		const GLfloat x,
		const GLfloat y,
		const GLfloat z
	)
	{
		OGLPLUS_GLFUNC(MatrixScalefEXT)(
			GLenum(matrix_mode),
			x, y, z
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixScalefEXT));
	}

	/// Scales the matrix specified by @p matrix_mode
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixScaleEXT}
	 */
	static void MatrixScale(
		MatrixMode matrix_mode,
		const Vector<GLfloat, 3>& amount
	)
	{
		OGLPLUS_GLFUNC(MatrixScalefEXT)(
			GLenum(matrix_mode),
			amount.x(), amount.y(), amount.z()
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixScalefEXT));
	}

	/// Scales the matrix specified by @p matrix_mode
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixScaleEXT}
	 */
	static void MatrixScale(
		MatrixMode matrix_mode,
		const Vector<GLdouble, 3>& amount
	)
	{
		OGLPLUS_GLFUNC(MatrixScaledEXT)(
			GLenum(matrix_mode),
			amount.x(), amount.y(), amount.z()
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixScaledEXT));
	}

	/// Applies translation to the matrix specified by @p matrix_mode
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixTranslateEXT}
	 */
	static void MatrixTranslate(
		MatrixMode matrix_mode,
		const GLfloat x,
		const GLfloat y,
		const GLfloat z
	)
	{
		OGLPLUS_GLFUNC(MatrixTranslatefEXT)(
			GLenum(matrix_mode),
			x, y, z
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixTranslatefEXT));
	}

	/// Applies translation the matrix specified by @p matrix_mode
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixTranslateEXT}
	 */
	static void MatrixTranslate(
		MatrixMode matrix_mode,
		const Vector<GLfloat, 3>& amount
	)
	{
		OGLPLUS_GLFUNC(MatrixTranslatefEXT)(
			GLenum(matrix_mode),
			amount.x(), amount.y(), amount.z()
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixTranslatefEXT));
	}

	/// Applies translation the matrix specified by @p matrix_mode
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixTranslateEXT}
	 */
	static void MatrixTranslate(
		MatrixMode matrix_mode,
		const Vector<GLdouble, 3>& amount
	)
	{
		OGLPLUS_GLFUNC(MatrixTranslatedEXT)(
			GLenum(matrix_mode),
			amount.x(), amount.y(), amount.z()
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixTranslatedEXT));
	}

	/// Makes an ortho-matrix from the matrix specified by @p matrix_mode
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixOrthoEXT}
	 */
	static void MatrixOrtho(
		MatrixMode matrix_mode,
		GLdouble left,
		GLdouble right,
		GLdouble bottom,
		GLdouble top,
		GLdouble near_depth,
		GLdouble far_depth
	)
	{
		OGLPLUS_GLFUNC(MatrixOrthoEXT)(
			GLenum(matrix_mode),
			left,
			right,
			bottom,
			top,
			near_depth,
			far_depth
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixOrthoEXT));
	}

	/// Makes a frustum-matrix from the matrix specified by @p matrix_mode
	/**
	 *  @glsymbols
	 *  @glfunref{MatrixFrustumEXT}
	 */
	static void MatrixFrustum(
		MatrixMode matrix_mode,
		GLdouble left,
		GLdouble right,
		GLdouble bottom,
		GLdouble top,
		GLdouble near_depth,
		GLdouble far_depth
	)
	{
		OGLPLUS_GLFUNC(MatrixFrustumEXT)(
			GLenum(matrix_mode),
			left,
			right,
			bottom,
			top,
			near_depth,
			far_depth
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MatrixFrustumEXT));
	}
};

/// Wrapper around matrix direct state access operations
/**
 *  @note Do not use this class directly use EXT_direct_state_access instead.
 */
struct DSATextureEXT
 : public FriendOf<Texture>
{
/* TODO
	void TextureParameteriEXT(uint texture, enum target,
				  enum pname, int param);
	void TextureParameterivEXT(uint texture, enum target,
				   enum pname, const int *param);

	void TextureParameterfEXT(uint texture, enum target,
				  enum pname, float param);
	void TextureParameterfvEXT(uint texture, enum target,
				   enum pname, const float *param);

	void TextureParameterIivEXT(uint texture, enum target,
				    enum pname, const int *params);
	void TextureParameterIuivEXT(uint texture, enum target,
				     enum pname, const uint *params);

	void GetTextureParameterIivEXT(uint texture, enum target,
				       enum pname, int *params);
	void GetTextureParameterIuivEXT(uint texture, enum target,
					enum pname, uint *params);

	void GetTextureParameterfvEXT(uint texture, enum target,
				      enum pname, float *params);
	void GetTextureParameterivEXT(uint texture, enum target,
				      enum pname, int *params);

	void GetTextureLevelParameterfvEXT(uint texture, enum target,
					   int level,
					   enum pname, float *params);
	void GetTextureLevelParameterivEXT(uint texture, enum target,
					   int level,
					   enum pname, int *params);
 */
	/// Specifies a one dimensional texture image
	/**
	 *  @glsymbols
	 *  @glfunref{TextureImage1DEXT}
	 */
	static void TextureImage1D(
		Texture& texture,
		Texture::Target target,
		GLint level,
		PixelDataInternalFormat internal_format,
		GLsizei width,
		GLint border,
		PixelDataFormat format,
		PixelDataType type,
		const void* data
	)
	{
		OGLPLUS_GLFUNC(TextureImage1DEXT)(
			FriendOf<Texture>::GetName(texture),
			GLenum(target),
			level,
			GLint(internal_format),
			width,
			border,
			GLenum(format),
			GLenum(type),
			data
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureImage1DEXT,
			Texture,
			EnumValueName(target),
			FriendOf<Texture>::GetName(texture)
		));
	}

	/// Specifies a two dimensional texture image
	/**
	 *  @glsymbols
	 *  @glfunref{TextureImage2DEXT}
	 */
	static void TextureImage2D(
		Texture& texture,
		Texture::Target target,
		GLint level,
		PixelDataInternalFormat internal_format,
		GLsizei width,
		GLsizei height,
		GLint border,
		PixelDataFormat format,
		PixelDataType type,
		const void* data
	)
	{
		OGLPLUS_GLFUNC(TextureImage2DEXT)(
			FriendOf<Texture>::GetName(texture),
			GLenum(target),
			level,
			GLint(internal_format),
			width,
			height,
			border,
			GLenum(format),
			GLenum(type),
			data
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureImage2DEXT,
			Texture,
			EnumValueName(target),
			FriendOf<Texture>::GetName(texture)
		));
	}

	/// Specifies a three dimensional texture image
	/**
	 *  @glsymbols
	 *  @glfunref{TextureImage3DEXT}
	 */
	static void TextureImage3D(
		Texture& texture,
		Texture::Target target,
		GLint level,
		PixelDataInternalFormat internal_format,
		GLsizei width,
		GLsizei height,
		GLsizei depth,
		GLint border,
		PixelDataFormat format,
		PixelDataType type,
		const void* data
	)
	{
		OGLPLUS_GLFUNC(TextureImage3DEXT)(
			FriendOf<Texture>::GetName(texture),
			GLenum(target),
			level,
			GLint(internal_format),
			width,
			height,
			depth,
			border,
			GLenum(format),
			GLenum(type),
			data
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureImage3DEXT,
			Texture,
			EnumValueName(target),
			FriendOf<Texture>::GetName(texture)
		));
	}

	/// Specifies a one dimensional texture sub-image
	/**
	 *  @glsymbols
	 *  @glfunref{TextureSubImage1DEXT}
	 */
	static void TextureSubImage1D(
		Texture& texture,
		Texture::Target target,
		GLint level,
		GLint xoffset,
		GLsizei width,
		PixelDataFormat format,
		PixelDataType type,
		const void* data
	)
	{
		OGLPLUS_GLFUNC(TextureSubImage1DEXT)(
			FriendOf<Texture>::GetName(texture),
			GLenum(target),
			level,
			xoffset,
			width,
			GLenum(format),
			GLenum(type),
			data
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureSubImage1DEXT,
			Texture,
			EnumValueName(target),
			FriendOf<Texture>::GetName(texture)
		));
	}

	/// Specifies a two dimensional texture sub-image
	/**
	 *  @glsymbols
	 *  @glfunref{TextureSubImage2DEXT}
	 */
	static void TextureSubImage2D(
		Texture& texture,
		Texture::Target target,
		GLint level,
		GLint xoffset,
		GLint yoffset,
		GLsizei width,
		GLsizei height,
		PixelDataFormat format,
		PixelDataType type,
		const void* data
	)
	{
		OGLPLUS_GLFUNC(TextureSubImage2DEXT)(
			FriendOf<Texture>::GetName(texture),
			GLenum(target),
			level,
			xoffset,
			yoffset,
			width,
			height,
			GLenum(format),
			GLenum(type),
			data
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureSubImage2DEXT,
			Texture,
			EnumValueName(target),
			FriendOf<Texture>::GetName(texture)
		));
	}

	/// Specifies a three dimensional texture sub-image
	/**
	 *  @glsymbols
	 *  @glfunref{TextureSubImage3DEXT}
	 */
	static void TextureSubImage3D(
		Texture& texture,
		Texture::Target target,
		GLint level,
		GLint xoffset,
		GLint yoffset,
		GLint zoffset,
		GLsizei width,
		GLsizei height,
		GLsizei depth,
		PixelDataFormat format,
		PixelDataType type,
		const void* data
	)
	{
		OGLPLUS_GLFUNC(TextureSubImage3DEXT)(
			FriendOf<Texture>::GetName(texture),
			GLenum(target),
			level,
			xoffset,
			yoffset,
			zoffset,
			width,
			height,
			depth,
			GLenum(format),
			GLenum(type),
			data
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureSubImage3DEXT,
			Texture,
			EnumValueName(target),
			FriendOf<Texture>::GetName(texture)
		));
	}

	/// Copies a one dimensional texture image from the framebuffer
	/**
	 *  @glsymbols
	 *  @glfunref{CopyTextureImage1DEXT}
	 */
	static void CopyTextureImage1D(
		Texture& texture,
		Texture::Target target,
		GLint level,
		PixelDataInternalFormat internal_format,
		GLint x,
		GLint y,
		GLsizei width,
		GLint border
	)
	{
		OGLPLUS_GLFUNC(CopyTextureImage1DEXT)(
			FriendOf<Texture>::GetName(texture),
			GLenum(target),
			level,
			GLint(internal_format),
			x,
			y,
			width,
			border
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			CopyTextureImage1DEXT,
			Texture,
			EnumValueName(target),
			FriendOf<Texture>::GetName(texture)
		));
	}

	/// Copies a two dimensional texture image from the framebuffer
	/**
	 *  @glsymbols
	 *  @glfunref{CopyTextureImage2DEXT}
	 */
	static void CopyTextureImage2D(
		Texture& texture,
		Texture::Target target,
		GLint level,
		PixelDataInternalFormat internal_format,
		GLint x,
		GLint y,
		GLsizei width,
		GLsizei height,
		GLint border
	)
	{
		OGLPLUS_GLFUNC(CopyTextureImage2DEXT)(
			FriendOf<Texture>::GetName(texture),
			GLenum(target),
			level,
			GLint(internal_format),
			x,
			y,
			width,
			height,
			border
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			CopyTextureImage2DEXT,
			Texture,
			EnumValueName(target),
			FriendOf<Texture>::GetName(texture)
		));
	}

	/// Copies a one dimensional texture sub-image from the framebuffer
	/**
	 *  @glsymbols
	 *  @glfunref{CopyTextureSubImage1DEXT}
	 */
	static void CopyTextureSubImage1D(
		Texture& texture,
		Texture::Target target,
		GLint level,
		GLint xoffset,
		GLint x,
		GLint y,
		GLsizei width
	)
	{
		OGLPLUS_GLFUNC(CopyTextureSubImage1DEXT)(
			FriendOf<Texture>::GetName(texture),
			GLenum(target),
			level,
			xoffset,
			x,
			y,
			width
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			CopyTextureSubImage1DEXT,
			Texture,
			EnumValueName(target),
			FriendOf<Texture>::GetName(texture)
		));
	}

	/// Copies a two dimensional texture sub-image from the framebuffer
	/**
	 *  @glsymbols
	 *  @glfunref{CopyTextureSubImage2DEXT}
	 */
	static void CopyTextureSubImage2D(
		Texture& texture,
		Texture::Target target,
		GLint level,
		GLint xoffset,
		GLint yoffset,
		GLint x,
		GLint y,
		GLsizei width,
		GLsizei height
	)
	{
		OGLPLUS_GLFUNC(CopyTextureSubImage2DEXT)(
			FriendOf<Texture>::GetName(texture),
			GLenum(target),
			level,
			xoffset,
			yoffset,
			x,
			y,
			width,
			height
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			CopyTextureSubImage2DEXT,
			Texture,
			EnumValueName(target),
			FriendOf<Texture>::GetName(texture)
		));
	}

	/// Copies a three dimensional texture sub-image from the framebuffer
	/**
	 *  @glsymbols
	 *  @glfunref{CopyTextureSubImage3DEXT}
	 */
	static void CopyTextureSubImage3D(
		Texture& texture,
		Texture::Target target,
		GLint level,
		GLint xoffset,
		GLint yoffset,
		GLint zoffset,
		GLint x,
		GLint y,
		GLsizei width,
		GLsizei height
	)
	{
		OGLPLUS_GLFUNC(CopyTextureSubImage3DEXT)(
			FriendOf<Texture>::GetName(texture),
			GLenum(target),
			level,
			xoffset,
			yoffset,
			zoffset,
			x,
			y,
			width,
			height
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			CopyTextureSubImage3DEXT,
			Texture,
			EnumValueName(target),
			FriendOf<Texture>::GetName(texture)
		));
	}

/*
	void GetTextureImageEXT(uint texture, enum target,
				int level,
				enum format, enum type, void *pixels);

	void CompressedTextureImage3DEXT(uint texture, enum target, int level,
					 enum internalformat,
					 sizei width, sizei height,
					 sizei depth, int border,
					 sizei imageSize, const void *data);
	void CompressedTextureImage2DEXT(uint texture, enum target, int level,
					 enum internalformat,
					 sizei width, sizei height,
					 int border, sizei imageSize,
					 const void *data);
	void CompressedTextureImage1DEXT(uint texture, enum target, int level,
					 enum internalformat,
					 sizei width, int border,
					 sizei imageSize, const void *data);
	void CompressedTextureSubImage3DEXT(uint texture, enum target, int level,
					    int xoffset, int yoffset,
					    int zoffset,
					    sizei width, sizei height,
					    sizei depth, enum format,
					    sizei imageSize, const void *data);
	void CompressedTextureSubImage2DEXT(uint texture, enum target, int level,
					    int xoffset, int yoffset,
					    sizei width, sizei height,
					    enum format,
					    sizei imageSize, const void *data);
	void CompressedTextureSubImage1DEXT(uint texture, enum target, int level,
					    int xoffset, sizei width,
					    enum format,
					    sizei imageSize, const void *data);

	void GetCompressedTextureImageEXT(uint texture, enum target,
					  int level, void *img);

 */
};

/// Wrapper for the EXT_direct_state_access extension
/**
 *  @glsymbols
 *  @glextref{EXT,direct_state_access}
 *
 *  @ingroup extensions
 */
class EXT_direct_state_access
 : public DSAContextEXT
 , public DSAMatrixEXT
 , public DSATextureEXT
{
public:
	OGLPLUS_EXTENSION_CLASS(EXT, direct_state_access)
};
#endif

} // namespace oglplus

#endif // include guard
