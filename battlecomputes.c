#include "battlecomputes.h"


Partymon Monsters_Self[1];
Partymon Monsters_Foe[1];


//Debug version that assumes there is exactly ONE
//monster per party. Actual game will need this expanded
//and the init from the player should simply copy the
//WRAM values from the permanent party.

/*Affinity is the replacement of level*/
/*Player level won't be taken into consideration
for simplicity, but actual gameplay would add an stat
boost on everything but HP, up to 20% player level and 30% affinity*/

void init_battle(int self_dex, int foe_dex) {
    // Initialize player’s first monster
    Monsters_Self[0].hp = get_hp_from_dex(self_dex);
    Monsters_Self[0].stamina = 100;
    //Stamina is actually a fixed constant, Stamina
    //consumption is mitigated by Resistance (DEF)
    Monsters_Self[0].status = 0;
    for (int i = 0; i < 6; i++) Monsters_Self[0].debuff[i] = 0;
    Monsters_Self[0].affinity = 1;
    Monsters_Self[0].moves[0] = get_base_move_from_dex(self_dex);
    Monsters_Self[0].moves[1] = get_random_move_from_dex(self_dex);
    // Initialize enemy’s first monster
    Monsters_Foe[0].hp = get_hp_from_dex(foe_dex);
    Monsters_Foe[0].stamina = 100;
    Monsters_Foe[0].status = 0;
    Monsters_Foe[0].moves[0] = get_base_move_from_dex(foe_dex);
    Monsters_Foe[0].moves[1] = get_random_move_from_dex(foe_dex);
    for (int i = 0; i < 6; i++) Monsters_Foe[0].debuff[i] = 0;
    Monsters_Foe[0].affinity = 1;
}




float calc_type_mod(int type_self, int type_foe)
{
    // attack_idx = index in ALL_TYPES (0..n-1)
    // defend_id  = id field of defending type (1..n)
    
    int effect = ALL_TYPES[type_foe - 1].resistance[type_self - 1];

    switch(effect) {
        case 0: return 1.0f;  // neutral
        case 1: return 2.0f;  // weak to → double damage
        case 2: return 0.5f;  // resistant → half damage
        default: return 1.0f;  // safety fallback
    }
}



int calc_damage(int attack, int defense, int power, int stab,
                float type_mod, float rnd)
{
    const float C = 225.0f;   // tunable constant
    const float BASE = 50.0f; // base scaling for raw HP damage

    float A = (float) attack;
    float D = (float) defense;
    float P = (float) power;

    float numerator = A * P;
    float denom = numerator + D * C;
    float fraction = 0.0f;

    if (denom > 0.0f)
        fraction = numerator / denom;

    // Apply type effectiveness and randomness
    fraction *= type_mod * rnd;

    // Scale to meaningful HP points
    int damage = (int)(fraction * BASE);

    // Ensure at least 1 damage
    if (damage < 1)
        damage = 1;

    // Apply STAB if applicable
    if (stab == 1)
        damage = (int)(damage * 1.5f);

    return damage;
}

int speed_check()
{
    int self_speed = get_spe_from_dex(Monsters_Self[0].dex_id);
    int foe_speed = get_spe_from_dex(Monsters_Foe[0].dex_id);

    if (self_speed > foe_speed) return 1;
    else return 0;
}

void battle_flow(int move_choice, int speed_check_result) {

    int self_turn_finished = 0;
    int foe_turn_finished = 0;
    
    if (speed_check_result == 1) goto self_turn;
    else goto foe_turn;

    

    self_turn:

        self_turn_finished = 1;
        if (foe_turn_finished == 0) goto foe_turn;


    foe_turn:

        foe_turn_finished = 1;
        if (self_turn_finished == 0) goto self_turn;


}


