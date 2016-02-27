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

void EventController::KeyCheck(int key, int action)
{
	if (action == GLFW_PRESS)
	{
		keys_status[key].is_press = true;
		keys_activated.push_back(key);
	}

	if (action == GLFW_RELEASE)
	{
		keys_status[key].is_press = false;
		keys_status[key].is_hold = false;
		std::remove(keys_activated.begin(), keys_activated.end(), key);
	}

	if (keys_status[key].is_press)
	{
		keys_status[key].is_hold = true;
		keys_status[key].is_press = false;
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

void EventController::KeyNotify()
{
	for (int key : keys_activated)
	{
		if (keys_status[key].is_hold)
			for (IKeyListener* listener : key_listiners)
				listener->OnKeyHold(key);
	}

	for (int key : keys_activated)
	{
		if (keys_status[key].is_press)
			for (IKeyListener* listener : key_listiners)
				listener->OnKeyPress(key);
	}

}

std::vector<IKeyListener*> EventController::key_listiners;
std::vector<IMouseListener*> EventController::mouse_listiners;
KeyStatus EventController::keys_status[1024];
std::vector<int> EventController::keys_activated;
bool EventController::first_mouse_measurment = true;
double EventController::last_y = 0;
double EventController::last_x = 0;