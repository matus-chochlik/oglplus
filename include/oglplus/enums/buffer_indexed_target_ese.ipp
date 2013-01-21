/*
 *  .file oglplus/enums/buffer_indexed_target_ese.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/buffer_indexed_target.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if defined GL_ATOMIC_COUNTER_BUFFER
# if defined AtomicCounter
#  pragma push_macro("AtomicCounter")
#  undef AtomicCounter
   OGLPLUS_ENUM_CLASS_VALUE(AtomicCounter, GL_ATOMIC_COUNTER_BUFFER)
#  pragma pop_macro("AtomicCounter")
# else
   OGLPLUS_ENUM_CLASS_VALUE(AtomicCounter, GL_ATOMIC_COUNTER_BUFFER)
# endif
#endif
#if defined GL_SHADER_STORAGE_BUFFER
# if defined ShaderStorage
#  pragma push_macro("ShaderStorage")
#  undef ShaderStorage
   OGLPLUS_ENUM_CLASS_VALUE(ShaderStorage, GL_SHADER_STORAGE_BUFFER)
#  pragma pop_macro("ShaderStorage")
# else
   OGLPLUS_ENUM_CLASS_VALUE(ShaderStorage, GL_SHADER_STORAGE_BUFFER)
# endif
#endif
#if defined GL_TRANSFORM_FEEDBACK_BUFFER
# if defined TransformFeedback
#  pragma push_macro("TransformFeedback")
#  undef TransformFeedback
   OGLPLUS_ENUM_CLASS_VALUE(TransformFeedback, GL_TRANSFORM_FEEDBACK_BUFFER)
#  pragma pop_macro("TransformFeedback")
# else
   OGLPLUS_ENUM_CLASS_VALUE(TransformFeedback, GL_TRANSFORM_FEEDBACK_BUFFER)
# endif
#endif
#if defined GL_UNIFORM_BUFFER
# if defined Uniform
#  pragma push_macro("Uniform")
#  undef Uniform
   OGLPLUS_ENUM_CLASS_VALUE(Uniform, GL_UNIFORM_BUFFER)
#  pragma pop_macro("Uniform")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Uniform, GL_UNIFORM_BUFFER)
# endif
#endif
