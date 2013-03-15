#version 330

uniform mat4 TransfMatrix;

in vec4 Position;
in vec2 TexCoord;

out vec3 vertTexCoord;
out float vertValue;

void main(void)
{
	vec4 OffsPos = Position;
	OffsPos.x += gl_InstanceID;
	OffsPos.y += sin(OffsPos.x*12.0+OffsPos.z*8)*0.1+0.5;
	gl_Position = TransfMatrix * OffsPos;
	vertTexCoord = vec3(TexCoord, gl_InstanceID);
	vertValue = OffsPos.y;
}

