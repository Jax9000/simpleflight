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


	//btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
	btCollisionShape* groundShape = new btBoxShape(btVector3(100000, 1, 100000));

	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
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
	btCollisionShape* fallShape = new btBoxShape(btVector3(10, 1, 50));
	glm::vec3 position = object->GetPosition();
	btVector3 btposition;
	for (int i = 0; i < 3; i++)
	{
		btposition[i] = position[i];
	}
	btDefaultMotionState* fallMotionState =
		new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));
	btScalar mass = 5;
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
	rigibody->setActivationState(1);
	btVector3 btforce;
	btVector3 btrel_pos;
	for (int i = 0; i < 3; i++)
	{
		btforce[i] = force[i];
		btrel_pos[i] = rel_pos[i];
	}

	btTransform boxTrans;
	boxTrans = rigibody->getWorldTransform();
	btVector3 correctedForce = (boxTrans * btforce) - boxTrans.getOrigin();
	rigibody->applyCentralForce(correctedForce);

	//rigibody->applyForce(btforce, btrel_pos);
}

void PhysicController::ApplySimpleForce(GameObject* object, glm::vec3 force, glm::vec3 rel_pos)
{
	auto rigibody = objects->find(object)->second;
	rigibody->setActivationState(1);
	btVector3 btforce;
	btVector3 btrel_pos;
	for (int i = 0; i < 3; i++)
	{
		btforce[i] = force[i];
		btrel_pos[i] = rel_pos[i];
	}
	rigibody->applyForce(btforce, btrel_pos);
}

void PhysicController::ApplyTorqueForce(GameObject* object, glm::vec3 torque)
{
	auto rigibody = objects->find(object)->second;
	btVector3 bttorque;
	for (int i = 0; i < 3; i++)
		bttorque[i] = torque[i];


	btTransform boxTrans;
	boxTrans = rigibody->getWorldTransform();
	btVector3 correctedForce = (boxTrans * bttorque) - boxTrans.getOrigin();
	rigibody->applyTorque(correctedForce);
}

void PhysicController::Reset(GameObject* object)
{
	auto rigibody = objects->find(object)->second;
	rigibody->clearForces();
	btTransform transform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0));
	rigibody->setWorldTransform(transform);
	rigibody->clearForces();
	rigibody->setActivationState(1);
}
