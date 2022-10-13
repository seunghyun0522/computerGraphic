#ifndef _MY_PLAIN_H_
#define _MY_PLAIN_H_

#include <vgl.h>
#include <vec.h>

struct MyPlainVertex 
{
	vec4 position;
	vec4 color;
};

class MyPlain {
public:
	bool bInitialized;

	
	GLuint vao;
	GLuint vbo;
	MyPlainVertex* vertices;
	int Division = 30;
	int rectangleNum = Division * Division;
	int numVertices = 6 * rectangleNum;
	int index = 0;

	MyPlain();
	void init();
	void update(int value);
	void setRectangle(int x, int y);
	void draw(GLuint prog, float gTime, int gWave);
	void setAttributePointers(GLuint prog);
};


MyPlain::MyPlain() {
	bInitialized = false;
}
void MyPlain::init() {

	 vertices = new MyPlainVertex[numVertices];

	int x = 0;
	int y = 0;

	for (int i = 0; i < Division; i++) {
		for (int j = 0; j < Division; j++) {
			setRectangle(x, y);
			x++;
		}
		x = 0;
		y++;
	}

	if (bInitialized == false) glGenVertexArrays(1, &vao);

	glGenBuffers(1, &vbo);
	if (bInitialized == false) glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(MyPlainVertex) * numVertices, vertices, GL_STATIC_DRAW);

	delete[] vertices;
	bInitialized = true;
}

void MyPlain::update(int _value) {
	if (Division <= 2 && _value < 0)return;

	Division += _value;
	rectangleNum = Division * Division;
	numVertices = 6 * rectangleNum;
	index = 0;

	init();
}

void MyPlain::setRectangle(int x, int y) {

	float interval = 1.5 / (float)Division;

	vec4 vertex_pos[4] = {
		vec4(-0.75 + ((float)x * interval), -0.75 + ((float)y * interval), 0, 1.0),
		vec4(-0.75 + ((float)x * interval), -0.75 + ((float)(y + 1) * interval), 0, 1.0),
		vec4(-0.75 + ((float)(x + 1) * interval), -0.75 + ((float)(y + 1) * interval), 0, 1.0),
		vec4(-0.75 + ((float)(x + 1) * interval), -0.75 + ((float)y * interval), 0, 1.0)
	};

	vec4 vertex_color[4];

	if (x % 2 == 0 && y % 2 == 0) {
		for (int i = 0; i < 4; i++) {
			vertex_color[i] = vec4(0.25, 0.25, 0.25, 1);
		}
	}
	else if (x % 2 == 1 && y % 2 == 1) {
		for (int i = 0; i < 4; i++) {
			vertex_color[i] = vec4(0.25, 0.25, 0.25, 1);
		}
	}
	else {
		for (int i = 0; i < 4; i++) {
			vertex_color[i] = vec4(0.75, 0.75, 0.75, 1);
		}
	}

	vertices[index].position = vertex_pos[0];	vertices[index].color = vertex_color[0]; index++;
	vertices[index].position = vertex_pos[1];	vertices[index].color = vertex_color[1]; index++;
	vertices[index].position = vertex_pos[2];	vertices[index].color = vertex_color[2]; index++;
	vertices[index].position = vertex_pos[2];	vertices[index].color = vertex_color[2]; index++;
	vertices[index].position = vertex_pos[3];	vertices[index].color = vertex_color[3]; index++;
	vertices[index].position = vertex_pos[0];	vertices[index].color = vertex_color[0]; index++;
}

void MyPlain::setAttributePointers(GLuint prog)
{
	GLuint vPosition = glGetAttribLocation(prog, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, FALSE,
		sizeof(MyPlainVertex), BUFFER_OFFSET(0));

	GLuint vColor = glGetAttribLocation(prog, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, FALSE,
		sizeof(MyPlainVertex), BUFFER_OFFSET(sizeof(vec4)));
}


void MyPlain::draw(GLuint prog, float gTime, int gWave) {
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glUseProgram(prog);
	setAttributePointers(prog);



	glDrawArrays(GL_TRIANGLES, 0, numVertices);
}

#endif