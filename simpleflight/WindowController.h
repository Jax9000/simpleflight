#include <iostream>
#include <string>
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "SOIL\soil.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "assimp/cimport.h"

#include "Scene.h"
#include "Time.h"

using namespace std;

class WindowController
{
 public:
	WindowController();
	~WindowController();
	static WindowController& GetInstance();
	void Update(Scene scene);
	void Terminate(std::string message);

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
	 int width = 1200;
	 int height = 800;
};

