#include "Light.h"

Light::Light()
{
	m_colour = glm::vec3(1.0f, 1.0f, 1.0f);
	m_ambientIntensity = 1.0f;
	m_diffuseIntensity = 0.0f;
}

Light::Light(GLfloat shadowWidth, GLfloat shadowHeight, GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity)
{
	m_shadowMap = new ShadowMap();
	m_shadowMap->init(shadowWidth, shadowHeight);

	m_colour = glm::vec3(red, green, blue);
	m_ambientIntensity = aIntensity;
	m_diffuseIntensity = dIntensity;
}

Light::~Light()
{
}