#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include "Cart_Point.h"
using namespace std;

class Game_Object
{
protected:
	Cart_Point location;
	int id_num;
	char display_code;
	char state;
public:
	Game_Object(char in_code);
	Game_Object(Cart_Point in_loc, int in_id, char in_code);
	virtual ~Game_Object();
	Cart_Point get_location();
	int get_id();
	char get_state();
	void drawself(char * ptr);
	virtual void show_status();
	virtual bool is_alive();
	virtual bool update() = 0;
};
#endif