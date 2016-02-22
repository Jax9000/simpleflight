#pragma once

class IKeyListener
{
public:
	virtual void OnKeyPressed(int key);
	virtual void OnKeyHold(int key);
};