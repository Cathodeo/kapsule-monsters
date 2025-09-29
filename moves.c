#include "moves.h"
#define NUM_MOVES (sizeof(ALL_MOVES) / sizeof(ALL_MOVES[0]))


const Move ALL_MOVES[] = {

{1, "Curl Bash", 1, 80, 95, 0, 0, 2, 30, 0, 102},
{2, "Cat Nap", 0, 0 ,100, 1, 0, 2, 100, 0, 302},
{3, "Dire Claws", 1, 95, 95, 0, 0, 1, 20, 5, 0},
{5, "Landslide", 1, 80, 85, 0, 0, 1, 25, 6, 0}, 
{6, "Enrage", 0, 0, 100, 1, 0, 1, 100, 0, 201}, 
{7, "Frostbite", 1, 65, 85, 0, 5, 4, 35, 7, 0}

};

const Move* get_move_by_id(int id){

     {
    for (size_t i = 0; i < NUM_MOVES; i++) {
        if (ALL_MOVES[i].id == id)
            return &ALL_MOVES[i]; // return pointer to the struct
    }
    return 0; // not found
}

}

char* get_name_from_move(int move_id)
{
    const Move* m = get_move_by_id(move_id);
    if (m != NULL) {
    printf("DEBUG: Species name: %m\n", m->name);
    return m->name;}
    }


int get_power_from_move(int move_id)
{
    const Move* m = get_move_by_id(move_id);
    if (m != NULL) {
    printf("DEBUG: Species name: %m\n", m->name);
    return m->power;}
    }

int get_accuracy_from_move(int move_id)
{
    const Move* m = get_move_by_id(move_id);
    if (m != NULL) {
    printf("DEBUG: Species name: %m\n", m->name);
    return m->accuracy;}
    }

int get_perfacur_from_move(int move_id)
{
    const Move* m = get_move_by_id(move_id);
    if (m != NULL) {
    printf("DEBUG: Species name: %m\n", m->name);
    return m->perfacur;}
    }

int get_type_from_move(int move_id)
{
    const Move* m = get_move_by_id(move_id);
    if (m != NULL) {
    printf("DEBUG: Species name: %m\n", m->name);
    return m->element;}
    }

int get_arch_from_move(int move_id)
{
    const Move* m = get_move_by_id(move_id);
    if (m != NULL) {
    printf("DEBUG: Species name: %m\n", m->name);
    return m->archetype;}
    }
