#include <stdio.h>
#include <stdlib.h>
#include "baza.h"

void print_menu() {
    printf("\n--- MECH FLEET MANAGEMENT SYSTEM 2264 ---\n");
    printf("1. List all mechs\n");
    printf("2. Add new mech\n");
    printf("3. Edit mech\n");
    printf("4. Delete mech\n");
    printf("5. Search mech\n");
    printf("6. Sort mechs\n");
    printf("7. Save and Exit\n");
    printf("0. Exit without saving\n");
    printf("Select option: ");
}

void free_memory(Mech *head) {
    Mech *current = head;
    while (current != NULL) {
        Mech *temp = current;
        current = current->next;
        free(temp);
    }
}