/*
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_Context
namespace oglplus {

class Context
 : public __context_Errors
 , public __context_Capabilities
 , public __context_ViewportOps
 , public __context_BufferSelection
 , public __context_BufferMasking
 , public __context_BufferClearing
 , public __context_Rasterization
 , public __context_Drawing
 , public __context_Computing
 , public __context_DepthTest
 , public __context_StencilTest
 , public __context_ScissorTest
 , public __context_LogicalOps
 , public __context_PixelOps
 , public __context_Blending
 , public __context_Synchronization
 , public __context_Hints
 , public __context_LimitQueries
 , public __context_NumericQueries
 , public __context_StringQueries
 , public __context_ObjectBinding
 , public __context_ObjectDSA
{ };

} // namespace oglplus
//]

