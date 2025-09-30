#ifndef BATTLECOMPUTES_H
#define BATTLECOMPUTES_H

#include <stdio.h>
#include <math.h>
#include <allegro.h>
#include <time.h>
#include "typing.h"
#include "moves.h"
#include "monsters.h"


//Going to expand the maximum party number
//but for testing purposes, i will keep them at 1

//This is the party of player and enemy:

extern Partymon Monsters_Self[1];
extern Partymon Monsters_Foe[1];

void wait_press();
void init_battle(int self_dex, int foe_dex);
float calc_type_mod(int type_self, int type_foe);
int calc_damage(int attack, int defense, int power, int stab, 
                   float type_mod, float rnd);
int speed_check();
int battle_flow(int move_choice, int speed_check_result);

                   
#endif 