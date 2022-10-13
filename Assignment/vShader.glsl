#version 330

in vec4 vPosition;
in vec4 vColor;

uniform float uTime;
uniform float uWave;


out vec4 color;
out float height;


void main()
{


/*
	float mat[2][2];
	[a  b]		[0][0]   [0][1]		// row major
	[c  d]      [1][0]   [1][1]
	|a  b|		[0][0]	 [1][0]		// column major
	|c  d|		[0][1]   [1][1]
*/

	float angle1 = 46.0f;
	float rad1 = angle1 /180.0f * 3.141592f;

	float angle2 =  uTime * 5.0f;
	float rad2 = angle2 / 180.0f * 3.141592f;

	mat4 rotX = mat4(1.0f);		
	//mat4 rotY = mat4(1.0f);
	mat4 rotZ = mat4(1.0f);

	mat4 wave = mat4(1.0f);
/*
	mat4[j][i]:			row i, col j
	[0][0]	[1][0]	[2][0]	[3][0]
	[0][1]	[1][1]	[2][1]	[3][1]
	[0][2]	[1][2]	[2][2]	[3][2]
	[0][3]	[1][3]	[2][3]	[3][3]
*/

	rotX[1][1] = cos(rad1);	rotX[2][1] = -sin(rad1);
	rotX[1][2] = sin(rad1);	rotX[2][2] = cos(rad1);
/*	
	rotY[0][0] = cos(rad2);	rotY[2][0] = sin(rad2);
	rotY[0][2] =-sin(rad2);	rotY[2][2] = cos(rad2);
*/
	rotZ[0][0] = cos(rad2);	rotZ[1][0] = -sin(rad2);
	rotZ[0][1] = sin(rad2);	rotZ[1][1] = cos(rad2);

	float distance = (vPosition.x * vPosition.x + vPosition.y * vPosition.y);
	
	int waveDepth= 40;

	if (distance <= 0.5f && uWave >= 1.0)
	{
		wave[3][2] = sin((uTime +(distance  * waveDepth))) * 0.4;
		wave[3][2] = wave[3][2] * (0.7 - distance * 1.5);
	}
	vec4 wPos = rotX*rotZ*wave*vPosition;

	wPos.z = wPos.z;
	gl_Position = wPos;
	color = vColor;
	height = wave[3][2];
}