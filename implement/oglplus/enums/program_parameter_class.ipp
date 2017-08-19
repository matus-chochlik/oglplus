//  File implement/oglplus/enums/program_parameter_class.ipp
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
namespace enums {
template <typename Base, template<ProgramParameter> class Transform>
class EnumToClass<Base, ProgramParameter, Transform>
 : public Base
{
private:
	Base& _base(void) { return *this; }
public:

#if defined GL_DELETE_STATUS
# if defined DeleteStatus
#  pragma push_macro("DeleteStatus")
#  undef DeleteStatus
	Transform<ProgramParameter::DeleteStatus> DeleteStatus;
#  pragma pop_macro("DeleteStatus")
# else
	Transform<ProgramParameter::DeleteStatus> DeleteStatus;
# endif
#endif
#if defined GL_LINK_STATUS
# if defined LinkStatus
#  pragma push_macro("LinkStatus")
#  undef LinkStatus
	Transform<ProgramParameter::LinkStatus> LinkStatus;
#  pragma pop_macro("LinkStatus")
# else
	Transform<ProgramParameter::LinkStatus> LinkStatus;
# endif
#endif
#if defined GL_VALIDATE_STATUS
# if defined ValidateStatus
#  pragma push_macro("ValidateStatus")
#  undef ValidateStatus
	Transform<ProgramParameter::ValidateStatus> ValidateStatus;
#  pragma pop_macro("ValidateStatus")
# else
	Transform<ProgramParameter::ValidateStatus> ValidateStatus;
# endif
#endif
#if defined GL_INFO_LOG_LENGTH
# if defined InfoLogLength
#  pragma push_macro("InfoLogLength")
#  undef InfoLogLength
	Transform<ProgramParameter::InfoLogLength> InfoLogLength;
#  pragma pop_macro("InfoLogLength")
# else
	Transform<ProgramParameter::InfoLogLength> InfoLogLength;
# endif
#endif
#if defined GL_ATTACHED_SHADERS
# if defined AttachedShaders
#  pragma push_macro("AttachedShaders")
#  undef AttachedShaders
	Transform<ProgramParameter::AttachedShaders> AttachedShaders;
#  pragma pop_macro("AttachedShaders")
# else
	Transform<ProgramParameter::AttachedShaders> AttachedShaders;
# endif
#endif
#if defined GL_ACTIVE_ATOMIC_COUNTER_BUFFERS
# if defined ActiveAtomicCounterBuffers
#  pragma push_macro("ActiveAtomicCounterBuffers")
#  undef ActiveAtomicCounterBuffers
	Transform<ProgramParameter::ActiveAtomicCounterBuffers> ActiveAtomicCounterBuffers;
#  pragma pop_macro("ActiveAtomicCounterBuffers")
# else
	Transform<ProgramParameter::ActiveAtomicCounterBuffers> ActiveAtomicCounterBuffers;
# endif
#endif
#if defined GL_ACTIVE_ATTRIBUTES
# if defined ActiveAttributes
#  pragma push_macro("ActiveAttributes")
#  undef ActiveAttributes
	Transform<ProgramParameter::ActiveAttributes> ActiveAttributes;
#  pragma pop_macro("ActiveAttributes")
# else
	Transform<ProgramParameter::ActiveAttributes> ActiveAttributes;
# endif
#endif
#if defined GL_ACTIVE_ATTRIBUTE_MAX_LENGTH
# if defined ActiveAttributeMaxLength
#  pragma push_macro("ActiveAttributeMaxLength")
#  undef ActiveAttributeMaxLength
	Transform<ProgramParameter::ActiveAttributeMaxLength> ActiveAttributeMaxLength;
#  pragma pop_macro("ActiveAttributeMaxLength")
# else
	Transform<ProgramParameter::ActiveAttributeMaxLength> ActiveAttributeMaxLength;
# endif
#endif
#if defined GL_ACTIVE_UNIFORMS
# if defined ActiveUniforms
#  pragma push_macro("ActiveUniforms")
#  undef ActiveUniforms
	Transform<ProgramParameter::ActiveUniforms> ActiveUniforms;
#  pragma pop_macro("ActiveUniforms")
# else
	Transform<ProgramParameter::ActiveUniforms> ActiveUniforms;
# endif
#endif
#if defined GL_ACTIVE_UNIFORM_MAX_LENGTH
# if defined ActiveUniformMaxLength
#  pragma push_macro("ActiveUniformMaxLength")
#  undef ActiveUniformMaxLength
	Transform<ProgramParameter::ActiveUniformMaxLength> ActiveUniformMaxLength;
#  pragma pop_macro("ActiveUniformMaxLength")
# else
	Transform<ProgramParameter::ActiveUniformMaxLength> ActiveUniformMaxLength;
# endif
#endif
#if defined GL_PROGRAM_BINARY_LENGTH
# if defined ProgramBinaryLength
#  pragma push_macro("ProgramBinaryLength")
#  undef ProgramBinaryLength
	Transform<ProgramParameter::ProgramBinaryLength> ProgramBinaryLength;
#  pragma pop_macro("ProgramBinaryLength")
# else
	Transform<ProgramParameter::ProgramBinaryLength> ProgramBinaryLength;
# endif
#endif
#if defined GL_COMPUTE_WORK_GROUP_SIZE
# if defined ComputeWorkGroupSize
#  pragma push_macro("ComputeWorkGroupSize")
#  undef ComputeWorkGroupSize
	Transform<ProgramParameter::ComputeWorkGroupSize> ComputeWorkGroupSize;
#  pragma pop_macro("ComputeWorkGroupSize")
# else
	Transform<ProgramParameter::ComputeWorkGroupSize> ComputeWorkGroupSize;
# endif
#endif
#if defined GL_TRANSFORM_FEEDBACK_BUFFER_MODE
# if defined TransformFeedbackBufferMode
#  pragma push_macro("TransformFeedbackBufferMode")
#  undef TransformFeedbackBufferMode
	Transform<ProgramParameter::TransformFeedbackBufferMode> TransformFeedbackBufferMode;
#  pragma pop_macro("TransformFeedbackBufferMode")
# else
	Transform<ProgramParameter::TransformFeedbackBufferMode> TransformFeedbackBufferMode;
# endif
#endif
#if defined GL_TRANSFORM_FEEDBACK_VARYINGS
# if defined TransformFeedbackVaryings
#  pragma push_macro("TransformFeedbackVaryings")
#  undef TransformFeedbackVaryings
	Transform<ProgramParameter::TransformFeedbackVaryings> TransformFeedbackVaryings;
#  pragma pop_macro("TransformFeedbackVaryings")
# else
	Transform<ProgramParameter::TransformFeedbackVaryings> TransformFeedbackVaryings;
# endif
#endif
#if defined GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH
# if defined TransformFeedbackVaryingMaxLength
#  pragma push_macro("TransformFeedbackVaryingMaxLength")
#  undef TransformFeedbackVaryingMaxLength
	Transform<ProgramParameter::TransformFeedbackVaryingMaxLength> TransformFeedbackVaryingMaxLength;
#  pragma pop_macro("TransformFeedbackVaryingMaxLength")
# else
	Transform<ProgramParameter::TransformFeedbackVaryingMaxLength> TransformFeedbackVaryingMaxLength;
# endif
#endif
#if defined GL_GEOMETRY_VERTICES_OUT
# if defined GeometryVerticesOut
#  pragma push_macro("GeometryVerticesOut")
#  undef GeometryVerticesOut
	Transform<ProgramParameter::GeometryVerticesOut> GeometryVerticesOut;
#  pragma pop_macro("GeometryVerticesOut")
# else
	Transform<ProgramParameter::GeometryVerticesOut> GeometryVerticesOut;
# endif
#endif
#if defined GL_GEOMETRY_INPUT_TYPE
# if defined GeometryInputType
#  pragma push_macro("GeometryInputType")
#  undef GeometryInputType
	Transform<ProgramParameter::GeometryInputType> GeometryInputType;
#  pragma pop_macro("GeometryInputType")
# else
	Transform<ProgramParameter::GeometryInputType> GeometryInputType;
# endif
#endif
#if defined GL_GEOMETRY_OUTPUT_TYPE
# if defined GeometryOutputType
#  pragma push_macro("GeometryOutputType")
#  undef GeometryOutputType
	Transform<ProgramParameter::GeometryOutputType> GeometryOutputType;
#  pragma pop_macro("GeometryOutputType")
# else
	Transform<ProgramParameter::GeometryOutputType> GeometryOutputType;
# endif
#endif

	EnumToClass(void) { }
	EnumToClass(Base&& base)
	 : Base(std::move(base))
#if defined GL_DELETE_STATUS
# if defined DeleteStatus
#  pragma push_macro("DeleteStatus")
#  undef DeleteStatus
	 , DeleteStatus(_base())
#  pragma pop_macro("DeleteStatus")
# else
	 , DeleteStatus(_base())
# endif
#endif
#if defined GL_LINK_STATUS
# if defined LinkStatus
#  pragma push_macro("LinkStatus")
#  undef LinkStatus
	 , LinkStatus(_base())
#  pragma pop_macro("LinkStatus")
# else
	 , LinkStatus(_base())
# endif
#endif
#if defined GL_VALIDATE_STATUS
# if defined ValidateStatus
#  pragma push_macro("ValidateStatus")
#  undef ValidateStatus
	 , ValidateStatus(_base())
#  pragma pop_macro("ValidateStatus")
# else
	 , ValidateStatus(_base())
# endif
#endif
#if defined GL_INFO_LOG_LENGTH
# if defined InfoLogLength
#  pragma push_macro("InfoLogLength")
#  undef InfoLogLength
	 , InfoLogLength(_base())
#  pragma pop_macro("InfoLogLength")
# else
	 , InfoLogLength(_base())
# endif
#endif
#if defined GL_ATTACHED_SHADERS
# if defined AttachedShaders
#  pragma push_macro("AttachedShaders")
#  undef AttachedShaders
	 , AttachedShaders(_base())
#  pragma pop_macro("AttachedShaders")
# else
	 , AttachedShaders(_base())
# endif
#endif
#if defined GL_ACTIVE_ATOMIC_COUNTER_BUFFERS
# if defined ActiveAtomicCounterBuffers
#  pragma push_macro("ActiveAtomicCounterBuffers")
#  undef ActiveAtomicCounterBuffers
	 , ActiveAtomicCounterBuffers(_base())
#  pragma pop_macro("ActiveAtomicCounterBuffers")
# else
	 , ActiveAtomicCounterBuffers(_base())
# endif
#endif
#if defined GL_ACTIVE_ATTRIBUTES
# if defined ActiveAttributes
#  pragma push_macro("ActiveAttributes")
#  undef ActiveAttributes
	 , ActiveAttributes(_base())
#  pragma pop_macro("ActiveAttributes")
# else
	 , ActiveAttributes(_base())
# endif
#endif
#if defined GL_ACTIVE_ATTRIBUTE_MAX_LENGTH
# if defined ActiveAttributeMaxLength
#  pragma push_macro("ActiveAttributeMaxLength")
#  undef ActiveAttributeMaxLength
	 , ActiveAttributeMaxLength(_base())
#  pragma pop_macro("ActiveAttributeMaxLength")
# else
	 , ActiveAttributeMaxLength(_base())
# endif
#endif
#if defined GL_ACTIVE_UNIFORMS
# if defined ActiveUniforms
#  pragma push_macro("ActiveUniforms")
#  undef ActiveUniforms
	 , ActiveUniforms(_base())
#  pragma pop_macro("ActiveUniforms")
# else
	 , ActiveUniforms(_base())
# endif
#endif
#if defined GL_ACTIVE_UNIFORM_MAX_LENGTH
# if defined ActiveUniformMaxLength
#  pragma push_macro("ActiveUniformMaxLength")
#  undef ActiveUniformMaxLength
	 , ActiveUniformMaxLength(_base())
#  pragma pop_macro("ActiveUniformMaxLength")
# else
	 , ActiveUniformMaxLength(_base())
# endif
#endif
#if defined GL_PROGRAM_BINARY_LENGTH
# if defined ProgramBinaryLength
#  pragma push_macro("ProgramBinaryLength")
#  undef ProgramBinaryLength
	 , ProgramBinaryLength(_base())
#  pragma pop_macro("ProgramBinaryLength")
# else
	 , ProgramBinaryLength(_base())
# endif
#endif
#if defined GL_COMPUTE_WORK_GROUP_SIZE
# if defined ComputeWorkGroupSize
#  pragma push_macro("ComputeWorkGroupSize")
#  undef ComputeWorkGroupSize
	 , ComputeWorkGroupSize(_base())
#  pragma pop_macro("ComputeWorkGroupSize")
# else
	 , ComputeWorkGroupSize(_base())
# endif
#endif
#if defined GL_TRANSFORM_FEEDBACK_BUFFER_MODE
# if defined TransformFeedbackBufferMode
#  pragma push_macro("TransformFeedbackBufferMode")
#  undef TransformFeedbackBufferMode
	 , TransformFeedbackBufferMode(_base())
#  pragma pop_macro("TransformFeedbackBufferMode")
# else
	 , TransformFeedbackBufferMode(_base())
# endif
#endif
#if defined GL_TRANSFORM_FEEDBACK_VARYINGS
# if defined TransformFeedbackVaryings
#  pragma push_macro("TransformFeedbackVaryings")
#  undef TransformFeedbackVaryings
	 , TransformFeedbackVaryings(_base())
#  pragma pop_macro("TransformFeedbackVaryings")
# else
	 , TransformFeedbackVaryings(_base())
# endif
#endif
#if defined GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH
# if defined TransformFeedbackVaryingMaxLength
#  pragma push_macro("TransformFeedbackVaryingMaxLength")
#  undef TransformFeedbackVaryingMaxLength
	 , TransformFeedbackVaryingMaxLength(_base())
#  pragma pop_macro("TransformFeedbackVaryingMaxLength")
# else
	 , TransformFeedbackVaryingMaxLength(_base())
# endif
#endif
#if defined GL_GEOMETRY_VERTICES_OUT
# if defined GeometryVerticesOut
#  pragma push_macro("GeometryVerticesOut")
#  undef GeometryVerticesOut
	 , GeometryVerticesOut(_base())
#  pragma pop_macro("GeometryVerticesOut")
# else
	 , GeometryVerticesOut(_base())
# endif
#endif
#if defined GL_GEOMETRY_INPUT_TYPE
# if defined GeometryInputType
#  pragma push_macro("GeometryInputType")
#  undef GeometryInputType
	 , GeometryInputType(_base())
#  pragma pop_macro("GeometryInputType")
# else
	 , GeometryInputType(_base())
# endif
#endif
#if defined GL_GEOMETRY_OUTPUT_TYPE
# if defined GeometryOutputType
#  pragma push_macro("GeometryOutputType")
#  undef GeometryOutputType
	 , GeometryOutputType(_base())
#  pragma pop_macro("GeometryOutputType")
# else
	 , GeometryOutputType(_base())
# endif
#endif
	{ }
};

} // namespace enums

