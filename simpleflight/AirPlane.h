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

private:
	void accelerate(float value);

	float max_speed = 1000;
	float max_back_speed = -100;
	float speed = 0;
	float max_acceleration = 50;
	float acceleration = 0;
	float delta_acceleration = 1;
	float max_back_acceleration = -1;
};

