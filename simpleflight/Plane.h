#pragma once
#include "GameObject.h"
#include "EventController.h"

class Plane :
	public GameObject, IKeyListener
{
public:
	Plane(string path, string directory, Shader* shader, float scale);
	~Plane();

	virtual void Draw(glm::mat4 projection, glm::mat4 view) override;
	virtual void OnKeyHold(int key) override;
	virtual void OnKeyPress(int key) override;


private:
	Mesh* mesh;
	void OnKey(int key);

};

