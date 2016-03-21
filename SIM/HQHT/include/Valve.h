#ifndef VALVE_H
#define VALVE_H

#include "Utils.h"

#include <string>

class Valve
{
	public:
		enum State { OPEN, CLOSED };

		Valve();
		~Valve();

		/* Initialization */
		void Init(std::string Name);

		/* Opens valve */
		void Open();

		/* Closes valve */
		void Close();

		/* Returns current state */
		inline State GetState() { return m_State; }

		struct Counter Count;

		std::string Name;
	private:
		State m_State;

};

#endif