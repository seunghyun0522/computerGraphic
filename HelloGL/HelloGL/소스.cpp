// GLUT 화면에 창을 띄우고 openGL의 운영체제마다 라이브러리  플랫폼 동일
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
    GLuint vao;     //OpenGL Unsigned int 공통의 int
    // GLuint vao[3] 일 경우 밑에는 3,&vao
    // 컴퓨터에게 메모리를 만들어줘 -> 내가 만든 메모리의 주소를 저장하는 용
    glGenVertexArrays(1, &vao);  //배열의 크기와 주소
    glBindVertexArray(vao);     //Binding

    //2-2. Create Vertext Buffer object in the Vertex Array
    GLuint vbo;     //buffer Obj create
    glGenBuffers(1, &vbo); //numbers input
    glBindBuffer(GL_ARRAY_BUFFER, vbo);  //GL_ARRAY_BUFFER :vertex information

    //array 를 설정하는 것이 binding
    //glBufferdata();
        //vertex의 정보 입력
        //구조체 내에 float (8bytes) * 배열의 사이즈 60000
        //만든 구조체 변수 point 를 추가
        //GL_STATIC_DRAW
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * NUM_POINTS, points, GL_STATIC_DRAW);
    //2-3. copy data in CPU into the buffer
    //CPU 에 있는 binding 되어 있는 buffer 로 copy 이동

    //3. Loading shaders
    GLuint prog =
        InitShader("vShader.glsl", "fShader.glsl");
    glUseProgram(prog);
    //4. Connect the shader with the data
    //vertex shader 와 connect
    int vPosition = 0;
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));


}


void display()
{
    // 화면 지우기
    glClear(GL_COLOR_BUFFER_BIT);

    // GL_TRIANGLES            : 3 개씩 처리
    // GL_LINES                : 2 개씩 처리
    // GL_POINTS            : 1 개씩 처리
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

    //최신 openGl 사용 할 수 있게 있는 함수들
    glewExperimental = true;
    glewInit();

    printf("OpenGl Version: %s\n", glGetString(GL_VERSION));
    printf("GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    //초기화
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
