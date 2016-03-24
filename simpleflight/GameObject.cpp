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

void GameObject::Update()
{
}

void GameObject::ApplyForce(glm::vec3 force, glm::vec3 rel_pos)
{
	PhysicController::GetInstance().ApplyForce(this, force, rel_pos);
}

void GameObject::ApplyTransformedForce(glm::vec3 force, glm::vec3 rel_pos)
{
	auto relative_matrix = glm::translate(model_matrix, rel_pos);
	PhysicController::GetInstance().ApplySimpleForce(this, force, rel_pos);
}

void GameObject::ApplyTorqueForce(glm::vec3 torque)
{
	PhysicController::GetInstance().ApplyTorqueForce(this, torque);
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

void GameObject::PrintModelMatrix()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << fixed << setprecision(2);
			cout << model_matrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << "-------------" << endl;
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

glm::mat4* GameObject::GetModelMatrix()
{
	return &model_matrix;
}

void GameObject::SetModelMatrix(glm::mat4 matrix)
{
	model_matrix = matrix;
}

glm::vec3 GameObject::GetPosition()
{
	glm::vec3 position;
	for (int i = 0; i < 3; i++)
		position[i] = model_matrix[3][i];
	return position;
}

glm::vec3 GameObject::GetRotation()
{
	glm::vec3 euler;
	return euler;
}
