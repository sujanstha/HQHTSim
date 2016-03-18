#ifndef TEMPSENSOR_H
#define TEMPSENSOR_H

#include "Utils.h"

const float MIN_TEMP 		= 21.0f;
const float OPTIMAL_TEMP 	= 85.0f;

class TemperatureSensor
{
	public:
		TemperatureSensor();
		~TemperatureSensor();

		/* Initialization */
		void Init();

		/* Gets current temperature */
		inline float GetTemperature() { return m_Temperature; }
		
		/* Calculates current temperature */
		float CalculateTemperature(float FillAmount, float DeltaFill, float BurnerTemp);

		struct Counter Count;

	private:
		float m_Temperature;

};

#endif