#pragma once
#include "GameObject.h"

static GLfloat cube_vertices[] = {
	-1.0f, -1.0f, -1.0f,  0.0f, 0.0f,
	1.0f, -1.0f, -1.0f,  1.0f, 0.0f,
	1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
	1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
	-1.0f,  1.0f, -1.0f,  0.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,  0.0f, 0.0f,

	-1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
	1.0f, -1.0f,  1.0f,  1.0f, 0.0f,
	1.0f,  1.0f,  1.0f,  1.0f, 1.0f,
	1.0f,  1.0f,  1.0f,  1.0f, 1.0f,
	-1.0f,  1.0f,  1.0f,  0.0f, 1.0f,
	-1.0f, -1.0f,  1.0f,  0.0f, 0.0f,

	-1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
	-1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
	-1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
	-1.0f,  1.0f,  1.0f,  1.0f, 0.0f,

	1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
	1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
	1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
	1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
	1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
	1.0f,  1.0f,  1.0f,  1.0f, 0.0f,

	-1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
	1.0f, -1.0f, -1.0f,  1.0f, 1.0f,
	1.0f, -1.0f,  1.0f,  1.0f, 0.0f,
	1.0f, -1.0f,  1.0f,  1.0f, 0.0f,
	-1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
	-1.0f, -1.0f, -1.0f,  0.0f, 1.0f,

	-1.0f,  1.0f, -1.0f,  0.0f, 1.0f,
	1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
	1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
	1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
	-1.0f,  1.0f,  1.0f,  0.0f, 0.0f,
	-1.0f,  1.0f, -1.0f,  0.0f, 1.0f
};

class Cube :
	public GameObject
{
public:
	Cube(string path, string directory, Shader* shader);
	~Cube();

	virtual void Draw(glm::mat4 projection, glm::mat4 view) override;

private:
	Mesh* mesh;
};

