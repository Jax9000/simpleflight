#include "FollowCamera.h"

FollowCamera::FollowCamera(GameObject* object)
{
	EventController::AddKeyListener(this);
	EventController::AddMouseListener(this);
	following_object = object;

	glm::mat4 model_matrix = *(following_object->GetModelMatrix());
	glm::vec3 object_position(model_matrix[3][0], model_matrix[3][1] + 40, model_matrix[3][2]);
	glm::vec3 camera_position(model_matrix[3][0], model_matrix[3][1] + 40, model_matrix[3][2] + 120);
	view_matrix = glm::lookAt(camera_position, object_position, glm::vec3(0, 1.f, 0));
}

FollowCamera::~FollowCamera()
{
}

void FollowCamera::Update()
{
	//glm::mat4 model_matrix = *(following_object->GetModelMatrix());
	//glm::vec3 object_position(model_matrix[3][0], model_matrix[3][1], model_matrix[3][2]);
	//view_matrix = model_matrix;
	//view_matrix = glm::translate(view_matrix, glm::vec3(0, 30, 120));
	//view_matrix = glm::lookAt(ca)
	//view_matrix = glm::rotate(view_matrix, 180.f, glm::vec3(0, 0, 0));
	//view_matrix[3][0] = object_position[0];
	//view_matrix[3][1] = -(object_position[1] + ypos);
	//view_matrix[3][2] = -(object_position[2] + zpos);
	glm::mat4 model_matrix = *(following_object->GetModelMatrix());
	glm::vec3 object_position(model_matrix[3][0], model_matrix[3][1] + 40, model_matrix[3][2]);
	view_matrix = glm::translate(model_matrix, glm::vec3(0, 30, 120));
	glm::vec3 camera_position(view_matrix[3][0], view_matrix[3][1], view_matrix[3][2]);
	view_matrix = glm::lookAt(camera_position, object_position, glm::vec3(0, 1.f, 0));
}

glm::mat4 FollowCamera::GetViewMatrix()
{
	Update();
	return view_matrix;
}

void FollowCamera::OnKeyPress(int key)
{
	if (key == GLFW_KEY_1)
		ypos++;
	if (key == GLFW_KEY_2)
		ypos--;
	if (key == GLFW_KEY_3)
		zpos++;
	if (key == GLFW_KEY_4)
		zpos--;
	//cout << "y: " << ypos << "z: " << zpos << endl;
	following_object->PrintModelMatrix();
}

void FollowCamera::OnMouseMoved(double xoffset, double yoffset)
{
	//glm::mat4 model_matrix = *(following_object->GetModelMatrix());
	//glm::vec3 object_position(model_matrix[3][0], model_matrix[3][1], model_matrix[3][2]);
	//view_matrix = glm::translate(view_matrix, glm::vec3(0, 100, 100));
	//view_matrix = glm::rotate(view_matrix, (float)xoffset, glm::vec3(0, 1.f, 0));
	//view_matrix = glm::translate(view_matrix, glm::vec3(0, -100, -100));
	//view_matrix = glm::lookAt()
}
