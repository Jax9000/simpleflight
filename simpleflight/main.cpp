#include <iostream>

#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "SOIL\soil.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "assimp/cimport.h"

#include "shader.h"
#include "texture2D.h"
#include "camera.cpp"
#include "Model.h"
#include "WindowController.h"

#define WIDTH 1400
#define HEIGHT 800

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool keys[1024];

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

GLfloat yaw = -90.0f;	// Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right (due to how Eular angles work) so we initially rotate a bit to the left.
GLfloat pitch = 0.0f;
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;


glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

GLint GlewInit()
{
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		return -1;

	glViewport(0, 0, WIDTH, HEIGHT);
	return 0;
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
	WindowController* windowController = &WindowController::GetInstance();
	if (windowController == nullptr)
		return Terminate("Failed to create window...");
	windowController->setHeight(800);
	windowController->setWidth(1200);

	Scene scene;
	
	windowController->Draw(scene);

	//glEnable(GL_DEPTH_TEST);

	//if (GlewInit() != 0)
	//	return Terminate("Failed to init glew");

	//Model nanosuit("./Resources/Models/nanosuit/nanosuit.obj");
	//Shader modelShader("./model.vs", "./model.frag");

	//while (!glfwWindowShouldClose(window))
	//{
	//	// Set frame time
	//	GLfloat currentFrame = glfwGetTime();
	//	deltaTime = currentFrame - lastFrame;
	//	lastFrame = currentFrame;

	//	// Check and call events
	//	glfwPollEvents();
	//	Do_Movement();

	//	// Clear the colorbuffer
	//	glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//	modelShader.Use();   // <-- Don't forget this one!
	//					// Transformation matrices
	//	glm::mat4 projection = glm::perspective(camera.Zoom, (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
	//	glm::mat4 view = camera.GetViewMatrix();
	//	glUniformMatrix4fv(glGetUniformLocation(modelShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	//	glUniformMatrix4fv(glGetUniformLocation(modelShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

	//	// Draw the loaded model
	//	glm::mat4 model;
	//	model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // Translate it down a bit so it's at the center of the scene
	//	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// It's a bit too big for our scene, so scale it down
	//	glUniformMatrix4fv(glGetUniformLocation(modelShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	//	nanosuit.Draw(modelShader);

	//	// Swap the buffers
	//	glfwSwapBuffers(window);
	//}
	system("pause");
	glfwTerminate();
	return 0;
}