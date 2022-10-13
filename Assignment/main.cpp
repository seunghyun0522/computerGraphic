#include <vgl.h>
#include <InitShader.h>
#include <vec.h>
#include "MyPlain.h"

//
#define Q 113
#define W 119
#define ONE 49
#define TWO 50
#define SPACEBAR 32

float gTime = 0.0f;
GLuint prog;
MyPlain plain;
bool gWave = false;
bool Reverse = false;

void init()
{
	plain.init();
	prog = InitShader("vShader.glsl", "fShader.glsl");
	glUseProgram(prog);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glUseProgram(prog);
	GLuint uTime = glGetUniformLocation(prog, "uTime");
	glUniform1f(uTime, gTime);
	GLuint uWave = glGetUniformLocation(prog, "uWave");
	glUniform1f(uWave, gWave);
	plain.draw(prog, gTime, gWave);
	glFlush();
}

void myIdle()
{
	if (Reverse) {
		gTime += 0.001f;
		//printf("time = %f\n", gTime);
		//Sleep(16);				// 16 msec = 1/60 sec = 60 Hz
		glutPostRedisplay();
	}
}

void changeReverse() {
	Reverse = !Reverse;
}
void updateRectangle(int _value) {
	plain.update(_value);

	if (!Reverse) {
		glutPostRedisplay();
	}
}
void keyDownInput(unsigned char key, int x, int y) {
	printf("Division : %d , Num. of Triangles : %d , Num of Vertices: %d\n", plain.Division, plain.rectangleNum*2, plain.numVertices);
	switch (key) {
	case Q:
		exit(0);
		break;
	case ONE:
		updateRectangle(-1);
		break;
	case TWO:
		updateRectangle(1);
		break;
	case SPACEBAR:
		changeReverse();
		break;
	case W:
		gWave = !gWave;
		glutPostRedisplay();
		break;
	}
	
}

void print() {
	printf("A Waving Color Plain\n");
	printf("Programming Assignment #1 for Computer Graphics\n");
	printf("Department of Software, Sejong University\n");
	printf("\n");
	printf("----------------------------------------------------------------\n");
	printf("`1' key: Decreaing the Number of Division\n");
	printf("`2' key: Increaing the Number of Division\n");
	printf("`w' key: Showing/hiding the waving pattern\n");
	printf("Spacebar: starting/stoping rotating and waving\n");
	printf("\n");
	printf("`Q' Key: Exit the program.\n");
	printf("----------------------------------------------------------------\n");
	printf("\n");
	printf("Division : %d , Num. of Triangles : %d , Num of Vertices: %d\n", plain.Division, plain.rectangleNum * 2, plain.numVertices);
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(512, 512);
	glutCreateWindow("Waving Plain");
	print();
	glewExperimental = true;
	glewInit();
	init();
	glutIdleFunc(myIdle);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyDownInput);
	glutMainLoop();

	return 0;
}