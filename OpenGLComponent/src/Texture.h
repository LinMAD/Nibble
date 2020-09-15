#pragma once

#include <GL\glew.h>

#include "stb_image.h"

class Texture
{
private:
	GLuint m_textureID;
	int m_width, m_height, bitDepth;

	const char* m_fileLocation;
public:
	Texture();
	Texture(const char* fileLoc);

	bool loadTexture();
	bool loadTextureWithAlpha();

	void useTexture();
	void clearTexture();

	~Texture();
};
