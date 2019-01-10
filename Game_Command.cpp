#include <iostream>
#include "Game_Object.h"
#include "Oxygen_Depot.h"
#include "Space_Station.h"
#include "Cart_Point.h"
#include "Cart_Vector.h"
#include "Person.h"
#include "Astronaut.h"
#include "Model.h"
#include "Game_Command.h"
#include "Model.h"
#include "Alien.h"
#include "InputHandling.h"
#include "stdlib.h"
void do_move_command(Model* model, int id1, Cart_Point loc)
{
	char choice;
	int counter = 0;

	do
	{
		//Ask move astronaut or alien
		cout << "Move Astronaut (enter 'a') or Alien (enter 'x'): ";
		cin >> choice;

		try
		{
			switch(choice)
			{
				//Find the pointer to the astronaut/alien
				case 'a':
				{
					Person * c1 = model -> get_Person_ptr(id1);

					//Astronaut/Alien starts moving
					c1 -> start_moving(loc);
					counter = 1;
					break;
				}
				case 'x':
				{
					Alien * c1 = model -> get_Alien_ptr(id1);

					//Astronaut/Alien starts moving
					c1 -> start_moving(loc);
					counter = 1;
					break;
				}
				default:
				cin.clear();
				cin.ignore();
				throw Invalid_Input("Illegal format enter again!");
			}
			
		}
		
		catch (Invalid_Input& except)
		{
			cout << "Invalid input - " << except.msg_ptr << endl;
		}

	} while (counter != 1);
}
void do_work_a_depot_command(Model* model, int id1, int id2)
{
	//Find the pointer to the astronaut as well as the oxygen depot
	Person * c1 = model -> get_Person_ptr(id1);
	Oxygen_Depot * c2 = model -> get_Oxygen_Depot_ptr(id2);

	//Astronaut object starts supplying
	c1 -> start_supplying(c2);
}
void do_attack(Model* model, int id1, int id2)
{
	//Find the pointer to the astronaut as well as the alien
	Person * c1 = model -> get_Person_ptr(id2);
	Alien * c2 = model -> get_Alien_ptr(id1);

	//Alien attack astronaut
	c2 -> start_attack(c1);

}
void do_deposit_moonstones_command(Model* model, int id1, int id2)
{
	//Find the pointer to the astronaut as well as the space station
	Person * c1 = model -> get_Person_ptr(id1);
	Space_Station * c2 = model -> get_Space_Station_ptr(id2);

	//Astronaut object starts depositing
	c1 -> start_depositing(c2);
}
void do_stop_command(Model* model, int id1)
{
	//Find the pointer to the astronaut
	Person * c1 = model -> get_Person_ptr(id1);

	//Astronaut object stops
	c1 -> stop();
}
void do_lock_in_at_station_command(Model* model, int id1, int id2)
{
	//Find the pointer to the astronaut as well as space station
	Person * c1 = model -> get_Person_ptr(id1);
	Space_Station * c2 = model -> get_Space_Station_ptr(id2);

	//Astronaut object goes to station
	c1 -> go_to_station(c2);
}
void do_go_command(Model* model)
{
	cout << "Advancing one tick." << endl;
	
	//Update all objects
	model -> update();
}
void do_run_command(Model* model)
{
	cout << "Advancing to next event." << endl;
	int count = 0;
	int counter = 0;
	int key = 0;

	//Update all objects until one returns true, or it has updated every object 5 times
	do
	{
		count++;
		if (model -> update() == true)
		{
			counter = 1;
		}
		if (count == 5 || counter == 1)
		{
			key = 1;
		}
	} while (key != 1);
}
void do_new_command(Model* model, char c1, int id1, Cart_Point loc)
{
	model -> handle_new_command(c1, id1, loc);
}
void do_quit_command(Model* model)
{
	//End program
	exit(0);
}
int get_int() 
{
	int res;
	if(!(cin >> res))
		throw Invalid_Input("Was expecting an integer");
	
	return res;
}
double get_double()
{
	double res;
	if(!(cin >> res))
		throw Invalid_Input("Was expecting a double");
	
	return res;
}
char get_type()
{
	char res;
	if(!(cin >> res))
		throw Invalid_Input("Was expecting a character");
	else
	{
		if(res != 'd' && res != 's' && res != 'a' && res != 'x')
			throw Invalid_Input("Illegal format enter again!");
		return res;
	}
	
}






