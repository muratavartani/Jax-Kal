#ifndef TIMER_H
#define TIMER_H

#include "SDL.h"

namespace JAX {
	class Timer {
	private:
		unsigned int prevTicks;
		unsigned int currTicks;
	public:
		Timer();
		~Timer();

		Timer(const Timer&) = delete;
		Timer(Timer&&) = delete;
		Timer& operator=(const Timer&) = delete;
		Timer& operator=(Timer&&) = delete;

		void Start();
		void UpdateFrameTicks();
		float GetDeltaTime() const;
		unsigned int GetSleepTime(const unsigned int fps) const;
	
	
	
	};
}

#endif
