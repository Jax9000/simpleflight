#include "Scene.h"



Scene::Scene()
{
}


Scene::~Scene()
{
}

void Scene::Draw(int width, int height)
{
	PhysicController::GetInstance().Update();

	for (GameObject* object : game_objects)
	{
		object->Update();
	}

	glm::mat4 projection = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 100000.0f);
	glm::mat4 view = camera->GetViewMatrix();

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

void Scene::AttachCamera(FollowCamera* camera)
{
	this->camera = camera;
}
