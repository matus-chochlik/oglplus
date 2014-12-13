/*
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
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

	static __TextureName Binding(Target target); /*<
	Returns the texture currently bound to the specified [^target].
	See [glfunc GetIntegerv].
	>*/
	static void Bind(Target target, __TextureName texture); /*<
	Binds the specified [^texture] to the specified [^target].
	See [glfunc BindTexture].
	>*/

	void Bind(Target target) const; /*<
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
		Target target,
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

