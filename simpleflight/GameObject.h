#pragma once
#include "Model.h"
#include "shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
using namespace std;

class GameObject
{
public:
	GameObject();
	GameObject(string name, Model* model, Shader* shader);
	~GameObject();
	virtual void Draw(glm::mat4 projection, glm::mat4 view);
	void Transform(glm::vec3 value);
	void Rotate(glm::vec3 value);

#pragma region getters and setters
	string GetName();
	void SetName(string text);

	Shader* GetShader();
	void SetShader(Shader* shader);

	glm::mat4 GetModelMatrix();
#pragma endregion

protected:
	string name;
	Model* model;
	Shader* shader;
	glm::mat4 model_matrix;
	
};