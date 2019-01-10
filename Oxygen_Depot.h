#ifndef OXYGEN_DEPOT_H
#define OXYGEN_DEPOT_H
#include "Game_Object.h"
using namespace std;
class Oxygen_Depot : public Game_Object
{
private:
	double amount_oxygen;
public:
	Oxygen_Depot();
	Oxygen_Depot(Cart_Point inputLoc, int inputld);
	~Oxygen_Depot();
	bool is_empty();
	double extract_oxygen(double amount_to_extract = 20);
	bool update();
	void show_status();
};


#endif