#version 330

uniform mat4 ProjectionMatrix, CameraMatrix;

in vec4 Position;

void main(void)
{
	 gl_Position = ProjectionMatrix* CameraMatrix* Position;
}

