#include "Scene.h"



Scene::Scene()
{
	camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
}


Scene::~Scene()
{
}

void Scene::Draw(int width, int height)
{
	glm::mat4 projection = glm::perspective(camera->Zoom, (float)width / (float)height, 0.1f, 100000.0f);
	glm::mat4 view = camera->GetViewMatrix();

	PhysicController::GetInstance().Update();

	for (GameObject* object : game_objects)
	{
		object->Update();
	}

	for (GameObject* object : game_objects)
	{
		object->Draw(projection, view);
		object->GetModelMatrix();
	}
}

void Scene::Add(GameObject* object)
{
	game_objects.push_back(object);
}