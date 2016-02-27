#include "GameObject.h"

GameObject::GameObject(std::string name, Model* model, Shader* shader)
{
	this->name = name;
	this->shader = shader;
	this->model = model;
}

GameObject::~GameObject()
{
}

void GameObject::Draw()
{
	model->Draw(*shader);
}

void GameObject::Transform(glm::vec3 value)
{
	model_matrix = glm::translate(model_matrix, value); // Translate it down a bit so it's at the center of the scene
}

void GameObject::Rotate(glm::vec3 value)
{
	model_matrix = glm::scale(model_matrix, value);	// It's a bit too big for our scene, so scale it down
}

string GameObject::GetName()
{
	return name;
}

void GameObject::SetName(string text)
{
	this->name = text;
}

Shader* GameObject::GetShader()
{
	return shader;
}

void GameObject::SetShader(Shader* shader)
{
	this->shader = shader;
}

glm::mat4 GameObject::GetModelMatrix()
{
	return model_matrix;
}
