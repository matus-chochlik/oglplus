/**
 *  @file oglplus/ext/ARB_bindless_texture/texture_handle.hpp
 *  @brief Texture handle wrapper.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXTURE_HANDLE_1309262134_HPP
#define OGLPLUS_TEXTURE_HANDLE_1309262134_HPP

#include <oglplus/fwd.hpp>
#include <oglplus/error.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/pixel_data.hpp>
#include <oglplus/access_specifier.hpp>

namespace oglplus {

#if OGLPLUS_DOCUMENTATION_ONLY || GL_ARB_bindless_texture

/// A handle for a bindless texture
class TextureHandleARB
 : public FriendOf<TextureOps>
 , public FriendOf<SamplerOps>
{
private:
	GLuint64 _handle;

	friend class FriendOf<TextureHandleARB>;

	template <typename ObjectOps>
	static GLuint _nameof(const ObjectOps& obj)
	{
		return FriendOf<ObjectOps>::GetName(obj);
	}
public:
	/// Construction from a texture
	TextureHandleARB(const TextureOps& texture)
	 : _handle(OGLPLUS_GLFUNC(GetTextureHandleARB)(_nameof(texture)))
	{
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GetTextureHandleARB));
	}

	/// Construction from a texture and a sampler
	TextureHandleARB(const TextureOps& texture, const SamplerOps& sampler)
	 : _handle(OGLPLUS_GLFUNC(GetTextureSamplerHandleARB)(
		_nameof(texture),
		_nameof(sampler)
	))
	{
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GetTextureSamplerHandleARB));
	}

	/// Make the texture resident
	void MakeResident(void)
	{
		OGLPLUS_GLFUNC(MakeTextureHandleResidentARB)(_handle);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(MakeTextureHandleResidentARB));
	}

	/// Make the texture non-resident
	void MakeNonResident(void)
	{
		OGLPLUS_GLFUNC(MakeTextureHandleNonResidentARB)(_handle);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(MakeTextureHandleNonResidentARB));
	}

	/// Make the texture non-resident
	bool IsResident(void) const
	{
		GLboolean result =
			OGLPLUS_GLFUNC(IsTextureHandleResidentARB)(_handle);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(IsTextureHandleResidentARB));
		return result == GL_TRUE;
	}
};

template <>
class FriendOf<TextureHandleARB>
{
protected:
	static GLuint64 GetHandle(const TextureHandleARB& th)
	OGLPLUS_NOEXCEPT(true)
	{
		return th._handle;
	}
};

/// A handle for a bindless texture image
class ImageHandleARB
 : public FriendOf<TextureOps>
{
private:
	GLuint64 _handle;

	friend class FriendOf<ImageHandleARB>;

	template <typename ObjectOps>
	static GLuint _nameof(const ObjectOps& obj)
	{
		return FriendOf<ObjectOps>::GetName(obj);
	}
public:
	/// Construction from a texture and additional parameters
	ImageHandleARB(
		const TextureOps& texture,
		GLint level,
		bool layered,
		GLint layer,
		ImageUnitFormat format
	): _handle(OGLPLUS_GLFUNC(GetImageHandleARB)(
		_nameof(texture),
		level,
		layered?GL_TRUE:GL_FALSE,
		layer,
		GLenum(format)
	))
	{
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GetImageHandleARB));
	}

	/// Make the image resident
	void MakeResident(AccessSpecifier access)
	{
		OGLPLUS_GLFUNC(MakeImageHandleResidentARB)(
			_handle,
			GLenum(access)
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(MakeImageHandleResidentARB));
	}

	/// Make the image non-resident
	void MakeNonResident(void)
	{
		OGLPLUS_GLFUNC(MakeImageHandleNonResidentARB)(_handle);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(MakeImageHandleNonResidentARB));
	}

	/// Make the image non-resident
	bool IsResident(void) const
	{
		GLboolean result =
			OGLPLUS_GLFUNC(IsImageHandleResidentARB)(_handle);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(IsImageHandleResidentARB));
		return result == GL_TRUE;
	}
};

template <>
class FriendOf<ImageHandleARB>
{
protected:
	static GLuint64 GetHandle(const ImageHandleARB& ih)
	OGLPLUS_NOEXCEPT(true)
	{
		return ih._handle;
	}
};

#endif // GL_ARB_bindless_texture

} // namespace oglplus

#endif // include guard
