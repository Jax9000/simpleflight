#include "GLFW\glfw3.h"
#include "EventController.h"

class WindowController
{
 public:
	WindowController();
	~WindowController();
	static WindowController& GetInstance();

	int getWidht() { return width; }
	void setWidth(int value);
	int getHeight() { return height; }
	void setHeight(int value);
 private:
	 void init();
	 static void mouseEventProvide(GLFWwindow* window, double xpos, double ypos);
	 static void keyEvenetProvide(GLFWwindow* window, int key, int scancode, int action, int mode);

	 GLFWwindow* glfw_window;
	 EventController* event_controller;
	 int width = 800;
	 int height = 800;
};

