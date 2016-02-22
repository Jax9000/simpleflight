#include <vector>
#include "IMouseListener.h"
#include "IKeyListener.h"

class EventController
{
public:
	EventController();
	~EventController();
	static EventController& GetInstance();
	static void AddMouseListener(IMouseListener listener);
	static void AddKeyListener(IKeyListener listener);
	static void RemoveMouseListener(IMouseListener listener);
	static void RemoveKeyListener(IKeyListener listener);
	static void KeyNotify(int key, int action);
	static void MouseNotify(int xpos, int ypos);

private:
	static std::vector<IKeyListener> key_listiners;
	static std::vector<IMouseListener> mouse_listiners;
};

