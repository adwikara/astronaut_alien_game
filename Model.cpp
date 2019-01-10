#include <iostream>
#include "Game_Object.h"
#include "Oxygen_Depot.h"
#include "Space_Station.h"
#include "Cart_Point.h"
#include "Cart_Vector.h"
#include "Person.h"
#include "Astronaut.h"
#include "Model.h"
#include "View.h"
#include "Alien.h"
#include <list>
#include <cstdlib>
using namespace std;

Model::Model()
{
	this -> time = 0;
	this -> count_down = 10;

	//Create astronaut 1
	Cart_Point p1 = Cart_Point(5,1);
	Astronaut *a1 = new Astronaut(1, p1);
	person_ptrs.push_front(a1);
	object_ptrs.push_front(a1);

	//Create astronaut 2
	Cart_Point p2 = Cart_Point(10,1);
	Astronaut *a2 = new Astronaut(2, p2);
	person_ptrs.push_back(a2);
	object_ptrs.push_back(a2);

	//Create Oxygen_Depot 1
	Cart_Point p3 = Cart_Point(1,20);
	Oxygen_Depot *o1 = new Oxygen_Depot(p3, 1);
	depot_ptrs.push_front(o1);
	object_ptrs.push_back(o1);

	//Create Oxygen_Depot 2
	Cart_Point p4 = Cart_Point(10,20);
	Oxygen_Depot *o2 = new Oxygen_Depot(p4, 2);
	depot_ptrs.push_back(o2);
	object_ptrs.push_back(o2);

	//Create Space_Station 1
	Cart_Point p6 = Cart_Point(0,0);
	Space_Station *s1 = new Space_Station(p6, 1);
	station_ptrs.push_front(s1);
	object_ptrs.push_back(s1);

	//Create Space_Station 2
	Cart_Point p5 = Cart_Point(5,5);
	Space_Station *s2 = new Space_Station(p5, 2);
	station_ptrs.push_back(s2);
	object_ptrs.push_back(s2);

	//Create Alien 1
	Cart_Point p7 = Cart_Point(7,14);
	Alien *x1 = new Alien(1, p7);
	alien_ptrs.push_front(x1);
	object_ptrs.push_back(x1);

	//Create Alien 2
	Cart_Point p8 = Cart_Point(7,5);
	Alien *x2 = new Alien(2, p8);
	alien_ptrs.push_back(x2);
	object_ptrs.push_back(x2);

	active_ptrs = object_ptrs;

	//Print 
	cout << "Model default constructed" << endl;
}

Model::~Model()
{
	list<Game_Object*>::iterator i1;

	//Destroying each object
	for (i1 = active_ptrs.begin(); i1 != active_ptrs.end(); i1++)
	{
		delete *i1;
	}
	cout << "Model destructed." << endl;
}

Person * Model::get_Person_ptr(int id)
{
	int count = 0;
	Person * res;
	list<Person*>::iterator i;

	//Find pointer with the same ID
	for (i = person_ptrs.begin(); i != person_ptrs.end(); i++)
	{
		if ((*i) -> get_id() == id)
		{
			res = *i;
			count++;
		}
	}
	//Return true if there is such pointer
	if (count == 1)
	{
		return res;
	}
	else
	{
		return NULL;
	}
}
Oxygen_Depot * Model::get_Oxygen_Depot_ptr(int id)
{
	int count = 0;
	Oxygen_Depot * res;
	list<Oxygen_Depot*>::iterator i;

	//Find pointer with the same ID
	for (i = depot_ptrs.begin(); i != depot_ptrs.end(); i++)
	{
		if ((*i) -> get_id() == id)
		{
			res = *i;
			count++;
		}
	}
	//Return true if there is such pointer
	if (count == 1)
	{
		return res;
	}
	else
	{
		return NULL;
	}
}
Space_Station * Model::get_Space_Station_ptr(int id)
{
	int count = 0;
	Space_Station * res;
	list<Space_Station*>::iterator i;

	//Find pointer with the same ID
	for (i = station_ptrs.begin(); i != station_ptrs.end(); i++)
	{
		if ((*i) -> get_id() == id)
		{
			res = *i;
			count++;
		}
	}
	//Return true if there is such pointer
	if (count == 1)
	{
		return res;
	}
	else
	{
		return NULL;
	}
}
Alien * Model::get_Alien_ptr(int id)
{
	int count = 0;
	Alien * res;
	list<Alien*>::iterator i;

	//Find pointer with the same ID
	for (i = alien_ptrs.begin(); i != alien_ptrs.end(); i++)
	{
		if (((*i) -> get_id()) == id)
		{
			res = *i;
			count++;
		}
	}
	//Return true if there is such pointer
	if (count == 1)
	{
		return res;
	}
	else
	{
		return NULL;
	}
}
bool Model::update()
{
	time++;

	//Initialize iterators
	list<Space_Station*>::iterator i;
	list<Game_Object*>::iterator i1;
	list<Person*>::iterator i2;
	int locked_astronauts = 0;
	int key1 = 0;

	//Update list for alive/dead astronauts
	for (i1 = active_ptrs.begin(); i1 != active_ptrs.end(); i1++)
	{
		if((*i1) -> is_alive() == 0)
		{
			i1 = active_ptrs.erase(i1);
		}
	}
	
	//Check if every station has been upgraded
	for (i = station_ptrs.begin(); i != station_ptrs.end(); i++)
	{
		if ((*i) -> get_state() == 'u')
		{
			key1++;
			//Check if every upgraded station has a astronaut
			if ((*i) -> get_astronauts() > 0)
			{
				locked_astronauts++;
			}
		}
	}

	if (key1 == station_ptrs.size())
	{
		//Case: If both stations upgraded and no astronauts in stations
		if (locked_astronauts <= station_ptrs.size())
		{
			cout << "Ready for takeoff? " << count_down << "..." << endl;
			count_down--;

			//If countdown is 0, game is lost
			if (count_down == 0)
 			{
 				cout << "Unmanned takeoff... You lose!" << endl;
 				exit(0);
 			}
 			//Case: Both stations upgraded and no missing astronauts. Game is won
			if (locked_astronauts == station_ptrs.size())
			{
				cout <<"Blast Off! You Win!" << endl;
				exit(0);
			}
 			//Print that stations are missing astronauts
			cout << "Missing " <<  station_ptrs.size() - locked_astronauts << " astronauts!" << endl;
			int res;

			//Update every object
			for (i1 = active_ptrs.begin(); i1 != active_ptrs.end(); i1++)
			{
				if (((*i1) -> update()) == true)
				{
					return true;
				}
			}
		}
	}

	//Case: If stations not upgraded, then update every object
	else
	{
		int res;
		for (i1 = active_ptrs.begin(); i1 != active_ptrs.end(); i1++)
		{
			if (((*i1) -> update()) == true)
			{
				return true;
			}
		}
		
	}
}
void Model::display(View &view)
{
	//Reset the grid into dots and spaces
	view.clear();

	list<Game_Object*>::iterator i;

	//Plot the object to the grid
	for (i = active_ptrs.begin(); i != active_ptrs.end(); i++)
	{
		view.plot(*i);
	}
	//Draw the grid
	view.draw();
}
void Model::show_status()
{
	//Print time before show status
	cout << "Time: " << time << endl;

	list<Game_Object*>::iterator i;

	//Show status for every object
	for (i = object_ptrs.begin(); i != object_ptrs.end(); i++)
	{
		(*i) -> show_status();
	}
}
void Model::handle_new_command(char type, int id1, Cart_Point loc)
{
		//Create astronaut
		if (type == 'a')
		{
			list<Person*>::iterator i1;
			for (i1 = person_ptrs.begin(); i1 != person_ptrs.end(); i1++)
			{
				//Create new object if object with id number doesnt exist
				bool counter = ((*i1) -> get_id()) == id1;
				if (counter == false)
				{
					Astronaut *a1 = new Astronaut(id1, loc);
					person_ptrs.push_back(a1);
					object_ptrs.push_back(a1);
					active_ptrs.push_back(a1);
					break;
				}
			}
		}
		//Create station
		else if(type == 's')
		{
			list<Space_Station*>::iterator i1;
			for (i1 = station_ptrs.begin(); i1 != station_ptrs.end(); i1++)
			{
				//Create new object if object with id number doesnt exist
				bool counter = ((*i1) -> get_id()) == id1;
				if (counter == false)
				{
					Space_Station *s1 = new Space_Station(loc, id1);
					station_ptrs.push_back(s1);
					object_ptrs.push_back(s1);
					active_ptrs.push_back(s1);
					break;
				}
			}
		}
		//Create depot
		else if (type == 'd')
		{
			list<Oxygen_Depot*>::iterator i1;
			for (i1 = depot_ptrs.begin(); i1 != depot_ptrs.end(); i1++)
			{
				//Create new object if object with id number doesnt exist
				bool counter = ((*i1) -> get_id()) == id1;
				if (counter == false)
				{
					Oxygen_Depot *d1 = new Oxygen_Depot(loc, id1);
					depot_ptrs.push_back(d1);
					object_ptrs.push_back(d1);
					active_ptrs.push_back(d1);
					break;
				}
			}
		}	
		//Create alien
		else if (type == 'x')
		{
			list<Alien*>::iterator i1;
			for (i1 = alien_ptrs.begin(); i1 != alien_ptrs.end(); i1++)
			{
				//Create new object if object with id number doesnt exist
				bool counter = ((*i1) -> get_id()) == id1;
				if (counter == false)
				{
					Alien *x1 = new Alien(id1, loc);
					alien_ptrs.push_back(x1);
					object_ptrs.push_back(x1);
					active_ptrs.push_back(x1);
					break;
				}
			}
		}
	}

	
	














