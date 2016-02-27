#pragma once

class Time
{
public:
	Time();
	~Time();
	static float GetDeltaTime();
	static void Update(float currentFrame);

private:
	static Time instance;
	static float current_frame;
	static float last_frame;
	static float delta_time;

};

