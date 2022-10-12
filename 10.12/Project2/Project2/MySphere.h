#ifndef _MY_SPHERE_H_
#define _MY_SPHERE_H_

#include <vgl.h>
#include <vec.h>

struct MySphereVertex
{
	vec4 position;
	vec4 color;
};

class MySphere
{
public:
	bool bInitialized;
	GLuint vao;
	GLuint vbo;
	int numVertices;

	MySphere();
	void init(int vdiv,int hdiv);	// 두개 필요
	void draw(GLuint prog);
	void setAttributePointers(GLuint prog);
};

MySphere::MySphere()
{
	bInitialized = false;
}


void MySphere::init(int vdiv, int hdiv)
{
	//	if (div < 3) return;

	numVertices = vdiv * (hdiv - 2) * 2 * 3 +vdiv * 3*2;
	MySphereVertex* vertices = new MySphereVertex[numVertices];
	
	float dtheta1 = 2 * 3.141592f / vdiv;	// 
	float dtheta2 = 3.141592f / hdiv;	// 180도 씩 자른다.
	float r = 0.5f;	// 구의 반지름
	int ind = 0;
	for (int j = 0; j < hdiv; j++) {	// j  값에 따라 반지름이 바뀐다.	j = 0 일떄 윗뚜껑 hdiv 보다 작을때 아래뚜껑
		//각도에 따라 자른다. 
		float vang1 = dtheta2 * j;
		float vang2 = dtheta2 * (j+1);
		float r1 = r*sin(vang1);// rsin(@)
		float r2= r*sin(vang2);
		float z1 = r * cos(vang1); //높이
		float z2 = r * cos(vang2);
		for (int i = 0; i < vdiv; i++)
		{
			float ang1 = dtheta1 * i;
			float ang2 = dtheta1 * (i + 1);
			float x1 = cos(ang1);
			float y1 = sin(ang1);
			float x2 = cos(ang2);
			float y2 = sin(ang2);
			vec4 a = vec4(r1 * x1, r1 * y1, z1, 1.0f);
			vec4 b = vec4(r2 * x1, r2 * y1, z2, 1.0f);
			vec4 c = vec4(r2 * x2, r2 * y2, z2, 1.0f);
			vec4 d = vec4(r1 * x2, r1 * y2, z1, 1.0f);



			vec4 c1 = vec4(1.0f - i / float(vdiv), 0, i / float(vdiv), 1.0f);
			vec4 c2 = vec4(1.0f - (i + 1) / float(vdiv), 0, (i + 1) / float(vdiv), 1.0f);

			if ((i + j) % 2 == 0) {
				c1 = 0.5f * c1;
			}
			if (j != hdiv - 1) {
				// 만나는 abc 삼각형
				vertices[ind].position = a;	vertices[ind].color = c1; ind++;
				vertices[ind].position = b;	vertices[ind].color = c1; ind++;
				vertices[ind].position = c;	vertices[ind].color = c1; ind++;
			}
			if (j != 0){
				//cda 삼각형 윗뚜껑이 삼각형으로만 구성 
			vertices[ind].position = c;	vertices[ind].color = c1; ind++;
			vertices[ind].position = d;	vertices[ind].color = c1; ind++;
			vertices[ind].position = a;	vertices[ind].color = c1; ind++;
			}
		}
	}

	if (bInitialized == false) glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	if (bInitialized == false) glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(MySphereVertex) * numVertices, vertices, GL_STATIC_DRAW);

	delete[] vertices;
	bInitialized = true;
}

void MySphere::setAttributePointers(GLuint prog)
{
	GLuint vPosition = glGetAttribLocation(prog, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, FALSE,
		sizeof(MySphereVertex), BUFFER_OFFSET(0));

	GLuint vColor = glGetAttribLocation(prog, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, FALSE,
		sizeof(MySphereVertex), BUFFER_OFFSET(sizeof(vec4)));
}

void MySphere::draw(GLuint prog)
{
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glUseProgram(prog);
	setAttributePointers(prog);

	glDrawArrays(GL_TRIANGLES, 0, numVertices);

}

#endif