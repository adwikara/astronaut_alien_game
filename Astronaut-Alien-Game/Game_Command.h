#ifndef GAME_COMMAND_H
#define GAME_COMMAND_H
#include "Game_Object.h"
#include "Oxygen_Depot.h"
#include "Space_Station.h"
#include "Cart_Point.h"
#include "Cart_Vector.h"
#include "Person.h"
#include "Model.h"
void do_move_command(Model* model, int id1, Cart_Point loc);
void do_work_a_depot_command(Model* model, int id1, int id2);
void do_deposit_moonstones_command(Model* model, int id1, int id2);
void do_stop_command(Model* model, int id1);
void do_lock_in_at_station_command(Model* model, int id1, int id2);
void do_go_command(Model* model);
void do_run_command(Model* model);
void do_quit_command(Model* model);
void do_attack(Model* model, int id1, int id2);
void do_new_command(Model* model, char c1, int id1, Cart_Point loc);
int get_int();
double get_double();
char get_type();
#endif