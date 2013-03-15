#version 330

uniform mat4 TransfMatrix;

in vec4 Position;

void main(void)
{
	vec4 OffsPos = Position;
	OffsPos.x += gl_InstanceID;
	gl_Position = TransfMatrix * OffsPos;
}

