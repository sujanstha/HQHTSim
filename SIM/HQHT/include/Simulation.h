#ifndef SIMULATION_H
#define SIMULATION_H

#include "Valve.h"
#include "LevelSensor.h"
#include "TempSensor.h"
#include "Burner.h"
#include "Utils.h"

#include <time.h>

#include "easywsclient.hpp"
#ifdef _WIN32
#pragma comment( lib, "ws2_32" )
#include <WinSock2.h>
#endif
#include <assert.h>
#include <stdio.h>
#include <string>

typedef struct
{
	float A;
	float B1;
	float B2;
	float B3;
	float B4;
	float C;
	float D;
	float E;
} values;

using easywsclient::WebSocket;

class Simulation
{
	enum State { RUNNING, EXIT };
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
		void Update(double Time);

		// If we use graphics...
		void Render();

		void Poll();

		std::string GetStatusString(values& V);

	private:
		TemperatureSensor m_tempSensor;
		Burner m_burner;
		LevelSensor m_levelSensor;
		Valve m_inputValve;		
		Valve m_outputValve1;		
		Valve m_outputValve2;		
		Valve m_outputValve3;		
		Valve m_outputValve4;

		std::vector<Valve*> m_OutputValves;

		struct Counter m_Counter;

		State m_State;
};

#endif