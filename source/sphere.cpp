#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

#include "GraphObjects.h"
#include <unistd.h>
#include <iostream>
#include "../include/shader.h"


void Sphere::Init()
{

	char cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
    	std::cout << "Current working dir: " << cwd << std::endl;
	}

	double fM_PI = glm::pi<float>();

	float step = static_cast<float>((360.0/180.0)*(fM_PI/180.0));

		//int totalverts = int(ceil(10.0/2.0)*100.0 * 6.0);

		int k = 0;
		for(float i = -fM_PI/2.0; i<=fM_PI/2.0; i+=step){
			for(float j = -fM_PI; j<=fM_PI; j+=step){
				//triangle 1
				//v4AmbientDiffuseColor[k] = vec4(1.0,1.0,1.0,1.0);
				v3Normal[k]= glm::vec3(radius*sin(j)*cos(i),radius*cos(j)*cos(i),radius*sin(i));
				v4Vertices[k]=   glm::vec4(radius*sin(j)*cos(i), radius*cos(j)*cos(i), radius*sin(i), 1.0);
				k++;

				//v4AmbientDiffuseColor[k] = vec4(1.0,1.0,1.0,1.0);
				v3Normal[k]=glm::vec3(radius*sin(j)*cos(i + step),radius*cos(j)*cos(i + step),radius*sin(i + step));
				v4Vertices[k]=   glm::vec4(radius*sin(j)*cos(i+step), radius*cos(j)*cos(i+step), radius*sin(i+step), 1.0);
				k++;

				//v4AmbientDiffuseColor[k] = vec4(1.0,1.0,1.0,1.0);
				v3Normal[k]=glm::vec3(radius*sin(j+step)*cos(i + step),radius*cos(j+step)*cos(i + step),radius*sin(i + step));
				v4Vertices[k]=   glm::vec4(radius*sin((j+step))*cos((i+step)), radius*cos(j+step)*cos(i+step), radius*sin(i+step), 1.0);
				k++;

				//triangle 2
				//v4AmbientDiffuseColor[k] = vec4(1.0,1.0,1.0,1.0);
				v3Normal[k]=glm::vec3(radius*sin((j+step))*cos((i+step)), radius*cos(j+step)*cos(i+step), radius*sin(i+step));
				v4Vertices[k]=   glm::vec4(radius*sin((j+step))*cos((i+step)), radius*cos(j+step)*cos(i+step), radius*sin(i+step), 1.0);
				k++;

				//v4AmbientDiffuseColor[k] = vec4(1.0,1.0,1.0,1.0);
				v3Normal[k]=glm::vec3(radius*sin(j+step)*cos(i), radius*cos(j+step)*cos(i), radius*sin(i));
				v4Vertices[k]=   glm::vec4(radius*sin(j+step)*cos(i), radius*cos(j+step)*cos(i), radius*sin(i), 1.0);
				k++;

				//v4AmbientDiffuseColor[k] = vec4(1.0,1.0,1.0,1.0);
				v3Normal[k]=glm::vec3(radius*sin(j)*cos(i), radius*cos(j)*cos(i), radius*sin(i));
				v4Vertices[k]=   glm::vec4(radius*sin(j)*cos(i), radius*cos(j)*cos(i), radius*sin(i), 1.0);
				k++;
			}
		}


	program = LoadShaders("./shaders/sphere.vert","./shaders/sphere.frag");
	glUseProgram(program);

	glGenVertexArrays(1, &vao[0]);
	glBindVertexArray(vao[0]);

	glGenBuffers(2,&vbo[0]);

	//position
	glBindBuffer(GL_ARRAY_BUFFER,vbo[0]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(v4Vertices),v4Vertices,GL_STATIC_DRAW);
	vPosition = glGetAttribLocation(program,"vPosition");

	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition,4,GL_FLOAT,GL_FALSE,0,0);

	//normal
	glBindBuffer(GL_ARRAY_BUFFER,vbo[1]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(v3Normal),v3Normal,GL_STATIC_DRAW);
	vNormal = glGetAttribLocation(program,"vNormal");

	glEnableVertexAttribArray(vNormal);
	glVertexAttribPointer(vNormal,3,GL_FLOAT,GL_FALSE,0,0);

	model_view = glGetUniformLocation(program,"model_view");
	projection = glGetUniformLocation(program,"projection");
	cursorX = glGetUniformLocation(program,"cursorX");
	cursorY = glGetUniformLocation(program,"cursorY");
	near = glGetUniformLocation(program, "near");
	far = glGetUniformLocation(program,"far");
	translate = glGetUniformLocation(program,"translate");

}


void Sphere::Draw(Camera *camera)
{
	glm::mat4 mv = glm::translate(camera->GetMv(), glm::vec3(tx,ty,tz));
	glm::vec3 t = glm::vec3(tx,ty,tz);


	glUniformMatrix4fv(model_view,1,GL_FALSE,glm::value_ptr(mv));
	glUniformMatrix4fv(projection,1,GL_FALSE,glm::value_ptr(camera->GetP()));
	glUniform1f(cursorX,pCursor->X());
	glUniform1f(cursorY,pCursor->Y());
	glUniform1f(near,camera->GetNear());
	glUniform1f(far,camera->GetFar());
	glUniform3fv(translate,1, glm::value_ptr(t));


	glBindVertexArray(vao[0]);
	glDrawArrays(GL_TRIANGLES,0,97200);
}
