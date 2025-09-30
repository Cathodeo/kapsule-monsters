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

void wait_press()
{
    while (!key[KEY_ENTER])
    {rest(16);}
}

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

int battle_flow(int move_choice, int speed_check_result) {
    int damage, stab;

    int move_id_self = Monsters_Self[0].moves[move_choice];
    int foe_choice = rand() % 2;
    int move_id_foe = Monsters_Foe[0].moves[foe_choice];

    // Determine turn order: 1 = self first, 0 = foe first
    int self_first = (speed_check_result == 1);

    // --- First turn ---
    if (self_first) {
        // Self turn
        stab = (get_arch_from_dex(Monsters_Self[0].dex_id) == get_arch_from_move(move_id_self));
        printf("DEBUG: Ally monster used: %s\n", get_name_from_move(move_id_self));

        damage = calc_damage(
            get_ata_from_dex(Monsters_Self[0].dex_id),
            get_def_from_dex(Monsters_Foe[0].dex_id),
            get_power_from_move(move_id_self),
            stab,
            calc_type_mod(get_type_from_move(move_id_self), get_type_from_dex(Monsters_Foe[0].dex_id)),
            0.85
        );

        Monsters_Foe[0].hp -= damage;
        if (damage) printf("DEBUG: Damage dealt: %d\n", damage);
        else printf("DEBUG: No damage\n");

        if (Monsters_Foe[0].hp <= 0) {
            Monsters_Foe[0].hp = 0;
            printf("The foe monster has fainted!\n");
            return 1;
        }
        printf("DEBUG: Foe health remaining: %d\n", Monsters_Foe[0].hp);
    } else {
        // Foe turn
        stab = (get_arch_from_dex(Monsters_Foe[0].dex_id) == get_arch_from_move(move_id_foe));
        printf("DEBUG: Foe monster used: %s\n", get_name_from_move(move_id_foe));

        damage = calc_damage(
            get_ata_from_dex(Monsters_Foe[0].dex_id),
            get_def_from_dex(Monsters_Self[0].dex_id),
            get_power_from_move(move_id_foe),
            stab,
            calc_type_mod(get_type_from_move(move_id_foe), get_type_from_dex(Monsters_Self[0].dex_id)),
            0.85
        );

        Monsters_Self[0].hp -= damage;
        if (damage) printf("DEBUG: Damage dealt: %d\n", damage);
        else printf("DEBUG: No damage\n");

        if (Monsters_Self[0].hp <= 0) {
            Monsters_Self[0].hp = 0;
            printf("The ally monster has fainted!\n");
            return 1;
        }
        printf("DEBUG: Ally health remaining: %d\n", Monsters_Self[0].hp);
    }

    // --- Second turn ---
    if (self_first) {
        // Foe turn
        stab = (get_arch_from_dex(Monsters_Foe[0].dex_id) == get_arch_from_move(move_id_foe));
        printf("DEBUG: Foe monster used: %s\n", get_name_from_move(move_id_foe));

        damage = calc_damage(
            get_ata_from_dex(Monsters_Foe[0].dex_id),
            get_def_from_dex(Monsters_Self[0].dex_id),
            get_power_from_move(move_id_foe),
            stab,
            calc_type_mod(get_type_from_move(move_id_foe), get_type_from_dex(Monsters_Self[0].dex_id)),
            0.85
        );

        Monsters_Self[0].hp -= damage;
        if (damage) printf("DEBUG: Damage dealt: %d\n", damage);
        else printf("DEBUG: No damage\n");

        if (Monsters_Self[0].hp <= 0) {
            Monsters_Self[0].hp = 0;
            printf("The ally monster has fainted!\n");
            return 1;
        }
        printf("DEBUG: Ally health remaining: %d\n", Monsters_Self[0].hp);
    } else {
        // Self turn
        stab = (get_arch_from_dex(Monsters_Self[0].dex_id) == get_arch_from_move(move_id_self));
        printf("DEBUG: Ally monster used: %s\n", get_name_from_move(move_id_self));

        damage = calc_damage(
            get_ata_from_dex(Monsters_Self[0].dex_id),
            get_def_from_dex(Monsters_Foe[0].dex_id),
            get_power_from_move(move_id_self),
            stab,
            calc_type_mod(get_type_from_move(move_id_self), get_type_from_dex(Monsters_Foe[0].dex_id)),
            0.85
        );

        Monsters_Foe[0].hp -= damage;
        if (damage) printf("DEBUG: Damage dealt: %d\n", damage);
        else printf("DEBUG: No damage\n");

        if (Monsters_Foe[0].hp <= 0) {
            Monsters_Foe[0].hp = 0;
            printf("The foe monster has fainted!\n");
            return 1;
        }
        printf("DEBUG: Foe health remaining: %d\n", Monsters_Foe[0].hp);
    }

    // Battle continues
    return 0;
}

