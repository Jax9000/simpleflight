#pragma once

class IMouseListener
{
public:
	virtual void OnMouseMoved(double xoffset, double yoffset);
};