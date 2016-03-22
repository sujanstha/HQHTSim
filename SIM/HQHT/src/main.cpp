/********************************************************
* @file: 	main.cpp
* @brief:	Main entry point for simulation executable 
* @author: 	John Jackson
* @date: 	03/22/2016
********************************************************/

/**
* MAIN LOOP
*/

#if 1

/* Standard Library includes */
#include <stdio.h>
#include <iostream> 
#include <time.h>
#include <stdlib.h>

/* HQHT Includes */
#include "Simulation.h"

bool isRunning = true;

int main(int argc, char** argv)
{
	// Seed random 
	srand(time(NULL));

	// Main Simulation
	Simulation Sim;
	Sim.Init();

	Sim.Run();
}

#endif 

/**
* SYSTEMS TEST
*/
#if 0
#endif


/**
*  UNIT TESTS
*/
#if 0

#endif









