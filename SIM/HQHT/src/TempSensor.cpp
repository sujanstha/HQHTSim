#include "TempSensor.h"


TemperatureSensor::TemperatureSensor() {}

TemperatureSensor::~TemperatureSensor() {}

/* Initialization */
void TemperatureSensor::Init()
{
	m_Temperature = 83.5f;	

	// Start its ticks here
	Utils::GetTicks(&Count.Start);
}

/* Calculates current temperature */
float TemperatureSensor::CalculateTemperature(float FillAmount, float DeltaFill, float BurnerTemp)
{
	// Don't divide by 0
	if (FillAmount == 0.0f && DeltaFill == 0.0f) return m_Temperature;

	// Calculate decay rate
	float Decay = (BurnerTemp == 0.0f && m_Temperature > MIN_TEMP) ? 1.0f / (5.0f * 60.0f) : 0.0f;

	// Calculate new temperature
	m_Temperature = (((FillAmount * m_Temperature) + (DeltaFill * MIN_TEMP)) / (FillAmount + DeltaFill)) + BurnerTemp - Decay; 

	return m_Temperature;
}

