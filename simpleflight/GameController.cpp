#include "GameController.h"

GameController::GameController()
{
	EventController::AddKeyListener(this);
}


GameController::~GameController()
{
}

GameController & GameController::GetInstance()
{
	return instance;
}

void GameController::OnKeyPress(int key)
{
	if (key == GLFW_KEY_ESCAPE)
		WindowController::GetInstance().Terminate("Closing by user...");
}

void GameController::OnKeyHold(int key)
{
	std::cout << "hold: " <<  key << std::endl;
}
GameController GameController::instance;