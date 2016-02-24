#include "GameController.h"


GameController::GameController()
{
	EventController::AddKeyListener(this);
	EventController::AddMouseListener(this);
}


GameController::~GameController()
{
}

GameController & GameController::GetInstance()
{
	return instance;
}

void GameController::OnKeyPressed(int key)
{
	std::cout << "pressed: " << key << std::endl;
}

void GameController::OnKeyHold(int key)
{
	std::cout << "hold: " <<  key << std::endl;
}

void GameController::OnMouseMoved(double xoffset, double yoffset)
{
	std::cout << "mouse moved: " << xoffset << " " << yoffset << std::endl;
}

GameController GameController::instance;