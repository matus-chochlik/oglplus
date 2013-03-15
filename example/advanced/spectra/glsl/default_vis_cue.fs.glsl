#version 330

uniform vec3 Color;
uniform float Alpha;

out vec4 fragColor;

void main(void)
{
	fragColor = vec4(Color, Alpha);
}

