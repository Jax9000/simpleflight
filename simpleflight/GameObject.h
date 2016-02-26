#pragma once
#include "Model.h"
#include "shader.h"

using namespace std;

class GameObject
{
public:
	GameObject(string name, Model* model, Shader* shader);
	~GameObject();
	virtual void Draw();

#pragma region getters and setters
	string GetName();
	void SetName(string text);

	Shader* GetShader();
	void SetShader(Shader* shader);

	glm::mat4 GetModelMatrix();
#pragma endregion

private:
	string name;
	Model* model;
	Shader* shader;
	glm::mat4 model_matrix;
	
};

