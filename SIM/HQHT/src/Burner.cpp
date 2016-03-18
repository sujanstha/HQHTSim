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
}

void Burner::SetValue(float Value)
{
	m_Value = Value <= 1.0f && Value >= 0.0f ? Value : Value > 1.0f ? 1.0f : 0.0f;
}
