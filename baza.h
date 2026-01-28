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

Mech* add_new_mech(Mech *head);
void print_all_mechs(Mech *head);

void save_to_file(Mech *head, const char *filename);
Mech* load_from_file(const char *filename);


#endif