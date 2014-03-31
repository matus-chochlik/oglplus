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

	float cd = rt.x;
	float mnd = 0.1;
	vec2 ndv, nds;

	nds = texture(RaytraceOutput, vertTexCoord+vec2(-1,-1)).xz;
	ndv += vec2(clamp(nds.x-cd,-mnd, mnd)*nds.y, nds.y);
	nds = texture(RaytraceOutput, vertTexCoord+vec2(-1, 0)).xz;
	ndv += vec2(clamp(nds.x-cd,-mnd, mnd)*nds.y, nds.y);
	nds = texture(RaytraceOutput, vertTexCoord+vec2(-1, 1)).xz;
	ndv += vec2(clamp(nds.x-cd,-mnd, mnd)*nds.y, nds.y);
	nds = texture(RaytraceOutput, vertTexCoord+vec2( 0,-1)).xz;
	ndv += vec2(clamp(nds.x-cd,-mnd, mnd)*nds.y, nds.y);
	nds = texture(RaytraceOutput, vertTexCoord+vec2( 0, 1)).xz;
	ndv += vec2(clamp(nds.x-cd,-mnd, mnd)*nds.y, nds.y);
	nds = texture(RaytraceOutput, vertTexCoord+vec2( 1,-1)).xz;
	ndv += vec2(clamp(nds.x-cd,-mnd, mnd)*nds.y, nds.y);
	nds = texture(RaytraceOutput, vertTexCoord+vec2( 1, 0)).xz;
	ndv += vec2(clamp(nds.x-cd,-mnd, mnd)*nds.y, nds.y);
	nds = texture(RaytraceOutput, vertTexCoord+vec2( 1, 1)).xz;
	ndv += vec2(clamp(nds.x-cd,-mnd, mnd)*nds.y, nds.y);

	lt += (1.5*ndv.x)/max(ndv.y,0.001);
	lt = clamp(lt, 0, 1);

	vec3 Air1 =
		mix(HazeColor, AirColor, iai)*
		sqrt(max(ul+0.3, 0.0))*
		mix(0.7, 1.0, min(abs(lr+0.6), 1.0));
	Air1 *= crl;

	vec3 Air2 =
		max(LightColor-AirColor*lai*crl, vec3(0))*pow(
			max(abs(lr+mix(0.00, 0.57, iai))-mix(0.00, 0.48, iai), 0.0),
			mix(0.25, 4.0, mix(hr, lai, 0.2))
		)*hr;
	Air2 *= crl;

	vec3 Air3 =
		(LightColor-AirColor*lai*0.4)*
		pow(max(lr+mix(0.0020, 0.0005, iai), 0.0), mix(256, 1024, hr));

	vec3 CloudsDk = mix(
		(LightColor-AirColor*mix(1.0-ul, lai, 0.4)*1.0)*ctl*2.41,
		(LightColor-AirColor*lai*0.3)*sqrt(max(ul+0.6, 0.0))*0.75,
		mix(1.0, rt.w, min(ctl, 1.0))
	);

	vec3 CloudsLt =
		LightColor-AirColor*lai*0.2*sqrt(max(ul+0.3, 0));

	vec3 Clouds = mix(CloudsDk, CloudsLt*sqrt(1+ul), lt*crl);

	float cl = length(Clouds);

	fragColor = mix(
		mix(Air1+Air2+Air3, Clouds, clamp(rt.w, 0, 1)),
		Air1+Air2*cl*(1.2-lr)*0.5,
		clamp(rt.w*(1-exp(-rt.x/(Far*0.5))), 0, 1)
	);
}
