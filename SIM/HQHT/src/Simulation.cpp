#include "Simulation.h"

#include <iostream>
#include <chrono>
#include <time.h>


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

	double Time = 1.001f;

	while(m_State == State::RUNNING)
	{
		// Update systems
		Update(Time);
	}

}

void Simulation::Update(double Time)
{
	////////////////////////////////////
	// LEVEL SENSOR  ///////////////////
	////////////////////////////////////

	static float CurrentTemp = m_tempSensor.GetTemperature();

	// Check level sensor 
	if (m_levelSensor.GetLevel() < 0.98f && m_inputValve.GetState() == Valve::State::CLOSED)
	{
		// Open input valve if closed 
		m_inputValve.Open();
	
		// Start timer and fill tank
		Utils::GetTicks(&m_inputValve.Count.Start);

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

			m_levelSensor.SetDeltaFill(0.0f);
		}

		else
		{
			// Get input valve time
			Utils::GetTicks(&m_inputValve.Count.End);

			time_t EndTicks = m_inputValve.Count.End;
			time_t StartTicks = m_inputValve.Count.Start;
			float Difference = (EndTicks - StartTicks);

			// If 1 second has passed
			if (Difference > 0)
			{
				// Fill tank by 0.5L normalized between 0 - 1
				float Delta = Utils::Scale(0.0f, 10.0f, 0.0f, 1.0f, 0.5f);

				// Add to level
				m_levelSensor.AddAmount(Delta);
				
				// Set delta fill
				m_levelSensor.SetDeltaFill(Delta);	

				// Reset input valve timer
				Utils::GetTicks(&m_inputValve.Count.Start);

			}

			// Otherwise there was no change in fill
			else m_levelSensor.SetDeltaFill(0.0f);
		}
	}

	////////////////////////////////////
	// TEMP SENSOR  ////////////////////
	////////////////////////////////////

	// Get end ticks for temp sensor
	Utils::GetTicks(&m_tempSensor.Count.End);

	// If 1 second has passed
	if (m_tempSensor.Count.End - m_tempSensor.Count.Start > 0)
	{
		// Get temperature from sensor
		CurrentTemp = m_tempSensor.CalculateTemperature(m_levelSensor.GetLevel(), m_levelSensor.GetDeltaFill(), m_burner.GetCalculatedTemp());

		// Reset start
		Utils::GetTicks(&m_tempSensor.Count.Start);

		std::cout << "Temp: " << CurrentTemp << std::endl;
		std::cout << "Level: " << m_levelSensor.GetLevel() << std::endl;
	}


	////////////////////////////////////
	// BURNER  /////////////////////////
	////////////////////////////////////

	// Turn burner on 
	if (m_tempSensor.GetTemperature() < OPTIMAL_TEMP && m_levelSensor.GetLevel() >= 0.05f && m_burner.GetState() == Burner::State::OFF)
	{
		m_burner.SetValue(m_levelSensor.GetLevel());

		// Start ticks here
		Utils::GetTicks(&m_burner.Count.Start);

		m_burner.SetState(Burner::State::ON);
	}

	// If burner is on
	if (m_burner.GetState() == Burner::State::ON)
	{
		// Get ticks
		Utils::GetTicks(&m_burner.Count.End);

		// Turn off burner
		if (m_tempSensor.GetTemperature() >= OPTIMAL_TEMP)
		{
			m_burner.SetValue(0.0f);

			m_burner.SetState(Burner::State::OFF);
		}

		// If 1 second has passed
		else if (m_burner.Count.End - m_burner.Count.Start > 0)
		{
			// Set value to current fill level
			m_burner.SetValue(m_levelSensor.GetLevel());
		
			// Reset ticks	
			Utils::GetTicks(&m_burner.Count.Start);			
		}
	}	

	///////////////////////////////////////////
	// OUTPUT VALVES  /////////////////////////
	///////////////////////////////////////////

	// Need to process input here
	

	static bool poured = false;
	// Check to see whether or not we can actually pour coffee
	if (m_tempSensor.GetTemperature() >= OPTIMAL_TEMP - 2.0f && m_tempSensor.GetTemperature() <= OPTIMAL_TEMP + 2.0f  && m_levelSensor.GetLevel() >= 0.06f)
	{
		// Simulate pouring small cup of coffee from valve 1
		if (m_outputValve1.GetState() == Valve::State::CLOSED && !poured)
		{
			std::cout << "Started pouring..." << std::endl;
			// Open valve
			m_outputValve1.Open();
		
			// Set start ticks	
			Utils::GetTicks(&m_outputValve1.Count.Start);	

			poured = true;
		}

		if (m_outputValve1.Count.TotalElapsed >= 5)
		{
			std::cout << "Coffee finished pouring..." << std::endl;
			// Close the valve
			m_outputValve1.Close();

			// Reset elapsed time
			m_outputValve1.Count.TotalElapsed = 0;	
		}

		if (m_outputValve1.GetState() == Valve::State::OPEN)
		{
			// Get End ticks
			Utils::GetTicks(&m_outputValve1.Count.End);

			unsigned int Difference = m_outputValve1.Count.End - m_outputValve1.Count.Start; 
			if (Difference > 0)
			{
				m_outputValve1.Count.TotalElapsed += Difference;

				float Delta;

				// Decrement level by amount
				if (m_outputValve1.Count.TotalElapsed >= 5) Delta = 0.0f;
				else Delta = Utils::Scale(0.0f, 10.0f, 0.0f, 1.0f, 0.05f);

				m_levelSensor.AddAmount(-Delta);

				Utils::GetTicks(&m_outputValve1.Count.Start);
			} 
		}
	}

}

// If we use graphics...
void Simulation::Render()
{
	
}













