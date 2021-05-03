
#ifndef __UTILITY
#define __UTILITY

#include <GL/glew.h>
#include <glm/glm.hpp>

class Utility
{
public:
	static GLfloat		MinMax(GLfloat x, GLfloat min, GLfloat max)
	{
		if (x < min)
			return min;
		else if (x > max)
			return max;
		else
			return x;
	}

	static GLfloat		Lim360(GLfloat angle)
	{
		if (angle >= 360)
			return angle - 360;
		else if (angle < 0)
			return angle + 360;
		else 
			return angle;
	}

	static glm::vec3 vec4_to_vec3(glm::vec4 v) { return glm::vec3(v.x,v.y,v.z);}
};

#endif
