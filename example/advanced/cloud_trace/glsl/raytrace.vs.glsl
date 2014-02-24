/*  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#version 330

uniform mat3 RayMatrix;

in vec2 Position;
out vec3 vertRay;

void main(void)
{
	gl_Position = vec4(Position, 0, 1);
	vertRay = RayMatrix * vec3(Position, 1);
}
