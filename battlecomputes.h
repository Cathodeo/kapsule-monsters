#ifndef BATTLECOMPUTES_H
#define BATTLECOMPUTES_H

#include <stdio.h>
#include <math.h>
#include "typing.h"
#include "moves.h"
#include "monsters.h"


//Going to expand the maximum party number
//but for testing purposes, i will keep them at 1

//This is the party of player and enemy:

extern Partymon Monsters_Self[1];
extern Partymon Monsters_Foe[1];


int calc_damage(int attack, int defense, int power, int stab, 
                   float type_mod, float rnd);

                   
#endif 