#ifndef MOVES_H
#define MOVES_H

#include "typing.h"
#include "status.h"


typedef struct {
    int id;
    char name[20];
    int isdamaging; //0 = non-damaging move
    int power;
    int accuracy;
    int perfacur; //1 = Ignore accuracy checks
    int element;  //0 = Inherit monster type element (default)
    int archetype;
    int secondary_effect_chance; //Non-damaging moves = 100
    int status_inflicted; 
    int special_effect; //Effects too specific to include on the struct
    //Like vamp, heal statuses, etc
} Move;


const Move ALL_MOVES[];

#endif
