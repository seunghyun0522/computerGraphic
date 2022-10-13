#version 330

in vec4 color;
//�ĵ��� ���̸� ������ �� �ִ� ���� height�� ����
in float height;

out vec4 fColor;

uniform float uTime;

void main()
{


	//	float avg = (color.r + color.g + color.b)/3;
	//	avg *= (sin(uTime)/2 + 0.5);
	//	fColor = vec4(avg, avg, avg, 1);

	fColor = color;
		
		
/*
	if(position.z < -0.45 || position.z > 0.45 )
		fColor = vec4(0,1,0,1);
	if(position.x < -0.45 || position.x > 0.45 )
	{
		if(position.y < -0.45 || position.y > 0.45 )
			fColor = vec4(0,1,0,1);
		if(position.z < -0.45 || position.z > 0.45 )
			fColor = vec4(0,1,0,1);
	}
*/
	if(height >= 0.0)
		fColor = color + vec4(1/7, 1, 1.0, 1.0) * height*3;
		
	else
		fColor = color + vec4(-1/3, -0.5, 0.5, 1.0) * height * 3;

}