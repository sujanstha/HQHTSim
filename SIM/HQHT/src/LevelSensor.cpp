/********************************************************
* @file: 	LevelSensor.cpp
* @brief:	Source file for LevelSensor class 
* @author: 	John Jackson
* @date: 	03/22/2016
********************************************************/

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
	m_Level = 0.98f;

	m_DeltaFill = 0.0f;
}
