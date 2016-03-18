#include "Simulation.h"

#include <iostream>

void Simulation::Init()
{
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
}

void Simulation::Update()
{

}

// If we use graphics...
void Simulation::Render()
{
	
}
