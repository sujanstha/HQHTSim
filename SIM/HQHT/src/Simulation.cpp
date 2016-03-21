#include "Simulation.h"

#include <iostream>
#include <stdio.h>
#include <chrono>
#include <time.h>
#include <vector>
#include <sstream>

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

values InValues;

/* Function prototypes */
static WebSocket::pointer ws = NULL;
void handle_message(const std::string& Message);
void parse_message(std::string& message);

void Simulation::Init()
{
	// Initialize counter to 0
	m_Counter = {0, 0, 0};

	InValues = {0, 0, 0, 0, 0, 0, 0, 0};

	// Set state to RUNNING
	m_State = State::RUNNING;	

	// Init all sub-systems
	InitSystems();	
}

void Simulation::InitSystems()
{

#ifdef _WIN32
    INT rc;
    WSADATA wsaData;

    rc = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (rc) {
        printf("WSAStartup Failed.\n");
        m_State = State::EXIT;
    }
#endif

    ws = WebSocket::from_url("ws://localhost:8126/foo");
    assert(ws);

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

		// Poll for messages
		Poll();
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
			ws->send("POST_BACKEND_STATUS");
			// Open valve
			m_outputValve1.Open();
			InValues.B1 = 1.0f;
			ws->send(GetStatusString().c_str());
		
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

std::string Simulation::GetStatusString()
{
	return "STATUS: A=" + std::to_string(InValues.A) + ", B=[" + std::to_string(InValues.B1) + 
						", " + std::to_string(InValues.B2 )+ ", " + std::to_string(InValues.B3) + ", " + std::to_string(InValues.B4) + "], C=" + std::to_string(InValues.C) + ", D=" + 
								std::to_string(InValues.D) + ", E=" + std::to_string(InValues.E);
}

void Simulation::Poll()
{
    ws->poll();
    ws->dispatch(handle_message);
}

// If we use graphics...
void Simulation::Render()
{
	
}

void handle_message(const std::string& message)
{
    printf(">>> %s\n", message.c_str());
    std::string M(message.c_str());

    parse_message(M);

    // if (message == "world") { ws->close(); }
    // if (message == "galaxy") printf("closing the valve...\n");
}

void parse_message(std::string& message)
{
	std::stringstream ss(message);
	std::string line;
	std::vector<std::string> wordVector;

	while(std::getline(ss, line))
	{
		std::size_t prev = 0, pos;
		while((pos = line.find_first_of(" []:=,", prev)) != std::string::npos)
		{
			if (pos > prev)
				wordVector.push_back(line.substr(prev, pos-prev));
			prev = pos + 1;
		}
		if (prev < line.length())
			wordVector.push_back(line.substr(prev, std::string::npos));
	}

	auto S = wordVector.size();
	printf("size: %d\n", S);
	for (auto i = 0; i < S; i++)
	{
		if (i + 1 >= S) continue;

		auto m = wordVector.at(i).c_str()[0];
		auto m2 = wordVector.at(i + 1).c_str();

		switch(m)
		{
			case 'A':
			{
				auto V = ::atof(m2);
				InValues.A = V;
				printf("Input valve set to %.2f\n", V);	
				break;
			} 
			case 'B':
			{
				auto v1 = i + 1, v2 = i + 2, v3 = i + 3, v4 = i + 4;
				if (v1 < S) 
				{
					auto V = ::atof(wordVector.at(v1).c_str());
					InValues.B1 = V;
					printf("Output Valve 1 set to %.2f\n", V);
				}
				if (v2 < S) 
				{
					auto V = ::atof(wordVector.at(v2).c_str());
					InValues.B2 = V;
					printf("Output Valve 2 set to %.2f\n", V);
				}
				if (v2 < S) 
				{
					auto V = ::atof(wordVector.at(v3).c_str());
					InValues.B3 = V;
					printf("Output Valve 3 set to %.2f\n", V);
				}
				if (v2 < S) 
				{
					auto V = ::atof(wordVector.at(v4).c_str());
					InValues.B4 = V;
					printf("Output Valve 4 set to %.2f\n", V);
				}
				break;
			} 
			case 'C':
			{
				auto V = ::atof(m2);
				InValues.C = V;
				printf("Burner set to %.2f\n", V);

				break;
			} 
			case 'D':
			{
				auto V = ::atof(m2);
				InValues.D = V;
				printf("Level sensor at %.2f\n", V);
				break;
			} 
			case 'E':
			{
				auto V = ::atof(m2);
				InValues.E = V;
				printf("Temp sensor at %.2f\n", V);
				break;
			} 
			default: break;
		}
	}
}










