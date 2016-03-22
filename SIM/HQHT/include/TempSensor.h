/********************************************************
* @file: 	TempSensor.h
* @brief:	Header file for TempSensor class 
* @author: 	John Jackson
* @date: 	03/22/2016
********************************************************/

#ifndef TEMPSENSOR_H
#define TEMPSENSOR_H

#include "Utils.h"

/* Constant values */
const float MIN_TEMP 		= 21.0f;
const float OPTIMAL_TEMP 	= 85.0f;

/********************************************************
* @class: 	TemperatureSensor
* @brief:	Class declaration for temp sensor used in main simulation 
* @author: 	John Jackson
********************************************************/
class TemperatureSensor
{
	public:

		/********************************************************
		* @brief:	Default Constructor for temperature sensor 
		* @author: 	John Jackson
		********************************************************/
		TemperatureSensor();

		/********************************************************
		* @brief:	Default Destructor for temperature sensor 
		* @author: 	John Jackson
		********************************************************/
		~TemperatureSensor();

		/********************************************************
		* @brief:	Init function for temp sensor - Use this to init subsytems 
		* @return:	void 
		* @author: 	John Jackson
		********************************************************/
		void Init();

		/********************************************************
		* @brief:	Responsible for returning current temperature
		* @return:	m_Temperature 
		* @author: 	John Jackson
		********************************************************/
		inline float GetTemperature() { return m_Temperature; }
		
		/********************************************************
		* @brief:	Responsible for calculating current temperature based on 
		* 			FillAmount, DeltaFill, and BurnerTemp
		* @param: 	FillAmount is amount of current liquid
		* @param: 	DeltaFill is amount being added to tank in that current frame
		* @param: 	BurnerTemp is the current temperature of the burner unit
		* @return:	float 
		* @author: 	John Jackson
		********************************************************/
		float CalculateTemperature(float FillAmount, float DeltaFill, float BurnerTemp);

		/* Public member variables */
		struct Counter Count;

	private:

		/* Private member variables */
		float m_Temperature;

};

#endif