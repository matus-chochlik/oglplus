//  File doc/quickbook/oglplus/quickref/enums/program_parameter_class.hpp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oglplus/program_parameter.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2017 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//[oglplus_enums_program_parameter_class
#if !__OGLPLUS_NO_ENUM_VALUE_CLASSES
namespace enums {

template <typename Base, template<__ProgramParameter> class Transform>
class __EnumToClass<Base, __ProgramParameter, Transform> /*<
Specialization of __EnumToClass for the __ProgramParameter enumeration.
>*/
 : public Base
{
public:
	EnumToClass(void);
	EnumToClass(Base&& base);

	Transform<ProgramParameter::DeleteStatus>
		DeleteStatus;
	Transform<ProgramParameter::LinkStatus>
		LinkStatus;
	Transform<ProgramParameter::ValidateStatus>
		ValidateStatus;
	Transform<ProgramParameter::InfoLogLength>
		InfoLogLength;
	Transform<ProgramParameter::AttachedShaders>
		AttachedShaders;
	Transform<ProgramParameter::ActiveAtomicCounterBuffers>
		ActiveAtomicCounterBuffers;
	Transform<ProgramParameter::ActiveAttributes>
		ActiveAttributes;
	Transform<ProgramParameter::ActiveAttributeMaxLength>
		ActiveAttributeMaxLength;
	Transform<ProgramParameter::ActiveUniforms>
		ActiveUniforms;
	Transform<ProgramParameter::ActiveUniformMaxLength>
		ActiveUniformMaxLength;
	Transform<ProgramParameter::ProgramBinaryLength>
		ProgramBinaryLength;
	Transform<ProgramParameter::ComputeWorkGroupSize>
		ComputeWorkGroupSize;
	Transform<ProgramParameter::TransformFeedbackBufferMode>
		TransformFeedbackBufferMode;
	Transform<ProgramParameter::TransformFeedbackVaryings>
		TransformFeedbackVaryings;
	Transform<ProgramParameter::TransformFeedbackVaryingMaxLength>
		TransformFeedbackVaryingMaxLength;
	Transform<ProgramParameter::GeometryVerticesOut>
		GeometryVerticesOut;
	Transform<ProgramParameter::GeometryInputType>
		GeometryInputType;
	Transform<ProgramParameter::GeometryOutputType>
		GeometryOutputType;
};

} // namespace enums
#endif
//]

