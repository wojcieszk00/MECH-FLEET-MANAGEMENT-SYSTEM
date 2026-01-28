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

    printf("Status (Operational, Damaged, Under_Repair, Requires_Inspection): ");
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

//item is head
    if (strcmp(head->model, target_model) == 0) {
        Mech *temp = head;
        head = head->next;
        free(temp);
        printf("Mech '%s' deleted successfully.\n", target_model);
        return head;
    }

//item is in body
    Mech *current = head->next;
    Mech *prev = head;

    while (current != NULL) {
        if (strcmp(current->model, target_model) == 0) {
            prev->next = current->next;
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