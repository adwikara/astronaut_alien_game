#include <iostream>
#include "Cart_Point.h"
#include "Game_Object.h"
#include "Space_Station.h"
using namespace std;
Space_Station::Space_Station():Game_Object('s')
{
	this -> state = 'o';
	this -> amount_moonstones = 0;
	this -> number_astronauts = 0;
	cout << "Space_Station default constructed" << endl;
}
Space_Station::Space_Station(Cart_Point inputLoc, int inputld):Game_Object(inputLoc, inputld, 's')
{
	this -> id_num = inputld;
	this -> location = inputLoc;
	this -> state = 'o';
	this -> amount_moonstones = 0;
	this -> number_astronauts = 0;
	cout << "Space_Station constructed" << endl;
}
Space_Station::~Space_Station()
{
	//Space Station destructor message
	cout << "Space_Station destructed." << endl;
}
void Space_Station::deposit_moonstones(double deposit_amount)
{
	//Depositing moonstones
	this -> amount_moonstones = amount_moonstones + deposit_amount;
}
bool Space_Station::add_astronaut()
{
	//Add astronaut if station is upgraded
	if (display_code == 'S')
	{
		if (number_astronauts > 0)
		{
			return true;
		}
		else 
		{
			number_astronauts++;
			return true;
		}
	}
	else
	{
		return false;
	}
}
int Space_Station::get_astronauts()
{
	return number_astronauts;
}
bool Space_Station::update()
{
	//If station already upgraded
	if (state == 'u')
	{
		return false;
	}

	//If station has at least 10 moonstones, it can be upgraded
	if (amount_moonstones >= 10)
	{
		this -> state = 'u';
		this -> display_code = 'S';
		cout << display_code << id_num << " has been upgraded." << endl;
		return true; 
	}
	else
	{
		return false;
	}
}
void Space_Station::show_status()
{
	cout << "Space Station status: ";

	//Calling Game Object's show status
	Game_Object::show_status();

	//Space Station's show status
	cout << " contains " << amount_moonstones << " moon stones contains " << number_astronauts << " astronauts.";
	if (state == 'u')
	{
		cout << " Upgraded." << endl;
	}
	else
	{
		cout << " Not yet upgraded." << endl;
	}
}
















