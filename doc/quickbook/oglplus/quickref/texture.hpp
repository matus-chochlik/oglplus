/*
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_texture_subtype
namespace oglplus {

template <>
struct __ObjectSubtype<__tag_Texture>
{
	typedef __TextureTarget Type;
};

//]
//[oglplus_texture_common

template <>
class __ObjCommonOps<__tag_Texture>
 : public __TextureName
{
public:
	typedef __TextureTarget Target; /*<
	Texture bind target.
	>*/

	static __TextureName Binding(__TextureTarget target); /*<
	Returns the texture currently bound to the specified [^target].
	See [glfunc GetIntegerv].
	>*/
	static void Bind(__TextureTarget target, __TextureName texture); /*<
	Binds the specified [^texture] to the specified [^target].
	See [glfunc BindTexture].
	>*/

	void Bind(__TextureTarget target) const; /*<
	Binds [^this] texture to the specified [^target].
	See [glfunc BindTexture].
	>*/

#if GL_VERSION_4_2 ||GL_ARB_shader_image_load_store
	static void BindImage(
		__ImageUnitSelector unit,
		__TextureName texture,
		GLint level,
		bool layered,
		GLint layer,
		__AccessSpecifier access,
		__ImageUnitFormat format
	); /*<
	Binds a [^level] of [^texture] to an image [^unit].
	See [glfunc BindTextureImage].
	>*/
#endif

#if GL_VERSION_4_4 || GL_ARB_multi_bind
	static void Bind(
		GLuint first,
		const __Sequence<__TextureName>& textures
	); /*<
	Sequentially binds [^textures] to texture units starting with [^first].
	See [glfunc BindTextures].
	>*/

	static void BindImage(
		GLuint first,
		const __Sequence<__TextureName>& textures
	); /*<
	Sequentially binds [^textures] to image units starting with [^first].
	See [glfunc BindImageTextures].
	>*/
#endif

	static void Active(__TextureUnitSelector index); /*<
	Specifies active texture unit for subsequent commands.
	See [glfunc ActiveTexture].
	>*/

	static GLint Active(void); /*<
	Returns the currently active texture unit.
	See [glfunc Get], [glconst ACTIVE_TEXTURE].
	>*/

	static __TextureTarget CubeMapFace(GLuint face); /*<
	Returns one of the values for cube map faces
	from the __TextureTarget enumeration. The value of [^face] must
	be between 0 and 5 with the following meaning:
	[itemized_list
	[0 = [^__TextureTarget::CubeMapPositiveX]]
	[1 = [^__TextureTarget::CubeMapNegativeX]]
	[2 = [^__TextureTarget::CubeMapPositiveY]]
	[3 = [^__TextureTarget::CubeMapNegativeY]]
	[4 = [^__TextureTarget::CubeMapPositiveZ]]
	[5 = [^__TextureTarget::CubeMapNegativeZ]]
	]
	>*/

#if GL_VERSION_4_3
	void InvalidateImage(GLsizei level); /*<
	Invalidates the specified [^level] of texture image.
	See [glfunc InvalidateTexImage].
	>*/

	void InvalidateSubImage(
		GLsizei level,
		GLint xoffs,
		GLint yoffs,
		GLint zoffs,
		GLsizei width,
		GLsizei height,
		GLsizei depth
	); /*<
	Invalidates the specified part of texture image.
	See [glfunc InvalidateTexSubImage].
	>*/
#endif

#if GL_VERSION_4_4
	template <typename GLtype>
	void ClearImage(
		GLsizei level,
		__PixelDataFormat format,
		const GLtype* data
	); /*<
	Clears the specified [^level] of texture image.
	See [glfunc ClearTexImage].
	>*/

	template <typename GLtype>
	void ClearSubImage(
		GLsizei level,
		GLint xoffs,
		GLint yoffs,
		GLint zoffs,
		GLsizei width,
		GLsizei height,
		GLsizei depth,
		__PixelDataFormat format,
		const GLtype* data
	); /*<
	Clears the specified part of texture image.
	See [glfunc ClearTexSubImage].
	>*/
#endif

#if GL_VERSION_4_3 || GL_ARB_texture_view
	void View(
		__TextureTarget target,
		__TextureName orig_texture,
		__PixelDataInternalFormat internal_format,
		GLuint min_level,
		GLuint num_levels,
		GLuint min_layer,
		GLuint num_layers
	); /*<
	References and reinteprets a subset of the data of another texture.
	See [glfunc TextureView].
	>*/
#endif
};
//]
//[oglplus_texture_1
template <>
class __ObjectOps<__tag_ExplicitSel, __tag_Texture>
 : public __ObjZeroOps<__tag_ExplicitSel, __tag_Texture>
{
public:
	struct Property
	{
		typedef __TextureCompareMode CompareMode;

		typedef __TextureFilter Filter;

		typedef __TextureMagFilter MagFilter;

		typedef __TextureMinFilter MinFilter;

		typedef __TextureSwizzleCoord SwizzleCoord;

		typedef __TextureSwizzle Swizzle;

#if GL_VERSION_3_3 || GL_ARB_texture_swizzle
		typedef __TextureSwizzleTuple SwizzleTuple;
#endif
		typedef __TextureWrapCoord WrapCoord;

		typedef __TextureWrap Wrap;

		typedef __OneOf<
			__DataType,
			__PixelDataType
		> PixDataType;
	};

#if GL_VERSION_3_0
	static
	GLsizei Width(__TextureTarget target, GLint level = 0); /*<
	Returns the width of the texture image on the specified [^level].
	See [glfunc GetTexLevelParameter], [glconst TEXTURE_WIDTH].
	>*/

	static
	GLsizei Height(__TextureTarget target, GLint level = 0); /*<
	Returns the height of the texture image on the specified [^level].
	See [glfunc GetTexLevelParameter], [glconst TEXTURE_HEIGHT].
	>*/

	static
	GLsizei Depth(__TextureTarget target, GLint level = 0); /*<
	Returns the depth of the texture image on the specified [^level].
	See [glfunc GetTexLevelParameter], [glconst TEXTURE_DEPTH].
	>*/

	static
	__PixelDataType RedType(__TextureTarget target, GLint level = 0); /*<
	Returns the data type used to store the RED component.
	See [glfunc GetTexLevelParameter], [glconst TEXTURE_RED_TYPE].
	>*/

	static
	__PixelDataType GreenType(__TextureTarget target, GLint level = 0); /*<
	Returns the data type used to store the GREEN component.
	See [glfunc GetTexLevelParameter], [glconst TEXTURE_GREEN_TYPE].
	>*/

	static
	__PixelDataType BlueType(__TextureTarget target, GLint level = 0); /*<
	Returns the data type used to store the BLUE component.
	See [glfunc GetTexLevelParameter], [glconst TEXTURE_BLUE_TYPE].
	>*/

	static
	__PixelDataType AlphaType(__TextureTarget target, GLint level = 0); /*<
	Returns the data type used to store the ALPHA component.
	See [glfunc GetTexLevelParameter], [glconst TEXTURE_ALPHA_TYPE].
	>*/

	static
	__PixelDataType DepthType(__TextureTarget target, GLint level = 0); /*<
	Returns the data type used to store the DEPTH component.
	See [glfunc GetTexLevelParameter], [glconst TEXTURE_DEPTH_TYPE].
	>*/

	static
	GLsizei RedSize(__TextureTarget target, GLint level = 0); /*<
	Returns the actual resolution of the RED component.
	See [glfunc GetTexLevelParameter], [glconst TEXTURE_RED_SIZE].
	>*/

	static
	GLsizei GreenSize(__TextureTarget target, GLint level = 0); /*<
	Returns the actual resolution of the GREEN component.
	See [glfunc GetTexLevelParameter], [glconst TEXTURE_GREEN_SIZE].
	>*/

	static
	GLsizei BlueSize(__TextureTarget target, GLint level = 0); /*<
	Returns the actual resolution of the BLUE component.
	See [glfunc GetTexLevelParameter], [glconst TEXTURE_BLUE_SIZE].
	>*/

	static
	GLsizei AlphaSize(__TextureTarget target, GLint level = 0); /*<
	Returns the actual resolution of the ALPHA component.
	See [glfunc GetTexLevelParameter], [glconst TEXTURE_ALPHA_SIZE].
	>*/

	static
	GLsizei DepthSize(__TextureTarget target, GLint level = 0); /*<
	Returns the actual resolution of the DEPTH component.
	See [glfunc GetTexLevelParameter], [glconst TEXTURE_DEPTH_SIZE].
	>*/

	static
	GLsizei StencilSize(__TextureTarget target, GLint level = 0); /*<
	Returns the actual resolution of the STENCIL component.
	See [glfunc GetTexLevelParameter], [glconst TEXTURE_STENCIL_SIZE].
	>*/

	static
	GLsizei SharedSize(__TextureTarget target, GLint level = 0); /*<
	Returns the actual resolution of all texture components.
	See [glfunc GetTexLevelParameter], [glconst TEXTURE_SHARED_SIZE].
	>*/
//]
//[oglplus_texture_2
	static
	GLsizei CompressedImageSize(__TextureTarget target, GLint level = 0); /*<
	Returns the size (in bytes) of the image array if it is compressed.
	See [glfunc GetTexLevelParameter], [glconst TEXTURE_COMPRESSED_IMAGE_SIZE].
	>*/

	static
	__PixelDataInternalFormat InternalFormat(__TextureTarget target, GLint level = 0); /*<
	Returns the internal data format of the image array.
	See [glfunc GetTexLevelParameter], [glconst TEXTURE_INTERNAL_FORMAT].
	>*/

	static void GetImage(
		__TextureTarget target,
		GLint level,
		__PixelDataFormat format,
		const __OutputData& dest
	); /*<
	Stores the image of the texture bound to
	the specified texture [^target] with the specified [^level]
	of detail in uncompressed form into the [^dest] buffer.
	See [glfunc GetTexImage].
	[note This function, unlike [^GetCompressedImage], does NOT
	automatically resize the destination buffer so that
	it can accomodate the texture data. The caller is responsible
	for keeping track or querying the type of the texture, its
	dimensions and current pixel transfer settings and resize
	the [^dest] buffer accordingly.]
	>*/
	static void GetImage(
		__TextureTarget target,
		GLint level,
		__PixelDataFormat format,
		Property::PixDataType type,
		GLsizei size,
		GLvoid* buffer
	);

	static void GetCompressedImage(
		__TextureTarget target,
		GLint level,
		const __OutputData& dest
	); /*<
	Stores the image of the texture bound to
	the specified texture [^target] with the specified [^level]
	of detail in compressed form into the [^dest] buffer.
	See [glfunc GetCompressedTexImage].
	This function automatically resizes the buffer so that
	it can accomodate the texture data.
	>*/
	static void GetCompressedImage(
		__TextureTarget target,
		GLint level,
		std::vector<GLubyte>& dest
	);
	static void GetCompressedImage(
		__TextureTarget target,
		GLint level,
		GLsizei size,
		GLubyte* buffer
	);
#endif
	static void Image3D(
		__TextureTarget target,
		GLint level,
		__PixelDataInternalFormat internal_format,
		GLsizei width,
		GLsizei height,
		GLsizei depth,
		GLint border,
		__PixelDataFormat format,
		Property::PixDataType type,
		const void* data
	); /*<
	Specifies a three dimensional texture image.
	See [glfunc TexImage3D].
	>*/

	static void Image3D(
		__TextureTarget target,
		const __images_Image& image,
		GLint level = 0,
		GLint border = 0
	);

	static void SubImage3D(
		__TextureTarget target,
		GLint level,
		GLint xoffs,
		GLint yoffs,
		GLint zoffs,
		GLsizei width,
		GLsizei height,
		GLsizei depth,
		__PixelDataFormat format,
		Property::PixDataType type,
		const void* data
	); /*<
	Specifies a three dimensional texture subimage.
	See [glfunc TexSubImage3D].
	>*/

	static void SubImage3D(
		__TextureTarget target,
		const __images_Image& image,
		GLint xoffs,
		GLint yoffs,
		GLint zoffs,
		GLint level = 0
	);

	static void Image2D(
		__TextureTarget target,
		GLint level,
		__PixelDataInternalFormat internal_format,
		GLsizei width,
		GLsizei height,
		GLint border,
		__PixelDataFormat format,
		Property::PixDataType type,
		const void* data
	); /*<
	Specifies a two dimensional texture image.
	See [glfunc TexImage2D].
	>*/

	static void Image2D(
		__TextureTarget target,
		const __images_Image& image,
		GLint level = 0,
		GLint border = 0
	);

	static void ImageCM(
		GLuint face,
		GLint level,
		__PixelDataInternalFormat internal_format,
		GLsizei width,
		GLsizei height,
		GLint border,
		__PixelDataFormat format,
		Property::PixDataType type,
		const void* data
	); /*<
	Specifies the image of the selected cube-map face.
	See [glfunc TexImage2D].
	>*/

	static void ImageCM(
		GLuint face,
		const __images_Image& image,
		GLint level = 0,
		GLint border = 0
	);

	static void SubImage2D(
		__TextureTarget target,
		GLint level,
		GLint xoffs,
		GLint yoffs,
		GLsizei width,
		GLsizei height,
		__PixelDataFormat format,
		Property::PixDataType type,
		const void* data
	); /*<
	Specifies a two dimensional texture subimage.
	See [glfunc TexSubImage2D].
	>*/

	static void SubImage2D(
		__TextureTarget target,
		const __images_Image& image,
		GLint xoffs,
		GLint yoffs,
		GLint level = 0
	);

#if GL_VERSION_3_0
	static void Image1D(
		__TextureTarget target,
		GLint level,
		__PixelDataInternalFormat internal_format,
		GLsizei width,
		GLint border,
		__PixelDataFormat format,
		Property::PixDataType type,
		const void* data
	); /*<
	Specifies a one dimensional texture image.
	See [glfunc TexImage1D].
	>*/

	static void Image1D(
		__TextureTarget target,
		const __images_Image& image,
		GLint level = 0,
		GLint border = 0
	);

	static void SubImage1D(
		__TextureTarget target,
		GLint level,
		GLint xoffs,
		GLsizei width,
		__PixelDataFormat format,
		Property::PixDataType type,
		const void* data
	);  /*<
	Specifies a one dimensional texture subimage.
	See [glfunc TexSubImage1D].
	>*/

	static void SubImage1D(
		__TextureTarget target,
		const __images_Image& image,
		GLint xoffs,
		GLint level = 0
	);
#endif

	static void Image(
		__TextureTarget target,
		const __images_Image& image,
		GLint level = 0,
		GLint border = 0
	); /*<
	Specifies one, two or three dimensional texture image.
	>*/

	static void Image(
		__TextureTarget target,
		const __images_ImageSpec& image_spec,
		GLint level = 0,
		GLint border = 0
	);
//]
//[oglplus_texture_3

	static void CopyImage2D(
		__TextureTarget target,
		GLint level,
		__PixelDataInternalFormat internal_format,
		GLint x,
		GLint y,
		GLsizei width,
		GLsizei height,
		GLint border
	); /*<
	Copies a two dimensional texture image from the current framebuffer.
	See [glfunc CopyTexImage2D].
	>*/

#if GL_VERSION_3_0
	static void CopyImage1D(
		__TextureTarget target,
		GLint level,
		__PixelDataInternalFormat internal_format,
		GLint x,
		GLint y,
		GLsizei width,
		GLint border
	); /*<
	Copies a one dimensional texture image from the current framebuffer.
	See [glfunc CopyTexImage1D].
	>*/
#endif

	static void CopySubImage3D(
		__TextureTarget target,
		GLint level,
		GLint xoffs,
		GLint yoffs,
		GLint zoffs,
		GLint x,
		GLint y,
		GLsizei width,
		GLsizei height
	); /*<
	Copies a three dimensional texture subimage from the current framebuffer.
	See [glfunc CopyTexSubImage3D].
	>*/

	static void CopySubImage2D(
		__TextureTarget target,
		GLint level,
		GLint xoffs,
		GLint yoffs,
		GLint x,
		GLint y,
		GLsizei width,
		GLsizei height
	); /*<
	Copies a two dimensional texture subimage from the current framebuffer.
	See [glfunc CopyTexSubImage2D].
	>*/

#if GL_VERSION_3_0
	static void CopySubImage1D(
		__TextureTarget target,
		GLint level,
		GLint xoffs,
		GLint x,
		GLint y,
		GLsizei width
	); /*<
	Copies a one dimensional texture subimage from the current framebuffer.
	See [glfunc CopyTexSubImage2D].
	>*/
#endif

	static void CompressedImage3D(
		__TextureTarget target,
		GLint level,
		__PixelDataInternalFormat internal_format,
		GLsizei width,
		GLsizei height,
		GLsizei depth,
		GLint border,
		GLsizei image_size,
		const void* data
	); /*<
	Specifies a three dimensional compressed texture image.
	See [glfunc CompressedTexImage3D].
	>*/

	static void CompressedImage2D(
		__TextureTarget target,
		GLint level,
		__PixelDataInternalFormat internal_format,
		GLsizei width,
		GLsizei height,
		GLint border,
		GLsizei image_size,
		const void* data
	); /*<
	Specifies a two dimensional compressed texture image.
	See [glfunc CompressedTexImage2D].
	>*/

#if GL_VERSION_3_0
	static void CompressedImage1D(
		__TextureTarget target,
		GLint level,
		__PixelDataInternalFormat internal_format,
		GLsizei width,
		GLint border,
		GLsizei image_size,
		const void* data
	); /*<
	Specifies a one dimensional compressed texture image.
	See [glfunc CompressedTexImage1D].
	>*/
#endif

	static void CompressedSubImage3D(
		__TextureTarget target,
		GLint level,
		GLint xoffs,
		GLint yoffs,
		GLint zoffs,
		GLsizei width,
		GLsizei height,
		GLsizei depth,
		__PixelDataFormat format,
		GLsizei image_size,
		const void* data
	); /*<
	Specifies a three dimensional compressed texture subimage.
	See [glfunc CompressedTexSubImage3D].
	>*/

	static void CompressedSubImage2D(
		__TextureTarget target,
		GLint level,
		GLint xoffs,
		GLint yoffs,
		GLsizei width,
		GLsizei height,
		__PixelDataFormat format,
		GLsizei image_size,
		const void* data
	); /*<
	Specifies a two dimensional compressed texture subimage.
	See [glfunc CompressedTexSubImage2D].
	>*/

#if GL_VERSION_3_0
	static void CompressedSubImage1D(
		__TextureTarget target,
		GLint level,
		GLint xoffs,
		GLsizei width,
		__PixelDataFormat format,
		GLsizei image_size,
		const void* data
	); /*<
	Specifies a one dimensional compressed texture subimage.
	See [glfunc CompressedTexSubImage1D].
	>*/
#endif
//]
//[oglplus_texture_4

#if GL_VERSION_3_2 || GL_ARB_texture_multisample
	static void Image3DMultisample(
		__TextureTarget target,
		GLsizei samples,
		__PixelDataInternalFormat internal_format,
		GLsizei width,
		GLsizei height,
		GLsizei depth,
		bool fixed_sample_locations
	); /*<
	Sets-up a three dimensional multisample texture.
	See [glfunc TexImage3DMultisample].
	>*/

	static void Image2DMultisample(
		__TextureTarget target,
		GLsizei samples,
		__PixelDataInternalFormat internal_format,
		GLsizei width,
		GLsizei height,
		bool fixed_sample_locations
	); /*<
	Sets-up a two dimensional multisample texture.
	See [glfunc TexImage3DMultisample].
	>*/

#endif

#if GL_VERSION_3_1
	static void Buffer(
		__TextureTarget target,
		__PixelDataInternalFormat internal_format,
		__BufferName buffer
	); /*<
	Assigns a buffer storing the texel data to the texture.
	See [glfunc TexBuffer].
	>*/
#endif

#if GL_VERSION_4_3
	static void BufferRange(
		__TextureTarget target,
		__PixelDataInternalFormat internal_format,
		__BufferName buffer,
		GLintptr offset,
		GLsizeiptr size
	); /*<
	Assigns a buffer range storing the texel data to the texture.
	See [glfunc TexBufferRange].
	>*/
#endif

#if GL_VERSION_4_2 || GL_ARB_texture_storage
	static void Storage3D(
		__TextureTarget target,
		GLsizei levels,
		__PixelDataInternalFormat internal_format,
		GLsizei width,
		GLsizei height,
		GLsizei depth
	); /*<
	Specifies all levels of 3D texture at the same time.
	See [glfunc TexStorage3D].
	>*/

	static void Storage2D(
		__TextureTarget target,
		GLsizei levels,
		__PixelDataInternalFormat internal_format,
		GLsizei width,
		GLsizei height
	); /*<
	Specifies all levels of 2D texture at the same time.
	See [glfunc TexStorage2D].
	>*/

	static void Storage1D(
		__TextureTarget target,
		GLsizei levels,
		__PixelDataInternalFormat internal_format,
		GLsizei width
	); /*<
	Specifies all levels of 1D texture at the same time.
	See [glfunc TexStorage1D].
	>*/
#endif
	static GLuint BaseLevel(__TextureTarget target); /*<
	Returns the texture base level.
	See [glfunc GetTexParameter], [glconst TEXTURE_BASE_LEVEL].
	>*/

	static void BaseLevel(__TextureTarget target, GLuint level); /*<
	Sets the texture base level.
	See [glfunc TexParameter], [glconst TEXTURE_BASE_LEVEL].
	>*/


};

// TODO

//]
//[oglplus_texture_def
typedef ObjectOps<__tag_ExplicitSel, __tag_Texture>
	TextureOps;

typedef __Object<TextureOps> Texture;

typedef __ObjectZero<__ObjZeroOps<__tag_ExplicitSel, __tag_Texture>>
	DefaultTexture;

} // namespace oglplus
//]

