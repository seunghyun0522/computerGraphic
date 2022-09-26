#include <vgl.h>
#include <InitShader.h>
#include <vec.h>
// include 에 나오는 vec.h 는 수업시간 용의 벡터이다. 


const int NUM_POINTS = 36; // 정육면체 6면 * 삼각형이 사각형 2개를 차지 * 삼각형의 꼭짓점 3개

//4차원 좌표
vec4 points[NUM_POINTS];
vec4 colors[NUM_POINTS];

// w 값은 일단 1로 고정
vec4 vertex_pos[8] = {
        vec4(-0.5, -0.5,  0.5, 1.0),
        vec4(-0.5,  0.5,  0.5, 1.0),
        vec4(0.5,  0.5,  0.5, 1.0),
        vec4(0.5, -0.5,  0.5, 1.0),
        vec4(-0.5, -0.5, -0.5, 1.0),
        vec4(-0.5,  0.5, -0.5, 1.0),
        vec4(0.5,  0.5, -0.5, 1.0),
        vec4(0.5, -0.5, -0.5, 1.0)
};


// RGBA colors
// w 값은 일단 1로 고정
vec4 vertex_colors[8] = {
    vec4(0.0, 0.0, 0.0, 1.0),  // black
    vec4(1.0, 0.0, 0.0, 1.0),  // red
    vec4(1.0, 1.0, 0.0, 1.0),  // yellow
    vec4(0.0, 1.0, 0.0, 1.0),  // green
    vec4(0.0, 0.0, 1.0, 1.0),  // blue
    vec4(1.0, 0.0, 1.0, 1.0),  // magenta
    vec4(1.0, 1.0, 1.0, 1.0),  // white
    vec4(0.0, 1.0, 1.0, 1.0)   // cyan
};


void setRectangle(int a, int b, int c, int d) {
    static int index = 0;   //전역변수 하기 싫을 때 전역으로 바꿀수 있음 static
    points[index] = vertex_pos[a];      colors[index] = vertex_pos[a];      index++;
    points[index] = vertex_pos[b];      colors[index] = vertex_pos[b];      index++;
    points[index] = vertex_pos[c];      colors[index] = vertex_pos[c];      index++;

    points[index] = vertex_pos[c];      colors[index] = vertex_pos[c];      index++;
    points[index] = vertex_pos[d];      colors[index] = vertex_pos[d];      index++;
    points[index] = vertex_pos[a];      colors[index] = vertex_pos[a];      index++;

}


//초기화의 과정들! 
//cpu, gpu, shaderLoading, connect shaders
void init() {
    //1. create date in CPU

    ///시계방향으로 좌표 넣기 (정육면체의 6면의 좌표를 입력) 
    setRectangle(0, 3, 2, 1);
    setRectangle(4, 5, 6, 7);
    setRectangle(0, 4, 7, 3);
    setRectangle(3, 7, 6, 2);
    setRectangle(2, 6, 5, 1);
    setRectangle(0, 1, 5, 4);

    //2. seding the data to GPU
    //2-1. create vertex array object : 그릴 대상을 하나하나를 vertex 
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    //2-2. create vertex buffer object 
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    //2-3. sending the data to the buffer
    //color 와 좌표를 같이 보냄
    glBufferData(GL_ARRAY_BUFFER, sizeof(points)+sizeof(colors), NULL,GL_STATIC_DRAW);//GL_ARRAY_BUFFER,size 를 보내기, 배열의 포인터, static
    
    //0번부터 시작해서 points의 배열 크기만큼 복사 
    //즉 buffer_offset은 시작점을 말한다. 
    //0부터 points 끝 => points 사이즈 부터 color 크기만큼을 보낸다.
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
    //points 배열 끝 부터 색깔의 배열을 넣는다. 
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors);
    // 메모리의 크기는 0~~~~~points_size ..... points~~~~~~~~~~~~color_size

    //3. loading the shaders
    // Load and use shaders
    // 읽는 과정
    GLuint prog
        = InitShader("vshader.glsl", "fshader.glsl");
    // 사용 과정
    glUseProgram(prog);

    //4. connect the data with the shaders
    GLuint vPosition = glGetAttribLocation(prog, "vPosition");  //변수를 찾아줘!
    glEnableVertexAttribArray(vPosition);   // 그 변수를 사용할 것이다.
    glVertexAttribPointer(vPosition,4,GL_FLOAT,FALSE,0,BUFFER_OFFSET(0));   //4개를 연달아서 float 으로 읽는값 그대로 gpu 처음부터 스타트

    GLuint vColor = glGetAttribLocation(prog, "vColor");  //변수를 찾아줘!
    glEnableVertexAttribArray(vColor);   // 그 변수를 사용할 것이다.
    glVertexAttribPointer(vColor,4,GL_FLOAT,FALSE,0,BUFFER_OFFSET(sizeof(points)));   //points 부터 시작
}

void display()
{
    // 화면 지우기
    glClear(GL_COLOR_BUFFER_BIT);

    // GL_TRIANGLES            : 3 개씩 처리
    // GL_LINES                : 2 개씩 처리
    // GL_POINTS            : 1 개씩 처리
    glDrawArrays(GL_TRIANGLES, 0, NUM_POINTS);
    glFlush();

    /*
    Old skills
    glBegin(GL_POINTS);
    for (int i = 0; i < NUM_POINTS; i++)
        glVertex2f(points[i].x, points[i].y);
    glEnd();
    glFlush();*/
}

// window 창을 만들고 띄어주는 역할 
// 그림을 그리는 곳은 콜백함수를 통해 이용 
// main.
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(512, 512);
    glutCreateWindow("Hello GL");

    //최신 openGl 사용 할 수 있게 있는 함수들
    glewExperimental = true;
    glewInit();

    //초기화
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;

}