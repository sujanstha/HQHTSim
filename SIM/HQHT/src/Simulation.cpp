#include "Simulation.h"

#include <stdio.h>


void Simulation::Init()
{
	InitSystems();	
}

void Simulation::InitSystems()
{
	m_burner.Init();
	m_tempSensor.Init();
	m_inputValve.Init();
	m_levelSensor.Init();
	m_outputValve4.Init();
	m_outputValve3.Init();
	m_outputValve2.Init();
	m_outputValve1.Init();

	printf("Everything initialized...\n");
}

void Simulation::Run()
{
	printf("Running...\n");
}

void Simulation::Update()
{

}

// If we use graphics...
void Simulation::Render()
{
	
}
