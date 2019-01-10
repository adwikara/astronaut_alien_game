#ifndef PERSON_H
#define PERSON_H
#include "Game_Object.h"
#include "Oxygen_Depot.h"
#include "Space_Station.h"
#include "Cart_Point.h"
#include "Cart_Vector.h"
using namespace std;
class Person : public Game_Object
{
public:
	Person();
	Person(char in_code);
	Person(Cart_Point in_loc, int in_id, char in_code);
	virtual ~Person();
	void start_moving(Cart_Point dest);
	void stop();
	void show_status();
	virtual void start_supplying(Oxygen_Depot* inputDepot);
	virtual void start_depositing(Space_Station* inputStation);
	virtual void go_to_station(Space_Station* inputStation);
	virtual bool update() = 0;
	bool is_alive();
	void take_hit(int attack_strength);
	
private:
	double speed;
	Cart_Point destination;
	Cart_Vector delta;
protected:
	bool update_location();
	void setup_destination(Cart_Point dest);
	int health;

};


#endif