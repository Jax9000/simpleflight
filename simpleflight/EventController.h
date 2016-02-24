#include <vector>
#include <algorithm>
#include "IMouseListener.h"
#include "IKeyListener.h"
#include "GLFW/glfw3.h"

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
	static void KeyNotify(int key, int action);
	static void MouseNotify(double xpos, double ypos);

private:
	static std::vector<IKeyListener*> key_listiners;
	static std::vector<IMouseListener*> mouse_listiners;
	static bool key_press;
	static bool key_hold;
	static bool first_mouse_measurment;
	static double last_y;
	static double last_x;
};

