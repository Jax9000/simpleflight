#include <iostream>

#include "GL\glew.h"
#include "GLFW\glfw3.h"

#include "shader.h"

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
	if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_ENTER) && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

GLint Terminate(GLchar* message)
{
	std::cout << message << std::endl;
	glfwTerminate();
	system("pause");
	return -1;
}


int main()
{
	GLFWwindow* window = WindowInit();
	if (window == nullptr)
		return Terminate("Failed to create window...");

	if (GlewInit() != 0)
		return Terminate("Failed to init glew");

	Shader* shader = new Shader("./shader.vs", "./shader.frag");

	glfwSetKeyCallback(window, KeyEvent);

	GLfloat vertices[] = {
		0.50f, 0.50f, 0.0f,
		1.0f, 0.0f, 0.0f,
		
		-0.50f, -0.50f, 0.0f,
		0.0f, 0.0f, 1.0f,
		
		0.50f, -0.50f, 0.0f,
		1.0f, 1.0f, 0.0f,
		
		-0.50f, 0.50f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 2,   // First Triangle
		0, 1, 3    // Second Triangle
	};

	GLuint VBO;
	glGenBuffers(1, &VBO);
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	GLuint EBO;
	glGenBuffers(1, &EBO);
	
	glBindVertexArray(VAO);
		
		glBindBuffer(GL_ARRAY_BUFFER, VBO);				
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	


	while (!glfwWindowShouldClose(window))
	{
		//events
		glfwPollEvents();

		//rendering
		glClearColor(1, 0.85f, 0.3f, 0.8f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO);

			shader->Use();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}