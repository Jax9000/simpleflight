#include <iostream>
#include <fstream>

#include "GL\glew.h"
#include "GLFW\glfw3.h"

GLFWwindow* WindowInit()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Simple Flight Simulator", nullptr, nullptr);

	if (window != nullptr)
	{
		glfwMakeContextCurrent(window);
	}

	return window;
}

GLint GlewInit()
{
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		return -1;

	glViewport(0, 0, 800, 600);
	return 0;
}

void KeyEvent(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// When a user presses the escape key, we set the WindowShouldClose property to true, 
	// closing the application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

GLint Terminate(GLchar* message)
{
	std::cout << message << std::endl;
	glfwTerminate();
	system("pause");
	return -1;
}

GLuint CompileShader(GLenum shaderType, const GLchar* shaderSource, GLchar* shaderName)
{
	GLuint shader;
	shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);

	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::" << shaderName << "::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return shader;
}

GLuint CreateProgram(GLuint vertexShader, GLuint fragmentShader)
{
	GLuint shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	GLint success;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[512];
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::LINK\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

const GLchar* vertexShaderSource = 
"#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\0";

const GLchar* fragmentShaderSource =
"#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"	color = vec4(1.0f, 1f, 0.2f, 1.0f);\n"
"}\0";

int main()
{
	GLFWwindow* window = WindowInit();
	if (window == nullptr)
		return Terminate("Failed to create window...");

	if (GlewInit() != 0)
		return Terminate("Failed to init glew");

	GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource, "VERTEX");
	GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource, "FRAGMENT");
	GLuint shaderProgram = CreateProgram(vertexShader, fragmentShader);

	glfwSetKeyCallback(window, KeyEvent);

	GLfloat vertices[] = {
		0.0f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f
	};

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window))
	{
		//events
		glfwPollEvents();

		//rendering
		glClearColor(1, 0.85f, 0.3f, 0.8f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}