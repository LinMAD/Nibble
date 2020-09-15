#pragma once
#include "Light.h"

class DirectionalLight : public Light
{
private:
	glm::vec3 m_direction;
public:
	DirectionalLight();
	DirectionalLight(
		GLfloat shadowWidth, GLfloat shadowHeight,
		GLfloat red, GLfloat green, GLfloat blue,
		GLfloat aIntensity, GLfloat dIntensity,
		GLfloat xDir, GLfloat yDir, GLfloat zDir
	);

	void useLight(
		GLfloat ambientIntensityLocation, GLfloat ambientColourLocation,
		GLfloat diffuseIntensityLocation, GLfloat directionLocation
	);

	glm::mat4 CalculateLightTransform();

	~DirectionalLight();
};
