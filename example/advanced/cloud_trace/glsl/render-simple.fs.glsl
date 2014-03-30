/*  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#version 330
uniform sampler2DRect RaytraceOutput;
uniform float Far;
uniform vec3 LightPos;

in vec3 vertRay;
in vec2 vertTexCoord;
out vec3 fragColor;

void main(void)
{
	vec4 rt = texture(RaytraceOutput, vertTexCoord);
	vec3 ld = normalize(LightPos);
	vec3 rd = normalize(vertRay);
	vec3 bc1 = vec3(0.3, 0.3, 0.6);
	vec3 bc2 = vec3(0.4, 0.4, 0.9);
	vec3 bc = mix(bc1, bc2, abs(dot(ld, rd)+0.2));

	float cl = mix(0.5, 1.0, rt.z);
	vec3 cc = vec3(cl);
	fragColor = mix(bc, cc, clamp(rt.w-(rt.x/(mix(0.5, 2, cl)*Far)), 0, 1));

}
