#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <GLM\glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>
#include <GLM\gtc\type_ptr.hpp>

#include "CommonValues.h"
#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
#include "Model.h"

const float toRadians = 3.14159265f / 180.0f;

GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
uniformSpecularIntensity = 0, uniformShininess = 0, uniformOmniLightPos = 0, uniformFarPlane = 0;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;
Shader directionalShadowShader;
Shader omniShadowShader;

Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;

Material shinyMaterial;
Material dullMaterial;

Model cube, cylinder, icosphere, cone, tree;

DirectionalLight mainLight;
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

unsigned int pointLightCount = 0;
unsigned int spotLightCount = 0;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

GLfloat icospereAngle = 0.0f;
GLfloat icospereMovment = 0.f;
bool icospereMovmentIsNegative = false;

// Vertex Shader
static const char* vShader = "Shaders/shader.vert";

// Fragment Shader
static const char* fShader = "Shaders/shader.frag";

void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}

void CreateObjects()
{
	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};

	Mesh* obj1 = new Mesh();
	obj1->createMesh(floorVertices, floorIndices, 32, 12);
	meshList.push_back(obj1);
}

void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->createFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	directionalShadowShader = Shader();
	directionalShadowShader.createFromFiles(
		"Shaders/Shadows/directional_shadow_map.vert",
		"Shaders/Shadows/directional_shadow_map.frag"
	);
	omniShadowShader = Shader();
	omniShadowShader.createFromFiles(
		"Shaders/Shadows/omni_directional_shadow_map.vert",
		"Shaders/Shadows/omni_directional_shadow_map.geom",
		"Shaders/Shadows/omni_directional_shadow_map.frag"
	);
}

void RenderScene()
{
	// Floor
	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	plainTexture.useTexture();
	dullMaterial.useMaterial(uniformSpecularIntensity, uniformShininess);
	meshList[0]->renderMesh();

	model = glm::translate(model, glm::vec3(0.0f, 19.0f, 0.f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	plainTexture.useTexture();
	dullMaterial.useMaterial(uniformSpecularIntensity, uniformShininess);
	meshList[0]->renderMesh();

	icospereAngle += 0.1f;
	if (icospereAngle > 360.0f) icospereAngle = 0.1f;

	if (icospereMovment >= 9.f) icospereMovmentIsNegative = true;
	else if (icospereMovment <= 0.f) icospereMovmentIsNegative = false;

	//if (icospereMovmentIsNegative) icospereMovment -= 0.01f;
	//else icospereMovment += 0.01f;

	// icosphere
	//model = glm::mat4(1.0f);
	//model = glm::translate(model, glm::vec3(1.5f, -0.5f, icospereMovment));
	//model = glm::rotate(model, icospereAngle * toRadians * 4, glm::vec3(1.0f, 0.0f, 0.0f));
	//model = glm::rotate(model, icospereAngle * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
	//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
	//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	//shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
	//icosphere.RenderModel();

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(3.0f, 2.0f, 0.0f));
	//model = glm::rotate(model, 0.f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	//model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	dullMaterial.useMaterial(uniformSpecularIntensity, uniformShininess);
	tree.renderModel();
}

void DirectionalShadowMapPass(DirectionalLight* light)
{
	directionalShadowShader.useShader();

	glViewport(0, 0, light->getShadowMap()->getShadowWidth(), light->getShadowMap()->getShadowHeight());

	light->getShadowMap()->write();
	glClear(GL_DEPTH_BUFFER_BIT);

	uniformModel = directionalShadowShader.getModelLocation();
	directionalShadowShader.setDirectionalLightTransform(&light->CalculateLightTransform());

	directionalShadowShader.validate();
	RenderScene();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OmniShadowMapPass(PointLight* light)
{
	glViewport(0, 0, light->getShadowMap()->getShadowWidth(), light->getShadowMap()->getShadowHeight());

	omniShadowShader.useShader();
	uniformModel = omniShadowShader.getModelLocation();
	uniformOmniLightPos = omniShadowShader.getOmniLightPosLocation();
	uniformFarPlane = omniShadowShader.getFarPlaneLocation();

	light->getShadowMap()->write();

	glClear(GL_DEPTH_BUFFER_BIT);

	glUniform3f(uniformOmniLightPos, light->getPosition().x, light->getPosition().y, light->getPosition().z);
	glUniform1f(uniformFarPlane, light->getFarPlane());
	omniShadowShader.setOmniLightMatrices(light->calculateLightTransform());

	omniShadowShader.validate();
	RenderScene();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderPass(glm::mat4 projectionMatrix, glm::mat4 viewMatrix)
{
	shaderList[0].useShader();

	uniformModel = shaderList[0].getModelLocation();
	uniformProjection = shaderList[0].getProjectionLocation();
	uniformView = shaderList[0].getViewLocation();
	uniformEyePosition = shaderList[0].getEyePositionLocation();
	uniformSpecularIntensity = shaderList[0].getSpecularIntensityLocation();
	uniformShininess = shaderList[0].getShininessLocation();

	glViewport(0, 0, 1366, 768);

	// Clear the window
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

	shaderList[0].setDirectionalLight(&mainLight);
	shaderList[0].setPointLights(pointLights, pointLightCount, 3, 0);
	shaderList[0].setSpotLights(spotLights, spotLightCount, 3 + pointLightCount, pointLightCount);
	shaderList[0].setDirectionalLightTransform(&mainLight.CalculateLightTransform());

	mainLight.getShadowMap()->read(GL_TEXTURE2);

	shaderList[0].setTexture(1);
	shaderList[0].setDirectionalShadowMap(2);

	//glm::vec3 lowerLight = camera.getCameraPosition();
	//lowerLight.y -= 0.3f;
	//spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());

	shaderList[0].validate();
	RenderScene();
}

int main()
{
	mainWindow = Window(1280, 720); // 16:9
	mainWindow.initialise();

	CreateObjects();
	CreateShaders();

	camera = Camera(
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		-60.0f,
		0.0f,
		5.0f,
		0.5f
	);

	brickTexture = Texture("Textures/brick.png");
	brickTexture.loadTextureWithAlpha();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.loadTextureWithAlpha();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.loadTextureWithAlpha();

	shinyMaterial = Material(4.0f, 256);
	dullMaterial = Material(0.3f, 4);

	tree = Model();
	tree.loadModel("Models/tree.obj");

	mainLight = DirectionalLight(
		2048, 2048,
		1.0f, 1.0f, 1.0f, // colour
		0.0f, 0.3f,
		0.0f, 0.0f, 0.0f // direction
	);

	pointLights[0] = PointLight(
		1024, 1024,
		0.0f, 0.3f,
		1.0f, 1.0f, 1.0f,  // colour
		0.1f, 1.0f,
		-5.0f, 0.0f, 0.0f, // pos
		0.3f, 0.01f, 0.01f
	);

	pointLightCount++;

	spotLights[0] = SpotLight(
		1024, 1024,
		0.1f, 50.0f,
		1.0f, 1.0f, 1.0f, // colour
		0.0f, 0.9f,
		0.0f, 10.0f, 0.0f, // poos
		5.0f, -1.0f, 3.0f, // dir
		1.0f, 0.0f, 0.0f,
		90.0f
	);

	spotLightCount++;

	glm::mat4 projection = glm::perspective(
		glm::radians(60.0f),
		(GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(),
		0.1f,
		100.0f
	);

	while (!mainWindow.getShouldClose())
	{
		// Delta time
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		lastTime = now;

		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		if (mainWindow.getsKeys()[GLFW_KEY_L])
		{
			spotLights[0].toggle();
			mainWindow.getsKeys()[GLFW_KEY_L] = false;
		}

		DirectionalShadowMapPass(&mainLight);

		for (size_t i = 0; i < pointLightCount; i++) OmniShadowMapPass(&pointLights[i]);
		for (size_t i = 0; i < spotLightCount; i++) OmniShadowMapPass(&spotLights[i]);

		RenderPass(projection, camera.calculateViewMatrix());

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}