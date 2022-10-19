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

	mat4 CTM(1.0);
	CTM = Translate(0,-0.5f,0)*RotateY(90 * g_Time);

	mat4 M(1.0);	// current transform matrix
	M = Scale(0.4, 0.3, 0.2);
	glUniformMatrix4fv(uMat, 1, true, CTM * M);
	pyramid.Draw(program);

	CTM *= RotateZ(45*g_Time)*Translate(0,0.2f, 0);
	M = Scale(0.1, 0.4, 0.1);
	glUniformMatrix4fv(uMat, 1, true, CTM * M);
	cube.Draw(program);

	CTM *= RotateZ(-45*g_Time)*Translate(0, 0.4f, 0);
	M = Scale(0.15, 0.4, 0.15);
	glUniformMatrix4fv(uMat, 1, true, CTM * M);
	cube.Draw(program);

	CTM *= Translate(0, 0.3f, 0);
	M = Scale(0.3, 0.2, 0.2);
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