#include "EventController.h"


EventController::EventController()
{
}


EventController::~EventController()
{
}

EventController& EventController::EventController::GetInstance()
{
	static EventController instance;
	return instance;
}

void EventController::AddMouseListener(IMouseListener* listener)
{
	mouse_listiners.push_back(listener);
}

void EventController::AddKeyListener(IKeyListener* listener)
{
	key_listiners.push_back(listener);
}

void EventController::RemoveMouseListener(IMouseListener* listener)
{
	std::remove(mouse_listiners.begin(), mouse_listiners.end(), listener);
}

void EventController::RemoveKeyListener(IKeyListener* listener)
{
	std::remove(key_listiners.begin(), key_listiners.end(), listener);
}

void EventController::KeyNotify(int key, int action)
{
	if (action == GLFW_PRESS)
	{
		key_press = true;
		for (IKeyListener* listener : key_listiners)
			listener->OnKeyPressed(key);
	}

	if (action == GLFW_RELEASE)
	{
		key_press = false;
		key_hold = false;
	}

	if (key_hold)
	{
		for (IKeyListener* listener : key_listiners)
			listener->OnKeyHold(key);
	}

	if (key_press)
	{
		key_hold = true;
	}
}

void EventController::MouseNotify(double xpos, double ypos)
{
	if (first_mouse_measurment)
	{
		EventController::last_x = xpos;
		EventController::last_y = ypos;
		first_mouse_measurment = false;
	}

	double xoffset = xpos - EventController::last_x;
	double yoffset = EventController::last_y - ypos;  // Reversed since y-coordinates go from bottom to left

	last_x = xpos;
	last_y = ypos;

	for (IMouseListener* listener : mouse_listiners)
		listener->OnMouseMoved(xoffset, yoffset);
}

std::vector<IKeyListener*> EventController::key_listiners;
std::vector<IMouseListener*> EventController::mouse_listiners;
bool EventController::key_press = false;
bool EventController::key_hold = false;
bool EventController::first_mouse_measurment = true;
double EventController::last_y = 0;
double EventController::last_x = 0;