#version 330
//openGL�� ���� 
//������ �ö󰥼��� �Լ����� ������ 


//vertexShader�� ���� �޴´�. 
// ���Ŀ� fshader�� ����

in vec4 vPosition;
in vec4 vColor;

out vec4 color;

void main()
{
	//gl_Position �� ȭ����� ��ġ�� ���������̴�. �� �������. 
	gl_Position = vPosition;
	color = vColor;
}