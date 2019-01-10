#ifndef ALIEN_H
#define ALIEN_H
#include "Game_Object.h"
#include "Oxygen_Depot.h"
#include "Space_Station.h"
#include "Cart_Point.h"
#include "Cart_Vector.h"
#include "Person.h"
using namespace std;
class Alien : public Game_Object
{
private:
	int attack_strength;
	double range;
	Person * target;
	double speed;
	Cart_Point destination;
	Cart_Vector delta;

protected:
	void setup_destination(Cart_Point dest);
	bool update_location();

public:
	Alien();
	Alien(int in_id, Cart_Point in_loc);
	virtual~Alien();
	void start_attack(Person * in_target);
	bool update();
	void show_status();
	void start_moving(Cart_Point dest);
	void stop();
};
#endif