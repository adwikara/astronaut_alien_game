#include <iostream>
#include "Game_Object.h"
#include "Cart_Point.h"
#include "Cart_Vector.h"
#include "Person.h"
#include "Astronaut.h"
#include "Oxygen_Depot.h"
#include "Space_Station.h"
#include <math.h>
using namespace std;
Person::Person():Game_Object('P')
{
	this -> speed = 5;
	cout << "Person default constructed" << endl;
}
Person::Person(char in_code):Game_Object(in_code)
{
	this -> speed = 5;
	this -> state = 's';
	this -> display_code = in_code;
	cout << "Person constructed" << endl;
}
Person::Person(Cart_Point in_loc, int in_id, char in_code):Game_Object(in_loc, in_id, in_code)
{
	this -> speed = 5;
	cout << "Person constructed" << endl;
}
Person::~Person()
{
	//Destructor message
	cout << "Person destructed." << endl;
}
void Person::start_moving(Cart_Point dest)
{
	if (get_state() == 'x')
	{
		cout << "I can't move, I am dead." << endl;
	}
	else
	{
		//Check if astronaut is already at location
		if ((location.x == dest.x) && (location.y == dest.y))
		{
			cout << display_code << id_num << ": I'm already there. See?" << endl;
		}
		else
		//Sets up new destination for astronaut
		{
			Person::setup_destination(dest);
			this -> state = 'm';
			cout << "Moving " << id_num << " to " << dest << endl;
			cout << display_code << id_num << ": On my way." << endl;
		}
	}
}
void Person::stop()
{
	//Check if astronaut alive or not
	if (get_state() == 'x')
	{
		cout << "I can't move, I am dead." << endl;
	}
	//Do command
	else
	{
		this -> state = 's';
		cout << display_code << id_num << ": Stopped" << endl;
	}
}
void Person::show_status()
{
	//Game Object's show status
	Game_Object::show_status();
	
	//Person's show status
	if (state == 'm' || state == 'o' || state == 'i' || state == 'd' || state == 'g')
	{
		cout << "moving at speed of " << speed << " towards " << destination;
		cout << " at each step of " << delta << endl;
	}
}
bool Person::update_location()
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
void Person::setup_destination(Cart_Point dest)
{
	//Sets destination and calculates delta(speed step)
	this -> destination = dest;
	Cart_Vector counter = destination - location;
	this -> delta = counter * (speed / cart_distance(destination, location));
}
void Person::start_supplying(Oxygen_Depot* inputDepot)
{
	cout << "Sorry, I can't work a depot." << endl;
}
void Person::start_depositing(Space_Station* inputStation)
{
	cout << "Sorry, I can't work a station." << endl;
}
void Person::go_to_station(Space_Station* inputStation)
{
	cout << "Sorry, I can't lock into a station" << endl;
}
bool Person::is_alive()
{
	if (get_state() == 'x')
	{
		return false;
	}
	else
	{
		return true;
	}
}
void Person::take_hit(int attack_strength)
{
	//Subtract health from attack
	this -> health = health - attack_strength;

	//Print message
	if (health <= 0)
	{
		cout << display_code << get_id() << ": " << "Gasp! I'm dying..." << endl;
		this -> state = 'x';
	}
	else
	{
		cout << display_code << get_id() << ": " << "Ouch!" << endl;
	}
}






