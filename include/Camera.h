#ifndef __CAMERA_H
#define __CAMERA_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class	Camera
{
public:
	
	void	Init(glm::vec3 eye, glm::vec3 at, glm::vec3 up, GLfloat fovy, GLfloat aspect, GLfloat fnear, GLfloat ffar)
	{
		this->eye		= eye;
		this->at		= at;
		this->up		= up;
		this->fovy		= fovy;
		this->aspect	= aspect;
		this->fnear		= fnear;
		this->ffar		= ffar;
	}

	void	ZoomInLens();
	void	ZoomOutLens();
	void	ZoomInPosition();
	void	ZoomOutPosition();
	void	Reset() {};
	glm::mat4	GetMv() const {return glm::lookAt(eye,at,up);}
	glm::mat4	GetP()	const {return glm::perspective(glm::radians(fovy),aspect,fnear,ffar);}
	void		SetEye(glm::vec4 v) {eye = v;}
	glm::vec3	GetEye() const {return eye;}
	void		SetAt(glm::vec4 v) {at = v;}
	glm::vec3	GetAt() const {return at;}
	void		SetUp(glm::vec4 v) {up = v;}
	glm::vec3	GetUp() const {return up;}
	void		SetFovy(GLfloat f) {fovy = f;}
	GLfloat		GetFovy() const {return fovy;}
	void		SetAspect(GLfloat f) {aspect = f;}
	GLfloat 	GetAspect() const {return aspect;}
	void		SetNear(GLfloat f) {fnear = f;}
	GLfloat 	GetNear() const {return fnear;}
	void		SetFar(GLfloat f) {ffar = f;}
	GLfloat 	GetFar() const {return ffar;}

private:

	glm::vec3	eye;
	glm::vec3	at;
	glm::vec3	up;

	GLfloat	fovy;
	GLfloat	aspect;
	GLfloat fnear;
	GLfloat ffar;
};

class	CameraStatic : public Camera
{
public:
	enum	FOCUS {CENTER = 0, CAR};

	FOCUS	GetFocus() {return eFocus;}
	void	SetFocus(FOCUS e) {eFocus = e;}

private:
	FOCUS	eFocus;
	
};

#endif
