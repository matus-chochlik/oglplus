/**
 *  @file oglplus/texgen/texture_node.ipp
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/config/basic.hpp>
#include <oglplus/texgen/data_type.hpp>
#include <oglplus/uniform.hpp>
#include <oglplus/program.hpp>
#include <cassert>

namespace oglplus {
namespace texgen {

OGLPLUS_LIB_FUNC
TextureOutputSlot::
TextureOutputSlot(
	Node& parent,
	Texture&& texture,
	TextureTarget target,
	PixelDataFormat format
): BaseOutputSlot(parent)
 , _coord(parent, "Coordinate")
 , _texture(std::move(texture))
 , _target(target)
 , _format(format)
{ }

OGLPLUS_LIB_FUNC
const char*
TextureOutputSlot::
TypeName(void)
{
	return "Texture";
}

OGLPLUS_LIB_FUNC
SlotDataType
TextureOutputSlot::
ValueType(void)
{
	switch(_format)
	{
#ifdef GL_RED
		case PixelDataFormat::Red:
			return SlotDataType::Float;
#endif
#ifdef GL_GREEN
		case PixelDataFormat::Green:
			return SlotDataType::Float;
#endif
#ifdef GL_BLUE
		case PixelDataFormat::Blue:
			return SlotDataType::Float;
#endif
#ifdef GL_DEPTH_COMPONENT
		case PixelDataFormat::DepthComponent:
			return SlotDataType::Float;
#endif

#ifdef GL_RED_INTEGER
		case PixelDataFormat::RedInteger:
			return SlotDataType::Int;
#endif
#ifdef GL_GREEN_INTEGER
		case PixelDataFormat::GreenInteger:
			return SlotDataType::Int;
#endif
#ifdef GL_BLUE_INTEGER
		case PixelDataFormat::BlueInteger:
			return SlotDataType::Int;
#endif
#ifdef GL_STENCIL_INDEX
		case PixelDataFormat::StencilIndex:
			return SlotDataType::Int;
#endif

#ifdef GL_RG
		case PixelDataFormat::RG:
			return SlotDataType::FloatVec2;
#endif

#ifdef GL_RG_INTEGER
		case PixelDataFormat::RGInteger:
			return SlotDataType::IntVec2;
#endif

#ifdef GL_RGB
		case PixelDataFormat::RGB:
			return SlotDataType::FloatVec3;
#endif
#ifdef GL_BGR
		case PixelDataFormat::BGR:
			return SlotDataType::FloatVec3;
#endif

#ifdef GL_RGB_INTEGER
		case PixelDataFormat::RGBInteger:
			return SlotDataType::IntVec3;
#endif
#ifdef GL_BGR_INTEGER
		case PixelDataFormat::BGRInteger:
			return SlotDataType::IntVec3;
#endif

#ifdef GL_RGBA
		case PixelDataFormat::RGBA:
			return SlotDataType::FloatVec4;
#endif
#ifdef GL_BGRA
		case PixelDataFormat::BGRA:
			return SlotDataType::FloatVec4;
#endif

#ifdef GL_RGBA_INTEGER
		case PixelDataFormat::RGBAInteger:
			return SlotDataType::IntVec4;
#endif
#ifdef GL_BGRA_INTEGER
		case PixelDataFormat::BGRAInteger:
			return SlotDataType::IntVec4;
#endif

		default:;
	}
	return SlotDataType::FloatVec4;
}

OGLPLUS_LIB_FUNC
std::ostream&
TextureOutputSlot::
Definitions(std::ostream& result, unsigned version)
{
	_coord.Definitions(result, version);

	result << "uniform ";
	if(_target == TextureTarget::_2D)
	{
		result << "sampler2D ";
	}
	else
	{
		OGLPLUS_ABORT("Unsuported texture target in texgen node");
	}

	AppendId(result);
	result << "s;\n";

	result << DataTypeName(ValueType());
	result << " ";
	AppendId(result);
	result << "(vec3 o){\n\treturn ";

	if(_target == TextureTarget::_2D)
	{
		static SlotDataType v2 = SlotDataType::FloatVec2;

		result << "texture2D(\n\t\t";
		AppendId(result);
		result << "s,\n\t\t";
		ConversionPrefix(result, _coord.ValueType(), v2);
		_coord.Expression(result, version);
		result << "(o)";
		ConversionSuffix(result, _coord.ValueType(), v2,0,0,0,0);
		result << "\n\t";
		result << ")";

		switch(_format)
		{
#ifdef GL_RED
		case PixelDataFormat::Red:
			result << ".r"; break;
#endif
#ifdef GL_RED_INTEGER
		case PixelDataFormat::RedInteger:
			result << ".r"; break;
#endif
#ifdef GL_DEPTH_COMPONENT
		case PixelDataFormat::DepthComponent:
			result << ".r"; break;
#endif
#ifdef GL_STENCIL_INDEX
		case PixelDataFormat::StencilIndex:
			result << ".r"; break;
#endif

#ifdef GL_GREEN
		case PixelDataFormat::Green:
			result << ".g"; break;
#endif
#ifdef GL_GREEN_INTEGER
		case PixelDataFormat::GreenInteger:
			result << ".g"; break;
#endif

#ifdef GL_BLUE
		case PixelDataFormat::Blue:
			result << ".b"; break;
#endif
#ifdef GL_BLUE_INTEGER
		case PixelDataFormat::BlueInteger:
			result << ".b"; break;
#endif



#ifdef GL_RG
		case PixelDataFormat::RG:
			result << ".rg"; break;
#endif
#ifdef GL_RG_INTEGER
		case PixelDataFormat::RGInteger:
			result << ".rg"; break;
#endif

#ifdef GL_RGB
		case PixelDataFormat::RGB:
			result << ".rgb"; break;
#endif
#ifdef GL_RGB_INTEGER
		case PixelDataFormat::RGBInteger:
			result << ".rgb"; break;
#endif

#ifdef GL_BGR
		case PixelDataFormat::BGR:
			result << ".rgb"; break; // TODO .bgr?
#endif
#ifdef GL_BGR_INTEGER
		case PixelDataFormat::BGRInteger:
			result << ".rgb"; break; // TODO .bgr?
#endif
		default:;
		}
		result << ";\n";
	}

	result << "}\n";
	return result;
}

OGLPLUS_LIB_FUNC
TextureNode::
TextureNode(Texture&& texture, TextureTarget target, PixelDataFormat format)
 : _output(*this, std::move(texture), target, format)
{ }

OGLPLUS_LIB_FUNC
std::size_t
TextureNode::
InputCount(void)
{
	return 1;
}

OGLPLUS_LIB_FUNC
InputSlot&
TextureNode::
Input(std::size_t i)
{
	assert(i < InputCount());
	return _output._coord;
}

OGLPLUS_LIB_FUNC
BaseOutputSlot&
TextureNode::
SingleOutput(void)
{
	return _output;
}

} // namespace texgen
} // namespace oglplus

