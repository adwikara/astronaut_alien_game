#include <iostream>
#include "Cart_Point.h"
#include <cmath>
using namespace std;

//Default Constructor
Cart_Point::Cart_Point()
{
	x = 0.0;
	y = 0.0;
}
//Constructor
Cart_Point::Cart_Point(double inputx, double inputy)
{
	x = inputx;
	y = inputy;
}
//Nonmember Functions
double cart_distance(Cart_Point p1, Cart_Point p2)
{
	double res;
	res = sqrt(pow((p2.x-p1.x),2)+ pow((p2.y-p1.y),2));
	return res;
}
//Overloaded Operators
ostream& operator<<(ostream& out, const Cart_Point& p1)
{
	out << "(" << p1.x << "," << p1.y << ")";
	return out;
}

Cart_Point operator+(const Cart_Point& p1, const Cart_Vector& v1)
{
	Cart_Point result;
	result.x = p1.x + v1.x;
	result.y = p1.y + v1.y;
	return result;
}

Cart_Vector operator-(const Cart_Point& p1, const Cart_Point& p2)
{
	Cart_Vector result;
	result.x = p1.x - p2.x;
	result.y = p1.y - p2.y;
	return result;
}