#include "AirPlane.h"

AirPlane::AirPlane(string name, Model* model, Shader* shader) : GameObject(name, model, shader)
{
	EventController::AddKeyListener(this);
}

AirPlane::~AirPlane()
{
}

void AirPlane::OnKeyPress(int key)
{
	OnKey(key);
}

void AirPlane::OnKeyHold(int key)
{
	OnKey(key);
}

void AirPlane::OnKey(int key)
{
	auto delta_time = Time::GetDeltaTime();

	switch (key)
	{
	case GLFW_KEY_UP:
		ApplyTorqueForce(glm::vec3(-400, 0, 0));
		break;
	case GLFW_KEY_DOWN:
		ApplyTorqueForce(glm::vec3(400, 0, 0));
		break;
	case GLFW_KEY_LEFT:
		ApplyTorqueForce(glm::vec3(0, 0, 50));
		break;
	case GLFW_KEY_RIGHT:
		ApplyTorqueForce(glm::vec3(0, 0, -50));
		break;
	case GLFW_KEY_Q:
		ApplyTorqueForce(glm::vec3(0, 100, 0));
		break;
	case GLFW_KEY_E:
		ApplyTorqueForce(glm::vec3(0, -100, 0));
		break;
	case GLFW_KEY_LEFT_ALT:
		ApplyTransformedForce(glm::vec3(0, 100, 0), glm::vec3(0, 0, 0));
		break;
	case GLFW_KEY_RIGHT_SHIFT:
		ApplyForce(glm::vec3(0, 0, -10), glm::vec3(0, 0, 0));
		break;
	case GLFW_KEY_0:
		PhysicController::GetInstance().Reset(this);
		break;
	case GLFW_KEY_RIGHT_ALT:
		ApplyTransformedForce(glm::vec3(0, 1000, 0), glm::vec3(0, 0, 0));
	}
}

void AirPlane::Update()
{
	//ApplyForce(glm::vec3(0, 10, 0), glm::vec3(0, 0, 0));
}

void AirPlane::accelerate(float value)
{
	if (speed + value > max_speed)
		speed = max_speed;
	else if (speed + value < max_back_speed)
		speed = max_back_speed;
	else
		speed += value;
}

void AirPlane::SetModelMatrix(glm::mat4 matrix)
{
	model_matrix = matrix;
	//model_matrix[3][1] -= 10; //to show model plane properly (box shape collider sets bad Y position)
}
