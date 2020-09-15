#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <GL\glew.h>
#include <GLM\glm.hpp>
#include <GLM\gtc\type_ptr.hpp>

#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

class Shader
{
private:
	int m_pointLightCount;
	int m_spotLightCount;

	GLuint m_shaderID,
		m_uniformProjection, m_uniformModel, m_uniformView, m_uniformEyePosition,
		m_uniformSpecularIntensity, m_uniformShininess,
		m_uniformTexture,
		m_uniformDirectionalLightTransform, m_uniformDirectionalShadowMap,
		m_uniformOmniLightPos, uniformFarPlane;

	GLuint m_uniformLightMatrices[MAX_POINT_LIGHTS + MAX_SPOT_LIGHTS];

	struct DirectionalLightStructure {
		GLuint uniformColour;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;

		GLuint uniformDirection;
	} m_uniformDirectionalLight;

	GLuint m_uniformPointLightCount;

	struct PointLightStructure {
		GLuint uniformColour;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;

		GLuint uniformPosition;
		GLuint uniformConstant;
		GLuint uniformLinear;
		GLuint uniformExponent;
	} m_uniformPointLight[MAX_POINT_LIGHTS];

	GLuint m_uniformSpotLightCount;

	struct SpotLightStructure {
		GLuint uniformColour;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;

		GLuint uniformPosition;
		GLuint uniformConstant;
		GLuint uniformLinear;
		GLuint uniformExponent;

		GLuint uniformDirection;
		GLuint uniformEdge;
	} m_uniformSpotLight[MAX_SPOT_LIGHTS];

	struct ShadowMapStructure {
		GLuint uniformShadowMap;
		GLuint uniformFarPlane;
	} m_uniformOmniShadowMap[MAX_POINT_LIGHTS + MAX_SPOT_LIGHTS];

	void compileShader(const char* vertexCode, const char* fragmentCode);
	void compileShader(const char* vertexCode, const char* geometryCode, const char* fragmentCode);
	void addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);

	void compileProgram();
public:
	Shader();

	void createFromString(const char* vertexCode, const char* fragmentCode);
	void createFromFiles(const char* vertexLocation, const char* fragmentLocation);
	void createFromFiles(const char* vertexLocation, const char* geometryLocation, const char* fragmentLocation);

	void validate();

	std::string readFile(const char* fileLocation);

	GLuint getProjectionLocation();
	GLuint getModelLocation();
	GLuint getViewLocation();
	GLuint getAmbientIntensityLocation();
	GLuint getAmbientColourLocation();
	GLuint getDiffuseIntensityLocation();
	GLuint getDirectionLocation();
	GLuint getSpecularIntensityLocation();
	GLuint getShininessLocation();
	GLuint getEyePositionLocation();
	GLuint getOmniLightPosLocation();
	GLuint getFarPlaneLocation();

	void setDirectionalLight(DirectionalLight* dLight);
	void setPointLights(PointLight* pLight, unsigned int lightCount, unsigned int textureUnit, unsigned int offset);
	void setSpotLights(SpotLight* sLight, unsigned int lightCount, unsigned int textureUnit, unsigned int offset);
	void setTexture(GLuint textureUnit);
	void setDirectionalShadowMap(GLuint textureUnit);
	void setDirectionalLightTransform(glm::mat4* lTransform);

	void setOmniLightMatrices(std::vector<glm::mat4> lightMatrices);

	void useShader();
	void clearShader();

	~Shader();
};
