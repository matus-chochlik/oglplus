#version 330

in vec3 vertTexCoord;
in float vertValue;

out vec3 fragColor;

void main(void)
{
	fragColor = vec3(vertValue, vertTexCoord.x, 0.0);
}

