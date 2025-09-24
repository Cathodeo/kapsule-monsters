#ifndef TYPING_H
#define TYPING_H


typedef struct {

    int id;
    char name[16];
    int strong_to[10];
    int weak_to[10];

} Type;

typedef struct {

    int id;
    char name[16];

} Archetype;



#endif
