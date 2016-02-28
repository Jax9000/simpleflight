#include <iostream>

#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "SOIL\soil.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "assimp/cimport.h"

#include "WindowController.h"

#define WIDTH 1400
#define HEIGHT 800

//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool keys[1024];


GLint GlewInit()
{
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		return -1;

	glViewport(0, 0, WIDTH, HEIGHT);
	glEnable(GL_DEPTH_TEST);
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

	GlewInit();

	Scene scene;

	string nanosuit_path = "./Resources/Models/nanosuit/nanosuit.obj";
	Shader* shader = new Shader("./model.vs", "./model.frag");
	Model* nanosuit_model = new Model(nanosuit_path);
	GameObject* nanosuit = new GameObject("nanosuit", nanosuit_model, shader);
	nanosuit->Transform(glm::vec3(2.0f, 0.0f, 0.0f));
	scene.Add(nanosuit);

	GameObject* nanosuit1 = new GameObject("nanosuit_clone", nanosuit_model, shader);
	nanosuit1->Transform(glm::vec3(3.0f, 5.0f, 5.0f));
	scene.Add(nanosuit1);


	windowController->Update(scene);

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
	glfwTerminate();
	system("pause");
	return 0;
}