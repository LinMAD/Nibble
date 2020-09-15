#include "Texture.h"

Texture::Texture()
{
	m_textureID = 0;
	m_width = 0;
	m_height = 0;
	bitDepth = 0;
	m_fileLocation = "";
}

Texture::Texture(const char* fileLoc)
{
	m_textureID = 0;
	m_width = 0;
	m_height = 0;
	bitDepth = 0;
	m_fileLocation = fileLoc;
}

bool Texture::loadTexture()
{
	unsigned char* texData = stbi_load(m_fileLocation, &m_width, &m_height, &bitDepth, 0);
	if (!texData)
	{
		printf("Failed to find: %s\n", m_fileLocation);
		return false;
	}

	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(texData);

	return true;
}

bool Texture::loadTextureWithAlpha()
{
	unsigned char* texData = stbi_load(m_fileLocation, &m_width, &m_height, &bitDepth, 0);
	if (!texData)
	{
		printf("Failed to find: %s\n", m_fileLocation);
		return false;
	}

	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(texData);

	return true;
}

void Texture::useTexture()
{
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void Texture::clearTexture()
{
	glDeleteTextures(1, &m_textureID);
	m_textureID = 0;
	m_width = 0;
	m_height = 0;
	bitDepth = 0;
	m_fileLocation = "";
}

Texture::~Texture()
{
	clearTexture();
}