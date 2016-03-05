#pragma once
#include <string>
#include <iostream>
#include "IKeyListener.h"
#include "IMouseListener.h"
#include "WindowController.h"

using namespace std;

class GameController : public IKeyListener
{
public:
	GameController();
	~GameController();
	static GameController& GetInstance();

	virtual void OnKeyPress(int key) override;
	virtual void OnKeyHold(int key) override;

private: 
	static GameController instance;

};

