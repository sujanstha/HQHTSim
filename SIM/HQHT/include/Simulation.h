#ifndef SIMULATION_H
#define SIMULATION_H

#include "Valve.h"
#include "LevelSensor.h"
#include "TempSensor.h"
#include "Burner.h"

class Simulation
{
	public:
		Simulation(){}
		~Simulation(){}

		void Init();

		void InitSystems();

		void Run();

		void Update();

		// If we use graphics...
		void Render();

	private:
		

};

#endif