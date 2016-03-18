#ifndef BURNER_H
#define BURNER_H

#include "Utils.h"

class Burner
{
	public:
		Burner();
		~Burner();

		void Init();

		void SetValue(float Value);

		struct Counter m_Counter;
	private:
		float m_Value;
};

#endif