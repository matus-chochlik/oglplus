/*
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_Context_example_1

__Context gl; /*<
Stateless wrapper for the current GL context operations.
>*/

gl.ClearColor(0.3f, 0.3f, 0.3f, 0.0f);
gl.ClearDepth(1.0f);
gl.Disable(__Capability::DepthTest);
gl.Enable(Capability::Blend);
gl.BlendFunc(__BlendFunction::SrcAlpha, BlendFunction::OneMinusSrcAlpha);

gl.LineWidth(1.5f);

gl.Viewport(800, 600);

gl.Clear().ColorBuffer().DepthBuffer().StencilBuffer();

__Program prog;
__VertexArray vao;

/* ... */

gl.Use(prog);
gl.Bind(vao);

gl.DrawArrays(__PrimitiveType::TriangleStrip, 0, n);

gl.DrawElements(__PrimitiveType::TriangleStrip, m, __DataType::UnsignedInt);

//]

