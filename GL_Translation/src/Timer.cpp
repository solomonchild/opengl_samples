#include <Timer.h>
#include <sys/time.h>

#include "logging.h"

namespace utility {

Timer::Timer(double treshold) :
		m_treshold(treshold),
		m_prevTicks(0){
	updateTimer();
	m_prevTicks = m_currTicks;
}

double Timer::getElapsed() {
	return (m_currTicks - m_prevTicks) / 1000000.0f;
}
void Timer::reset() {
	m_prevTicks = m_currTicks;
}

bool Timer::isTresholdReached() {
	updateTimer();
	double delta = getElapsed();
	return  delta >= m_treshold;
}

void Timer::updateTimer() {
	struct timeval tp;
	gettimeofday(&tp, NULL);
	m_currTicks = tp.tv_sec * 1000000 + tp.tv_usec;
}

}
