#pragma once
#include "Model.h"
#include "shader.h"
#include "PhysicController.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
using namespace std;

class PhysicController;

class GameObject
{
public:
	GameObject();
	GameObject(string name, Model* model, Shader* shader);
	GameObject(const GameObject& object);
	~GameObject();
	virtual void Draw(glm::mat4 projection, glm::mat4 view);
	virtual void Update();
	void ApplyForce(glm::vec3 force, glm::vec3 rel_pos);
	void ApplyTransformedForce(glm::vec3 force, glm::vec3 rel_pos);
	void ApplyTorqueForce(glm::vec3 torque);
	void Transform(glm::vec3 value);
	void Scale(glm::vec3 value);
	void Rotate(glm::vec3 value);

#pragma region getters and setters
	string GetName();
	void SetName(string text);

	Shader* GetShader();
	void SetShader(Shader* shader);

	glm::mat4* GetModelMatrix();
	void SetModelMatrix(glm::mat4 matrix);

	int GetMass() const { return mass; }
	void SetMass(int val) { mass = val; }

	glm::vec3 GetPosition();
	glm::vec3 GetRotation();
#pragma endregion
protected:
	string name;
	Model* model;
	Shader* shader;
	glm::mat4 model_matrix;
	int mass;
};