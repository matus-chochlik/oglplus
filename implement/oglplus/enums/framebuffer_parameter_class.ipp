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
# if defined DefaultWidth
#  pragma push_macro("DefaultWidth")
#  undef DefaultWidth
	Transform<FramebufferParameter::DefaultWidth> DefaultWidth;
#  pragma pop_macro("DefaultWidth")
# else
	Transform<FramebufferParameter::DefaultWidth> DefaultWidth;
# endif
#endif
#if defined GL_FRAMEBUFFER_DEFAULT_HEIGHT
# if defined DefaultHeight
#  pragma push_macro("DefaultHeight")
#  undef DefaultHeight
	Transform<FramebufferParameter::DefaultHeight> DefaultHeight;
#  pragma pop_macro("DefaultHeight")
# else
	Transform<FramebufferParameter::DefaultHeight> DefaultHeight;
# endif
#endif
#if defined GL_FRAMEBUFFER_DEFAULT_LAYERS
# if defined Layers
#  pragma push_macro("Layers")
#  undef Layers
	Transform<FramebufferParameter::Layers> Layers;
#  pragma pop_macro("Layers")
# else
	Transform<FramebufferParameter::Layers> Layers;
# endif
#endif
#if defined GL_FRAMEBUFFER_DEFAULT_SAMPLES
# if defined Samples
#  pragma push_macro("Samples")
#  undef Samples
	Transform<FramebufferParameter::Samples> Samples;
#  pragma pop_macro("Samples")
# else
	Transform<FramebufferParameter::Samples> Samples;
# endif
#endif
#if defined GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS
# if defined FixedSampleLocations
#  pragma push_macro("FixedSampleLocations")
#  undef FixedSampleLocations
	Transform<FramebufferParameter::FixedSampleLocations> FixedSampleLocations;
#  pragma pop_macro("FixedSampleLocations")
# else
	Transform<FramebufferParameter::FixedSampleLocations> FixedSampleLocations;
# endif
#endif

	EnumToClass(void) { }
	EnumToClass(Base&& base)
	 : Base(std::move(base))
#if defined GL_FRAMEBUFFER_DEFAULT_WIDTH
# if defined DefaultWidth
#  pragma push_macro("DefaultWidth")
#  undef DefaultWidth
	 , DefaultWidth(_base())
#  pragma pop_macro("DefaultWidth")
# else
	 , DefaultWidth(_base())
# endif
#endif
#if defined GL_FRAMEBUFFER_DEFAULT_HEIGHT
# if defined DefaultHeight
#  pragma push_macro("DefaultHeight")
#  undef DefaultHeight
	 , DefaultHeight(_base())
#  pragma pop_macro("DefaultHeight")
# else
	 , DefaultHeight(_base())
# endif
#endif
#if defined GL_FRAMEBUFFER_DEFAULT_LAYERS
# if defined Layers
#  pragma push_macro("Layers")
#  undef Layers
	 , Layers(_base())
#  pragma pop_macro("Layers")
# else
	 , Layers(_base())
# endif
#endif
#if defined GL_FRAMEBUFFER_DEFAULT_SAMPLES
# if defined Samples
#  pragma push_macro("Samples")
#  undef Samples
	 , Samples(_base())
#  pragma pop_macro("Samples")
# else
	 , Samples(_base())
# endif
#endif
#if defined GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS
# if defined FixedSampleLocations
#  pragma push_macro("FixedSampleLocations")
#  undef FixedSampleLocations
	 , FixedSampleLocations(_base())
#  pragma pop_macro("FixedSampleLocations")
# else
	 , FixedSampleLocations(_base())
# endif
#endif
	{ }
};

} // namespace enums

