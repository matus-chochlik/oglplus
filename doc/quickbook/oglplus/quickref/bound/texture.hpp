
/*
 *  Automatically generated file, do not edit manually!
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
//[oglplus_object_BoundObjOps_Texture

template <>
class __BoundObjOps<__tag_Texture>
{
private:
	typedef typename __ObjectOps_Explicit_Texture<__tag_ExplicitSel, __tag_Texture> ExplicitOps;
public:
	typedef typename ExplicitOps::Target Target;

	Target target;

	BoundObjOps(void);

	BoundObjOps(Target init_tgt);
	GLint GetIntParam(
		GLenum query
	) const;

	GLfloat GetFloatParam(
		GLenum query
	) const;

	GLint GetIntParam(
		GLint level,
		GLenum query
	) const;

	GLfloat GetFloatParam(
		GLint level,
		GLenum query
	) const;

	SizeType Width(
		GLint level = 0
	) const;

	SizeType Height(
		GLint level = 0
	) const;

	SizeType Depth(
		GLint level = 0
	) const;

	PixelDataType RedType(
		GLint level = 0
	) const;

	PixelDataType GreenType(
		GLint level = 0
	) const;

	PixelDataType BlueType(
		GLint level = 0
	) const;

	PixelDataType AlphaType(
		GLint level = 0
	) const;

	PixelDataType DepthType(
		GLint level = 0
	) const;

	SizeType RedSize(
		GLint level = 0
	) const;

	SizeType GreenSize(
		GLint level = 0
	) const;

	SizeType BlueSize(
		GLint level = 0
	) const;

	SizeType AlphaSize(
		GLint level = 0
	) const;

	SizeType DepthSize(
		GLint level = 0
	) const;

	SizeType StencilSize(
		GLint level = 0
	) const;

	SizeType SharedSize(
		GLint level = 0
	) const;

	SizeType CompressedImageSize(
		GLint level = 0
	) const;

	PixelDataInternalFormat InternalFormat(
		GLint level = 0
	) const;

	const BoundObjOps& GetImage(
		GLint level,
		PixelDataFormat format,
		const OutputData & dest
	) const;

	const BoundObjOps& GetImage(
		GLint level,
		PixelDataFormat format,
		ExplicitOps::Property::PixDataType type,
		SizeType size,
		GLvoid * buffer
	) const;

	const BoundObjOps& GetCompressedImage(
		GLint level,
		const OutputData & dest
	) const;

	const BoundObjOps& GetCompressedImage(
		GLint level,
		SizeType size,
		GLubyte * buffer
	) const;

	const BoundObjOps& GetCompressedImage(
		GLint level,
		std::vector< GLubyte > & dest
	) const;

	const BoundObjOps& Image3D(
		GLint level,
		PixelDataInternalFormat internal_format,
		SizeType width,
		SizeType height,
		SizeType depth,
		GLint border,
		PixelDataFormat format,
		ExplicitOps::Property::PixDataType type,
		const void * data
	) const;

	const BoundObjOps& Image3D(
		const images::Image & image,
		GLint level = 0,
		GLint border = 0
	) const;

	const BoundObjOps& SubImage3D(
		GLint level,
		GLint xoffs,
		GLint yoffs,
		GLint zoffs,
		SizeType width,
		SizeType height,
		SizeType depth,
		PixelDataFormat format,
		ExplicitOps::Property::PixDataType type,
		const void * data
	) const;

	const BoundObjOps& SubImage3D(
		const images::Image & image,
		GLint xoffs,
		GLint yoffs,
		GLint zoffs,
		GLint level = 0
	) const;

	const BoundObjOps& Image2D(
		GLint level,
		PixelDataInternalFormat internal_format,
		SizeType width,
		SizeType height,
		GLint border,
		PixelDataFormat format,
		ExplicitOps::Property::PixDataType type,
		const void * data
	) const;

	const BoundObjOps& Image2D(
		const images::Image & image,
		GLint level = 0,
		GLint border = 0
	) const;

	const BoundObjOps& SubImage2D(
		GLint level,
		GLint xoffs,
		GLint yoffs,
		SizeType width,
		SizeType height,
		PixelDataFormat format,
		ExplicitOps::Property::PixDataType type,
		const void * data
	) const;

	const BoundObjOps& SubImage2D(
		const images::Image & image,
		GLint xoffs,
		GLint yoffs,
		GLint level = 0
	) const;

	const BoundObjOps& Image1D(
		GLint level,
		PixelDataInternalFormat internal_format,
		SizeType width,
		GLint border,
		PixelDataFormat format,
		ExplicitOps::Property::PixDataType type,
		const void * data
	) const;

	const BoundObjOps& Image1D(
		const images::Image & image,
		GLint level = 0,
		GLint border = 0
	) const;

	const BoundObjOps& SubImage1D(
		GLint level,
		GLint xoffs,
		SizeType width,
		PixelDataFormat format,
		ExplicitOps::Property::PixDataType type,
		const void * data
	) const;

	const BoundObjOps& SubImage1D(
		const images::Image & image,
		GLint xoffs,
		GLint level = 0
	) const;

	const BoundObjOps& Image(
		const images::Image & image,
		GLint level = 0,
		GLint border = 0
	) const;

	const BoundObjOps& Image(
		const images::ImageSpec & image_spec,
		GLint level = 0,
		GLint border = 0
	) const;

	const BoundObjOps& CopyImage2D(
		GLint level,
		PixelDataInternalFormat internal_format,
		GLint x,
		GLint y,
		SizeType width,
		SizeType height,
		GLint border
	) const;

	const BoundObjOps& CopyImage1D(
		GLint level,
		PixelDataInternalFormat internal_format,
		GLint x,
		GLint y,
		SizeType width,
		GLint border
	) const;

	const BoundObjOps& CopySubImage3D(
		GLint level,
		GLint xoffs,
		GLint yoffs,
		GLint zoffs,
		GLint x,
		GLint y,
		SizeType width,
		SizeType height
	) const;

	const BoundObjOps& CopySubImage2D(
		GLint level,
		GLint xoffs,
		GLint yoffs,
		GLint x,
		GLint y,
		SizeType width,
		SizeType height
	) const;

	const BoundObjOps& CopySubImage1D(
		GLint level,
		GLint xoffs,
		GLint x,
		GLint y,
		SizeType width
	) const;

	const BoundObjOps& CompressedImage3D(
		GLint level,
		PixelDataInternalFormat internal_format,
		SizeType width,
		SizeType height,
		SizeType depth,
		GLint border,
		SizeType image_size,
		const void * data
	) const;

	const BoundObjOps& CompressedImage2D(
		GLint level,
		PixelDataInternalFormat internal_format,
		SizeType width,
		SizeType height,
		GLint border,
		SizeType image_size,
		const void * data
	) const;

	const BoundObjOps& CompressedImage1D(
		GLint level,
		PixelDataInternalFormat internal_format,
		SizeType width,
		GLint border,
		SizeType image_size,
		const void * data
	) const;

	const BoundObjOps& CompressedSubImage3D(
		GLint level,
		GLint xoffs,
		GLint yoffs,
		GLint zoffs,
		SizeType width,
		SizeType height,
		SizeType depth,
		PixelDataFormat format,
		SizeType image_size,
		const void * data
	) const;

	const BoundObjOps& CompressedSubImage2D(
		GLint level,
		GLint xoffs,
		GLint yoffs,
		SizeType width,
		SizeType height,
		PixelDataFormat format,
		SizeType image_size,
		const void * data
	) const;

	const BoundObjOps& CompressedSubImage1D(
		GLint level,
		GLint xoffs,
		SizeType width,
		PixelDataFormat format,
		SizeType image_size,
		const void * data
	) const;

#if GL_VERSION_3_2 || GL_ARB_texture_multisample
	const BoundObjOps& Image3DMultisample(
		SizeType samples,
		PixelDataInternalFormat internal_format,
		SizeType width,
		SizeType height,
		SizeType depth,
		Boolean fixed_sample_locations
	) const;
#endif

#if GL_VERSION_3_2 || GL_ARB_texture_multisample
	const BoundObjOps& Image2DMultisample(
		SizeType samples,
		PixelDataInternalFormat internal_format,
		SizeType width,
		SizeType height,
		Boolean fixed_sample_locations
	) const;
#endif

#if GL_VERSION_3_1
	const BoundObjOps& Buffer(
		PixelDataInternalFormat internal_format,
		BufferName buffer
	) const;
#endif

#if GL_VERSION_4_3
	const BoundObjOps& BufferRange(
		PixelDataInternalFormat internal_format,
		BufferName buffer,
		GLintptr offset,
		BigSizeType size
	) const;
#endif

#if GL_VERSION_4_2 || GL_ARB_texture_storage
	const BoundObjOps& Storage1D(
		SizeType levels,
		PixelDataInternalFormat internal_format,
		SizeType width
	) const;
#endif

#if GL_VERSION_4_2 || GL_ARB_texture_storage
	const BoundObjOps& Storage2D(
		SizeType levels,
		PixelDataInternalFormat internal_format,
		SizeType width,
		SizeType height
	) const;
#endif

#if GL_VERSION_4_2 || GL_ARB_texture_storage
	const BoundObjOps& Storage3D(
		SizeType levels,
		PixelDataInternalFormat internal_format,
		SizeType width,
		SizeType height,
		SizeType depth
	) const;
#endif

	GLuint BaseLevel(void) const;

	const BoundObjOps& BaseLevel(
		GLint level
	) const;

	Vector< GLfloat, 4 > BorderColor(
		TypeTag< GLfloat > 
	) const;

	const BoundObjOps& BorderColor(
		Vector< GLfloat, 4 > color
	) const;

	Vector< GLint, 4 > BorderColor(
		TypeTag< GLint > 
	) const;

	const BoundObjOps& BorderColor(
		Vector< GLint, 4 > color
	) const;

	Vector< GLuint, 4 > BorderColor(
		TypeTag< GLuint > 
	) const;

	const BoundObjOps& BorderColor(
		Vector< GLuint, 4 > color
	) const;

	TextureCompareMode CompareMode(void) const;

	const BoundObjOps& CompareMode(
		TextureCompareMode mode
	) const;

	CompareFunction CompareFunc(void) const;

	const BoundObjOps& CompareFunc(
		CompareFunction func
	) const;

	GLfloat LODBias(void) const;

	const BoundObjOps& LODBias(
		GLfloat value
	) const;

	const BoundObjOps& Filter(
		TextureFilter filter
	) const;

	TextureMagFilter MagFilter(void) const;

	const BoundObjOps& MagFilter(
		TextureMagFilter filter
	) const;

	TextureMinFilter MinFilter(void) const;

	const BoundObjOps& MinFilter(
		TextureMinFilter filter
	) const;

	GLfloat MinLOD(void) const;

	const BoundObjOps& MinLOD(
		GLfloat value
	) const;

	GLfloat MaxLOD(void) const;

	const BoundObjOps& MaxLOD(
		GLfloat value
	) const;

	GLint MaxLevel(void) const;

	const BoundObjOps& MaxLevel(
		GLint value
	) const;

	GLfloat MaxAnisotropy(void) const;

	GLfloat Anisotropy(void) const;

	const BoundObjOps& Anisotropy(
		GLfloat value
	) const;

#if GL_VERSION_3_3 || GL_ARB_texture_swizzle
	TextureSwizzle Swizzle(
		TextureSwizzleCoord coord
	) const;
#endif

#if GL_VERSION_3_3 || GL_ARB_texture_swizzle
	const BoundObjOps& Swizzle(
		TextureSwizzleCoord coord,
		TextureSwizzle mode
	) const;
#endif

#if GL_VERSION_3_3 || GL_ARB_texture_swizzle
	TextureSwizzle SwizzleR(void) const;
#endif

#if GL_VERSION_3_3 || GL_ARB_texture_swizzle
	const BoundObjOps& SwizzleR(
		TextureSwizzle mode
	) const;
#endif

#if GL_VERSION_3_3 || GL_ARB_texture_swizzle
	TextureSwizzle SwizzleG(void) const;
#endif

#if GL_VERSION_3_3 || GL_ARB_texture_swizzle
	const BoundObjOps& SwizzleG(
		TextureSwizzle mode
	) const;
#endif

#if GL_VERSION_3_3 || GL_ARB_texture_swizzle
	TextureSwizzle SwizzleB(void) const;
#endif

#if GL_VERSION_3_3 || GL_ARB_texture_swizzle
	const BoundObjOps& SwizzleB(
		TextureSwizzle mode
	) const;
#endif

#if GL_VERSION_3_3 || GL_ARB_texture_swizzle
	TextureSwizzle SwizzleA(void) const;
#endif

#if GL_VERSION_3_3 || GL_ARB_texture_swizzle
	const BoundObjOps& SwizzleA(
		TextureSwizzle mode
	) const;
#endif

#if GL_VERSION_3_3 || GL_ARB_texture_swizzle
	TextureSwizzleTuple SwizzleRGBA(void) const;
#endif

#if GL_VERSION_3_3 || GL_ARB_texture_swizzle
	const BoundObjOps& SwizzleRGBA(
		TextureSwizzle mode
	) const;
#endif

#if GL_VERSION_3_3 || GL_ARB_texture_swizzle
	const BoundObjOps& SwizzleRGBA(
		TextureSwizzle mode_r,
		TextureSwizzle mode_g,
		TextureSwizzle mode_b,
		TextureSwizzle mode_a
	) const;
#endif

#if GL_VERSION_3_3 || GL_ARB_texture_swizzle
	const BoundObjOps& SwizzleRGBA(
		const TextureSwizzleTuple & modes
	) const;
#endif

	TextureWrap Wrap(
		TextureWrapCoord coord
	) const;

	const BoundObjOps& Wrap(
		TextureWrapCoord coord,
		TextureWrap mode
	) const;

	TextureWrap WrapS(void) const;

	const BoundObjOps& WrapS(
		TextureWrap mode
	) const;

	TextureWrap WrapT(void) const;

	const BoundObjOps& WrapT(
		TextureWrap mode
	) const;

	TextureWrap WrapR(void) const;

	const BoundObjOps& WrapR(
		TextureWrap mode
	) const;

#if GL_VERSION_4_3
	PixelDataFormat DepthStencilMode(void) const;
#endif

#if GL_VERSION_4_3
	const BoundObjOps& DepthStencilMode(
		PixelDataFormat mode
	) const;
#endif

#if GL_ARB_seamless_cubemap_per_texture
	Boolean Seamless(void) const;
#endif

#if GL_ARB_seamless_cubemap_per_texture
	const BoundObjOps& Seamless(
		Boolean enable
	) const;
#endif

	const BoundObjOps& GenerateMipmap(void) const;


};
//]
