#pragma once

#include <stdio.h>

#include <GL\glew.h>

class ShadowMap
{
protected:
	GLuint m_FBO, m_shadowMap;
	GLuint m_shadowWidth, m_shadowHeight;
public:
	ShadowMap();

	virtual bool init(GLuint width, GLuint height);
	virtual void write();
	virtual void read(GLenum textureUnit);

	GLuint getShadowWidth() { return m_shadowWidth; }
	GLuint getShadowHeight() { return m_shadowHeight; }

	~ShadowMap();
};
