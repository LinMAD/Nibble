#pragma once
#include <vector>

#include "Light.h"
#include "OmniShadowMap.h"

class PointLight : public Light
{
protected:
	glm::vec3 m_position;

	GLfloat m_constant, m_linear, m_exponent;
	GLfloat m_farPlane;
public:
	PointLight();
	PointLight(
		GLfloat shadowWidth, GLfloat shadowHeight,
		GLfloat near, GLfloat far,
		GLfloat red, GLfloat green, GLfloat blue,
		GLfloat aIntensity, GLfloat dIntensity,
		GLfloat xPos, GLfloat yPos, GLfloat zPos,
		GLfloat con, GLfloat lin, GLfloat exp
	);

	void useLight(
		GLuint ambientIntensityLocation, GLuint ambientColourLocation,
		GLuint diffuseIntensityLocation, GLuint positionLocation,
		GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation
	);

	std::vector<glm::mat4> calculateLightTransform();

	glm::vec3 getPosition();
	GLfloat getFarPlane();

	~PointLight();
};
