#pragma once
// Std. Includes
#include <vector>

// GL Includes
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include "IMouseListener.h"
#include "EventController.h"
#include "Time.h"

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

// Default camera values
const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 3.0f;
const GLfloat SENSITIVTY = 0.1f;
const GLfloat ZOOM = 45.0f;
const GLfloat BOOST = 10.0f;

class Camera : IMouseListener, IKeyListener
{
public:
	Camera(
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), 
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), 
		GLfloat yaw = YAW, 
		GLfloat pitch = PITCH);
	Camera(
		GLfloat posX, 
		GLfloat posY, 
		GLfloat posZ, 
		GLfloat upX, 
		GLfloat upY, 
		GLfloat upZ, 
		GLfloat yaw, 
		GLfloat pitch);
	~Camera();
	
	glm::mat4 GetViewMatrix();
	void SetViewMatrix(glm::mat4 matrix);
	void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime);
	void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true);
	void ProcessMouseScroll(GLfloat yoffset);
	virtual void OnMouseMoved(double xoffset, double yoffset) override;
	virtual void OnKeyPress(int key) override;
	virtual void OnKeyHold(int key) override;
	virtual void OnKeyRelease(int key) override;

	// Camera Attributes
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	// Eular Angles
	GLfloat Yaw;
	GLfloat Pitch;
	// Camera options
	GLfloat Movement_Speed;
	GLfloat Mouse_Sensitivity;
	GLfloat Zoom;

private:
	void updateCameraVectors();
	void onKeyEvent(int key);



};