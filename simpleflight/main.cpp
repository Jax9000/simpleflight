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

#define WIDTH 1400
#define HEIGHT 800

//glm::mat4 model, view, projection;
GLFWwindow* window;


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

GLFWwindow* WindowInit()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Simple Flight Simulator", nullptr, nullptr);

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

	glViewport(0, 0, WIDTH, HEIGHT);
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

// Moves/alters the camera positions based on user input
void Do_Movement()
{
	// Camera controls
	if (keys[GLFW_KEY_W])
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	//cout << key << endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

int main()
{
	window = WindowInit();
	if (window == nullptr)
		return Terminate("Failed to create window...");

	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glEnable(GL_DEPTH_TEST);

	if (GlewInit() != 0)
		return Terminate("Failed to init glew");

	Shader* shader = new Shader("./shader.vs", "./shader.frag");

	GLfloat vertices[] = {
		0.50f, 0.50f, 0.5f, //position
		1.0f, 0.0f, 0.0f,   //color
	    1.0f, 1.0f,		//texture 
		
		-0.50f, -0.50f, 0.5f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f,

		0.50f, -0.50f, 0.5f,
		1.0f, 1.0f, 0.0f,
		1.0f, 0.0f,
		
		-0.50f, 0.50f, 0.5f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f,
		/////////back///////////
		0.50f, 0.50f, -0.5f, //position
		1.0f, 0.0f, 0.0f,   //color
		1.0f, 1.0f,		//texture 

		-0.50f, -0.50f, -0.5f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f,

		0.50f, -0.50f, -0.5f,
		1.0f, 1.0f, 0.0f,
		1.0f, 0.0f,

		-0.50f, 0.50f, -0.5f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f,
		/////////left////////////
		-0.50f, 0.50f, -0.5f, //position
		1.0f, 0.0f, 0.0f,   //color
		0.0f, 1.0f,		//texture 

		-0.50f, -0.50f, 0.5f,
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f,

		-0.50f, 0.50f, 0.5f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f,

		-0.50f, -0.50f, -0.5f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f,
		/////////right////////////
		0.50f, -0.50f, -0.5f, //position
		1.0f, 0.0f, 0.0f,   //color
		1.0f, 0.0f,		//texture 

		0.50f, 0.50f, 0.5f,
		0.0f, 0.0f, 1.0f,
		0.0f, 1.0f,

		0.50f, -0.50f, 0.5f,
		1.0f, 1.0f, 0.0f,
		0.0f, 0.0f,

		0.50f, 0.50f, -0.5f,
		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f,
		/////////top////////////
		0.50f, 0.50f, 0.5f, //position
		1.0f, 0.0f, 0.0f,   //color
		0.0f, 1.0f,		//texture 

		-0.50f, 0.50f, -0.5f,
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f,

		-0.50f, 0.50f, 0.5f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f,

		0.50f, 0.50f, -0.5f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f,
		/////////bottom////////////
		-0.50f, -0.50f, 0.5f, //position
		1.0f, 0.0f, 0.0f,   //color
		0.0f, 1.0f,		//texture 

		0.50f, -0.50f, -0.5f,
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f,

		0.50f,- 0.50f, 0.5f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f,

		-0.50f, -0.50f, -0.5f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 2,   // First Triangle
		0, 1, 3,    // Second Triangle
		4, 5, 6,
		4, 5, 7,
		8, 9, 10,
		8, 9, 11,
		12, 13, 14,
		12, 13, 15,
		16, 17, 18,
		16, 17, 19,
		20, 21, 22,
		20, 21, 23
	};

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(0.50f,  0.0f, 1.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
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
		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
	Texture2D* wallTexture = new Texture2D("./Resources/Textures/wall.jpg");
	Texture2D* woodTexture = new Texture2D("./Resources/Textures/lmao.jpg");

	/*projection = glm::perspective(45.0f, (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
	model = glm::rotate(model, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::translate(view, glm::vec3(0, 0, -3.0f));*/
	
	GLint projectionLocation = glGetUniformLocation(shader->Program, "projection");
	GLint viewLocation = glGetUniformLocation(shader->Program, "view");
	GLint modelLocation = glGetUniformLocation(shader->Program, "model");

	Model nanosuit("./Resources/Models/nanosuit/nanosuit.obj");
	Shader modelShader("./model.vs", "./model.frag");

	while (!glfwWindowShouldClose(window))
	{
		// Set frame time
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Create camera transformation
		glm::mat4 view;
		view = camera.GetViewMatrix();
		glm::mat4 projection;
		projection = glm::perspective(camera.Zoom, (float)WIDTH / (float)HEIGHT, 0.1f, 1000.0f);
		
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
		//glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

		// Check and call events
		glfwPollEvents();
		Do_Movement();

		//rendering
		glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		wallTexture->Use();
		glUniform1i(glGetUniformLocation(shader->Program, "ourTexture0"), 0);
		
		glActiveTexture(GL_TEXTURE1);
		woodTexture->Use();
		glUniform1i(glGetUniformLocation(shader->Program, "ourTexture1"), 1);


		shader->Use();
		
		glBindVertexArray(VAO);
		for (GLuint i = 0; i < 10; i++)
		{
			glm::mat4 model;
			model = glm::translate(model, cubePositions[i]);
			GLfloat angle = 20.0f * i;
			if (i % 3 == 0)  // Every 3rd iteration (including the first) we set the angle using GLFW's time function.
				angle = glfwGetTime() * 25.0f;

			model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
			//glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);

		nanosuit.Draw(modelShader);
		glfwSwapBuffers(window);

	}

	glfwTerminate();
	return 0;
}