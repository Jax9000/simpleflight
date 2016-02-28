#include "GameObject.h"

GameObject::GameObject()
{
	name = "object";
}

GameObject::GameObject(std::string name, Model* model, Shader* shader)
{
	this->name = name;
	this->shader = shader;
	this->model = model;
	has_model_matrix = true;
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
	model_matrix = glm::translate(model_matrix, value);
}

void GameObject::Rotate(glm::vec3 value)
{
	model_matrix = glm::scale(model_matrix, value);
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

bool GameObject::HasModelMatrix()
{
	return has_model_matrix;
}

glm::mat4 GameObject::GetModelMatrix()
{
	return model_matrix;
}
