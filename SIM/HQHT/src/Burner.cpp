#include "Burner.h"


Burner::Burner()
{

}

Burner::~Burner()
{

}

void Burner::Init()
{
	// Initial state is OFF
	TurnOff();
}

void Burner::TurnOff()
{
	m_State = State::OFF;	
}

void Burner::TurnOn()
{
	m_State = State::ON;
}
