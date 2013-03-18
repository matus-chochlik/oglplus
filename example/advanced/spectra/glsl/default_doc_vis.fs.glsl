/*
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#version 330

float SpectrumValue(vec3 coord);

in vec3 vertTexCoord;
in float vertValue;

out vec3 fragColor;

void main(void)
{
	fragColor = vec3(vertTexCoord.y*0.1, vertValue, -vertValue);
}

