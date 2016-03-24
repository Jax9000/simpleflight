#pragma once
#include "GameObject.h"
#include "EventController.h"

class FollowCamera : IKeyListener, IMouseListener
{
public:
	FollowCamera(GameObject* object);
	~FollowCamera();
	void Update();
	glm::mat4 GetViewMatrix();

	virtual void OnKeyPress(int key) override;

	virtual void OnMouseMoved(double xoffset, double yoffset) override;

private: 
	GameObject* following_object;
	glm::mat4 view_matrix;

	float zpos = -120;
	float ypos = 22;
};

