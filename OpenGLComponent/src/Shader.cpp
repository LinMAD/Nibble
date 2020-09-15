#include "Shader.h"

Shader::Shader()
{
	m_shaderID = 0;
	m_uniformModel = 0;
	m_uniformProjection = 0;

	m_pointLightCount = 0;
	m_spotLightCount = 0;
}

void Shader::createFromString(const char* vertexCode, const char* fragmentCode)
{
	compileShader(vertexCode, fragmentCode);
}

void Shader::createFromFiles(const char* vertexLocation, const char* fragmentLocation)
{
	std::string vertexString = readFile(vertexLocation);
	std::string fragmentString = readFile(fragmentLocation);
	const char* vertexCode = vertexString.c_str();
	const char* fragmentCode = fragmentString.c_str();

	compileShader(vertexCode, fragmentCode);
}

void Shader::createFromFiles(const char* vertexLocation, const char* geometryLocation, const char* fragmentLocation)
{
	std::string vertexString = readFile(vertexLocation);
	std::string geometryString = readFile(geometryLocation);
	std::string fragmentString = readFile(fragmentLocation);
	const char* vertexCode = vertexString.c_str();
	const char* geometryCode = geometryString.c_str();
	const char* fragmentCode = fragmentString.c_str();

	compileShader(vertexCode, geometryCode, fragmentCode);
}

void Shader::validate()
{
	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glValidateProgram(m_shaderID);
	glGetProgramiv(m_shaderID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(m_shaderID, sizeof(eLog), NULL, eLog);
		printf("Error validating program: '%s'\n", eLog);
		return;
	}
}

std::string Shader::readFile(const char* fileLocation)
{
	std::string content;
	std::ifstream fileStream(fileLocation, std::ios::in);

	if (!fileStream.is_open()) {
		printf("Failed to read %s! File doesn't exist.", fileLocation);
		return "";
	}

	std::string line = "";
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

void Shader::compileShader(const char* vertexCode, const char* fragmentCode)
{
	m_shaderID = glCreateProgram();

	if (!m_shaderID)
	{
		printf("Error creating shader program!\n");
		return;
	}

	addShader(m_shaderID, vertexCode, GL_VERTEX_SHADER);
	addShader(m_shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	compileProgram();
}

void Shader::compileShader(const char* vertexCode, const char* geometryCode, const char* fragmentCode)
{
	m_shaderID = glCreateProgram();

	if (!m_shaderID)
	{
		printf("Error creating shader program!\n");
		return;
	}

	addShader(m_shaderID, vertexCode, GL_VERTEX_SHADER);
	addShader(m_shaderID, geometryCode, GL_GEOMETRY_SHADER);
	addShader(m_shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	compileProgram();
}

void Shader::compileProgram()
{
	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(m_shaderID);
	glGetProgramiv(m_shaderID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(m_shaderID, sizeof(eLog), NULL, eLog);
		printf("Error linking program: '%s'\n", eLog);
		return;
	}

	m_uniformProjection = glGetUniformLocation(m_shaderID, "projection");
	m_uniformModel = glGetUniformLocation(m_shaderID, "model");
	m_uniformView = glGetUniformLocation(m_shaderID, "view");
	m_uniformDirectionalLight.uniformColour = glGetUniformLocation(m_shaderID, "directionalLight.base.colour");
	m_uniformDirectionalLight.uniformAmbientIntensity = glGetUniformLocation(m_shaderID, "directionalLight.base.ambientIntensity");
	m_uniformDirectionalLight.uniformDirection = glGetUniformLocation(m_shaderID, "directionalLight.direction");
	m_uniformDirectionalLight.uniformDiffuseIntensity = glGetUniformLocation(m_shaderID, "directionalLight.base.diffuseIntensity");
	m_uniformSpecularIntensity = glGetUniformLocation(m_shaderID, "material.specularIntensity");
	m_uniformShininess = glGetUniformLocation(m_shaderID, "material.shininess");
	m_uniformEyePosition = glGetUniformLocation(m_shaderID, "eyePosition");

	m_uniformPointLightCount = glGetUniformLocation(m_shaderID, "pointLightCount");

	for (size_t i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		char locBuff[100] = { '\0' };

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.colour", i);
		m_uniformPointLight[i].uniformColour = glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.ambientIntensity", i);
		m_uniformPointLight[i].uniformAmbientIntensity = glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.diffuseIntensity", i);
		m_uniformPointLight[i].uniformDiffuseIntensity = glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].position", i);
		m_uniformPointLight[i].uniformPosition = glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].constant", i);
		m_uniformPointLight[i].uniformConstant = glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].linear", i);
		m_uniformPointLight[i].uniformLinear = glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].exponent", i);
		m_uniformPointLight[i].uniformExponent = glGetUniformLocation(m_shaderID, locBuff);
	}

	m_uniformSpotLightCount = glGetUniformLocation(m_shaderID, "spotLightCount");

	for (size_t i = 0; i < MAX_SPOT_LIGHTS; i++)
	{
		char locBuff[100] = { '\0' };

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.base.colour", i);
		m_uniformSpotLight[i].uniformColour = glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.base.ambientIntensity", i);
		m_uniformSpotLight[i].uniformAmbientIntensity = glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.base.diffuseIntensity", i);
		m_uniformSpotLight[i].uniformDiffuseIntensity = glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.position", i);
		m_uniformSpotLight[i].uniformPosition = glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.constant", i);
		m_uniformSpotLight[i].uniformConstant = glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.linear", i);
		m_uniformSpotLight[i].uniformLinear = glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.exponent", i);
		m_uniformSpotLight[i].uniformExponent = glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].direction", i);
		m_uniformSpotLight[i].uniformDirection = glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].edge", i);
		m_uniformSpotLight[i].uniformEdge = glGetUniformLocation(m_shaderID, locBuff);
	}

	for (size_t i = 0; i < MAX_SPOT_LIGHTS + MAX_POINT_LIGHTS; i++)
	{
		char locBuff[100] = { '\0' };

		snprintf(locBuff, sizeof(locBuff), "omniShadowMaps[%d].shadowMap", i);
		m_uniformOmniShadowMap[i].uniformShadowMap = glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "omniShadowMaps[%d].farPlane", i);
		m_uniformOmniShadowMap[i].uniformFarPlane = glGetUniformLocation(m_shaderID, locBuff);
	}

	m_uniformDirectionalLightTransform = glGetUniformLocation(m_shaderID, "directionalLightTransform");
	m_uniformTexture = glGetUniformLocation(m_shaderID, "theTexture");
	m_uniformDirectionalShadowMap = glGetUniformLocation(m_shaderID, "directionalShadowMap");

	m_uniformOmniLightPos = glGetUniformLocation(m_shaderID, "lightPos");
	uniformFarPlane = glGetUniformLocation(m_shaderID, "farPlane");

	for (size_t i = 0; i < 6; i++)
	{
		char locBuff[100] = { '\0' };

		snprintf(locBuff, sizeof(locBuff), "lightMatrices[%d]", i);
		m_uniformLightMatrices[i] = glGetUniformLocation(m_shaderID, locBuff);
	}
}

GLuint Shader::getProjectionLocation()
{
	return m_uniformProjection;
}
GLuint Shader::getModelLocation()
{
	return m_uniformModel;
}
GLuint Shader::getViewLocation()
{
	return m_uniformView;
}
GLuint Shader::getAmbientColourLocation()
{
	return m_uniformDirectionalLight.uniformColour;
}
GLuint Shader::getAmbientIntensityLocation()
{
	return m_uniformDirectionalLight.uniformAmbientIntensity;
}
GLuint Shader::getDiffuseIntensityLocation()
{
	return m_uniformDirectionalLight.uniformDiffuseIntensity;
}
GLuint Shader::getDirectionLocation()
{
	return m_uniformDirectionalLight.uniformDirection;
}
GLuint Shader::getSpecularIntensityLocation()
{
	return m_uniformSpecularIntensity;
}
GLuint Shader::getShininessLocation()
{
	return m_uniformShininess;
}
GLuint Shader::getEyePositionLocation()
{
	return m_uniformEyePosition;
}
GLuint Shader::getOmniLightPosLocation()
{
	return m_uniformOmniLightPos;
}
GLuint Shader::getFarPlaneLocation()
{
	return uniformFarPlane;
}

void Shader::setDirectionalLight(DirectionalLight* dLight)
{
	dLight->useLight(m_uniformDirectionalLight.uniformAmbientIntensity, m_uniformDirectionalLight.uniformColour,
		m_uniformDirectionalLight.uniformDiffuseIntensity, m_uniformDirectionalLight.uniformDirection);
}

void Shader::setPointLights(PointLight* pLight, unsigned int lightCount, unsigned int textureUnit, unsigned int offset)
{
	if (lightCount > MAX_POINT_LIGHTS) lightCount = MAX_POINT_LIGHTS;

	glUniform1i(m_uniformPointLightCount, lightCount);

	for (size_t i = 0; i < lightCount; i++)
	{
		pLight[i].useLight(m_uniformPointLight[i].uniformAmbientIntensity, m_uniformPointLight[i].uniformColour,
			m_uniformPointLight[i].uniformDiffuseIntensity, m_uniformPointLight[i].uniformPosition,
			m_uniformPointLight[i].uniformConstant, m_uniformPointLight[i].uniformLinear, m_uniformPointLight[i].uniformExponent);

		pLight[i].getShadowMap()->read(GL_TEXTURE0 + textureUnit + i);
		glUniform1i(m_uniformOmniShadowMap[i + offset].uniformShadowMap, textureUnit + i);
		glUniform1f(m_uniformOmniShadowMap[i + offset].uniformFarPlane, pLight[i].getFarPlane());
	}
}

void Shader::setSpotLights(SpotLight* sLight, unsigned int lightCount, unsigned int textureUnit, unsigned int offset)
{
	if (lightCount > MAX_SPOT_LIGHTS) lightCount = MAX_SPOT_LIGHTS;

	glUniform1i(m_uniformSpotLightCount, lightCount);

	for (size_t i = 0; i < lightCount; i++)
	{
		sLight[i].useLight(m_uniformSpotLight[i].uniformAmbientIntensity, m_uniformSpotLight[i].uniformColour,
			m_uniformSpotLight[i].uniformDiffuseIntensity, m_uniformSpotLight[i].uniformPosition, m_uniformSpotLight[i].uniformDirection,
			m_uniformSpotLight[i].uniformConstant, m_uniformSpotLight[i].uniformLinear, m_uniformSpotLight[i].uniformExponent,
			m_uniformSpotLight[i].uniformEdge);

		sLight[i].getShadowMap()->read(GL_TEXTURE0 + textureUnit + i);
		glUniform1i(m_uniformOmniShadowMap[i + offset].uniformShadowMap, textureUnit + i);
		glUniform1f(m_uniformOmniShadowMap[i + offset].uniformFarPlane, sLight[i].getFarPlane());
	}
}

void Shader::setTexture(GLuint textureUnit)
{
	glUniform1i(m_uniformTexture, textureUnit);
}

void Shader::setDirectionalShadowMap(GLuint textureUnit)
{
	glUniform1i(m_uniformDirectionalShadowMap, textureUnit);
}

void Shader::setDirectionalLightTransform(glm::mat4* lTransform)
{
	glUniformMatrix4fv(m_uniformDirectionalLightTransform, 1, GL_FALSE, glm::value_ptr(*lTransform));
}

void Shader::setOmniLightMatrices(std::vector<glm::mat4> lightMatrices)
{
	for (size_t i = 0; i < 6; i++)
	{
		glUniformMatrix4fv(m_uniformLightMatrices[i], 1, GL_FALSE, glm::value_ptr(lightMatrices[i]));
	}
}

void Shader::useShader()
{
	glUseProgram(m_shaderID);
}

void Shader::clearShader()
{
	if (m_shaderID != 0)
	{
		glDeleteProgram(m_shaderID);
		m_shaderID = 0;
	}

	m_uniformModel = 0;
	m_uniformProjection = 0;
}

void Shader::addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		printf("Error compiling the %d shader: '%s'\n", shaderType, eLog);
		return;
	}

	glAttachShader(theProgram, theShader);
}

Shader::~Shader()
{
	clearShader();
}