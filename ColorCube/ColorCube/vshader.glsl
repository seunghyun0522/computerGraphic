#version 330
//openGL의 버전 
//버전이 올라갈수록 함수들이 많아짐 


//vertexShader가 먼저 받는다. 
// 그후에 fshader로 연결

in vec4 vPosition;
in vec4 vColor;

out vec4 color;

void main()
{
	//gl_Position 은 화면상의 위치의 전역변수이다. 꼭 쎃어야함. 
	gl_Position = vPosition;
	color = vColor;
}