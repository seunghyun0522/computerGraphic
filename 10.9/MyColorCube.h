#ifndef _MY_COLOR_CUBE_H_
#define _MY_COLOR_CUBE_H_

#include <vgl.h>
#include <vec.h>

struct MyCubeVertex
{
	vec4 position;
	vec4 color;
};


class MyColorCube
{
public:
	const int NUM_POINTS = 36;
	MyCubeVertex* vertices;
	GLuint vao;
	GLuint vbo;

	void init();
	void setRectangle(int a, int b, int c, int d, vec4* vertex_pos, vec4* vertex_color);
	void draw(GLuint prog);
	void setAttributePointers(GLuint prog);

};

void MyColorCube::setRectangle(int a, int b, int c, int d, vec4* vertex_pos, vec4* vertex_color)
{
	static int index = 0;
	vertices[index].position = vertex_pos[a];		vertices[index].color = vertex_color[a]; index++;
	vertices[index].position = vertex_pos[b];		vertices[index].color = vertex_color[b]; index++;
	vertices[index].position = vertex_pos[c];		vertices[index].color = vertex_color[c]; index++;

	vertices[index].position = vertex_pos[c];		vertices[index].color = vertex_color[c]; index++;
	vertices[index].position = vertex_pos[d];		vertices[index].color = vertex_color[d]; index++;
	vertices[index].position = vertex_pos[a];		vertices[index].color = vertex_color[a]; index++;
}

void MyColorCube::init()
{
	vertices = new MyCubeVertex[NUM_POINTS];

	vec4 vertex_pos[8] = {
		vec4(-0.5,-0.5,0.5,1.0),
		vec4(-0.5, 0.5,0.5,1.0),
		vec4(0.5, 0.5,0.5,1.0),
		vec4(0.5,-0.5,0.5,1.0),
		vec4(-0.5,-0.5,-0.5,1.0),
		vec4(-0.5, 0.5,-0.5,1.0),
		vec4(0.5, 0.5,-0.5,1.0),
		vec4(0.5,-0.5,-0.5,1.0)
	};

	vec4 vertex_color[8] = {
		vec4(1,1,1,1),
		vec4(1,0,0,1),
		vec4(0,1,0,1),
		vec4(0,0,1,1),
		vec4(1,1,0,1),
		vec4(1,0,1,1),
		vec4(0,1,1,1),
		vec4(0,0,0,1)
	};

	setRectangle(0, 3, 2, 1, vertex_pos, vertex_color);
	setRectangle(4, 5, 6, 7, vertex_pos, vertex_color);
	setRectangle(0, 4, 7, 3, vertex_pos, vertex_color);
	setRectangle(3, 7, 6, 2, vertex_pos, vertex_color);
	setRectangle(2, 6, 5, 1, vertex_pos, vertex_color);
	setRectangle(0, 1, 5, 4, vertex_pos, vertex_color);


	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	// 2-2. create vertex buffer object

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(MyCubeVertex) * NUM_POINTS,
		vertices, GL_STATIC_DRAW);

	delete[] vertices;

}

void MyColorCube::setAttributePointers(GLuint prog)
{
	GLuint vPosition = glGetAttribLocation(prog, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, FALSE,
		sizeof(MyCubeVertex), BUFFER_OFFSET(0));

	GLuint vColor = glGetAttribLocation(prog, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, FALSE,
		sizeof(MyCubeVertex), BUFFER_OFFSET(sizeof(vec4)));

}

void MyColorCube::draw(GLuint prog)
{
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	setAttributePointers(prog);

	glDrawArrays(GL_TRIANGLES, 0, NUM_POINTS);
}

#endif