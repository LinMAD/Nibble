#pragma once
#include "PointLight.h"
class SpotLight : public PointLight
{
private:
	glm::vec3 m_direction;

	GLfloat m_edge, m_procEdge;

	bool m_isOn;
public:
	SpotLight();

	SpotLight(GLfloat shadowWidth, GLfloat shadowHeight,
		GLfloat near, GLfloat far,
		GLfloat red, GLfloat green, GLfloat blue,
		GLfloat aIntensity, GLfloat dIntensity,
		GLfloat xPos, GLfloat yPos, GLfloat zPos,
		GLfloat xDir, GLfloat yDir, GLfloat zDir,
		GLfloat con, GLfloat lin, GLfloat exp,
		GLfloat edg);

	void useLight(
		GLuint ambientIntensityLocation, GLuint ambientColourLocation,
		GLuint diffuseIntensityLocation, GLuint positionLocation, GLuint directionLocation,
		GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation,
		GLuint edgeLocation
	);

	void setFlash(glm::vec3 pos, glm::vec3 dir);
	void setPosition(glm::vec3 pos);
	void toggle() { m_isOn = !m_isOn; }

	~SpotLight();
};
