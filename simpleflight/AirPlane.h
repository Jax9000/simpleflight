#pragma once
#include "GameObject.h"
#include "EventController.h"
#include "Time.h"

class AirPlane :
	public GameObject, IKeyListener
{
public:
	AirPlane(string name, Model* model, Shader* shader);
	~AirPlane();

	virtual void OnKeyPress(int key) override;
	virtual void OnKeyHold(int key) override;
	void OnKey(int key);
	virtual void Update() override;
	virtual void SetModelMatrix(glm::mat4 matrix) override;

private:

};

