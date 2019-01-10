#include <iostream>
#include "Cart_Point.h"
#include "Game_Object.h"
#include "Oxygen_Depot.h"
using namespace std;
Oxygen_Depot::Oxygen_Depot():Game_Object('O')
{
	this -> amount_oxygen = 50;
	this -> state = 'f';
	cout << "Oxygen_Depot default constructed" << endl;
}
Oxygen_Depot::Oxygen_Depot(Cart_Point inputLoc, int inputld):Game_Object(inputLoc, inputld, 'O')
{
	this -> amount_oxygen = 50;
	this -> id_num = inputld;
	this -> location = inputLoc;
	this -> state = 'f';
	cout << "Oxygen_Depot constructed" << endl;
}
Oxygen_Depot::~Oxygen_Depot()
{
	//Destructor message
	cout << "Oxygen_Depot destructed." << endl;
}
bool Oxygen_Depot::is_empty()
{
	if(amount_oxygen == 0)
		return true;
	else
		return false;
}
double Oxygen_Depot::extract_oxygen(double amount_to_extract)
{
	//Extract oxygen if amount is enough
	double res;
	if(amount_oxygen >= amount_to_extract)
	{
		this -> amount_oxygen = amount_oxygen - amount_to_extract;
		res = amount_to_extract;
		return res;
	}
	else
	{
		res = amount_oxygen;
		this -> amount_oxygen = 0;
		return res;
	}
}
bool Oxygen_Depot::update()
{
	//If no more oxygen in depot
	if(amount_oxygen == 0)
	{
		this -> state = 'e';
		this -> display_code = 'o';
		cout << "Oxygen_Depot " << id_num << " has been depleted." << endl;
		return true;
	}
	else
		return false;
}
void Oxygen_Depot::show_status()
{
	//Oxygen Depot's show status
	cout << "Oxygen Depot Status: " << display_code << id_num << " at location " << location << " contains " << amount_oxygen << endl;
}








