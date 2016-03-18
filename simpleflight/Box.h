#pragma once
#include "GameObject.h"
class Box :
	public GameObject
{
public:
	Box(string name, Model* model, Shader* shader);
	~Box();

	
};

