#include "battlecomputes.h"


Partymon Monsters_Self[1];
Partymon Monsters_Foe[1];







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



