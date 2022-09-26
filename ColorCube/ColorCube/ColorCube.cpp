#include <vgl.h>
#include <InitShader.h>
#include <vec.h>
// include �� ������ vec.h �� �����ð� ���� �����̴�. 


const int NUM_POINTS = 36; // ������ü 6�� * �ﰢ���� �簢�� 2���� ���� * �ﰢ���� ������ 3��

//4���� ��ǥ
vec4 points[NUM_POINTS];
vec4 colors[NUM_POINTS];

// w ���� �ϴ� 1�� ����
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
// w ���� �ϴ� 1�� ����
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
    static int index = 0;   //�������� �ϱ� ���� �� �������� �ٲܼ� ���� static
    points[index] = vertex_pos[a];      colors[index] = vertex_pos[a];      index++;
    points[index] = vertex_pos[b];      colors[index] = vertex_pos[b];      index++;
    points[index] = vertex_pos[c];      colors[index] = vertex_pos[c];      index++;

    points[index] = vertex_pos[c];      colors[index] = vertex_pos[c];      index++;
    points[index] = vertex_pos[d];      colors[index] = vertex_pos[d];      index++;
    points[index] = vertex_pos[a];      colors[index] = vertex_pos[a];      index++;

}


//�ʱ�ȭ�� ������! 
//cpu, gpu, shaderLoading, connect shaders
void init() {
    //1. create date in CPU

    ///�ð�������� ��ǥ �ֱ� (������ü�� 6���� ��ǥ�� �Է�) 
    setRectangle(0, 3, 2, 1);
    setRectangle(4, 5, 6, 7);
    setRectangle(0, 4, 7, 3);
    setRectangle(3, 7, 6, 2);
    setRectangle(2, 6, 5, 1);
    setRectangle(0, 1, 5, 4);

    //2. seding the data to GPU
    //2-1. create vertex array object : �׸� ����� �ϳ��ϳ��� vertex 
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    //2-2. create vertex buffer object 
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    //2-3. sending the data to the buffer
    //color �� ��ǥ�� ���� ����
    glBufferData(GL_ARRAY_BUFFER, sizeof(points)+sizeof(colors), NULL,GL_STATIC_DRAW);//GL_ARRAY_BUFFER,size �� ������, �迭�� ������, static
    
    //0������ �����ؼ� points�� �迭 ũ�⸸ŭ ���� 
    //�� buffer_offset�� �������� ���Ѵ�. 
    //0���� points �� => points ������ ���� color ũ�⸸ŭ�� ������.
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
    //points �迭 �� ���� ������ �迭�� �ִ´�. 
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors);
    // �޸��� ũ��� 0~~~~~points_size ..... points~~~~~~~~~~~~color_size

    //3. loading the shaders
    // Load and use shaders
    // �д� ����
    GLuint prog
        = InitShader("vshader.glsl", "fshader.glsl");
    // ��� ����
    glUseProgram(prog);

    //4. connect the data with the shaders
    GLuint vPosition = glGetAttribLocation(prog, "vPosition");  //������ ã����!
    glEnableVertexAttribArray(vPosition);   // �� ������ ����� ���̴�.
    glVertexAttribPointer(vPosition,4,GL_FLOAT,FALSE,0,BUFFER_OFFSET(0));   //4���� ���޾Ƽ� float ���� �д°� �״�� gpu ó������ ��ŸƮ

    GLuint vColor = glGetAttribLocation(prog, "vColor");  //������ ã����!
    glEnableVertexAttribArray(vColor);   // �� ������ ����� ���̴�.
    glVertexAttribPointer(vColor,4,GL_FLOAT,FALSE,0,BUFFER_OFFSET(sizeof(points)));   //points ���� ����
}

void display()
{
    // ȭ�� �����
    glClear(GL_COLOR_BUFFER_BIT);

    // GL_TRIANGLES            : 3 ���� ó��
    // GL_LINES                : 2 ���� ó��
    // GL_POINTS            : 1 ���� ó��
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

// window â�� ����� ����ִ� ���� 
// �׸��� �׸��� ���� �ݹ��Լ��� ���� �̿� 
// main.
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(512, 512);
    glutCreateWindow("Hello GL");

    //�ֽ� openGl ��� �� �� �ְ� �ִ� �Լ���
    glewExperimental = true;
    glewInit();

    //�ʱ�ȭ
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;

}