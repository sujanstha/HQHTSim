/********************************************************
* @file: 	Burner.h
* @brief:	Header file for Burner class 
* @author: 	John Jackson
* @date: 	03/22/2016
********************************************************/

#ifndef BURNER_H
#define BURNER_H

#include "Utils.h"

/********************************************************
* @class: 	Burner
* @brief:	Class declaration for burner used in simulation
* @author: 	John Jackson
********************************************************/
class Burner
{
	public:

		// Enum for state of burner
		enum State { ON, OFF };

		/********************************************************
		* @brief:	Default Constructor for Burner 
		* @author: 	John Jackson
		********************************************************/
		Burner();

		/********************************************************
		* @brief:	Default Destructor for Burner 
		* @author: 	John Jackson
		********************************************************/
		~Burner();

		/********************************************************
		* @brief:	Init function for burner - Use instead of relying o constructor 
		* @return: 	void
		* @author: 	John Jackson
		********************************************************/
		void Init();

		/********************************************************
		* @brief:	Function for setting value of burner
		* @return: 	void
		* @param: 	Value between 0.0f - 1.0f 
		* @author: 	John Jackson
		********************************************************/
		void SetValue(float Value);

		/********************************************************
		* @brief:	Responsible for getting current value of burner
		* @return: 	m_Value
		* @author: 	John Jackson
		********************************************************/
		inline float GetValue() { return m_Value; }

		/********************************************************
		* @brief:	Gets calculated temperature of burner based off of current value
		* @return: 	float 
		* @author: 	John Jackson
		********************************************************/
		float GetCalculatedTemp();

		/********************************************************
		* @brief:	Returns current state of burner - either ON / OFF
		* @return: 	m_State 
		* @author: 	John Jackson
		********************************************************/
		State GetState() 		{ return m_State; }

		/********************************************************
		* @brief:	Sets current state of burner - either ON / OFF
		* @return: 	void 
		* @param: 	State s 
		* @author: 	John Jackson
		********************************************************/
		void SetState(State S) 	{ m_State = S; }

		/* Public member variables */
		struct Counter Count;

	private:

		/* Private member variables */

		float m_Value;
		float m_Temperature;
		State m_State;
};

#endif