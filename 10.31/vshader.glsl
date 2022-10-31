#version 330

in  vec4 vPosition;
in  vec4 vColor;
out vec4 color;

uniform mat4 uMat;

void main()
{
	gl_Position  = uMat*vPosition;

    color = vColor;
}
