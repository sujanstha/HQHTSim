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
}

/* Opens valve */
void Valve::Open()
{
	std::cout << m_Name + " opening..." << std::endl;
	m_State = State::OPEN;
}


/* Closes valve */
void Valve::Close()
{
	std::cout << m_Name + " closing..." << std::endl;
	m_State = State::CLOSE;
}

