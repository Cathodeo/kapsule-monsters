#include "moves.h"

    /**
    int id;
    char name[20];
    int isdamaging; //0 = non-damaging move
    int power;
    int accuracy;
    int perfacur; //1 = Ignore accuracy checks
    int element;  //0 = Inherit monster type element (default)
    int archetype -1 BRAWLER, 2 TANK, 3 NIMBLE, 4 WIZARD, 5 CLERIC, 6 BURSTER;
    int secondary_effect_chance; //Non-damaging moves = 100
    int status_inflicted; 
    int special_effect; //Effects too specific to include on the struct
    //Like vamp, heal statuses, etc */



const Move ALL_MOVES[] = {

{1, "Curl Bash", 1, 80, 95, 0, 0, 2, 30, 0, 102},
{2, "Cat Nap", 0, 0 ,100, 1, 0, 2, 100, 0, 302},
{3, "Dire Claws", 1, 95, 95, 0, 0, 1, 20, 5, 0},
{5, "Landslide", 1, 80, 85, 0, 0, 1, 25, 6, 0}, 
{6, "Enrage", 0, 0, 100, 1, 0, 1, 100, 0, 201}, 
{7, "Frostbite", 1, 65, 85, 0, 5, 4, 35, 7, 0}

};