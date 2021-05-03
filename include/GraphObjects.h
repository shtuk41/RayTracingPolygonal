#ifndef __GRAPH_OBJECTS
#define __GRAPH_OBJECTS

#include <vector>
#include <glm/glm.hpp>
#include "Lightsource.h"
#include "Cursor.h"
#include "Camera.h"

using namespace std;

struct LightStruct
{
	GLuint position;
	GLuint color;
	GLuint direction;
	GLuint cutoffangle;
};

class	GraphObject
{
public:

	GraphObject(Cursor *cursor = 0) {
	tx=
	ty=
	tz=
	rx=
	ry=
	rz= 0.0;
	pCursor = cursor;
	}

	virtual void Init() = 0;
	virtual void Draw(Camera *) = 0;

	void SetTx(GLfloat val) {tx = val;}
	GLfloat GetTx() const {return tx;}

	void SetTy(GLfloat val) {ty = val;}
	GLfloat GetTy() const {return ty;}

	void SetTz(GLfloat val) {tz = val;}
	GLfloat GetTz() const {return tz;}

	void SetRx(GLfloat val) {rx = val;}
	GLfloat GetRx() const {return tx;}

	void SetRy(GLfloat val) {ry = val;}
	GLfloat GetRy() const {return ty;}

	void SetRz(GLfloat val) {rz = val;}
	GLfloat GetRz() const {return tz;}

	glm::vec4	GetSpecularColor() const {return glm::vec4(1.0,1.0,1.0,1.0);}
	GLfloat	GetSpecularExponent() const {return 100;}


protected:

	GLfloat		tx;
	GLfloat		ty;
	GLfloat		tz;

	GLfloat		rx;
	GLfloat		ry;
	GLfloat		rz;

	GLuint vao[2];
	GLuint vbo[6];

	GLuint vPosition;
	GLuint vAmbientDiffuseColor;
	GLuint vNormal;

	GLuint vSpecularColor;
	GLuint vSpecularExponent;
	GLuint model_view;
	GLuint projection;
	GLuint cursorX;
	GLuint cursorY;
	GLuint near;
	GLuint far;
	GLuint translate;

	GLuint program;

	Cursor *pCursor;
};

class Field : public GraphObject
{
public:
	Field(GLfloat minx,GLfloat maxx, GLfloat minz, GLfloat maxz) : dMinX(minx),dMaxX(maxx),dMinZ(minz),dMaxZ(maxz){}
	void Init();
	void Draw(Camera *);
	GLfloat GetMinX() const {return dMinX;}
	GLfloat GetMaxX() const {return dMaxX;}
	GLfloat GetMinZ() const {return dMinZ;}
	GLfloat GetMaxZ() const {return dMaxZ;}

private:
	glm::vec4		v4Vertices[3];

	GLfloat		dMinX;
	GLfloat		dMaxX;
	GLfloat		dMinZ;
	GLfloat		dMaxZ;
};

class Sphere : public GraphObject
{
public:
	Sphere(GLfloat r, Cursor *cursor) : GraphObject(cursor), radius(r) {}
	void Init();
	void Draw(Camera *);

	GLfloat GetRadius() const { return radius; }

private:
	glm::vec4	v4Vertices[97200];
	glm::vec3 	v3Normal[97200];

	GLfloat 	radius;
};



#endif
