/*
 *  .file eglplus/config_attrib.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/eglplus/config_attrib.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <eglplus/egl.hpp>
#include <eglplus/config_attrib.hpp>

#include <boost/python.hpp>

void eglplus_py_config_attrib(void)
{
	boost::python::enum_<eglplus::ConfigAttrib>("ConfigAttrib")
#if defined EGL_BUFFER_SIZE
# if defined BufferSize
#  pragma push_macro("BufferSize")
#  undef BufferSize
	.value("BufferSize", eglplus::ConfigAttrib::BufferSize)
#  pragma pop_macro("BufferSize")
# else
	.value("BufferSize", eglplus::ConfigAttrib::BufferSize)
# endif
#endif
#if defined EGL_RED_SIZE
# if defined RedSize
#  pragma push_macro("RedSize")
#  undef RedSize
	.value("RedSize", eglplus::ConfigAttrib::RedSize)
#  pragma pop_macro("RedSize")
# else
	.value("RedSize", eglplus::ConfigAttrib::RedSize)
# endif
#endif
#if defined EGL_GREEN_SIZE
# if defined GreenSize
#  pragma push_macro("GreenSize")
#  undef GreenSize
	.value("GreenSize", eglplus::ConfigAttrib::GreenSize)
#  pragma pop_macro("GreenSize")
# else
	.value("GreenSize", eglplus::ConfigAttrib::GreenSize)
# endif
#endif
#if defined EGL_BLUE_SIZE
# if defined BlueSize
#  pragma push_macro("BlueSize")
#  undef BlueSize
	.value("BlueSize", eglplus::ConfigAttrib::BlueSize)
#  pragma pop_macro("BlueSize")
# else
	.value("BlueSize", eglplus::ConfigAttrib::BlueSize)
# endif
#endif
#if defined EGL_LUMINANCE_SIZE
# if defined LuminanceSize
#  pragma push_macro("LuminanceSize")
#  undef LuminanceSize
	.value("LuminanceSize", eglplus::ConfigAttrib::LuminanceSize)
#  pragma pop_macro("LuminanceSize")
# else
	.value("LuminanceSize", eglplus::ConfigAttrib::LuminanceSize)
# endif
#endif
#if defined EGL_ALPHA_SIZE
# if defined AlphaSize
#  pragma push_macro("AlphaSize")
#  undef AlphaSize
	.value("AlphaSize", eglplus::ConfigAttrib::AlphaSize)
#  pragma pop_macro("AlphaSize")
# else
	.value("AlphaSize", eglplus::ConfigAttrib::AlphaSize)
# endif
#endif
#if defined EGL_ALPHA_MASK_SIZE
# if defined AlphaMaskSize
#  pragma push_macro("AlphaMaskSize")
#  undef AlphaMaskSize
	.value("AlphaMaskSize", eglplus::ConfigAttrib::AlphaMaskSize)
#  pragma pop_macro("AlphaMaskSize")
# else
	.value("AlphaMaskSize", eglplus::ConfigAttrib::AlphaMaskSize)
# endif
#endif
#if defined EGL_BIND_TO_TEXTURE_RGB
# if defined BindToTextureRGB
#  pragma push_macro("BindToTextureRGB")
#  undef BindToTextureRGB
	.value("BindToTextureRGB", eglplus::ConfigAttrib::BindToTextureRGB)
#  pragma pop_macro("BindToTextureRGB")
# else
	.value("BindToTextureRGB", eglplus::ConfigAttrib::BindToTextureRGB)
# endif
#endif
#if defined EGL_BIND_TO_TEXTURE_RGBA
# if defined BindToTextureRGBA
#  pragma push_macro("BindToTextureRGBA")
#  undef BindToTextureRGBA
	.value("BindToTextureRGBA", eglplus::ConfigAttrib::BindToTextureRGBA)
#  pragma pop_macro("BindToTextureRGBA")
# else
	.value("BindToTextureRGBA", eglplus::ConfigAttrib::BindToTextureRGBA)
# endif
#endif
#if defined EGL_COLOR_BUFFER_TYPE
# if defined ColorBufferType
#  pragma push_macro("ColorBufferType")
#  undef ColorBufferType
	.value("ColorBufferType", eglplus::ConfigAttrib::ColorBufferType)
#  pragma pop_macro("ColorBufferType")
# else
	.value("ColorBufferType", eglplus::ConfigAttrib::ColorBufferType)
# endif
#endif
#if defined EGL_CONFIG_CAVEAT
# if defined ConfigCaveat
#  pragma push_macro("ConfigCaveat")
#  undef ConfigCaveat
	.value("ConfigCaveat", eglplus::ConfigAttrib::ConfigCaveat)
#  pragma pop_macro("ConfigCaveat")
# else
	.value("ConfigCaveat", eglplus::ConfigAttrib::ConfigCaveat)
# endif
#endif
#if defined EGL_CONFIG_ID
# if defined ConfigId
#  pragma push_macro("ConfigId")
#  undef ConfigId
	.value("ConfigId", eglplus::ConfigAttrib::ConfigId)
#  pragma pop_macro("ConfigId")
# else
	.value("ConfigId", eglplus::ConfigAttrib::ConfigId)
# endif
#endif
#if defined EGL_CONFORMANT
# if defined Conformant
#  pragma push_macro("Conformant")
#  undef Conformant
	.value("Conformant", eglplus::ConfigAttrib::Conformant)
#  pragma pop_macro("Conformant")
# else
	.value("Conformant", eglplus::ConfigAttrib::Conformant)
# endif
#endif
#if defined EGL_DEPTH_SIZE
# if defined DepthSize
#  pragma push_macro("DepthSize")
#  undef DepthSize
	.value("DepthSize", eglplus::ConfigAttrib::DepthSize)
#  pragma pop_macro("DepthSize")
# else
	.value("DepthSize", eglplus::ConfigAttrib::DepthSize)
# endif
#endif
#if defined EGL_LEVEL
# if defined Level
#  pragma push_macro("Level")
#  undef Level
	.value("Level", eglplus::ConfigAttrib::Level)
#  pragma pop_macro("Level")
# else
	.value("Level", eglplus::ConfigAttrib::Level)
# endif
#endif
#if defined EGL_MAX_PBUFFER_WIDTH
# if defined MaxPbufferWidth
#  pragma push_macro("MaxPbufferWidth")
#  undef MaxPbufferWidth
	.value("MaxPbufferWidth", eglplus::ConfigAttrib::MaxPbufferWidth)
#  pragma pop_macro("MaxPbufferWidth")
# else
	.value("MaxPbufferWidth", eglplus::ConfigAttrib::MaxPbufferWidth)
# endif
#endif
#if defined EGL_MAX_PBUFFER_HEIGHT
# if defined MaxPbufferHeight
#  pragma push_macro("MaxPbufferHeight")
#  undef MaxPbufferHeight
	.value("MaxPbufferHeight", eglplus::ConfigAttrib::MaxPbufferHeight)
#  pragma pop_macro("MaxPbufferHeight")
# else
	.value("MaxPbufferHeight", eglplus::ConfigAttrib::MaxPbufferHeight)
# endif
#endif
#if defined EGL_MAX_PBUFFER_PIXELS
# if defined MaxPbufferPixels
#  pragma push_macro("MaxPbufferPixels")
#  undef MaxPbufferPixels
	.value("MaxPbufferPixels", eglplus::ConfigAttrib::MaxPbufferPixels)
#  pragma pop_macro("MaxPbufferPixels")
# else
	.value("MaxPbufferPixels", eglplus::ConfigAttrib::MaxPbufferPixels)
# endif
#endif
#if defined EGL_MAX_SWAP_INTERVAL
# if defined MaxSwapInterval
#  pragma push_macro("MaxSwapInterval")
#  undef MaxSwapInterval
	.value("MaxSwapInterval", eglplus::ConfigAttrib::MaxSwapInterval)
#  pragma pop_macro("MaxSwapInterval")
# else
	.value("MaxSwapInterval", eglplus::ConfigAttrib::MaxSwapInterval)
# endif
#endif
#if defined EGL_MIN_SWAP_INTERVAL
# if defined MinSwapInterval
#  pragma push_macro("MinSwapInterval")
#  undef MinSwapInterval
	.value("MinSwapInterval", eglplus::ConfigAttrib::MinSwapInterval)
#  pragma pop_macro("MinSwapInterval")
# else
	.value("MinSwapInterval", eglplus::ConfigAttrib::MinSwapInterval)
# endif
#endif
#if defined EGL_NATIVE_RENDERABLE
# if defined NativeRenderable
#  pragma push_macro("NativeRenderable")
#  undef NativeRenderable
	.value("NativeRenderable", eglplus::ConfigAttrib::NativeRenderable)
#  pragma pop_macro("NativeRenderable")
# else
	.value("NativeRenderable", eglplus::ConfigAttrib::NativeRenderable)
# endif
#endif
#if defined EGL_NATIVE_VISUAL_ID
# if defined NativeVisualId
#  pragma push_macro("NativeVisualId")
#  undef NativeVisualId
	.value("NativeVisualId", eglplus::ConfigAttrib::NativeVisualId)
#  pragma pop_macro("NativeVisualId")
# else
	.value("NativeVisualId", eglplus::ConfigAttrib::NativeVisualId)
# endif
#endif
#if defined EGL_NATIVE_VISUAL_TYPE
# if defined NativeVisualType
#  pragma push_macro("NativeVisualType")
#  undef NativeVisualType
	.value("NativeVisualType", eglplus::ConfigAttrib::NativeVisualType)
#  pragma pop_macro("NativeVisualType")
# else
	.value("NativeVisualType", eglplus::ConfigAttrib::NativeVisualType)
# endif
#endif
#if defined EGL_RENDERABLE_TYPE
# if defined RenderableType
#  pragma push_macro("RenderableType")
#  undef RenderableType
	.value("RenderableType", eglplus::ConfigAttrib::RenderableType)
#  pragma pop_macro("RenderableType")
# else
	.value("RenderableType", eglplus::ConfigAttrib::RenderableType)
# endif
#endif
#if defined EGL_SAMPLE_BUFFERS
# if defined SampleBuffers
#  pragma push_macro("SampleBuffers")
#  undef SampleBuffers
	.value("SampleBuffers", eglplus::ConfigAttrib::SampleBuffers)
#  pragma pop_macro("SampleBuffers")
# else
	.value("SampleBuffers", eglplus::ConfigAttrib::SampleBuffers)
# endif
#endif
#if defined EGL_SAMPLES
# if defined Samples
#  pragma push_macro("Samples")
#  undef Samples
	.value("Samples", eglplus::ConfigAttrib::Samples)
#  pragma pop_macro("Samples")
# else
	.value("Samples", eglplus::ConfigAttrib::Samples)
# endif
#endif
#if defined EGL_STENCIL_SIZE
# if defined StencilSize
#  pragma push_macro("StencilSize")
#  undef StencilSize
	.value("StencilSize", eglplus::ConfigAttrib::StencilSize)
#  pragma pop_macro("StencilSize")
# else
	.value("StencilSize", eglplus::ConfigAttrib::StencilSize)
# endif
#endif
#if defined EGL_SURFACE_TYPE
# if defined SurfaceType
#  pragma push_macro("SurfaceType")
#  undef SurfaceType
	.value("SurfaceType", eglplus::ConfigAttrib::SurfaceType)
#  pragma pop_macro("SurfaceType")
# else
	.value("SurfaceType", eglplus::ConfigAttrib::SurfaceType)
# endif
#endif
#if defined EGL_TRANSPARENT_TYPE
# if defined TransparentType
#  pragma push_macro("TransparentType")
#  undef TransparentType
	.value("TransparentType", eglplus::ConfigAttrib::TransparentType)
#  pragma pop_macro("TransparentType")
# else
	.value("TransparentType", eglplus::ConfigAttrib::TransparentType)
# endif
#endif
#if defined EGL_TRANSPARENT_RED_VALUE
# if defined TransparentRedValue
#  pragma push_macro("TransparentRedValue")
#  undef TransparentRedValue
	.value("TransparentRedValue", eglplus::ConfigAttrib::TransparentRedValue)
#  pragma pop_macro("TransparentRedValue")
# else
	.value("TransparentRedValue", eglplus::ConfigAttrib::TransparentRedValue)
# endif
#endif
#if defined EGL_TRANSPARENT_GREEN_VALUE
# if defined TransparentGreenValue
#  pragma push_macro("TransparentGreenValue")
#  undef TransparentGreenValue
	.value("TransparentGreenValue", eglplus::ConfigAttrib::TransparentGreenValue)
#  pragma pop_macro("TransparentGreenValue")
# else
	.value("TransparentGreenValue", eglplus::ConfigAttrib::TransparentGreenValue)
# endif
#endif
#if defined EGL_TRANSPARENT_BLUE_VALUE
# if defined TransparentBlueValue
#  pragma push_macro("TransparentBlueValue")
#  undef TransparentBlueValue
	.value("TransparentBlueValue", eglplus::ConfigAttrib::TransparentBlueValue)
#  pragma pop_macro("TransparentBlueValue")
# else
	.value("TransparentBlueValue", eglplus::ConfigAttrib::TransparentBlueValue)
# endif
#endif
	;

	eglplus::StrLit (*PEnumValueName)(eglplus::ConfigAttrib) =
		&eglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);
}
