/*
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#version 330

float SpectrumValue(vec3 coord);

in vec3 vertTexCoord;
in float vertValue;
in float vertHighlight;
in float vertSelection;

out vec3 fragColor;

void main(void)
{
	fragColor = mix(
		mix(
			vec3(0.0, vertTexCoord.y*0.3, 1.0),
			vec3(1.0, vertTexCoord.y*0.3, 0.0),
			vertValue
		),
		vec3(1.0, 1.0, 1.0),
		vertHighlight+vertSelection*0.2
	);
}

