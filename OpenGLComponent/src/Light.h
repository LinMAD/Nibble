#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "ShadowMap.h"

class Light
{
protected:
	glm::vec3 m_colour;
	glm::mat4 m_lightProj;
	GLfloat m_ambientIntensity;
	GLfloat m_diffuseIntensity;

	ShadowMap* m_shadowMap;
public:
	Light();
	Light(GLfloat shadowWidth, GLfloat shadowHeight,
		GLfloat red, GLfloat green, GLfloat blue,
		GLfloat aIntensity, GLfloat dIntensity);

	ShadowMap* getShadowMap() { return m_shadowMap; }

	~Light();
};
