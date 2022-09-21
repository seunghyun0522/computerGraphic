// GLUT 화면에 창을 띄우고 openGL의 운영체제마다 라이브러리  플랫폼 동일
//
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <stdio.h>
#include <stdlib.h>


struct vec2
{
    float x;
    float y;
};

const int NUM_POINTS = 60000;
vec2 points[NUM_POINTS];

void init()
{
    for (int i = 0; i < NUM_POINTS; i++)
    {
        float x = (rand() % 1000) / 1000.0f*2.0f - 1.0f;
        float y = (rand() % 1000) / 1000.0f*2.0f - 1.0f;
        points[i].x = x;
        points[i].y = y;
    }
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    // GL_TRIANGLES            : 3 개씩 처리
    // GL_LINES                : 2 개씩 처리
    // GL_POINTS            : 1 개씩 처리
    glBegin(GL_POINTS);
    for (int i = 0; i < NUM_POINTS; i++)
        glVertex2f(points[i].x, points[i].y);
    glEnd();
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(512, 512);
    glutCreateWindow("Hello GL");

    glewExperimental = true;
    glewInit();
    printf("OpenGl Version: %s\n", glGetString(GL_VERSION));
    printf("GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
