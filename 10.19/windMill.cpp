#include <vgl.h>
#include <InitShader.h>
#include <mat.h>
#include "MyCube.h"
#include "MyPyramid.h"

MyCube cube;
MyPyramid pyramid;

GLuint program;
GLuint uMat;

mat4 g_Mat = mat4(1.0);

float g_Time = 0;

void myInit()
{
	cube.Init();
	pyramid.Init();

	program = InitShader("vshader.glsl", "fshader.glsl");
	glUseProgram(program);
}



void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	GLuint uMat = glGetUniformLocation(program, "uMat");

	//1.0을 넣는 것은 대각선이 1이고 단위행렬을 만드는 것이다. 
	mat4 CTM(1.0);
	CTM= RotateY(90 * g_Time);
	//피라미드
	mat4 M(1.0);	// current transform matrix
	M = Scale(0.5, 1, 0.4);	//가로 0.5 세로 1 z 0.4 길이 

	//오른쪽에서 왼쪽으로 rotate
	// Rotate!
	// Scale
	//translate
	// 순서는 t- r -s 순으로
	/*
	M = Translate(0.2, 0.4, 0)
		*RotateZ(90 * g_Time) 
		* RotateY(90 * g_Time) 
		* Scale(1,1, 0.1);
	*/

	//uMat 에 해당하는 변수를 float, pointer 형태로  1개를 보내고 
	// 완성된 CTM을 M에 곱해준다.
	glUniformMatrix4fv(uMat, 1, true, CTM*M);
	//M[i][j];	// c : row major M[row][col]
	//			shader: col major M[col][row]
	pyramid.Draw(program);

	CTM *= Translate(0, 0.25, 0.25) * RotateZ(180 * g_Time);

	// 날개 가로
	M = Scale(0.8, 0.1, 0.1);
	glUniformMatrix4fv(uMat, 1, true,  CTM*M);
	cube.Draw(program);
	// 날개 세로
	M = RotateZ(90) * Scale(0.8, 0.1, 0.1);
	glUniformMatrix4fv(uMat, 1, true, CTM*M);
	cube.Draw(program);
	//중심부
	M = Scale(0.15, 0.15, 0.15);
	glUniformMatrix4fv(uMat, 1, true, CTM * M);
	cube.Draw(program);
	glutSwapBuffers();
}

//컴퓨터가 쉬고 있을 때 마다 활동
void myIdle()
{
	g_Time += 0.016f; // 실제 시간.
	Sleep(16);
	glutPostRedisplay();
}



int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Cube and Pyramid");

	glewExperimental = true;
	glewInit();

	myInit();
	glutDisplayFunc(myDisplay);
	glutIdleFunc(myIdle);

	glutMainLoop();

	return 0;
}