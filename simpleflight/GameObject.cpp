#include "GameObject.h"

GameObject::GameObject(std::string name, std::string model_path, Shader* shader)
{
	this->name = name;
	this->shader = shader;
	model = new Model(model_path);
}

GameObject::~GameObject()
{
}

void GameObject::Draw()
{
	model->Draw(*shader);
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
