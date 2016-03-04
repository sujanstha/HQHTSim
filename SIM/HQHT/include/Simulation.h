#ifndef SIMULATION_H
#define SIMULATION_H

#include "Valve.h"
#include "LevelSensor.h"
#include "TempSensor.h"
#include "Burner.h"

class Simulation
{
	public:
		/* Constructor */
		Simulation(){}

		/* Destructor */
		~Simulation(){}

		/* Initialization */
		void Init();

		/* Responsible for initializing individual systems of simulation */
		void InitSystems();

		/* Main run function */
		void Run();

		/* Updates all systems */
		void Update();

		// If we use graphics...
		void Render();

	private:
		TemperatureSensor m_tempSensor;
		Burner m_burner;
		LevelSensor m_levelSensor;
		Valve m_inputValve;		
		Valve m_outputValve1;		
		Valve m_outputValve2;		
		Valve m_outputValve3;		
		Valve m_outputValve4;
};

#endif