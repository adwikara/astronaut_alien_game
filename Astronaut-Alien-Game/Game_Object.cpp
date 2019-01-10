#include <iostream>
#include "Cart_Point.h"
#include "Game_Object.h"
#include "string.h"
using namespace std;

	Game_Object::Game_Object(char in_code)
	{
		//Initialize values
		this -> display_code = in_code;
		this -> id_num = 1;
		this -> state = 's';
		cout << "Game_Object constructed" << endl;
	}
	Game_Object::Game_Object(Cart_Point in_loc, int in_id, char in_code)
	{
		//Initialize values
		this -> display_code = in_code;
		this -> location = in_loc;
		this -> id_num = in_id;
		this -> state = 's';
		cout << "Game_Object constructed" << endl;
	}
	Game_Object::~Game_Object()
	{
		//Destructor message
		cout << "Game_Object destructed." << endl;
	}
	Cart_Point Game_Object::get_location()
	{
		//Returns location of object
		return location; 
	}
	int Game_Object::get_id()
	{
		//Returns id number of object
		return id_num;
	}
	char Game_Object::get_state()
	{
		//Returns state of object
		return state;
	}
	void Game_Object::show_status()
	{
		//Prints status of object
		cout << display_code << id_num << " at " << location << " ";
	}
	void Game_Object::drawself(char * ptr)
	{
		//Assigns the object's display code and id to a pointer to char
		*ptr = display_code;
		//Adding 48 corresponds to getting the right ASCII value
		*(ptr+1) = get_id() + 48;
	}
	bool Game_Object::is_alive()
	{
		return true;
	}

