//  File implement/oglplus/enums/framebuffer_parameter_class.ipp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oglplus/framebuffer_parameter.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2017 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
namespace enums {
template <typename Base, template<FramebufferParameter> class Transform>
class EnumToClass<Base, FramebufferParameter, Transform>
 : public Base
{
private:
	Base& _base(void) { return *this; }
public:

#if defined GL_FRAMEBUFFER_DEFAULT_WIDTH
# if defined FramebufferDefaultWidth
#  pragma push_macro("FramebufferDefaultWidth")
#  undef FramebufferDefaultWidth
	Transform<FramebufferParameter::FramebufferDefaultWidth> FramebufferDefaultWidth;
#  pragma pop_macro("FramebufferDefaultWidth")
# else
	Transform<FramebufferParameter::FramebufferDefaultWidth> FramebufferDefaultWidth;
# endif
#endif
#if defined GL_FRAMEBUFFER_DEFAULT_HEIGHT
# if defined FramebufferDefaultHeight
#  pragma push_macro("FramebufferDefaultHeight")
#  undef FramebufferDefaultHeight
	Transform<FramebufferParameter::FramebufferDefaultHeight> FramebufferDefaultHeight;
#  pragma pop_macro("FramebufferDefaultHeight")
# else
	Transform<FramebufferParameter::FramebufferDefaultHeight> FramebufferDefaultHeight;
# endif
#endif
#if defined GL_FRAMEBUFFER_DEFAULT_LAYERS
# if defined FramebufferDefaultLayers
#  pragma push_macro("FramebufferDefaultLayers")
#  undef FramebufferDefaultLayers
	Transform<FramebufferParameter::FramebufferDefaultLayers> FramebufferDefaultLayers;
#  pragma pop_macro("FramebufferDefaultLayers")
# else
	Transform<FramebufferParameter::FramebufferDefaultLayers> FramebufferDefaultLayers;
# endif
#endif
#if defined GL_FRAMEBUFFER_DEFAULT_SAMPLES
# if defined FramebufferDefaultSamples
#  pragma push_macro("FramebufferDefaultSamples")
#  undef FramebufferDefaultSamples
	Transform<FramebufferParameter::FramebufferDefaultSamples> FramebufferDefaultSamples;
#  pragma pop_macro("FramebufferDefaultSamples")
# else
	Transform<FramebufferParameter::FramebufferDefaultSamples> FramebufferDefaultSamples;
# endif
#endif
#if defined GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS
# if defined FramebufferDefaultFixedSampleLocations
#  pragma push_macro("FramebufferDefaultFixedSampleLocations")
#  undef FramebufferDefaultFixedSampleLocations
	Transform<FramebufferParameter::FramebufferDefaultFixedSampleLocations> FramebufferDefaultFixedSampleLocations;
#  pragma pop_macro("FramebufferDefaultFixedSampleLocations")
# else
	Transform<FramebufferParameter::FramebufferDefaultFixedSampleLocations> FramebufferDefaultFixedSampleLocations;
# endif
#endif

	EnumToClass(void) { }
	EnumToClass(Base&& base)
	 : Base(std::move(base))
#if defined GL_FRAMEBUFFER_DEFAULT_WIDTH
# if defined FramebufferDefaultWidth
#  pragma push_macro("FramebufferDefaultWidth")
#  undef FramebufferDefaultWidth
	 , FramebufferDefaultWidth(_base())
#  pragma pop_macro("FramebufferDefaultWidth")
# else
	 , FramebufferDefaultWidth(_base())
# endif
#endif
#if defined GL_FRAMEBUFFER_DEFAULT_HEIGHT
# if defined FramebufferDefaultHeight
#  pragma push_macro("FramebufferDefaultHeight")
#  undef FramebufferDefaultHeight
	 , FramebufferDefaultHeight(_base())
#  pragma pop_macro("FramebufferDefaultHeight")
# else
	 , FramebufferDefaultHeight(_base())
# endif
#endif
#if defined GL_FRAMEBUFFER_DEFAULT_LAYERS
# if defined FramebufferDefaultLayers
#  pragma push_macro("FramebufferDefaultLayers")
#  undef FramebufferDefaultLayers
	 , FramebufferDefaultLayers(_base())
#  pragma pop_macro("FramebufferDefaultLayers")
# else
	 , FramebufferDefaultLayers(_base())
# endif
#endif
#if defined GL_FRAMEBUFFER_DEFAULT_SAMPLES
# if defined FramebufferDefaultSamples
#  pragma push_macro("FramebufferDefaultSamples")
#  undef FramebufferDefaultSamples
	 , FramebufferDefaultSamples(_base())
#  pragma pop_macro("FramebufferDefaultSamples")
# else
	 , FramebufferDefaultSamples(_base())
# endif
#endif
#if defined GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS
# if defined FramebufferDefaultFixedSampleLocations
#  pragma push_macro("FramebufferDefaultFixedSampleLocations")
#  undef FramebufferDefaultFixedSampleLocations
	 , FramebufferDefaultFixedSampleLocations(_base())
#  pragma pop_macro("FramebufferDefaultFixedSampleLocations")
# else
	 , FramebufferDefaultFixedSampleLocations(_base())
# endif
#endif
	{ }
};

} // namespace enums

