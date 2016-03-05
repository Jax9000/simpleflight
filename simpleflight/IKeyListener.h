#pragma once

class IKeyListener
{
public:
	virtual void OnKeyPress(int key);
	virtual void OnKeyHold(int key);
	virtual void OnKeyRelease(int key);
};