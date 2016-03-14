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

GameObject::GameObject(const GameObject& object)
{
	this->model = object.model;
	this->shader = object.shader;
	this->model_matrix = object.model_matrix;
	this->name = object.name + "Clone";
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

void GameObject::Scale(glm::vec3 value)
{
	model_matrix = glm::scale(model_matrix, value);
}

void GameObject::Rotate(glm::vec3 value)
{
	model_matrix = glm::rotate(model_matrix, value.x, glm::vec3(1.0f, 0.0f, 0.0f));
	model_matrix = glm::rotate(model_matrix, value.y, glm::vec3(0.0f, 1.0f, 0.0f));
	model_matrix = glm::rotate(model_matrix, value.z, glm::vec3(0.0f, 0.0f, 1.0f));
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
