#include <iostream>
#include "Game_Object.h"
#include "Person.h"
#include "Oxygen_Depot.h"
#include "Space_Station.h"
#include "Cart_Point.h"
#include "Cart_Vector.h"
#include "Astronaut.h"
using namespace std;

Astronaut::Astronaut():Person('A')
{
	this -> amount_moonstones = 0;
	this -> amount_oxygen = 20;
	this -> depot = NULL;
	this -> home = NULL;
	this -> health = 5;
	cout << "Astronaut default constructed." << endl;
}
Astronaut::Astronaut(int in_id, Cart_Point in_loc): Person(in_loc, in_id, 'A')
{
	this -> amount_moonstones = 0;
	this -> amount_oxygen = 20;
	this -> depot = NULL;
	this -> home = NULL;
	this -> health = 5;
	cout << "Astronaut constructed." << endl;
}
Astronaut::~Astronaut()
{
	//Destructor message
	cout << "Astronaut destructed." << endl;
}
bool Astronaut::update()
{
	//Check Health
	if (health < 3)
	{
		this -> display_code = 'a';
	}

	//Check State
	switch(state)
	{
		case 'x'://State 'x'
		{
			return false;
		}
		case 's'://State 's'
		{
			return false;
		}
		case 'm'://State 'm'
		{
			//Case where astronaut has no more oxygen
			if (amount_oxygen==0)
			{
				cout << "I'm out of oxygen. I'm dying!" << endl;
				this -> state = 'x';
				return true;
			}
			else
			{
				//Updating astronaut's location
				bool sample = Person::update_location();

				//Astronaut has not arrived
				if (sample == false)
				{
					this -> amount_oxygen = amount_oxygen - 1;
					this -> amount_moonstones = amount_moonstones + 1;
					return false;
				}
				else
				//Astronaut has arrived
				{
					this -> state = 's';
					return true;
				}
			}
		}
		case 'o'://State 'o'
		{
			//Case where astronaut has no more oxygen
			if (amount_oxygen==0)
			{
				cout << "I'm out of oxygen. I'm dying!" << endl;
				this -> state = 'x';
				return true;
			}
			else
			{
				bool sample2 = Person::update_location();
			
				//Check if astronaut has reached destination, if not decrease oxygen and increase moonstone
				if (sample2 == true)
				{
					this -> state = 'g';
					return true;
				}
				else
				{
					this -> amount_oxygen = amount_oxygen - 1;
					this -> amount_moonstones = amount_moonstones + 1;
					return false;
				}
			}
			
		}
		case 'g'://state 'g'
		{
			//Extract Oxygen from depot
			double res = depot -> extract_oxygen();
			cout << display_code << id_num << ": Got " << res << " more oxygen." << endl;
			this -> amount_oxygen = amount_oxygen + res;
			this -> state = 's';
			return true;
		}
		case 'i'://state 'i'
		{
			//Case where astronaut has no more oxygen
			if (amount_oxygen==0)
			{
				cout << "I'm out of oxygen. I'm dying!" << endl;
				this -> state = 'x';
				return true;
			}
			else
			{
				bool sample3 = Person::update_location();

				//Check if astronaut has reached destination, if not decrease oxygen and increase moonstone
				if (sample3 == true)
				{
					this -> state = 'd';
					return true;
				}
				else
				{
					this -> amount_oxygen = amount_oxygen - 1;
					this -> amount_moonstones = amount_moonstones + 1;
					return false;
				}
			}
			
		}
		case 'd'://state 'd'
		{
			//Deposit moonstones
			cout << display_code << id_num << ": Deposit " << amount_moonstones << " of moonstones." << endl;
			home -> deposit_moonstones(amount_moonstones);
			this -> amount_moonstones = 0;
			this -> state = 's';
			return true;
		} 
		case 'l'://state 'l'
		{
			//Case where astronaut has no more oxygen
			if (amount_oxygen==0)
			{
				cout << "I'm out of oxygen. I'm dying!" << endl;
				this -> state = 'x';
				return true;
			}
			else
			{
				//If there are already locked astronauts
				if (home -> get_astronauts() > 0)
				{
					return false;
				}
				else
				{
					bool sample4 = Person::update_location();

					//Check if astronaut has reached destination, if not decrease oxygen and increase moonstone
					if (sample4 == true)
					{
						home -> add_astronaut();
						return true;
					}
					else
					{
						this -> amount_oxygen = amount_oxygen - 1;
						this -> amount_moonstones = amount_moonstones + 1;
						return false;
					}
				}	
			}
			
		}
	}
}
void Astronaut::start_supplying(Oxygen_Depot* inputDepot)
{
	//Check if astronaut alive or not
	if (get_state() == 'x')
	{
		cout << "I can't move, I am dead." << endl;
	}
	//Do command
	else
	{
		Person::setup_destination(inputDepot -> get_location());
		this -> state = 'o';
		cout << "Astronaut " << id_num << " supplying from Oxygen Depot " << (inputDepot -> get_id()) << "." << endl;
		cout << display_code << id_num << ": Yes, my lord." << endl;
		this -> depot = inputDepot;
	}
}
void Astronaut::start_depositing(Space_Station* inputStation)
{
	//Check if astronaut alive or not
	if (get_state() == 'x')
	{
		cout << "I can't move, I am dead." << endl;
	}
	//Do command
	else
	{
		Person::setup_destination(inputStation -> get_location());
		this -> state = 'i';
		cout << "Astronaut " << id_num << " depositing to Space Station " << (inputStation -> get_id()) << "." << endl;
		cout << display_code << id_num << ": Yes, my lord." << endl;
		this -> home = inputStation;
	}
}
void Astronaut::go_to_station(Space_Station* inputStation)
{
	//Check if astronaut alive or not
	if (get_state() == 'x')
	{
		cout << "I can't move, I am dead." << endl;
	}
	//Do command	
	else
	{
		cout << "Astronaut " << id_num << " locking in at Space Station " << (inputStation -> get_id()) << "." << endl;
		Person::setup_destination(inputStation -> get_location());
		this -> state = 'l';
		this -> home = inputStation;
	}
}
void Astronaut::show_status()
{
	cout << "Astronaut Status: ";
	//Calling Person's show status
	Person::show_status();

	//Astronaut's show status depending on state
	if (state == 'o')
	{
		cout << "is outbound to a Depot with " << amount_oxygen;
		cout << " oxygen and " << amount_moonstones << " moonstones." << endl;
	}
	else if (state == 'x')
	{
		cout << "is dead" << endl;
	}
	else if (state == 'i')
	{
		cout << "is inbound to home with load: " << amount_moonstones;
		cout << " moon stones and " << amount_oxygen << " oxygen." << endl;
	}
	else if (state == 'd')
	{
		cout << "depositing " << amount_moonstones << " moon stones." << endl;
	}
	else if (state == 'g')
	{
		cout << "is getting oxygen from Depot." << endl;
	}
	else if (state == 'l')
	{
			cout << "is locked at Space Station." << endl;
	}
	else if (state == 's')
	{
		if (amount_oxygen == 0)
		{
			cout << "is locked. Out of oxygen." << endl;
		}
		else
		{
			cout << "is stopped with " << amount_oxygen << " oxygen and " << amount_moonstones << " moon stones." << endl;
		}
	}
}



