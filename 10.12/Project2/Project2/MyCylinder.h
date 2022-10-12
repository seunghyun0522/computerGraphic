#ifndef _MY_CYLINDER_H_
#define _MY_CYLINDER_H_

#include <vgl.h>
#include <vec.h>

struct MyCylinderVertex
{
	vec4 position;
	vec4 color;
};

class MyCylinder
{
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

MyCylinder::MyCylinder()
{
	bInitialized = false;
}


void MyCylinder::init(int div)
{
	//	if (div < 3) return;

	numVertices = div * 2 * 3;
	MyCylinderVertex* vertices = new MyCylinderVertex[numVertices];

	float dtheta = 2 * 3.141592f / div;
	float r = 0.5f;
	int ind = 0;
	for (int i = 0; i < div; i++)
	{
		float ang1 = dtheta * i;
		float ang2 = dtheta * (i + 1);
		float x1 = r * cos(ang1);
		float y1 = r * sin(ang1);
		float x2 = r * cos(ang2);
		float y2 = r * sin(ang2);
		vec4 a = vec4(x1, y1, 0.5f, 1.0f);
		vec4 b = vec4(x1, y1, -0.5f, 1.0f);
		vec4 c = vec4(x2, y2, -0.5f, 1.0f);
		vec4 d = vec4(x2, y2, 0.5f, 1.0f);
		vec4 c1 = vec4(1.0f - i / float(div), 0, i / float(div), 1.0f);
		vec4 c2 = vec4(1.0f - (i + 1) / float(div), 0, (i + 1) / float(div), 1.0f);

		vertices[ind].position = a;	vertices[ind].color = c1; ind++;
		vertices[ind].position = b;	vertices[ind].color = c1; ind++;
		vertices[ind].position = c;	vertices[ind].color = c1; ind++;

		vertices[ind].position = c;	vertices[ind].color = c1; ind++;
		vertices[ind].position = d;	vertices[ind].color = c1; ind++;
		vertices[ind].position = a;	vertices[ind].color = c1; ind++;
	}

	if (bInitialized == false) glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	if (bInitialized == false) glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(MyCylinderVertex) * numVertices, vertices, GL_STATIC_DRAW);

	delete[] vertices;
	bInitialized = true;
}

void MyCylinder::setAttributePointers(GLuint prog)
{
	GLuint vPosition = glGetAttribLocation(prog, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, FALSE,
		sizeof(MyCylinderVertex), BUFFER_OFFSET(0));

	GLuint vColor = glGetAttribLocation(prog, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, FALSE,
		sizeof(MyCylinderVertex), BUFFER_OFFSET(sizeof(vec4)));
}

void MyCylinder::draw(GLuint prog)
{
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glUseProgram(prog);
	setAttributePointers(prog);

	glDrawArrays(GL_TRIANGLES, 0, numVertices);

}

#endif