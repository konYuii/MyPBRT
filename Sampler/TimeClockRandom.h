#pragma once
#ifndef __TIMECLOCKRANDOM_H__
#define __TIMECLOCKRANDOM_H__

#include <stdlib.h>
#include <time.h>

inline void ClockRandomInit() {
	srand((unsigned)time(NULL));
}
inline double getClockRandom() {
	return rand() / (RAND_MAX + 1.0);
}

#endif // !__TIMECLOCKRANDOM_H__
