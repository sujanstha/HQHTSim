#ifndef LEVELSENSOR_H
#define LEVELSENSOR_H

class LevelSensor
{
	public:
		LevelSensor();
		~LevelSensor();

		void Init();

		inline float GetLevel() { return m_Level; }

		inline void AddAmount(float Amount) { m_Level += Amount; }

	private:
		float m_Level;
};

#endif