#ifndef UTILS_H
#define UTILS_H

#include <time.h>

struct Counter 
{
	unsigned int TotalElapsed;
	time_t Start;
	time_t End;	
};

namespace Utils
{
	inline void GetTicks(time_t* Time) 	{ time(Time); }
}

#endif