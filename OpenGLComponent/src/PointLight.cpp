#include "PointLight.h"

PointLight::PointLight() : Light()
{
	m_position = glm::vec3(0.0f, 0.0f, 0.0f);
	m_constant = 1.0f;
	m_linear = 0.0f;
	m_exponent = 0.0f;
}

PointLight::PointLight(GLfloat shadowWidth, GLfloat shadowHeight,
	GLfloat near, GLfloat far,
	GLfloat red, GLfloat green, GLfloat blue,
	GLfloat aIntensity, GLfloat dIntensity,
	GLfloat xPos, GLfloat yPos, GLfloat zPos,
	GLfloat con, GLfloat lin, GLfloat exp) : Light(shadowWidth, shadowHeight, red, green, blue, aIntensity, dIntensity)
{
	m_position = glm::vec3(xPos, yPos, zPos);
	m_constant = con;
	m_linear = lin;
	m_exponent = exp;

	float aspect = (float)shadowWidth / (float)shadowHeight;

	m_farPlane = far;
	m_lightProj = glm::perspective(glm::radians(90.0f), aspect, near, far);

	m_shadowMap = new OmniShadowMap();
	m_shadowMap->init(shadowWidth, shadowHeight);
}

void PointLight::useLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation,
	GLuint diffuseIntensityLocation, GLuint positionLocation,
	GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation)
{
	glUniform3f(ambientColourLocation, m_colour.x, m_colour.y, m_colour.z);
	glUniform1f(ambientIntensityLocation, m_ambientIntensity);
	glUniform1f(diffuseIntensityLocation, m_diffuseIntensity);

	glUniform3f(positionLocation, m_position.x, m_position.y, m_position.z);
	glUniform1f(constantLocation, m_constant);
	glUniform1f(linearLocation, m_linear);
	glUniform1f(exponentLocation, m_exponent);
}

std::vector<glm::mat4> PointLight::calculateLightTransform()
{
	std::vector<glm::mat4> lightTransforms;
	lightTransforms.push_back(m_lightProj *
		glm::lookAt(m_position, m_position + glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
	lightTransforms.push_back(m_lightProj *
		glm::lookAt(m_position, m_position + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
	lightTransforms.push_back(m_lightProj *
		glm::lookAt(m_position, m_position + glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)));
	lightTransforms.push_back(m_lightProj *
		glm::lookAt(m_position, m_position + glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 0.0, -1.0)));
	lightTransforms.push_back(m_lightProj *
		glm::lookAt(m_position, m_position + glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, -1.0, 0.0)));
	lightTransforms.push_back(m_lightProj *
		glm::lookAt(m_position, m_position + glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, -1.0, 0.0)));

	return lightTransforms;
}

glm::vec3 PointLight::getPosition()
{
	return m_position;
}

GLfloat PointLight::getFarPlane()
{
	return m_farPlane;
}

PointLight::~PointLight()
{
}