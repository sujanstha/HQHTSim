#ifndef VALVE_H
#define VALVE_H

#include <string>


class Valve
{
	public:
		enum State { OPEN, CLOSE };

		Valve();
		~Valve();

		/* Initialization */
		void Init(std::string Name);

		/* Opens valve */
		void Open();

		/* Closes valve */
		void Close();

	private:
		State m_State;
		std::string m_Name;
};

#endif