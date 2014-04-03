/*  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#version 330
uniform sampler2DRect RaytraceOutput;
uniform float Near, Far;
uniform float PlanetRadius, AtmThickness;
uniform vec3 LightPos;

const vec3 LightColor = vec3(1, 1, 1);
const vec3 AirColor = vec3(0.28, 0.38, 0.62);
const vec3 HazeColor = vec3(0.75, 0.77, 0.85);

in vec3 vertRay;
in vec2 vertTexCoord;

out vec3 fragColor;

float atm_intersection(vec3 v)
{
	vec3 c = vec3(0.0, -PlanetRadius, 0.0);
	float r = PlanetRadius + AtmThickness;
	float c_c = dot(-c, -c);
	float v_c = dot( v, -c);
	return (-v_c + sqrt(v_c*v_c - c_c + r*r))/AtmThickness;
}

vec2 ssao_neighbor(vec2 offs, float dist)
{
	vec2 sam = texture(RaytraceOutput, vertTexCoord+offs).xw;
	float d = sam.x - dist;
	float e = abs(d*5);

	return vec2(sign(d)*e*exp(-e), sam.y);
}

void main(void)
{
	vec4 rt = texture(RaytraceOutput, vertTexCoord);
	vec3 up = vec3(0.0, 1.0, 0.0);
	vec3 ld = normalize(LightPos);
	vec3 rd = normalize(vertRay);

	float lt = rt.z;
	float lr = dot(ld, rd);
	float ur = dot(up, rd);
	float ul = dot(up, ld);
	float ai = atm_intersection(rd);
	float hr = (1.0-abs(ur));
	float iai = clamp(1.4/ai, 0, 1);
	float lai = log(ai);
	float ctl = pow(max(lr+0.3, 0.0), 2);
	float crl = mix(0.7, 1.1, rt.y);

	vec2 ndv = vec2(0, 0);

	ndv += ssao_neighbor(vec2(-1,-1), rt.x);
	ndv += ssao_neighbor(vec2(-1, 0), rt.x);
	ndv += ssao_neighbor(vec2(-1, 1), rt.x);
	ndv += ssao_neighbor(vec2( 0,-1), rt.x);
	ndv += ssao_neighbor(vec2( 0, 1), rt.x);
	ndv += ssao_neighbor(vec2( 1,-1), rt.x);
	ndv += ssao_neighbor(vec2( 1, 0), rt.x);
	ndv += ssao_neighbor(vec2( 1, 1), rt.x);

	float dd = (rt.w*ndv.x)/(max(ndv.y, 0.00001)*rt.x);

	lt += 2.81*dd;
	lt = clamp(lt, 0, 1);

	float eid = exp(-(2.0*rt.x-Near)/(Far-Near));
	eid += dd;

	float dc = (0.8+0.2*rt.z)*(2.60*eid);
	dc *= rt.w;

	vec3 Air1 =
		mix(HazeColor, AirColor, iai)*
		sqrt(max(ul+0.3, 0.0))*
		mix(0.9, 1.0, min(abs(lr+0.6), 1.0));
	Air1 *= crl;

	vec3 Air2 =
		max(LightColor-AirColor*lai*crl, vec3(0))*pow(
			max(abs(lr+mix(0.00, 0.57, iai))-mix(0.00, 0.48, iai), 0.0),
			mix(0.25, 4.0, mix(hr, lai, 0.2))
		)*hr;
	Air2 *= crl;

	vec3 Air3 =
		(LightColor-AirColor*lai*0.4)*
		pow(max(lr+mix(0.0015, 0.0004, iai), 0.0), mix(256, 1024, hr));

	vec3 CloudsDk = mix(
		(LightColor-AirColor*mix(1.0-ul, lai, 0.4))*ctl*2.31,
		(LightColor-AirColor*lai*0.3)*sqrt(max(ul+0.6, 0.0))*0.55,
		mix(1.0, rt.w, min(ctl, 1.0))
	);

	vec3 CloudsLt = LightColor-AirColor*lai*0.2;

	vec3 Clouds = mix(
		CloudsDk,
		CloudsLt*sqrt(0.7+ul*0.5),
		lt*mix(mix(0.2, 0.9, eid), 1.0, crl)
	);

	fragColor = mix(Air1+Air2+Air3, Clouds, clamp(dc, 0, 1));
}
