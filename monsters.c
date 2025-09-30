#include "monsters.h"
#define NUM_SPECIES (sizeof(ALL_SPECIES) / sizeof(ALL_SPECIES[0]))


const Species ALL_SPECIES[] = {

    {38, "Medvul",60, 60, 60, 75, 50, 60, 2, 1, 1, 5,
    {5, 6, 7, 7}
    },
    {40, "Mogshka", 45, 80, 45, 35, 110, 85, 3, 1, 2, 1,
    {1, 2, 3, 3}
    }
};


const Species* get_species_by_id(int id) {
    for (size_t i = 0; i < NUM_SPECIES; i++) {
        if (ALL_SPECIES[i].id == id)
            return &ALL_SPECIES[i]; // return pointer to the struct
    }
    return 0; // not found
}

char* get_name_from_dex(int dex_id)
{
    const Species* s = get_species_by_id(dex_id);
    if (s != NULL) {
    return s->name;}

    }

int get_hp_from_dex(int dex_id)
{
    const Species* s = get_species_by_id(dex_id);
    if (s != NULL) {
    return s->hp;}

    }

int get_ata_from_dex(int dex_id)
{
    const Species* s = get_species_by_id(dex_id);
    if (s != NULL) {
    return s->ata;}

    }

int get_def_from_dex(int dex_id)
{
    const Species* s = get_species_by_id(dex_id);
    if (s != NULL) {
    return s->def;}

    }
int get_mag_from_dex(int dex_id)
{
    const Species* s = get_species_by_id(dex_id);
    if (s != NULL) {
    return s->mag;}
    }

int get_wis_from_dex(int dex_id)
{
    const Species* s = get_species_by_id(dex_id);
    if (s != NULL) {
    return s->wis;}
    }

int get_spe_from_dex(int dex_id)
{
    const Species* s = get_species_by_id(dex_id);
    if (s != NULL) {
    return s->spe;}
   
}


    int get_arch_from_dex(int dex_id)
{
    const Species* s = get_species_by_id(dex_id);
    if (s != NULL) {
    return s->archetype;}

    }

    int get_type_from_dex(int dex_id)
{
    const Species* s = get_species_by_id(dex_id);
    if (s != NULL) {
    return s->type;}

    }

    int get_base_move_from_dex(int dex_id)
    {
    const Species* s = get_species_by_id(dex_id);
    if (s != NULL) {
    return s->moves[0];} 
    }

    int get_random_move_from_dex(int dex_id)
    {
    const Species* s = get_species_by_id(dex_id);
    if (s != NULL) {
    //Hardcoded to 2 for simplicity, should be
    //random between 1 and 2
    return s->moves[2];}   
    }




