#include "Time.h"

Time::Time()
{
}

Time::~Time()
{
}

float Time::GetDeltaTime()
{
	return delta_time;
}

void Time::Update(float currentFrame)
{
	current_frame = currentFrame;
	delta_time = currentFrame - last_frame;
	last_frame = currentFrame;
}

Time Time::instance;

float Time::current_frame;
float Time::last_frame;
float Time::delta_time;