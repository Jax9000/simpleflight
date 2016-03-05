#pragma once

#include <vector>
#include <algorithm>
#include "GLFW/glfw3.h"
#include "IMouseListener.h"
#include "IKeyListener.h"
#include "KeyStatus.h"

class EventController
{
public:
	EventController();
	~EventController();
	static EventController& GetInstance();
	static void AddMouseListener(IMouseListener* listener);
	static void AddKeyListener(IKeyListener* listener);
	static void RemoveMouseListener(IMouseListener* listener);
	static void RemoveKeyListener(IKeyListener* listener);
	static void MouseNotify(double xpos, double ypos);
	static void KeyNotify();
	static void KeyCheck(int key, int action);

private:
	static std::vector<IKeyListener*> key_listiners;
	static std::vector<IMouseListener*> mouse_listiners;
	static KeyStatus keys_status[1024];
	static std::vector<int> keys_activated;
	static bool first_mouse_measurment;
	static double last_y;
	static double last_x;
};

