#include <iostream>
#include <exception>
#include "Cart_Point.h"
#include "Cart_Vector.h"
#include "Game_Object.h"
#include "Oxygen_Depot.h"
#include "Space_Station.h"
#include "Astronaut.h"
#include "Person.h"
#include "Model.h"
#include "Game_Command.h"
#include "InputHandling.h"
using namespace std;

int main()
{
	cout << "EC327: Introduction to Software Engineering" << endl;
	cout << "Fall 2017" << endl;
	cout << "Programming Assignment 4" << endl;

	//Initialize Model
	Model * m1 = new Model();
	View v1 = View();
	m1 -> show_status();
	m1 -> display(v1);


	char input;
	int inputid1;
	int inputid2;
	double inputx;
	double inputy;
	//char * pinput;

	do
	{
		cout << "Enter command: ";
		cin >> input;

		try
		{

			// Using switch, the letters bellow will have corresponding commands
			switch (input)
			{
				case 'm':
				{
					int inputid1 = get_double();
					int inputx = get_int();
					int inputy = get_int();

					Cart_Point p1 = Cart_Point(inputx, inputy);
					do_move_command(m1, inputid1, p1);
					break;
				}
				case 'a':
				{
					int inputid1 = get_int();
					int inputid2 = get_int();
					do_attack(m1, inputid1, inputid2);
					break;
				}
				case 'w':
				{
					int inputid1 = get_int();
					int inputid2 = get_int();
					do_work_a_depot_command(m1, inputid1, inputid2);
					break;
				}
				case 'd':
				{
					int inputid1 = get_int();
					int inputid2 = get_int();
					do_deposit_moonstones_command(m1, inputid1, inputid2);
					break;
				}
				case 's':
				{
					int inputid1 = get_int();
					do_stop_command(m1, inputid1);
					break;
				}
				case 'l':
				{
					int inputid1 = get_int();
					int inputid2 = get_int();
					do_lock_in_at_station_command(m1, inputid1, inputid2);
					break;
				}
				case 'g':
				{
					do_go_command(m1);
					m1 -> show_status();
					m1 -> display(v1);
					break;
				}
				case 'r':
				{
					do_run_command(m1);
					m1 -> show_status();
					m1 -> display(v1);
					break;
				}
				case 'n':
				{
					char type = get_type();
					int inputid1 = get_double();
					int inputx = get_int();
					int inputy = get_int();
					

					Cart_Point p1 = Cart_Point(inputx, inputy);
					do_new_command(m1, type, inputid1, p1);
					break;
				}
				case 'q':
				{
					cout << "Terminating program." << endl;
					delete m1;
					do_quit_command(m1);
				}
				default:
				throw Invalid_Input("Illegal format enter again!");
			}	
		}

		catch (Invalid_Input& except)
		{
			cout << "Invalid input - " << except.msg_ptr << endl;
			cin.clear();
			cin.ignore();
		}

	} while(input != 'q');

	return 0;
}

