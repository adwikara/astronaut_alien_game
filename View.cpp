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
#include "View.h"
View::View()
{
	//Initialize View Constructor
	this -> size = 11;
	this -> scale = 2;
	this -> origin = Cart_Point();
}
void View::clear()
{
	//Resets the grid, make its dots and spaces
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			this -> grid[i][j][0] = '.';
			this -> grid[i][j][1] = ' ';	
		}
	}
}
void View::plot(Game_Object * ptr1)
{
	int x = 0;
	int y = 0;
	Cart_Point loc = ptr1 -> get_location();
	//Call get_subscripts to see if location is within the grid scale
	if (get_subscripts(x, y, loc))
	{
		//Check is astronaut alive or dead
		if (ptr1 -> get_state() == 'x')
		{
			grid[y][x][0] = '.';
			grid[y][x][1] = ' ';

		}
		else
		{
			//If the initial location of the grid is a dot, plot that point. y = rows, x = columns
			if (grid[y][x][0] == '.')
			{
				ptr1 -> drawself(grid[y][x]);
			}
			//If there is an object at that location, then print below
			else
			{
				this -> grid[y][x][0] = '*';
				this -> grid[y][x][1] = ' ';
			}
		}
	}
}
void View::draw()
{
	// Print vertical axis
	for (int i = size -1; i >=0; i--)
	{
		if (i%2 == 0)
		{
			if ((2*i) > 9)
			{
				cout << 2*i;
			}
			else
			{
				cout << 2*i << " ";
			}
			// Print columns when even row
			for (int j = 0; j <= size; j++)
			{
				cout << grid[i][j][0];
				cout << grid[i][j][1];
			}
		}
		else
		{
			//Print columns when odd row
			cout << "  ";
			for (int j = 0; j <= size; j++)
			{
				cout << grid[i][j][0];
				cout << grid[i][j][1];
			}
		}
		cout << endl;
	}
	//Print bottom horizontal axis
	for (int j = 0; j <= size; j++)
	{
		if (j%2 == 0)
		{
			cout << "  ";
		}
		else
		{
			if ((j-1)*2 > 9)
			{
				cout << (j-1)*2;
			}
			else
			{
				cout << (j-1)*2 << " ";
			}
		}
	}
	cout << endl;
}
bool View::get_subscripts(int &ix, int &iy, Cart_Point location)
{
	ix = (location.x-origin.x)/scale;
	iy = (location.y-origin.y)/scale;

	//If object is within range
	if (ix <= size && iy <= size)
	{
		return true;
	}
	else
	//If object not within range
	{
		cout << "An object is outside the display." << endl;
		return false;
	}
}