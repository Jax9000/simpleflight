#pragma once
#include "GameObject.h"

class Plane :
	public GameObject
{
public:
	Plane(string path, string directory, Shader* shader, float scale);
	~Plane();

	virtual void Draw(glm::mat4 projection, glm::mat4 view) override;


private:
	Mesh* mesh;

};

