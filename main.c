#include <stdio.h>
#include <stdlib.h>
#include "baza.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("No database file provided.\n");
        printf("Usage: %s <filename.txt>\n", argv[0]);
        return 1;
    }

    char *file = argv[1];
    
    Mech *head = load_from_file(file);

    int choice;

    do {
        print_menu();
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            choice = -1;
        }

        switch (choice) {
            case 1:
                print_all_mechs(head);
                break;
            case 2:
                head = add_new_mech(head);
                break;
            case 3:
                printf("...\n");
                break;
            case 4:
                head = delete_mech(head);
                break;
            case 5:
                search_mechs(head);
                break;
            case 6:
                printf("...\n");
                break;
            case 7:
                save_to_file(head, file);
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