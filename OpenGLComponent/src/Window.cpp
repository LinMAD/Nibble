#include "Window.h"

Window::Window()
{
	m_width = 800;
	m_height = 600;

	for (size_t i = 0; i < 1024; i++)
	{
		m_keys[i] = 0;
	}

	m_xChange = 0.0f;
	m_yChange = 0.0f;
}

Window::Window(GLint windowWidth, GLint windowHeight)
{
	m_width = windowWidth;
	m_height = windowHeight;

	for (size_t i = 0; i < 1024; i++)
	{
		m_keys[i] = 0;
	}

	m_xChange = 0.0f;
	m_yChange = 0.0f;
}

int Window::initialise()
{
	if (!glfwInit())
	{
		printf("Error Initialising GLFW");
		glfwTerminate();
		return 1;
	}

	// Setup GLFW Windows Properties
	// OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Core Profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Allow forward compatiblity
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create the window
	m_mainWindow = glfwCreateWindow(m_width, m_height, "Test Window", NULL, NULL);
	if (!m_mainWindow)
	{
		printf("Error creating GLFW window!");
		glfwTerminate();
		return 1;
	}

	// Get buffer size information
	glfwGetFramebufferSize(m_mainWindow, &m_bufferWidth, &m_bufferHeight);

	// Set the current context
	glfwMakeContextCurrent(m_mainWindow);

	// Handle Key + Mouse Input
	createCallbacks();
	glfwSetInputMode(m_mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Allow modern extension access
	glewExperimental = GL_TRUE;

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		printf("Error: %s", glewGetErrorString(error));
		glfwDestroyWindow(m_mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST);

	// Create Viewport
	glViewport(0, 0, m_bufferWidth, m_bufferHeight);

	glfwSetWindowUserPointer(m_mainWindow, this);
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(m_mainWindow, handleKeys);
	glfwSetCursorPosCallback(m_mainWindow, handleMouse);
}

GLfloat Window::getXChange()
{
	GLfloat theChange = m_xChange;
	m_xChange = 0.0f;
	return theChange;
}

GLfloat Window::getYChange()
{
	GLfloat theChange = m_yChange;
	m_yChange = 0.0f;
	return theChange;
}

void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->m_keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->m_keys[key] = false;
		}
	}
}

void Window::handleMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->m_mouseFirstMoved)
	{
		theWindow->m_lastX = xPos;
		theWindow->m_lastY = yPos;
		theWindow->m_mouseFirstMoved = false;
	}

	theWindow->m_xChange = xPos - theWindow->m_lastX;
	theWindow->m_yChange = theWindow->m_lastY - yPos;

	theWindow->m_lastX = xPos;
	theWindow->m_lastY = yPos;
}

Window::~Window()
{
	glfwDestroyWindow(m_mainWindow);
	glfwTerminate();
}