#include "LevelSensor.h"


LevelSensor::LevelSensor()
{

}

LevelSensor::~LevelSensor()
{

}

void LevelSensor::Init()
{
	// Set initial level to be 5%, normalized between [0.0f, 1.0f] 
	m_Level = 0.05f;
}
