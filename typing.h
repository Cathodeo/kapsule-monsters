#ifndef TYPING_H
#define TYPING_H


typedef struct {

    int id;
    char name[16];
    int resistance[10];
    int physical;


} Type;

typedef struct {

    int id;
    char name[16];

} Archetype;

extern const Type ALL_TYPES[];
extern const Archetype ALL_ARCHETYPES[];

#endif
