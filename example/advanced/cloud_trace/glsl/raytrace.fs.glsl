/*  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#version 330
#define MaxClouds 1024
#define N 64
#define K 2

uniform sampler3D CloudTex;
uniform int CloudCount;
layout (std140)
uniform CloudBlock
{
	mat4 CloudMatrices[MaxClouds];
};

uniform vec3 LightPos;
uniform float HighLight;
uniform float AmbiLight;
uniform float UnitOpacity;
uniform float UnitAttenuation;

in vec3 vertRay;
out vec4 fragColor;

vec4 sphere_geom(int idx)
{
	return transpose(CloudMatrices[idx])[3];
}

vec3 sphere_para(int idx)
{
	return CloudMatrices[idx][3].xyz;
}

mat3 sphere_rot(int idx)
{
	return mat3(CloudMatrices[idx]);
}

vec2 ray_sphere_hit(vec3 o, vec3 d, int idx)
{
	vec4 s = sphere_geom(idx);
	float r = s.w;
	vec3 v = o-s.xyz;
	float dv = dot(d,v);
	float vv = dot(v,v);
	float rr = r*r;
	float x = dv*dv-vv+rr;
	return vec2(dv, x);
}

vec3 sphere_point_coord(vec3 x, int idx)
{
	vec4 s = sphere_geom(idx);
	mat3 r = sphere_rot(idx);
	x -= s.xyz;
	x /= 2.0;
	x /= s.w;
	x = r*x;
	x += 0.5;
	return x;
}

const float maxt = 1e9;
float tmin[K], tmax[K];
vec3 hits[K*N];
vec3 wc0[K*N], wc1[K*N], tc0[K*N], tc1[K*N];

int find_hits(int k, vec3 ori, vec3 ray)
{
	tmin[k] = maxt;
	tmax[k] = 0;
	int n = 0, i = 0;
	while(i < CloudCount)
	{
		vec2 h = ray_sphere_hit(ori, ray, i);
		if(h.y >= 0)
		{
			h.y = sqrt(h.y);
			float tn = -h.x-h.y;
			float tf = -h.x+h.y;
			if((tn >= 0.0) || (tf >= 0.0))
			{
				tmin[k] = min(tmin[k], max(0, tn));
				tmax[k] = max(tmax[k], max(0, tf));
				hits[k*N+n] = vec3(i, tn, tf);
				wc0[k*N+n] = ori+ray*tn;
				wc1[k*N+n] = ori+ray*tf;
				tc0[k*N+n] = sphere_point_coord(wc0[k*N+n], i);
				tc1[k*N+n] = sphere_point_coord(wc1[k*N+n], i);
				++n;
			}
		}
		++i;
	}
	return n;
}

vec4 sample_ray(int k, int n, float t, float dc)
{
	float sd = 0.0;
	float ts = 1.0;
	float tmin = tmin[k];
	float tmax = tmax[k];
	for(int i=0; i<n; ++i)
	{
		float tn = hits[k*N+i][1];
		float tf = hits[k*N+i][2];
		float td = tf-tn;
		float tm = 0.001;
		if((td > tm) && (tn <= t) && (tf >= t))
		{
			int id = int(hits[k*N+i][0]);
			float ssc = (t-tn)/td;
			vec3 sp = sphere_para(id);
			vec3 tc = mix(tc0[k*N+i], tc1[k*N+i], ssc);
			float ssd = max(texture(CloudTex, tc).r - sp[0], 0.0);
			sd += ssd * dc * sp[1];
			sd = min(sd, 1.0);

			vec3 tcd = abs(tc0[k*N+i]-tc1[k*N+i]);
			vec3 tsn = tcd*textureSize(CloudTex, 0);
			float nsam = ceil(max(max(tsn.x, tsn.y), tsn.z));
			ts = min(ts, td / nsam);
		}
		if(tn > t)
		{
			tmin = min(tmin, tn);
		}
		if(tf < t)
		{
			tmax = max(tmax, tf);
		}
	}
	return vec4(sd, ts, tmin, tmax);
}

void main(void)
{
	const vec3 ori0 = vec3(0);
	vec3 ray0 = normalize(vertRay);
	int n0 = find_hits(0, ori0, ray0);
	float t0 = tmin[0];
	tmin[0] = maxt;
	float tfirst = maxt, tlast = 0;
	float den0 = 0.0;
	while((t0 < tmax[0]) && (den0 < 1.0))
	{
		vec4 sr0 = sample_ray(0, n0, t0, UnitOpacity);
		if(sr0[0] > 0.0)
		{
			den0 += sr0[0];
			tfirst = min(tfirst, t0);
			tlast = t0;
		}
		if(sr0[1] < 1.0)
		{
			t0 += sr0[1];
		}
		else
		{
			t0 = sr0[2];
			tmin[0] = maxt;
		}
	}
	tfirst = max(tfirst, 0);
	float lt = 0.0;
	if(den0 > 0.0)
	{
		float first = 1.0;
		t0 = tlast;
		tmax[0] = 0.0;
		while(t0 >= tfirst)
		{
			vec4 sr0 = sample_ray(0, n0, t0, UnitOpacity);

			if(sr0[1] < 1.0)
			{
				t0 -= sr0[1];
			}
			else
			{
				t0 = min(sr0[3], t0-0.01);
				tmax[0] = 0.0;
			}

			vec3 ori1 = ori0+ray0*t0;
			vec3 ray1 = normalize(LightPos-ori1);
			int n1 = find_hits(1, ori1, ray1);

			float t1 = tmin[1];
			tmin[1] = maxt;
			float den1 = 0.0;
			while((t1 < tmax[1]) && (den1 < 1.0))
			{
				vec4 sr1 = sample_ray(1, n1, t1, UnitAttenuation);
				den1 += sr1[0];

				if(sr1[1] < 1.0)
				{
					t1 += sr1[1];
				}
				else
				{
					t1 = sr1[2];
					tmin[1] = maxt;
				}
			}
			lt = mix(
				mix(lt, mix(HighLight, AmbiLight, den1), sr0[0]),
				mix(mix(AmbiLight, HighLight, sr0[0]), AmbiLight, den1),
				first
			);
			first = 0;
		}
	}
	fragColor = vec4(lt, lt, lt, den0);
}
