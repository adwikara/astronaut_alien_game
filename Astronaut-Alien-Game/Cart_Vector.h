#ifndef CART_VECTOR_H
#define CART_VECTOR_H
#include "Cart_Point.h"
using namespace std;
class Cart_Vector
{
	public:
	double x;
	double y;
	Cart_Vector();
	Cart_Vector(double inputx, double inputy);
};
ostream& operator<<(ostream& out, const Cart_Vector& p1);
Cart_Vector operator * (const Cart_Vector& v1, const double d);
Cart_Vector operator / (const Cart_Vector& v1, const double d);
#endif