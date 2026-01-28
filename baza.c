#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "baza.h"

void print_menu() {
    printf("\n--- MECH FLEET MANAGEMENT SYSTEM ---\n");
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

void remove_newline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

Mech* add_new_mech(Mech *head) {
    Mech *new_node = (Mech*)malloc(sizeof(Mech));
    if (new_node == NULL) {
        printf("Memory allocation failed!\n");
        return head;
    }

    while (getchar() != '\n');
    
    printf("\n ADDING NEW MECH \n");
    printf("Model name (ID): ");
    fgets(new_node->model, 100, stdin);
    remove_newline(new_node->model);

    printf("Type (Assault, Scout, Defensive, Fire_Support): ");
    fgets(new_node->type, 50, stdin);
    remove_newline(new_node->type);

    printf("Reactor Power (0-100): ");
    if (scanf("%d", &new_node->reactor_power) != 1) {
        new_node->reactor_power = 0;
    }
    while (getchar() != '\n');

    printf("Pilot Nickname: ");
    fgets(new_node->pilot, 100, stdin);
    remove_newline(new_node->pilot);

    printf("Status (Operational, Damaged, Repair, Scrapped, Requires Inspection): ");
    fgets(new_node->status, 50, stdin);
    remove_newline(new_node->status);

    new_node->next = NULL;

    // adding to list
    if (head == NULL) {
        printf("First mech added to the fleet.\n");
        return new_node;
    } else {
        Mech *current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
        printf("Mech added successfully.\n");
        return head;
    }
}

void print_all_mechs(Mech *head) {
    if (head == NULL) {
        printf("\n[Fleet is empty]\n");
        return;
    }

    printf("\n%-20s %-15s %-10s %-20s %-15s\n", "MODEL", "TYPE", "POWER", "PILOT", "STATUS");
    printf("----------------------------------------------------------------------------------\n");
    Mech *current = head;
    while (current != NULL) {
        printf("%-20s %-15s %-10d %-20s %-15s\n",
            current->model, 
            current->type, 
            current->reactor_power, 
            current->pilot, 
            current->status);
        current = current->next;
    }
}

void save_to_file(Mech *head, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Could not open file %s for writing.\n", filename);
        return;
    }

    Mech *current = head;
    while (current != NULL) {
        fprintf(fp, "%s\n", current->model);
        fprintf(fp, "%s\n", current->type);
        fprintf(fp, "%d\n", current->reactor_power);
        fprintf(fp, "%s\n", current->pilot);
        fprintf(fp, "%s\n", current->status);
        current = current->next;
    }

    fclose(fp);
    printf("Database saved to %s\n", filename);
}

Mech* load_from_file(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("No database file found. Starting with empty fleet.\n");
        return NULL;
    }

    Mech *head = NULL;
    Mech *tail = NULL;
    char buffer[100];

    while (1) {
        Mech *new_node = (Mech*)malloc(sizeof(Mech));
        if (fgets(new_node->model, 100, fp) == NULL) {
            free(new_node);
            break;
        }
        remove_newline(new_node->model);

        fgets(new_node->type, 50, fp);
        remove_newline(new_node->type);

        fgets(buffer, 100, fp);
        new_node->reactor_power = atoi(buffer);

        fgets(new_node->pilot, 100, fp);
        remove_newline(new_node->pilot);

        fgets(new_node->status, 50, fp);
        remove_newline(new_node->status);

        new_node->next = NULL;

        if (head == NULL) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }

    fclose(fp);
    printf("Database loaded from %s.\n", filename); 
    return head;
}


Mech* delete_mech(Mech *head) {
    if (head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return NULL;
    }

    char target_model[101];
    while (getchar() != '\n');
    
    printf("Enter Model Name (ID) to delete: ");
    fgets(target_model, 100, stdin);
    remove_newline(target_model);

    Mech *current = head;
    Mech *prev = NULL;

    while (current != NULL) {
        if (strcmp(current->model, target_model) == 0) {

            if (strcmp(current->status, "Repair") != 0 && strcmp(current->status, "Scrapped") != 0) {
                printf("\n  Cannot delete mech '%s'.\n", target_model);
                printf("    Current status: '%s'\n", current->status);
                printf("    Allowed statuses for deletion: 'Repair', 'Scrapped'\n");
                return head;
            }

            if (prev == NULL) {
                head = current->next;
            } else {
                prev->next = current->next;
            }
            
            free(current);
            printf("Mech '%s' deleted successfully.\n", target_model);
            return head;
        }

        prev = current;
        current = current->next;
    }

    printf("Mech '%s' not found.\n", target_model);
    return head;
}


void search_mechs(Mech *head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    int choice;
    printf("\n--- SEARCH OPTIONS ---\n");
    printf("1. Search by Model ID (Prefix)\n");
    printf("2. Search by Minimum Reactor Power\n");
    printf("Select option: ");
    
    if (scanf("%d", &choice) != 1) {
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n'); 

    int found_count = 0;

    if (choice == 1) {
        char query[101];
        printf("Enter Model Name (or start of name): ");
        fgets(query, 100, stdin);
        remove_newline(query);

        printf("\n--- SEARCH RESULTS (Model starts with '%s') ---\n", query);
        printf("%-20s %-15s %-10s %-20s %-15s\n", "MODEL", "TYPE", "POWER", "PILOT", "STATUS");
        printf("----------------------------------------------------------------------------------\n");

        Mech *current = head;
        while (current != NULL) {
            size_t len = strlen(query);
            if (strncmp(current->model, query, len) == 0) {
                printf("%-20s %-15s %-10d %-20s %-15s\n", 
                    current->model, 
                    current->type, 
                    current->reactor_power, 
                    current->pilot, 
                    current->status);
                found_count++;
            }
            current = current->next;
        }

    } else if (choice == 2) {
        int min_power;
        printf("Enter minimum reactor power: ");
        scanf("%d", &min_power);
        while (getchar() != '\n'); 

        printf("\n--- SEARCH RESULTS (Power >= %d) ---\n", min_power);
        printf("%-20s %-15s %-10s %-20s %-15s\n", "MODEL", "TYPE", "POWER", "PILOT", "STATUS");
        printf("----------------------------------------------------------------------------------\n");

        Mech *current = head;
        while (current != NULL) {
            if (current->reactor_power >= min_power) {
                printf("%-20s %-15s %-10d %-20s %-15s\n", 
                    current->model, 
                    current->type, 
                    current->reactor_power, 
                    current->pilot, 
                    current->status);
                found_count++;
            }
            current = current->next;
        }
    } else {
        printf("Invalid search option.\n");
        return;
    }

    if (found_count == 0) {
        printf("[No mechs found]\n");
    }
}

void edit_mech(Mech *head) {
    if (head == NULL) {
        printf("List is empty. Nothing to edit.\n");
        return;
    }

    char target_model[101];
    while (getchar() != '\n');
    
    printf("Enter Model Name (ID) to edit: ");
    fgets(target_model, 100, stdin);
    remove_newline(target_model);

    Mech *current = head;
    while (current != NULL) {
        if (strcmp(current->model, target_model) == 0) {
            printf("\n--- EDITING MECH: %s ---\n", current->model);
            printf("NOTE: Model ID cannot be changed.\n");

            printf("Current Type: %s\n", current->type);
            printf("Enter New Type: ");
            fgets(current->type, 50, stdin);
            remove_newline(current->type);

            printf("Current Power: %d\n", current->reactor_power);
            printf("Enter New Reactor Power (0-100): ");
            if (scanf("%d", &current->reactor_power) != 1) {
                current->reactor_power = 0;
            }
            while (getchar() != '\n');

            printf("Current Pilot: %s\n", current->pilot);
            printf("Enter New Pilot: ");
            fgets(current->pilot, 100, stdin);
            remove_newline(current->pilot);

            printf("Current Status: %s\n", current->status);
            printf("Enter New Status: ");
            fgets(current->status, 50, stdin);
            remove_newline(current->status);

            printf("\nMech updated successfully.\n");
            return;
        }
        current = current->next;
    }

    printf("Mech '%s' not found.\n", target_model);
}