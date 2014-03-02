/**
 *  @file advanced/cloud_trace/textures.cpp
 *  @brief Implementation of texture classes
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2008-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include "textures.hpp"

#include <oglplus/images/cloud.hpp>
#include <oglplus/images/image_spec.hpp>

#include <fstream>
#include <string>

namespace oglplus {
namespace cloud_trace {

CloudTexture::CloudTexture(RenderData& data, ResourceAllocator& alloc)
 : tex_unit(alloc.GetNextTexUnit())
{
	Texture::Active(tex_unit);

	const std::string& cip = data.cloud_image_path;

	if(cip.empty() || data.dump_cloud_image)
	{
		std::ofstream output;
		output.exceptions(std::ifstream::failbit|std::ifstream::badbit);

		if(data.dump_cloud_image)
		{
			if(cip.empty())
			{
				std::string message;
				message.append("No output image file specified");
				throw std::runtime_error(message);
			}
			else try { output.open(cip.c_str()); }
			catch(std::ifstream::failure& f)
			{
				std::string message;
				message.append("Opening image file '");
				message.append(cip);
				message.append("' failed with: ");
				message.append(f.what());
				throw std::runtime_error(message);
			}
		}

		auto image = images::Cloud(
				data.cloud_res,
				data.cloud_res,
				data.cloud_res,
				Vec3f(),
				0.45f,
				0.333f,
				0.55f,
				0.005f
		);

		if(data.dump_cloud_image)
		{
			if(!cip.empty()) try
			{
				output.write(
					(const char*)
					image.RawData(),
					image.DataSize()
				);
			}
			catch(std::ifstream::failure& f)
			{
				std::string message;
				message.append("Saving image file '");
				message.append(cip);
				message.append("' failed with: ");
				message.append(f.what());
				throw std::runtime_error(message);
			}
		}

		*this	<< TextureTarget::_3D
			<< TextureWrap::ClampToBorder
			<< TextureFilter::Linear
			<< image;
	}
	else if(cip.rfind(".r8") ==  cip.size()-3)
	{
		std::ifstream input;
		input.exceptions(std::ifstream::failbit|std::ifstream::badbit);
		try
		{
			input.open(cip.c_str());
			std::vector<GLubyte> image(
				data.cloud_res*
				data.cloud_res*
				data.cloud_res
			);
			input.read((char*)image.data(), image.size());
			if(input.gcount() < std::streamsize(image.size()))
			{
				std::string message;
				message.append("Not enough data in file '");
				message.append(cip);
				message.append("' for specified image size");
				throw std::runtime_error(message);
			}

			*this	<< TextureTarget::_3D
				<< TextureWrap::ClampToBorder
				<< TextureFilter::Linear
				<< images::ImageSpec(
					data.cloud_res,
					data.cloud_res,
					data.cloud_res,
					PixelDataFormat::Red,
					PixelDataInternalFormat::Red,
					image.data()
				);
		}
		catch(std::ifstream::failure& f)
		{
			std::string message;
			message.append("Loading image file '");
			message.append(cip);
			message.append("' failed with: ");
			message.append(f.what());
			throw std::runtime_error(message);
		}
	}
	else
	{
		std::string message;
		message.append("Unsupported image file format '");
		message.append(cip);
		message.append("'");
		throw std::runtime_error(message);
	}
}

} // namespace cloud_trace
} // namespace oglplus
