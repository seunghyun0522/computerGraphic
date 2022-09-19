// GLUT 화면에 창을 띄우고 openGL의 운영체제마다 라이브러리  플랫폼 동일
//
#ifdef __APPLE__
/* Defined before OpenGL and GLUT includes to avoid deprecation messages */
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#include <stdio.h>
#include <stdlib.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif


typedef struct vec2{
    float x;
    float y;
}vec2;

const int NUM_POINTS =10000;
vec2 points[NUM_POINTS];

void init(){
    for(int i=0;i<NUM_POINTS;i++){
        float x= (rand()%1000)/1000.0f*2.0f-1.0f;
        float y= (rand()%1000)/1000.0f*2.0f-1.0f;
        points[i].x = x;
        points[i].y=y;
    }
    
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);       // All Black clear
  
    //GL_TRIANGLES 3개씩 처리
    //GL_LINES 2개씩 처리
    //GL_POINTS 1개씩 처리
    glBegin(GL_POINTS);              //점을 보내는 것(삼각형)
    // 이곳에 초기화를 넣으면 계속해서 모양이 바뀜 display 함수는 계속해서 변화함
    for(int i=0;i<NUM_POINTS;i++){
        glVertex2f(points[i].x,points[i].y);
    }
    glEnd();
    glFlush();                          //데이터를 하드웨어 gpu 상으로 보내는 것
}

//main 함수는 변하지 않을 예정 display 함수가 모양을 결정한다.
int main(int argc, char** argv)
{
    ///초기화 과정
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(512, 512);//사이즈
    glutCreateWindow("Hello GL");//폴더 명
    
    // 좌표를 미리 설정하여 화면이 작아져도 변화없이
    init();
    ///그리는 곳
    glutDisplayFunc(display);   //그림을 그리는 함수를 호출
    glutMainLoop();             // while문을 반복 후 프로그램이 종료 (ex) 키보드 입력을 기다리는 과정

    return 0;
}
