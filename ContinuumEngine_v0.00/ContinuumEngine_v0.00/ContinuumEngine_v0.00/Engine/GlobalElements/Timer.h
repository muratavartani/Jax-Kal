#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

class Timer
{
public:
	Timer(const Timer&) = delete;
	Timer(Timer&&) = delete;
	Timer& operator=(const Timer&) = delete;
	Timer& operator=(Timer&&) = delete;

	Timer();
	~Timer();
	void Start();
	void UpdateFrameTicks();
	float getDeltaTime() const;
	unsigned int GetSleepTime(const unsigned int fps_) const;
	float GetCurrentTicks() const;

private:
	unsigned int prevTicks;
	unsigned int currentTicks;
};

#endif // TIMER_H!