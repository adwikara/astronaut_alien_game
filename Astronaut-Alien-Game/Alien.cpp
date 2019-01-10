#include <iostream>
#include "Game_Object.h"
#include "Person.h"
#include "Oxygen_Depot.h"
#include "Space_Station.h"
#include "Cart_Point.h"
#include "Cart_Vector.h"
#include "Astronaut.h"
#include "Alien.h"
#include <math.h>
using namespace std;

Alien::Alien():Game_Object('X')
{
	this -> attack_strength = 2;
	this -> range = 2.0;
	this -> target = NULL;
	this -> speed = 5;
	cout << "Alien default constructed." << endl;
}
Alien::Alien(int in_id, Cart_Point in_loc): Game_Object(in_loc, in_id, 'X')
{
	this -> attack_strength = 2;
	this -> range = 2.0;
	this -> target = NULL;
	this -> speed = 5;
	cout << "Alien constructed." << endl;
}
Alien::~Alien()
{
	//Destructor message
	cout << "Alien destructed." << endl;
}
void Alien::start_attack(Person * in_target)
{
	//Get Astronaut's location
	Cart_Point loc = in_target -> get_location();

	//Calculate distance between astronaut and alien's location
	double distance = cart_distance(loc, get_location());

	//Check
	if (distance <= range)
	{
		cout << "X" << get_id() << ": " << "Smash!" << endl;
		this -> state = 'a';
		this -> target = in_target;
	}
	else
	{
		cout << "Target is out of range" << endl;
 	}
}
bool Alien::update()
{
	switch(state)
	{
		case 's':
		{
			return false;
		}

		case 'm':
		{
			//Updating aliens's location
			bool sample = Alien::update_location();

			//Alien has not arrived
			if (sample == false)
			{
				return false;
			}
			else
			//Alien has arrived
			{
				this -> state = 's';
				return true;
			}
		}

		case 'a':
		{
			//Calculate distance between astronaut and alien's location
			double distance = cart_distance(target -> get_location(), get_location());

			if (distance > range)
			{
				cout << "X" << get_id() << ": " << "Target out of range" << endl;
				cout << "X" << get_id() << ": " << "Charge!" << endl;
				this -> state = 's';
				return true;
			}
			else if (distance <= range)
			{
				if (target -> is_alive() == false)
				{
					cout  << "X" << get_id() << ": " << "I win!" << endl;
					this -> state = 's';
					return true;
				}
				else
				{
					cout << "X" << get_id() << ": " << "Take that!" << endl;
					target -> take_hit(attack_strength);
					return false;
				}
			}


		}
	}
}
void Alien::show_status()
{
	cout << "Alien status: ";

	//Game Object's show status
	Game_Object::show_status();

	//Print depending on state
	if (state == 's')
	{
		cout << "is stopped" << endl;
	}
	else if (state == 'm')
	{
		cout << "moving at speed of " << speed << " towards " << destination;
		cout << " at each step of " << delta << endl;
	}
	else if (state == 'a')
	{
		cout << "is attacking astronaut " << "A" << target -> get_id() << endl;
	}
}
void Alien::setup_destination(Cart_Point dest)
{
	//Sets destination and calculates delta(speed step)
	this -> destination = dest;
	Cart_Vector counter = destination - location;
	this -> delta = counter * (speed / cart_distance(destination, location));
}
bool Alien::update_location()
{
	//Check if object is within one step within the destination
	if ((fabs(destination.x-location.x) <= fabs(delta.x)) && (fabs(destination.y-location.y) <= fabs(delta.y)))
	{
		this -> location = destination;
		cout << display_code << id_num << ": I'm there!" << endl;
		return true;
	}
	else
	{
		this -> location = location + delta;
		cout << display_code << id_num << ": step..." << endl;
		return false;
	}
}
void Alien::start_moving(Cart_Point dest)
{
	//Check if alien is already at location
	if ((location.x == dest.x) && (location.y == dest.y))
	{
		cout << display_code << id_num << ": I'm already there. See?" << endl;
	}
	else
	//Sets up new destination for alien
	{
		Alien::setup_destination(dest);
		this -> state = 'm';
		cout << "Moving " << id_num << " to " << dest << endl;
		cout << display_code << id_num << ": On my way." << endl;
	}
}
void Alien::stop()
{
	this -> state = 's';
	cout << display_code << id_num << ": Stopped" << endl;
}


















