#ifndef BURNER_H
#define BURNER_H

class Burner
{
	public:
		enum State { ON, OFF }; 

		Burner();
		~Burner();

		void Init();

		void TurnOff();
		void TurnOn();
	private:
		State m_State;
};

#endif