#include "Burner.h"

#include <iostream>

Burner::Burner()
{

}

Burner::~Burner()
{

}

void Burner::Init()
{
	// Initial state is OFF
	SetValue(0.0f);

	m_State = State::OFF;

	m_Temperature = 0.0f;
}

/* Sets value clamped between 0.0f and 1.0f */
void Burner::SetValue(float Value)
{
	m_Value = (Value <= 1.0f && Value >= 0.0f) ? Value : Value > 1.0f ? 1.0f : 0.0f;

	// Constant value for now
	m_Temperature = Value == 0.0f ? 0.0f : 0.1f;
}

/* Gets a calculated temperature of burner based off of current value */
float Burner::GetCalculatedTemp()
{
	return m_Temperature;	
}

