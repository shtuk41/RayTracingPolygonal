
#include <algorithm>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"

#include "GraphObjects.h"


//****************************************************************
//	Date:		03/02/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		Field
//	Function:	Init
//	Inputs:		none
//	Output:		none
//	Purpose:	INitialize Field
//******************************************************************
void Field::Init()
{
	v4Vertices[0] = glm::vec4(-1.0,-1.0, 0.0,1.0);
	v4Vertices[1] = glm::vec4(1.0,-1.0, 0.0,1.0);
	v4Vertices[2] = glm::vec4(0.0,  1.0, 0.0,1.0);

	program = LoadShaders("../texture.vert","../texture.frag");
	glUseProgram(program);

	glGenVertexArrays(1, &vao[0]);
	glBindVertexArray(vao[0]);

	glGenBuffers(1,&vbo[0]);
	glBindBuffer(GL_ARRAY_BUFFER,vbo[0]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(v4Vertices),v4Vertices,GL_STATIC_DRAW);
	vPosition = glGetAttribLocation(program,"vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition,4,GL_FLOAT,GL_FALSE,0,0);
}
//****************************************************************
//	Date:		03/02/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		Field
//	Function:	Draw
//	Inputs:		none
//	Output:		none
//	Purpose:	Draw Field
//******************************************************************
void Field::Draw(Camera *)
{
	glBindVertexArray(vao[0]);
	glDrawArrays(GL_TRIANGLES,0,3);
}

