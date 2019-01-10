#ifndef VIEW_H
#define VIEW_H
#include "Game_Object.h"
#include "Oxygen_Depot.h"
#include "Space_Station.h"
#include "Cart_Point.h"
#include "Cart_Vector.h"
#include "Person.h"

const int view_maxsize = 20;

class View
{
private:
	int size;
	double scale;
	Cart_Point origin;
	char grid[view_maxsize][view_maxsize][2];
	bool get_subscripts(int &ix, int &iy, Cart_Point location);
	
public:
	View();
	void clear();
	void plot(Game_Object * ptr);
	void draw();
};

#endif
