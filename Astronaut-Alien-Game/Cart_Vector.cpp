#include <iostream>
#include "Cart_Point.h"
using namespace std;

//Default Constructor
Cart_Vector::Cart_Vector()
{
	x = 0.0;
	y = 0.0;
}
//Other Constructors
Cart_Vector::Cart_Vector(double inputx, double inputy)
{
	x = inputx;
	y = inputy;
}
//Overloaded Operators
ostream& operator<<(std::ostream& out, const Cart_Vector& p1)
{
	out << "<" << p1.x << "," << " " << p1.y << ">";
	return out;
}
Cart_Vector operator * (const Cart_Vector& v1, const double d)
{
	Cart_Vector result;
	result.x = v1.x * d;
	result.y = v1.y * d;
	return result;
}
Cart_Vector operator / (const Cart_Vector& v1, const double d)
{
	Cart_Vector result;
	if (d == 0)
	{
		result.x = v1.x;
		result.y = v1.y;
		return result;
	}
	else
	{
		result.x = v1.x / d;
		result.y = v1.y / d;
		return result;
	}
}