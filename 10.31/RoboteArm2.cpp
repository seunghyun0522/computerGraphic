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

#include <list>

void myDisplay()
{

	std::list<mat4> matrixStack;


	float ang1 = 45*sin(2*3.141592*g_Time);
	float ang2 = 60 *sin(3.141592 * g_Time);
	float ang3 = 30 * sin(2*3.141592 * g_Time);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	GLuint uMat = glGetUniformLocation(program, "uMat");

	mat4 CTM(1.0);					// current transform matrix
	CTM = Translate(0, -0.5f, 0) * RotateY(90 * g_Time);
	matrixStack.push_back(CTM);


	//Base
	matrixStack.push_back(CTM);
	mat4 M(1.0);
	M = Scale(0.4, 0.3, 0.2);	//r가로 세로 깊이 
	glUniformMatrix4fv(uMat, 1, true, CTM * M);
	pyramid.Draw(program);


	//Upper arm
	matrixStack.push_back(CTM);
	CTM *= Translate(0,0.1,0)*RotateZ(ang1);
	M = Translate(0,0.2,0)*Scale(0.1, 0.4, 0.1);
	glUniformMatrix4fv(uMat, 1, true, CTM * M);
	cube.Draw(program);


	//MIDDLE ARM
	matrixStack.push_back(CTM);
	CTM *= Translate(0, 0.4, 0)*RotateZ(ang2);
	M = Translate(0,0.05,0)*Scale(0.4, 0.1, 0.1);
	glUniformMatrix4fv(uMat, 1, true, CTM * M);
	cube.Draw(program);



	//LOWER ARM1
	matrixStack.push_back(CTM);
	CTM *= Translate(-0.2, 0.1, 0)*RotateZ(ang3);
	M = Translate(0, 0.2, 0) * Scale(0.1, 0.4, 0.1);
	glUniformMatrix4fv(uMat, 1, true, CTM * M);
	cube.Draw(program);

	//back to center of middle arm
	CTM = matrixStack.back();
	matrixStack.pop_back();

	//LOWER ARM2
	matrixStack.push_back(CTM);
	CTM *= Translate(0.2, 0.1, 0) * RotateZ(-ang3);
	M = Translate(0, 0.2, 0) * Scale(0.1, 0.4, 0.1);
	glUniformMatrix4fv(uMat, 1, true, CTM * M);
	cube.Draw(program);
	matrixStack.push_back(CTM);
	glutSwapBuffers();

}

void myIdle()
{
	g_Time += 0.016f;
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
