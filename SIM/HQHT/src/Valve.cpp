#include "Valve.h"		

#include <iostream>

Valve::Valve()
{

}

Valve::~Valve()
{

}

/* Initialization */
void Valve::Init(std::string N)
{
	// Set its name
	Name = N;

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


