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
	// Returns ticks of counter
	inline void GetTicks(time_t* Time) 	{ time(Time); }

	// Scaling function
	inline float Scale(float Min, float Max, float a, float b, float x)
	{
		return (((b-a) * (x - Min)) / (Max - Min)) + a;
	}

}

#endif