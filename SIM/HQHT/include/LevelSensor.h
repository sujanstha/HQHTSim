/********************************************************
* @file: 	LevelSensor.h
* @brief:	Header file for LevelSensor class 
* @author: 	John Jackson
* @date: 	03/22/2016
********************************************************/

#ifndef LEVELSENSOR_H
#define LEVELSENSOR_H

/********************************************************
* @class: 	LevelSensor
* @brief:	Class declaration for level sensor used in main simulation 
* @author: 	John Jackson
********************************************************/
class LevelSensor
{
	public:

		/********************************************************
		* @brief:	Default Constructor for level sensor 
		* @author: 	John Jackson
		********************************************************/
		LevelSensor();

		/********************************************************
		* @brief:	Default Destructor for level sensor 
		* @author: 	John Jackson
		********************************************************/
		~LevelSensor();

		/********************************************************
		* @brief:	Init function for level sensor - Use this to init subsytems 
		* @return:	void 
		* @author: 	John Jackson
		********************************************************/
		void Init();

		/********************************************************
		* @brief:	Responsible for getting current level of sensor
		* @return:	m_Level 
		* @author: 	John Jackson
		********************************************************/
		inline float GetLevel() 				{ return m_Level; }

		/********************************************************
		* @brief:	Responsible for adding an amount of level to current level
		* @return:	void 
		* @param:	Amount is a float value to be added to m_Level 
		* @author: 	John Jackson
		********************************************************/
		inline void AddAmount(float Amount) 	{ m_Level += Amount; }

		/********************************************************
		* @brief:	Responsible for setting the current delta fill amount used in the 
		 * 			temperature calculation by temp sensor
		* @return:	void 
		* @param:	DF is a float value to set m_DeltaFill to 
		* @author: 	John Jackson
		********************************************************/
		inline void SetDeltaFill(float DF) 		{ m_DeltaFill = DF; }	

		/********************************************************
		* @brief:	Responsible for returning current delta fill value 
		* @return:	m_DeltaFill 
		* @author: 	John Jackson
		********************************************************/
		inline float GetDeltaFill()				{ return m_DeltaFill; }	

	private:

		/* Public member varialbes */
		float m_Level;
		float m_DeltaFill;
};

#endif