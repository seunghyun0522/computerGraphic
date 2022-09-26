#pragma once

#include <vgl.h>
#include <vec.h>

struct MyPymVertex
{
	vec4 position;
	vec4 color;
};

class MyPyramid
{
public:
	MyPyramid(void);
	~MyPyramid(void);

	static const int NumVertices = 24;

	MyPymVertex Vertices[NumVertices];
	GLuint Init();
	void SetPositionAndColorAttribute(GLuint program);


	void ColorPyramid(vec4 * vin, vec4 * cin);
	void Quad (int a, int b, int c, int d, vec4 * vin, vec4 * cin);
	void Triangle (int a, int b, int c, vec4 * vin, vec4 * cin);

	int NumCurVertices;

	GLuint vao;
	GLuint buffer;
	bool bInitialized;

	void Draw(GLuint program);

};



MyPyramid::MyPyramid(void)
{
	bInitialized = false;
	NumCurVertices = 0;
}


MyPyramid::~MyPyramid(void)
{
}


void MyPyramid::Quad (int a, int b, int c, int d, vec4 * vin, vec4 * cin)
{
	Vertices[NumCurVertices].position = vin[a]; Vertices[NumCurVertices].color = cin[a]; 
	NumCurVertices++;
	Vertices[NumCurVertices].position = vin[b]; Vertices[NumCurVertices].color = cin[b]; 
	NumCurVertices++;
	Vertices[NumCurVertices].position = vin[c]; Vertices[NumCurVertices].color = cin[c]; 
	NumCurVertices++;
	
	Vertices[NumCurVertices].position = vin[a]; Vertices[NumCurVertices].color = cin[a]; 
	NumCurVertices++;
	Vertices[NumCurVertices].position = vin[c]; Vertices[NumCurVertices].color = cin[c]; 
	NumCurVertices++;
	Vertices[NumCurVertices].position = vin[d]; Vertices[NumCurVertices].color = cin[d]; 
	NumCurVertices++;

}

void MyPyramid::Triangle (int a, int b, int c, vec4 * vin, vec4 * cin)
{
	Vertices[NumCurVertices].position = vin[a]; Vertices[NumCurVertices].color = cin[a]; 
	NumCurVertices++;
	Vertices[NumCurVertices].position = vin[b]; Vertices[NumCurVertices].color = cin[b]; 
	NumCurVertices++;
	Vertices[NumCurVertices].position = vin[c]; Vertices[NumCurVertices].color = cin[c]; 
	NumCurVertices++;


}

void MyPyramid::ColorPyramid(vec4 * vin, vec4 * cin)
{
	Quad(0,1,2,3, vin, cin);
	Quad(0,4,5,1, vin, cin);
	Quad(2,5,4,3, vin, cin);
	Triangle(0,3,4, vin, cin);
	Triangle(1,5,2, vin, cin);
}


GLuint MyPyramid::Init()
{
	// The Cube should be initialized only once;
	if(bInitialized == true) return vao;

	vec4 vertex_positions[6] ={
		vec4( -0.5, -0.5,  0.5, 1.0 ),
		vec4( -0.5, -0.5, -0.5, 1.0 ),
		vec4(  0.5, -0.5, -0.5, 1.0 ),
		vec4(  0.5, -0.5,  0.5, 1.0 ),
		vec4(   0 ,  0.5,  0.5, 1.0 ),
		vec4(   0 ,  0.5, -0.5, 1.0 )
	
	};

	vec4 vertex_colors[6] ={
		vec4( 1, 0, 0, 1),
		vec4( 1, 1, 1, 1),
		vec4( 1, 1, 0, 1),
		vec4( 0, 1, 0, 1),
		vec4( 0, 0, 1, 1),
		vec4( 1, 0, 1, 1)
	};

	ColorPyramid(vertex_positions, vertex_colors);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	
	bInitialized = true;
	return vao;
}

void MyPyramid::SetPositionAndColorAttribute(GLuint program)
{
	GLuint vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, sizeof(MyPymVertex), BUFFER_OFFSET(0));

	GLuint vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, sizeof(MyPymVertex), BUFFER_OFFSET(sizeof(vec4)));
}


void MyPyramid::Draw(GLuint program)
{
	if(!bInitialized) return;			// check whether it is initiazed or not. 
	
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	SetPositionAndColorAttribute(program);
	
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);

}

