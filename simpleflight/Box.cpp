#include "Box.h"



Box::Box(string name, Model* model, Shader* shader) : GameObject(name, model, shader)
{
	PhysicController::GetInstance().Add(this);
}


Box::~Box()
{
}
