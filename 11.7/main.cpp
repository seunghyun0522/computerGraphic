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
float g_aspect = 1.0f;

void myInit()
{
	cube.Init();
	pyramid.Init();

	program = InitShader("vshader.glsl", "fshader.glsl");
	glUseProgram(program);
}

mat4 myLookAt(vec3 e, vec3 f, vec3 u)
{
	// 1. Rw
//	vec3 n = f - e;
//	n = n / length(n);
	vec3 n = normalize(f - e);					// -z
	float a = dot(u, n);
	vec3 v = normalize(u - a * n);				// y
	vec3 w = cross(v, -n);						// x

	mat4 Rw(1.0f);
	Rw[0][0] = w.x;	Rw[0][1] = v.x; Rw[0][2] = -n.x;
	Rw[1][0] = w.y;	Rw[1][1] = v.y; Rw[1][2] = -n.y;
	Rw[2][0] = w.z;	Rw[2][1] = v.z; Rw[2][2] = -n.z;

	// 2. Rc
	mat4 Rc(1.0f);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			Rc[i][j] = Rw[j][i];

	// 3. Tc
	mat4 Tc = Translate(-e.x, -e.y, -e.z);
	// 4. V = Rc Tc
	mat4 V = Rc * Tc;
	return V;
}

mat4 myOrtho(float xmin, float xmax,
			 float ymin, float ymax, 
			 float nearr, float ffar) 
{
	mat4 m;

	float ox = (xmin + xmax) / 2;
	float oy = (ymin + ymax) / 2;
	//float oz = -1.0f*(nearr + ffar) / 2;
	float oz = -1.0f * (nearr);

	mat4 T = Translate(-ox, -oy, -oz);

	float sx = (xmax - xmin);
	float sy = (ymax - ymin);
	float sz = (ffar - nearr);

	mat4 S = Scale(2 / sx, 2 / sy, 1 / sz);
	
	m = S * T;
	return m;
}

void myDisplay()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	GLuint uMat = glGetUniformLocation(program, "uMat");

	mat4 V(1.0);

	float angle = g_Time * 3.141592 / 8.0f;
	float height = 4 + 4 * sin(angle);

	vec3 e = vec3(5 * sin(angle), height, 5 * cos(angle));
	vec3 f = vec3(0, 0, 0);
	vec3 u = vec3(0, 1, 0);


	V = myLookAt(e, f, u);

	mat4 P(1.0);	//projection matrix
	float size = 2;
	P = myOrtho(-size*g_aspect,size * g_aspect,-size,size,1,100); // left,right, bottom,top, near,far


	glUniformMatrix4fv(uMat, 1, true, P*V);

	//pyramid.Draw(program);
	cube.Draw(program);

	glutSwapBuffers();
}

void myIdle()
{
	g_Time += 0.1f;
	Sleep(16);
	glutPostRedisplay();
}


void myReshape(int wx, int wy)
{
	printf("window size = %d, %d \n",wx,wy);
	glViewport(0, 0, wx, wy);
	g_aspect = (float)wx / (float)wy;
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
	glutReshapeFunc(myReshape);	//콘솔의 크기에 따라 변함
	glutMainLoop();

	return 0;
}
