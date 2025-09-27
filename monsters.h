#ifndef MONSTERS_H
#define MONSTERS_H

#include <stdio.h>
#include "moves.h"
#include "typing.h"

typedef struct {
    int id;
    char name[20];
    int hp;
    int ata;
    int def;
    int mag;
    int wis;
    int spe;
    int affinity_curve;
    int stage;
    int archetype;      // brawler, tank, nimble, etc.
    int type;           // metal, robot, radio, etc.
    Move moves[4]; //Note: The first move is already builtin, 
    //A second random one to pick from the remaining three upon leveling
    //up the affinity
} Species;

//Current RAM info for a monster in the party,
//with a particular moveset and hp value

typedef struct {
    int dex_id;
    int hp;
    int stamina;
    int status;
    int debuff[6];
    int affinity;
    Move moves[4]; 
} Partymon;

extern const Species ALL_SPECIES[];


const Species* get_species_by_id(int id);
int get_hp_from_dex(int dex_id);
int get_ata_from_dex(int dex_id);
int get_def_from_dex(int dex_id);
int get_mag_from_dex(int dex_id);
int get_wis_from_dex(int dex_id);
int get_spe_from_dex(int dex_id);
int get_arch_from_dex(int dex_id);
int get_type_from_dex(int dex_id);

#endif
