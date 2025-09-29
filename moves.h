#ifndef MOVES_H
#define MOVES_H

#include "typing.h"
#include "status.h"
#include <stdio.h>


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


extern const Move ALL_MOVES[];
const Move* get_move_by_id(int id);
char* get_name_from_move(int move_id);
int get_power_from_move(int move_id);
int get_accuracy_from_move(int move_id);
int get_type_from_move(int move_id);
int get_arch_from_move(int move_id);
int get_perfacur_from_move(int move_id);

#endif
