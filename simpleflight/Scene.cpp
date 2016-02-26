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
	glm::mat4 projection = glm::perspective(camera->Zoom, (float)width / (float)height, 0.1f, 100.0f);
	glm::mat4 view = camera->GetViewMatrix();

	for (GameObject* object : game_objects)
	{
		Shader* shader = object->GetShader();
		shader->Use();

		glUniformMatrix4fv(glGetUniformLocation(shader->Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(shader->Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glm::mat4 model_matrix = object->GetModelMatrix();
		glUniformMatrix4fv(glGetUniformLocation(shader->Program, "model"), 1, GL_FALSE, glm::value_ptr(model_matrix));

		object->Draw();
	}
}

void Scene::Add(GameObject* object)
{
	game_objects.push_back(object);
}