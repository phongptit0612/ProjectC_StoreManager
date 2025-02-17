#include <stdio.h>
#include <string.h>
#include "datatype.h"
#include <conio.h>
#define CATEGORY_FILE "category.bin"
#define MAX_CATEGORIES 30
struct Category categories[MAX_CATEGORIES];  
int categoryCount = 0;
char cateName [20];

//tro lai menu
void returnMenu() {
    printf("\nPress ESC to return to the main menu: \n");
    while (1) {
        if (getch() == 27) { 
            system("cls");
            break; 
        }
    }
}

//Luu dulieu categories
void loadCategories() {
    FILE *fptr = fopen(CATEGORY_FILE, "rb");
    if (fptr == NULL) {
        categoryCount = 0;
        return;
    }

    categoryCount = fread(categories, sizeof(struct Category), MAX_CATEGORIES, fptr);
    fclose(fptr);
}

//Load dulieu categories
void saveCategories() {
    FILE *fptr = fopen(CATEGORY_FILE, "wb");
    if (fptr == NULL) {
        printf("\nCannot open file to save categories!\n");
        return;
    }

    fwrite(categories, sizeof(struct Category), categoryCount, fptr);
    fclose(fptr);
    printf("\nCategories saved successfully!\n");
}

//Hien Thi Cagetory
void showCategories() {
    if (categoryCount == 0) {
        printf("\nNo categories available!\n\n");
        return;
    }
    printf("\n======================================\n");
    printf("| No. |    ID    |   Category Name   |\n");
    printf("======================================\n");

    for (int i = 0; i < categoryCount; i++) {
        printf("| %-3d | %-8s | %-17s |\n", i + 1, categories[i].CategoryId, categories[i].CategoryName);
    }
    printf("======================================\n");
}

//Them Cagetory
void addCategory() {
    if (categoryCount >= MAX_CATEGORIES) {  
        printf("\nCannot add more categories!\n");
        return; 
    }
    char tempId[50], tempName[50];  //su dung temp lon hon (overflow)
    int valid;
    while (getchar() != '\n');  //xia buffer
    do {
        valid = 1;
        printf("\nEnter Category ID (max 10 characters): ");
        fgets(tempId, sizeof(tempId), stdin);
        tempId[strcspn(tempId, "\n")] = 0; //xoa newline.
        if (strlen(tempId) == 0) {
            printf("ID cannot be empty. Try again.\n");
            valid = 0;
        } else if (strlen(tempId) > 10) {
            printf("ID cannot exceed 10 characters!\n");
            valid = 0;
        }
        for (int i = 0; i < categoryCount; i++) {
            if (strcmp(categories[i].CategoryId, tempId) == 0) {
                printf("ID already exists!\n");
                valid = 0;
                break;
            }
        }
    } while (!valid);
    do {
        valid = 1;
        printf("Enter Category Name (max 20 characters): ");
        fgets(tempName, sizeof(tempName), stdin);
        tempName[strcspn(tempName, "\n")] = 0; 
        if (strlen(tempName) == 0) {
            printf("Name cannot be empty!\n");
            valid = 0;
        } else if (strlen(tempName) > 20) {
            printf("Name cannot exceed 20 characters!\n");
            valid = 0;
        }
        for (int i = 0; i < categoryCount; i++) {
            if (strcmp(categories[i].CategoryName, tempName) == 0) {
                printf("! Name already exists!\n");
                valid = 0;
                break;
            }
        }
    } while (!valid);
    strncpy(categories[categoryCount].CategoryId, tempId, sizeof(categories[categoryCount].CategoryId) - 1);
    categories[categoryCount].CategoryId[sizeof(categories[categoryCount].CategoryId) - 1] = '\0'; //xoa null
    strncpy(categories[categoryCount].CategoryName, tempName, sizeof(categories[categoryCount].CategoryName) - 1);
    categories[categoryCount].CategoryName[sizeof(categories[categoryCount].CategoryName) - 1] = '\0'; // xoa null
    categoryCount++;
    printf("\nCategory added successfully!\n");
    saveCategories();
}


//Sua Cagetory
void editCategory() {
    char id[10], newName[50]; 
    int found = 0, valid;
    while (getchar() != '\n');  
    printf("\nEnter category ID to edit: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = 0;  
    for (int i = 0; i < categoryCount; i++) {
        if (strcmp(id, categories[i].CategoryId) == 0) {
            found = 1;
            printf("Current category name: %s\n", categories[i].CategoryName);
            do {
                valid = 1;
                printf("Enter new category name (max 20 characters): ");
                fgets(newName, sizeof(newName), stdin);
                newName[strcspn(newName, "\n")] = 0; 
                if (strlen(newName) == 0) {
                    printf("Name cannot be empty!\n");
                    valid = 0;
                } else if (strlen(newName) > 20) {
                    printf("Name cannot exceed 20 characters!\n");
                    valid = 0;
                }
                for (int j = 0; j < categoryCount; j++) {
                    if (strcmp(categories[j].CategoryName, newName) == 0) {
                        printf("Name already exists!\n");
                        valid = 0;
                        break;
                    }
                }
            } while (!valid);
            strncpy(categories[i].CategoryName, newName, sizeof(categories[i].CategoryName) - 1);
            categories[i].CategoryName[sizeof(categories[i].CategoryName) - 1] = '\0'; 
            printf("\nCategory updated successfully!\n");
            return;
        }
    }
    if (!found) {
        printf("\nInvalid ID or category does not exist!\n");
    }
    saveCategories();
}

//Xoa Cagetory
void deleteCategory() {
    char id[50], confirm;
    int found = 0;
    printf("\nEnter category ID to delete: ");
    scanf("%49s", id); //gioi han 49 kitu (overflow prevent)
    for (int i = 0; i < categoryCount; i++) {
        if (strcmp(id, categories[i].CategoryId) == 0) {
            found = 1;
            printf("\n======================================\n");
            printf("| No. |    ID    |   Category Name   |\n");
            printf("======================================\n");
            printf("| %-3d | %-8s | %-17s |\n", i + 1, categories[i].CategoryId, categories[i].CategoryName);
            printf("======================================\n");
            printf("\nAre you sure you want to delete this category?\n");
            printf("Type 'y' to confirm or 'n' to cancel: ");
            scanf(" %c", &confirm);
            if (confirm == 'y' || confirm == 'Y') {
                for (int j = i; j < categoryCount - 1; j++) {
                    categories[j] = categories[j + 1];
                }
                categoryCount--;
                printf("\nCategory deleted successfully!\n");
            } else {
                printf("\nDeletion canceled.\n");
            }
            return;
        }
    }
    if (!found) {
        printf("\nInvalid ID or category does not exist!\n");
    }
    saveCategories();
}
//strcpy(categories[i].CategoryId, categories[categoryCount - 1].CategoryId); Cach 2 
//strcpy(categories[i].CategoryName, categories[categoryCount - 1].CategoryName);
//CategoryCount--;

//Tim category
void findCategory() {
    int found = 0;  
    printf("\nEnter category name to find: ");
    scanf("%s", cateName);
    printf("\n======================================\n");
    printf("| No. |    ID    |   Category Name   |\n");
    printf("======================================\n");

    for (int i = 0; i < categoryCount; i++) {
        if (strstr(categories[i].CategoryName,cateName)) {  
            printf("| %-3d | %-8s | %-17s |\n", i + 1, categories[i].CategoryId, categories[i].CategoryName);
            found = 1; 
        }
    }
    if (!found) {
        printf("|         Category not found!        |\n");
    }

    printf("======================================\n");
    saveCategories();
}

//Sort Category theo ma Ascii
//strcmp(A, b swap) (a<b sort roi) (a=b ko swap) bubble sort number 1.
void sortCategory() {
    int choice;
    struct Category temp;
    printf("\nSort categories:\n[1] A-Z\n[2] Z-A\nEnter choice: ");
    scanf("%d", &choice);
    for (int i = 0; i < categoryCount - 1; i++) {
        for (int j = i + 1; j < categoryCount; j++) {
            if ((choice == 1 && strcmp(categories[i].CategoryName, categories[j].CategoryName) > 0) ||
                (choice == 2 && strcmp(categories[i].CategoryName, categories[j].CategoryName) < 0)) {
                temp = categories[i];
                categories[i] = categories[j];
                categories[j] = temp;
            }
        }
    }
    printf("\nCategories sorted!\n");
    showCategories();
    saveCategories();
}

//============================================================================================================//

//Show products menu

