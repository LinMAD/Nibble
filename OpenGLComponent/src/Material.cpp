#include "Material.h"

Material::Material()
{
	m_specularIntensity = 0.0f;
	m_shininess = 0.0f;
}

Material::Material(GLfloat sIntensity, GLfloat shine)
{
	m_specularIntensity = sIntensity;
	m_shininess = shine;
}

void Material::useMaterial(GLuint specularIntensityLocation, GLuint shininessLocation)
{
	glUniform1f(specularIntensityLocation, m_specularIntensity);
	glUniform1f(shininessLocation, m_shininess);
}

Material::~Material()
{
}