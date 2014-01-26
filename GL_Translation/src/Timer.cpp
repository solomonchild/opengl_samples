#include <Timer.h>
#include <sys/time.h>

#include "logging.h"

namespace utility {

Timer::Timer(double treshold) :
		m_treshold(treshold),
		m_prevTicks(0){
	updateTimer();
}

bool Timer::isTresholdReached() {
	updateTimer();
	double delta = (double) ((m_currTicks - m_prevTicks) / 1000000.0f);
	LOG_INFO("DELTA: %f", delta);
	bool res =  delta >= m_treshold;
	if(res){
		m_prevTicks = m_currTicks;
	}
	return res;
}

void Timer::updateTimer() {
	struct timeval tp;
	gettimeofday(&tp, NULL);
	m_currTicks = tp.tv_sec * 1000000 + tp.tv_usec;
}

}
