#pragma once
#include <iostream>
#include "IKeyListener.h"
#include "IMouseListener.h"
#include "EventController.h"

class GameController : public IKeyListener, public IMouseListener
{
public:
	GameController();
	~GameController();
	static GameController& GetInstance();

	virtual void OnKeyPressed(int key) override;
	virtual void OnKeyHold(int key) override;
	virtual void OnMouseMoved(double xoffset, double yoffset) override;

private: 
	static GameController instance;

};

