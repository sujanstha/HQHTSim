/********************************************************
* @file: 	Utils.h
* @brief:	Utility file for various useful functions and data types 
* @author: 	John Jackson
* @date: 	03/22/2016
********************************************************/

#ifndef UTILS_H
#define UTILS_H

#include <time.h>

/********************************************************
* @struct: 	Counter
* @brief:	All purpose counter used for keeping track of time during program execution
* @author: 	John Jackson
* @date: 	03/22/2016
********************************************************/
struct Counter 
{
	unsigned int TotalElapsed;
	time_t Start;
	time_t End;	
};

namespace Utils
{
	/********************************************************
	* @brief:	Gets current ticks from system clock in form of unsigned integer and stores in passed in param Time
	* @param: 	Time
	* @return: 	void
	* @author: 	John Jackson
	* @date: 	03/22/2016
	********************************************************/
	inline void GetTicks(time_t* Time) 	{ time(Time); }

	/********************************************************
	* @brief:	Linear scaling function
	* @param: 	Min is minimum of first coordinate system
	* @param: 	Max is maximum of first coordinate system
	* @param: 	a is minimum of second coordinate system
	* @param: 	b is maximum of second coordinate system
	* @param: 	x is value to be scaled and interoplated in terms of second system
	* @return: 	float
	* @author: 	John Jackson
	* @date: 	03/22/2016
	********************************************************/
	inline float Scale(float Min, float Max, float a, float b, float x)
	{
		return (((b-a) * (x - Min)) / (Max - Min)) + a;
	}

}

#endif