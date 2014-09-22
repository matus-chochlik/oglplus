/*
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_texture_unit_selector
namespace oglplus {

class TextureUnitSelector
 : public __LimitedCount
{
public:
	TextureUnitSelector(GLuint number); /*<
	Throws __LimitError if [^number] is greater than
	the implementation-dependent maximum number of texture units.
	See [glconst MAX_COMBINED_TEXTURE_IMAGE_UNITS].
	>*/
};

#if GL_VERSION_4_2 || GL_ARB_shader_image_load_store
class ImageUnitSelector
 : public __LimitedCount
{
public:
	ImageUnitSelector(GLuint number); /*<
	Throws __LimitError if [^number] is greater than
	the implementation-dependent maximum number of image units.
	See [glconst MAX_IMAGE_UNITS].
	>*/
};
#endif

} // namespace oglplus
//]

