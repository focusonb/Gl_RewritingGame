#include <glad/glad.h>
#include <iostream>

#include "GlfwConfigure.h"



using std::cout;
using std::endl;

//extern void framebuffer_size_callback(GLFWwindow* window, int width, int height);

GlfwConfigure* GlfwConfigure::m_singleton = nullptr;
GLFWwindow* GlfwConfigure::m_window = nullptr;
bool GlfwConfigure::run()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WINDOWS_WIDTH, WINDOWS_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	m_window = window;//creat a copy of the handle in case of being swept
	glfwMakeContextCurrent(window);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//hide cursor
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetMouseButtonCallback(window, mouseClick_callback);
	//load gl dynamic library
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	return true;
}

GLFWwindow * GlfwConfigure::getGlfWindowHandle() const
{
	return m_window;
}

GlfwConfigure * GlfwConfigure::getInstance()
{
	if (m_singleton != nullptr)
		return m_singleton;
	m_singleton = new GlfwConfigure();
	return m_singleton;
}
