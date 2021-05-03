#ifndef __LIGHTSOURCE_H
#define __LIGHTSOURCE_H

#include <GL/glew.h>
#include <list>
#include <vector>
#include <glm/glm.hpp>

using namespace std;

class	LightSource
{
public:

	LightSource():v4Position(glm::vec4(0,0,0,1)),v4Color(glm::vec4(0,0,0,1)),v4Direction(glm::vec4(0,0,0,0)),glfCutoffAngle(0){}
	LightSource(glm::vec4 pos, glm::vec4 color, glm::vec4 direction,GLfloat angle) : v4Position(pos),v4Color(color),v4Direction(direction),glfCutoffAngle(angle) {}

	void	SetPosition(glm::vec4 pos) {v4Position = pos;}
	glm::vec4	GetPosition() const {return v4Position;}
	void	SetColor(glm::vec4 color) {v4Color = color;}
	glm::vec4	GetColor() const {return v4Color;}
	void	SetDirection(glm::vec4 dir) {v4Direction = dir;}
	glm::vec4	GetDirection() const {return v4Direction;}
	void	SetCutoffAngle(GLfloat angle)  {glfCutoffAngle = angle;}
	GLfloat GetCutoffAngle() const {return glfCutoffAngle;}
private:
	glm::vec4	v4Position;
	glm::vec4	v4Color;
	glm::vec4	v4Direction;
	GLfloat	glfCutoffAngle;
};


class	LightSourceManager : private vector<LightSource *>
{
public:

	static  LightSourceManager* GetInstance() { if (!lightSourceManager) return  lightSourceManager = new LightSourceManager(); else return lightSourceManager;}

	void AddLightSource(LightSource *s) {push_back(s);}
	int	 GetNumberOfLights() const {return size();}

	~LightSourceManager() {if(lightSourceManager) delete lightSourceManager; lightSourceManager = 0; }

	LightSource*	GetLightNumber(unsigned int pos) { if (size() > pos) return at(pos); else return 0;}
private:

	static LightSourceManager *lightSourceManager;
};



#endif
