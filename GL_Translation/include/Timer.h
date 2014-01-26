#ifndef TIMER_H
#define TIMER_H
#include <stdint.h>


namespace utility
{
class Timer {
public:
	Timer(double treshold = 1 / 30.0f);

	bool isTresholdReached();
	double getElapsed();
	void reset();
protected:
	void updateTimer();
	uint32_t m_currTicks;
	uint32_t m_prevTicks;
	double m_treshold;
};
}

#endif
