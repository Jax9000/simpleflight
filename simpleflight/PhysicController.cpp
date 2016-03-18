#include "PhysicController.h"

PhysicController::PhysicController()
{
	objects = new map<GameObject*, btRigidBody*>();

	btBroadphaseInterface* broadphase = new btDbvtBroadphase();

	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0, -10, 0));


	btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);

	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
	btRigidBody::btRigidBodyConstructionInfo
		groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
	btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
	dynamicsWorld->addRigidBody(groundRigidBody);


	//btDefaultMotionState* fallMotionState =
	//	new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0)));
	//btScalar mass = 1;
	//btVector3 fallInertia(0, 0, 0);
	//fallShape->calculateLocalInertia(mass, fallInertia);
	//btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, fallShape, fallInertia);
	//btRigidBody* fallRigidBody = new btRigidBody(fallRigidBodyCI);
	//dynamicsWorld->addRigidBody(fallRigidBody);
}

PhysicController& PhysicController::GetInstance()
{
	static PhysicController instance;
	return instance;
}

PhysicController::~PhysicController()
{
}

void PhysicController::Update()
{
	dynamicsWorld->stepSimulation(Time::GetDeltaTime(), 10);

	for (auto object : *objects) 
	{
		auto go = object.first;
		auto rigibody = object.second;

		glm::mat4* matrix = go->GetModelMatrix();
		btScalar new_matrix[16];
		rigibody->getWorldTransform().getOpenGLMatrix(new_matrix);

		go->SetModelMatrix(glm::make_mat4(new_matrix));
	}
}

void PhysicController::Add(GameObject* object)
{
	btCollisionShape* fallShape = new btBoxShape(btVector3(10, 1.5f, 1));
	btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0));
	btDefaultMotionState* fallMotionState =
		new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0)));
	btScalar mass = 1;
	btVector3 fallInertia(0, 0, 0);
	fallShape->calculateLocalInertia(mass, fallInertia);
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, fallShape, fallInertia);
	btRigidBody* fallRigidBody = new btRigidBody(fallRigidBodyCI);
	dynamicsWorld->addRigidBody(fallRigidBody);

	objects->insert(std::pair<GameObject*, btRigidBody*>(object, fallRigidBody));
}

void PhysicController::ApplyForce(GameObject* object, glm::vec3 force, glm::vec3 rel_pos)
{
	auto rigibody = objects->find(object)->second;
	btVector3 new_force;
	btVector3 new_rel_pos;
	for (int i = 0; i < 3; i++)
	{
		new_force[i] = force[i];
		new_rel_pos[i] = rel_pos[i];
	}
	
	rigibody->applyForce(new_force, new_rel_pos);
}
