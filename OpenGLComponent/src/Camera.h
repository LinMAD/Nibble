#pragma once

#include <GL\glew.h>
#include <GLM\glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>
#include <GLFW\glfw3.h>

class Camera
{
private:
	glm::vec3 m_position;
	glm::vec3 m_front;
	glm::vec3 m_up;
	glm::vec3 m_right;
	glm::vec3 m_worldUp;

	GLfloat m_yaw;
	GLfloat m_pitch;

	GLfloat m_moveSpeed;
	GLfloat m_turnSpeed;

	void update();
public:
	Camera();
	Camera(
		glm::vec3 startPosition,
		glm::vec3 startUp,
		GLfloat startYaw,
		GLfloat startPitch,
		GLfloat startMoveSpeed,
		GLfloat startTurnSpeed
	);

	void keyControl(bool* keys, GLfloat deltaTime);
	void mouseControl(GLfloat xChange, GLfloat yChange);

	glm::vec3 getCameraPosition();
	glm::vec3 getCameraDirection();

	glm::mat4 calculateViewMatrix();

	~Camera();
};
