#include "Camera.h"

// Constructor with vectors
Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), Movement_Speed(SPEED), Mouse_Sensitivity(SENSITIVTY), Zoom(ZOOM)
{
	EventController::AddMouseListener(this);
	EventController::AddKeyListener(this);
	this->Position = position;
	this->WorldUp = up;
	this->Yaw = yaw;
	this->Pitch = pitch;
	this->updateCameraVectors();
}

// Constructor with scalar values
Camera::Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), Movement_Speed(SPEED), Mouse_Sensitivity(SENSITIVTY), Zoom(ZOOM)
{
	EventController::AddMouseListener(this);
	EventController::AddKeyListener(this);
	this->Position = glm::vec3(posX, posY, posZ);
	this->WorldUp = glm::vec3(upX, upY, upZ);
	this->Yaw = yaw;
	this->Pitch = pitch;
	this->updateCameraVectors();
}

Camera::~Camera()
{
	EventController::RemoveKeyListener(this);
	EventController::RemoveMouseListener(this);
}

// Returns the view matrix calculated using Eular Angles and the LookAt Matrix
glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(this->Position, this->Position + this->Front, this->Up);
}

void Camera::SetViewMatrix(glm::mat4 matrix)
{
	
}

// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void Camera::ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime)
{
	GLfloat velocity = this->Movement_Speed * deltaTime;
	if (direction == FORWARD)
		this->Position += this->Front * velocity;
	if (direction == BACKWARD)
		this->Position -= this->Front * velocity;
	if (direction == LEFT)
		this->Position -= this->Right * velocity;
	if (direction == RIGHT)
		this->Position += this->Right * velocity;
	if (direction == UP)
		this->Position += this->WorldUp * velocity;
	if (direction == DOWN)
		this->Position -= this->WorldUp * velocity;
}

// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Camera::ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch)
{
	xoffset *= this->Mouse_Sensitivity;
	yoffset *= this->Mouse_Sensitivity;

	this->Yaw += xoffset;
	this->Pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (this->Pitch > 89.0f)
			this->Pitch = 89.0f;
		if (this->Pitch < -89.0f)
			this->Pitch = -89.0f;
	}

	// Update Front, Right and Up Vectors using the updated Eular angles
	this->updateCameraVectors();
}

// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void Camera::ProcessMouseScroll(GLfloat yoffset)
{
	if (this->Zoom >= 1.0f && this->Zoom <= 45.0f)
		this->Zoom -= yoffset;
	if (this->Zoom <= 1.0f)
		this->Zoom = 1.0f;
	if (this->Zoom >= 45.0f)
		this->Zoom = 45.0f;
}

// Calculates the front vector from the Camera's (updated) Eular Angles
void Camera::updateCameraVectors()
{
	// Calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
	front.y = sin(glm::radians(this->Pitch));
	front.z = sin(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
	this->Front = glm::normalize(front);
	// Also re-calculate the Right and Up vector
	this->Right = glm::normalize(glm::cross(this->Front, this->WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	this->Up = glm::normalize(glm::cross(this->Right, this->Front));
}

void Camera::OnKeyPress(int key)
{
	onKeyEvent(key);
	if (key == GLFW_KEY_LEFT_SHIFT || key == GLFW_KEY_RIGHT_SHIFT)
		Movement_Speed = BOOST;
}

void Camera::OnKeyHold(int key)
{
	onKeyEvent(key);
}

void Camera::OnKeyRelease(int key)
{
	if (key == GLFW_KEY_LEFT_SHIFT || key == GLFW_KEY_RIGHT_SHIFT)
		Movement_Speed = SPEED;
}


void Camera::OnMouseMoved(double xoffset, double yoffset)
{
	ProcessMouseMovement(xoffset, yoffset);
}

void Camera::onKeyEvent(int key)
{
	float Delta_Time = Time::GetDeltaTime();
	if (key == GLFW_KEY_W)
		 ProcessKeyboard(FORWARD, Delta_Time);
	if (key == GLFW_KEY_S)
		 ProcessKeyboard(BACKWARD, Delta_Time);
	if (key == GLFW_KEY_A)
		 ProcessKeyboard(LEFT, Delta_Time);
	if (key == GLFW_KEY_D)
		 ProcessKeyboard(RIGHT, Delta_Time);
	if (key == GLFW_KEY_SPACE)
		ProcessKeyboard(UP, Delta_Time);
	if (key == GLFW_KEY_LEFT_CONTROL)
		ProcessKeyboard(DOWN, Delta_Time);
}
