#pragma once
#include <vector>

#include "GL\glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Camera.h"
#include "FollowCamera.h"
#include "Skybox.h"
#include "PhysicController.h"


class Scene
{
public:
	Scene();
	~Scene();
	void Draw(int width, int height);
	void Add(GameObject* object);
	void AttachCamera(FollowCamera* camera);

private:
	std::vector<GameObject*> game_objects;
	FollowCamera* camera;
	//Camera* camera;
};

