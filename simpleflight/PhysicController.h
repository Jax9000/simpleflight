#pragma once

#include <map>

#include "btBulletCollisionCommon.h"
#include "BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h"
#include "BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h"
#include "GameObject.h"
#include "Time.h"

class GameObject;

class PhysicController
{
public:
	PhysicController();
	static PhysicController& GetInstance();
	~PhysicController();
	void Update();
	void Add(GameObject* object);
	void ApplyForce(GameObject* object, glm::vec3 force, glm::vec3 rel_pos);

private:
	btDiscreteDynamicsWorld* dynamicsWorld;
	map<GameObject*, btRigidBody*> *objects;
};