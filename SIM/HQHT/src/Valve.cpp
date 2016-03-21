#include "Valve.h"		

#include <iostream>

Valve::Valve()
{

}

Valve::~Valve()
{

}

/* Initialization */
void Valve::Init(std::string Name)
{
	// Set its name
	m_Name = Name;

	// Set initial state to being closed
	Close();

	Count = {0, 0, 0};
}

/* Opens valve */
void Valve::Open()
{
	m_State = State::OPEN;
}


/* Closes valve */
void Valve::Close()
{
	m_State = State::CLOSED;
}


