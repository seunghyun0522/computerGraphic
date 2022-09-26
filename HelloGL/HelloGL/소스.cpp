// GLUT ȭ�鿡 â�� ���� openGL�� �ü������ ���̺귯��  �÷��� ����
//
#include <vgl.h>
#include <stdio.h>
#include <stdlib.h>
#include <InitShader.h>
struct vec2
{
    float x;
    float y;
};

const int NUM_POINTS = 60000;
vec2 points[NUM_POINTS];

void init()
{
    //1. Generate data in CPU
    for (int i = 0; i < NUM_POINTS; i++)
    {
        float x = (rand() % 1000) / 1000.0f * 2.0f - 1.0f;
        float y = (rand() % 1000) / 1000.0f * 2.0f - 1.0f;
        points[i].x = x;
        points[i].y = y;
    }
    ///2. Sending the data to GPU : VAO (vertex array obj)--> VBO(vertex buffer obj)
    ///
    //2-1. Create Vertex Array object
    GLuint vao;     //OpenGL Unsigned int ������ int
    // GLuint vao[3] �� ��� �ؿ��� 3,&vao
    // ��ǻ�Ϳ��� �޸𸮸� ������� -> ���� ���� �޸��� �ּҸ� �����ϴ� ��
    glGenVertexArrays(1, &vao);  //�迭�� ũ��� �ּ�
    glBindVertexArray(vao);     //Binding

    //2-2. Create Vertext Buffer object in the Vertex Array
    GLuint vbo;     //buffer Obj create
    glGenBuffers(1, &vbo); //numbers input
    glBindBuffer(GL_ARRAY_BUFFER, vbo);  //GL_ARRAY_BUFFER :vertex information

    //array �� �����ϴ� ���� binding
    //glBufferdata();
        //vertex�� ���� �Է�
        //����ü ���� float (8bytes) * �迭�� ������ 60000
        //���� ����ü ���� point �� �߰�
        //GL_STATIC_DRAW
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * NUM_POINTS, points, GL_STATIC_DRAW);
    //2-3. copy data in CPU into the buffer
    //CPU �� �ִ� binding �Ǿ� �ִ� buffer �� copy �̵�

    //3. Loading shaders
    GLuint prog =
        InitShader("vShader.glsl", "fShader.glsl");
    glUseProgram(prog);
    //4. Connect the shader with the data
    //vertex shader �� connect
    int vPosition = 0;
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));


}


void display()
{
    // ȭ�� �����
    glClear(GL_COLOR_BUFFER_BIT);

    // GL_TRIANGLES            : 3 ���� ó��
    // GL_LINES                : 2 ���� ó��
    // GL_POINTS            : 1 ���� ó��
    glDrawArrays(GL_POINTS, 0, NUM_POINTS);
    glFlush();

    /*
    Old skills

    glBegin(GL_POINTS);

    for (int i = 0; i < NUM_POINTS; i++)
        glVertex2f(points[i].x, points[i].y);
    glEnd();
    glFlush();*/
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(512, 512);
    glutCreateWindow("Hello GL");

    //�ֽ� openGl ��� �� �� �ְ� �ִ� �Լ���
    glewExperimental = true;
    glewInit();

    printf("OpenGl Version: %s\n", glGetString(GL_VERSION));
    printf("GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    //�ʱ�ȭ
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
