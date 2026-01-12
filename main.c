#include <stdio.h>
#include <stdlib.h>
#include "baza.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Error: No database file provided.\n");
        printf("Usage: %s <filename.txt>\n", argv[0]);
        return 1;
    }

    char *file = argv[1];
    Mech *head = NULL;
    int choice;

    do {
        print_menu();
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            choice = -1;
        }

        switch (choice) {
            case 1:
                printf("...\n");
                break;
            case 2:
                printf("...\n");
                break;
            case 3:
                printf("...\n");
                break;
            case 4:
                printf("...\n");
                break;
            case 5:
                printf("...\n");
                break;
            case 6:
                printf("...\n");
                break;
            case 7:
                printf("Saving to %s and exiting...\n", file);
                free_memory(head);
                return 0;
            case 0:
                printf("Exiting without saving...\n");
                free_memory(head);
                return 0;
            default:
                printf("Invalid option. Try again.\n");
        }
    } while (choice != 7 && choice != 0);

    return 0;
}