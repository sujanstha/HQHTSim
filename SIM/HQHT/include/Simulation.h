/********************************************************
* @file: 	Simulation.h
* @brief:	Header file for Simulation class 
* @author: 	John Jackson
* @date: 	03/22/2016
********************************************************/

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

/********************************************************
* @struct: 	values
* @brief:	Struct needed to hold output and input values from server 
* @author: 	John Jackson
********************************************************/
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

/********************************************************
* @class: 	Simulation
* @brief:	Class declaration for main simulation 
* @author: 	John Jackson
********************************************************/
class Simulation
{

	// Enum for state of simulation 	
	enum State { RUNNING, EXIT };

 public:
	
		/********************************************************
		* @brief:	Default Constructor for simulation 
		* @author: 	John Jackson
		********************************************************/
		Simulation(){}

		/********************************************************
		* @brief:	Default Destructor for simulation 
		* @author: 	John Jackson
		********************************************************/
		~Simulation(){}

		/********************************************************
		* @brief:	Init function for simulation - Use this to init subsytems 
		* @author: 	John Jackson
		********************************************************/
		void Init();

		/********************************************************
		* @brief:	Responsible for initializing individual systems of simulation 
		* @author: 	John Jackson
		********************************************************/
		void InitSystems();

		/********************************************************
		* @brief:	Main run function for simulation
		* @author: 	John Jackson
		********************************************************/
		void Run();

		/********************************************************
		* @brief:	Updates all systems
		* @author: 	John Jackson
		********************************************************/
		void Update(double Time);

		/********************************************************
		* @brief:	Render function - Not being used
		* @author: 	John Jackson
		********************************************************/
		void Render();

		/********************************************************
		* @brief:	Responsible for polling server for messages and parsing those
		* @author: 	John Jackson
		********************************************************/
		void Poll();

		/********************************************************
		* @brief:	Creates a status string from the output values struct
		* @author: 	John Jackson
		********************************************************/
		std::string GetStatusString(values& V);

	private:

		/* Private member variables */
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