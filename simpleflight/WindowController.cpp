#include "WindowController.h"
#include <iostream>

WindowController::WindowController()
{
	init();
}

WindowController::~WindowController()
{
}

WindowController& WindowController::GetInstance()
{
	static WindowController instance;
	return instance;
}

void WindowController::init()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	glfw_window = glfwCreateWindow(800, 800, "Simple Flight Simulator", nullptr, nullptr);

	if (glfw_window == nullptr)
	{
		std::cout << "Failed to initialize game window" << std::endl;
		return;
	}

	glfwMakeContextCurrent(glfw_window);
	glfwSetWindowPos(glfw_window, 50, 50);
	glfwSetKeyCallback(glfw_window, keyEvenetProvide);
	glfwSetCursorPosCallback(glfw_window, mouseEventProvide);
	glfwSetInputMode(glfw_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void WindowController::setWidth(int value)
{
	width = value;
	glfwSetWindowSize(glfw_window, value, height);
}

void WindowController::setHeight(int value)
{
	height = value;
	glfwSetWindowSize(glfw_window, width, value);
}

void WindowController::mouseEventProvide(GLFWwindow* window, double xpos, double ypos)
{
	EventController::MouseNotify(xpos, ypos);
}
void WindowController::keyEvenetProvide(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	EventController::KeyNotify(key, action);
}