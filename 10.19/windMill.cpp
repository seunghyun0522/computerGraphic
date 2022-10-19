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

	//1.0�� �ִ� ���� �밢���� 1�̰� ��������� ����� ���̴�. 
	mat4 CTM(1.0);
	CTM= RotateY(90 * g_Time);
	//�Ƕ�̵�
	mat4 M(1.0);	// current transform matrix
	M = Scale(0.5, 1, 0.4);	//���� 0.5 ���� 1 z 0.4 ���� 

	//�����ʿ��� �������� rotate
	// Rotate!
	// Scale
	//translate
	// ������ t- r -s ������
	/*
	M = Translate(0.2, 0.4, 0)
		*RotateZ(90 * g_Time) 
		* RotateY(90 * g_Time) 
		* Scale(1,1, 0.1);
	*/

	//uMat �� �ش��ϴ� ������ float, pointer ���·�  1���� ������ 
	// �ϼ��� CTM�� M�� �����ش�.
	glUniformMatrix4fv(uMat, 1, true, CTM*M);
	//M[i][j];	// c : row major M[row][col]
	//			shader: col major M[col][row]
	pyramid.Draw(program);

	CTM *= Translate(0, 0.25, 0.25) * RotateZ(180 * g_Time);

	// ���� ����
	M = Scale(0.8, 0.1, 0.1);
	glUniformMatrix4fv(uMat, 1, true,  CTM*M);
	cube.Draw(program);
	// ���� ����
	M = RotateZ(90) * Scale(0.8, 0.1, 0.1);
	glUniformMatrix4fv(uMat, 1, true, CTM*M);
	cube.Draw(program);
	//�߽ɺ�
	M = Scale(0.15, 0.15, 0.15);
	glUniformMatrix4fv(uMat, 1, true, CTM * M);
	cube.Draw(program);
	glutSwapBuffers();
}

//��ǻ�Ͱ� ���� ���� �� ���� Ȱ��
void myIdle()
{
	g_Time += 0.016f; // ���� �ð�.
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