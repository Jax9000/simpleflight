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
}

GameObject::~GameObject()
{
}

void GameObject::Draw(glm::mat4 projection, glm::mat4 view)
{
	shader->Use();
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "model"), 1, GL_FALSE, glm::value_ptr(model_matrix));
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

glm::mat4 GameObject::GetModelMatrix()
{
	return model_matrix;
}
