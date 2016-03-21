#ifndef LEVELSENSOR_H
#define LEVELSENSOR_H

class LevelSensor
{
	public:
		LevelSensor();
		~LevelSensor();

		void Init();

		inline float GetLevel() 				{ return m_Level; }

		inline void AddAmount(float Amount) 	{ m_Level += Amount; }
		inline void SetDeltaFill(float DF) 		{ m_DeltaFill = DF; }	
		inline float GetDeltaFill()				{ return m_DeltaFill; }	

	private:
		float m_Level;
		float m_DeltaFill;
};

#endif