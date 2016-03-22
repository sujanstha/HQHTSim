/********************************************************
* @file: 	Valve.h
* @brief:	Header file for Valve class 
* @author: 	John Jackson
* @date: 	03/22/2016
********************************************************/

#ifndef VALVE_H
#define VALVE_H

#include "Utils.h"

#include <string>

/********************************************************
* @class: 	Valve
* @brief:	Class declaration for valves used in simulation code 
* @author: 	John Jackson
********************************************************/

class Valve
{
	public:
		enum State { OPEN, CLOSED };

		Valve();
		~Valve();

		/********************************************************
		* @brief:	Initialization function
		* @param: 	Name - name of valve 
		* @author: 	John Jackson
		********************************************************/
		void Init(std::string Name);

		/********************************************************
		* @brief:	Function to open valve - sets current state to OPEN
		* @author: 	John Jackson
		********************************************************/
		void Open();

		/********************************************************
		* @brief:	Function to close valve - sets current state to CLOSED
		* @author: 	John Jackson
		********************************************************/
		void Close();

		/********************************************************
		* @brief:	Returns current state of valve
		* @author: 	John Jackson
		********************************************************/
		inline State GetState() { return m_State; }

		/********************************************************
		* @brief:	Returns current value of valve
		* @author: 	John Jackson
		********************************************************/
		inline float GetValue() { return m_State == State::OPEN ? 1.0f : 0.0f; }

		/* Public member variables */

		struct Counter Count;
		std::string Name;

	private:

		/* Private member variables */
		State m_State;
};

#endif