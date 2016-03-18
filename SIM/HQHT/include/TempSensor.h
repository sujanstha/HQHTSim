#ifndef TEMPSENSOR_H
#define TEMPSENSOR_H

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
		void CalculateTemperature(float FillAmount);	

	private:
		float m_Temperature;
};

#endif