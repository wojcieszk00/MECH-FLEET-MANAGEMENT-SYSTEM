#ifndef BAZA_H
#define BAZA_H

typedef struct Mech {
    char model[101];
    char type[50];
    int reactor_power;
    char pilot[101];
    char status[50];
    struct Mech *next;
} Mech;

void print_menu();
void free_memory(Mech *head);

#endif