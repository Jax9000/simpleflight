#include <iostream>

#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "SOIL\soil.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "assimp/cimport.h"

#include "Skybox.h"
#include "Plane.h"
#include "AirPlane.h"
#include "WindowController.h"
#include "PhysicController.h"
#include "FollowCamera.h"

#define WIDTH 1400
#define HEIGHT 800

string plane_dirpath = "./Resources/Textures";
string plane_texture_name = "grass.png";
string skybox_path = "./Resources/Textures/TropicalSunnyDay";
string skybox_file_extension = ".png";
string airplane_path = "./Resources/Models/Boeing 747/Boeing747.obj";
string building_path = "./Resources/Models/building/building.obj";

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
	//windowController->setHeight(800);
	//windowController->setWidth(1200);

	GlewInit();

	Scene scene;

	Shader* shader = new Shader("./model.vs", "./model.frag");

	Light light = Light::getInstance();
	Light::position = glm::vec3(5, 50, 5);

	Skybox* skybox = new Skybox(skybox_path, skybox_file_extension);
	scene.Add(skybox);

	Plane* plane = new Plane(plane_texture_name, plane_dirpath, shader, 10000);
	scene.Add(plane);
	Model* building_model = new Model(building_path);
	Model* airplane_model = new Model(airplane_path);
	AirPlane* airplane = new AirPlane("Boeing 747", airplane_model, shader);
	PhysicController::GetInstance().Add(airplane);
	scene.Add(airplane);

	FollowCamera* camera = new FollowCamera(airplane);
	scene.AttachCamera(camera);

	GameObject* building = new GameObject("Building", building_model, shader);
	building->Rotate(glm::vec3(0, 0, 90.0f));
	building->Transform(glm::vec3(11.8f * 5, 250, 0));
	building->Scale(glm::vec3(5, 5, 5));
	scene.Add(building);

	//building = new GameObject(*building);
	//building->Transform(glm::vec3(0, -5, 15.0f));
	//scene.Add(building);

	//Box* box = new Box("box", building_model, shader);
	//scene.Add(box);

	windowController->Update(scene);

	glfwTerminate();
	system("pause");
	return 0;
}