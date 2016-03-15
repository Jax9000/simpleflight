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
		if (acceleration < max_acceleration)
			acceleration += delta_acceleration * delta_time;
		break;
	case GLFW_KEY_DOWN:
		if (acceleration > max_back_acceleration)
			acceleration -= delta_acceleration * delta_time;
		break;
	case GLFW_KEY_LEFT:
		Rotate(glm::vec3(0, 0, 10.0f * delta_time));
		break;
	case GLFW_KEY_RIGHT:
		Rotate(glm::vec3(0, 0, -10.0f * delta_time));
		break;
	case GLFW_KEY_Q:
		Rotate(glm::vec3(-5 * delta_time, 0, 0));
		break;
	case GLFW_KEY_Z:
		Rotate(glm::vec3(5 * delta_time, 0, 0));
		break;
	}
}

void AirPlane::Update()
{
	speed += acceleration * Time::GetDeltaTime();
	Transform(glm::vec3(0, 0, -speed * Time::GetDeltaTime()));
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
