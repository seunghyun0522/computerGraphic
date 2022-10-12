#ifndef _MY_CYLINDER_H_
#define _MY_CYLINDER_H_

#include <vec.h>
#include <vgl.h>

struct MyCylinderVertex {
	vec4 position;
	vec4 color;
};

class MyCylinder {
public:
	bool bInitialized;
	GLuint vao;
	GLuint vbo;
	int numVertices;

	MyCylinder();
	void init(int div);
	void draw(GLuint prog);
	void setAttributePointers(GLuint prog);

};


MyCylinder::MyCylinder() {
	bInitialized = false;
}

void MyCylinder::init(int div) {
	//if(div<3)	// 삼각형의 최소 개수

	//사각형에서 -> 삼각형의 개수 2 -> 삼각형에서 꼭짓점 3 개 
	numVertices = div * 2 * 3;
	MyCylinderVertex* vertices = new MyCylinderVertex[numVertices];
	float dtheta = 2*3.141592f / div;	// 각도
	float r = 0.5f;
	int ind = 0;
	for (int i = 0; i < div; i++) {
		float ang1 = dtheta * i;
		float ang2 = dtheta * (i + 1);
		float x1 = r*cos(ang1);
		float y1 = r * sin(ang1);
		float x2 = r * cos(ang2);
		float y2 = r * sin(ang2);

		vec4 a = vec4(x1, y1, 0.5f,1.0f);
		vec4 b = vec4(x1, y1, -0.5f, 1.0f);
		vec4 c = vec4(x2, y2, -0.5f, 1.0f);
		vec4 d = vec4(x2, y2, 0.5f, 1.0f);
		vec4 c1 = vec4(1.0f - i/float(div),0, i / float(div), 1.0f);
		vec4 c2 = vec4(1.0f - (i+1) / float(div), 0, (i+1) / float(div), 1.0f);
		vertices[ind].position = a;	vertices[ind].color = c1; ind++;
		vertices[ind].position = b; vertices[ind].color = c1; ind++;
		vertices[ind].position = c; vertices[ind].color = c1; ind++;

		vertices[ind].position = c;	vertices[ind].color = c1; ind++;
		vertices[ind].position = d; vertices[ind].color = c1; ind++;
		vertices[ind].position = a; vertices[ind].color = c1; ind++;
	}

	// 반복 배열을 막기 위해서 불리언 값을 추가 
	if(bInitialized == false) glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);


	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//메모리 보내기
	glBufferData(GL_ARRAY_BUFFER, sizeof(MyCylinderVertex) * numVertices,vertices, GL_STATIC_DRAW);
	
	delete[] vertices;
	bInitialized = true;
}

void MyCylinder::setAttributePointers(GLuint prog) {
	GLuint vPosition = glGetAttribLocation(prog, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, FALSE,
		sizeof(MyCylinderVertex), BUFFER_OFFSET(0));

	GLuint vColor = glGetAttribLocation(prog, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, FALSE,
		sizeof(MyCylinderVertex), BUFFER_OFFSET(sizeof(vec4)));
}
void MyCylinder::draw(GLuint prog) {
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	setAttributePointers(prog);
	glDrawArrays(GL_TRIANGLES, 0, numVertices);
}

#endif