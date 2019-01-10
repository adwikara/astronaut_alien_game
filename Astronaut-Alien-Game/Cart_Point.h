#ifndef CART_POINT_H
#define CART_POINT_H
#include "Cart_Vector.h"
using namespace std;
class Cart_Point
{
	public:
	double x;
	double y;
	Cart_Point();
	Cart_Point(double inputx, double inputy);
};
ostream& operator<<(ostream& out, const Cart_Point& p1);
Cart_Point operator+(const Cart_Point& p1, const Cart_Vector& v1);
Cart_Vector operator-(const Cart_Point& p1, const Cart_Point& p2);
double cart_distance(Cart_Point p1, Cart_Point p2);

#endif