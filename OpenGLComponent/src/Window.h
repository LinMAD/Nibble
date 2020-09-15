#pragma once

#include "stdio.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

class Window
{
private:
	GLFWwindow* m_mainWindow;

	GLint m_width, m_height;
	GLint m_bufferWidth, m_bufferHeight;

	bool m_keys[1024];

	GLfloat m_lastX;
	GLfloat m_lastY;
	GLfloat m_xChange;
	GLfloat m_yChange;
	bool m_mouseFirstMoved;

	void createCallbacks();
	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void handleMouse(GLFWwindow* window, double xPos, double yPos);
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);

	int initialise();

	GLint getBufferWidth() { return m_bufferWidth; }
	GLint getBufferHeight() { return m_bufferHeight; }

	bool getShouldClose() { return glfwWindowShouldClose(m_mainWindow); }

	bool* getsKeys() { return m_keys; }
	GLfloat getXChange();
	GLfloat getYChange();

	void swapBuffers() { glfwSwapBuffers(m_mainWindow); }

	~Window();
};