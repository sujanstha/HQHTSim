#ifndef BURNER_H
#define BURNER_H

#include "Utils.h"

class Burner
{
	public:

		enum State { ON, OFF };

		Burner();
		~Burner();

		void Init();

		void SetValue(float Value);

		/* Gets a calculated temperature of burner based off of current value */
		float GetCalculatedTemp();

		State GetState() 		{ return m_State; }
		void SetState(State S) 	{ m_State = S; }

		struct Counter Count;
	private:
		float m_Value;
		float m_Temperature;
		State m_State;
};

#endif