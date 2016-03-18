#include "Simulation.h"

#include <iostream>
#include <chrono>
#include <time.h>

/* Necessary Function Prototypes */
float Scale(float Min, float Max, float a, float b, float x);

void Simulation::Init()
{
	// Initialize counter to 0
	m_Counter = {0, 0, 0};

	// Set state to RUNNING
	m_State = State::RUNNING;	

	// Init all sub-systems
	InitSystems();	
}

void Simulation::InitSystems()
{
	// Initialize burner
	m_burner.Init();

	// Initialize temperature sensor
	m_tempSensor.Init();

	// Initialize input valve
	m_inputValve.Init("Input Valve");

	// Initialize level senosr
	m_levelSensor.Init();

	// Initialize output valve 4
	m_outputValve4.Init("Output Valve 4");

	// Initialize output valve 3
	m_outputValve3.Init("Output Valve 3");

	// Initialize output valve 2
	m_outputValve2.Init("Output Valve 2");

	// Initialize output valve 1
	m_outputValve1.Init("Output Valve 1");

	std::cout << "Everything initialized..." << std::endl;
}

void Simulation::Run()
{
	std::cout << "Running..." << std::endl;

	while(m_State == State::RUNNING)
	{
		// Update systems
		Update();
	}

}

void Simulation::Update()
{
	////////////////////////////////////
	// LEVEL SENSOR  ///////////////////
	////////////////////////////////////

	// Check level sensor 
	if (m_levelSensor.GetLevel() < 0.98f && m_inputValve.GetState() == Valve::State::CLOSED)
	{
		// Open input valve if closed 
		m_inputValve.Open();
	
		// Start timer and fill tank
		Utils::GetTicks(&m_inputValve.m_Counter.Start);
	}

	////////////////////////////////////
	// INPUT VALVE  ////////////////////
	////////////////////////////////////

	if (m_inputValve.GetState() == Valve::State::OPEN)
	{
		// If level sensor is at this level, then we can't fill another 0.5fL, so we have to exit this loop
		if (m_levelSensor.GetLevel() > 0.93f) 
		{
			// Close the input valve
			m_inputValve.Close();

		}

		else
		{
			// Get input valve time
			Utils::GetTicks(&m_inputValve.m_Counter.End);

			// If 1 second has passed
			if (m_inputValve.m_Counter.End - m_inputValve.m_Counter.Start > 0)
			{
				// Fill tank by 0.5L
				m_levelSensor.AddAmount(Scale(0.0f, 10.0f, 0.0f, 1.0f, 0.5f));

				// Reset input valve timer
				Utils::GetTicks(&m_inputValve.m_Counter.Start);
			}
		}
	}


	////////////////////////////////////
	// BURNER  /////////////////////////
	////////////////////////////////////

	// Get temperature from sensor
	



}

// If we use graphics...
void Simulation::Render()
{
	
}

// Scaling function
float Scale(float Min, float Max, float a, float b, float x)
{
	return (((b-a) * (x - Min)) / (Max - Min)) + a;
}












