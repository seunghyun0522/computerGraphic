#version 330

in vec4 vPosition;  // in ����    
out vec4 pos;   //fShader �� in���� ���� -> fshader ������ �̵�

void main()
{
	gl_Position = vPosition*0.5;     //vShader ������ �ڵ�
    gl_Position.w =1.0f;
    pos = vPosition;    //fShader�� ���� ���� 
    //glsl language �̴�. vs ���� compile�� ������ ���� ����.
    
    // ��ǥ�� 0.5 ��ŭ ������ �� ���̴�. ��ü ȭ���� 0.5 ������ ���
    // shader �� �ٲ� �����̴�. 

}