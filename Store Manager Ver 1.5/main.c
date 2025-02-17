#include <stdio.h>
#include <stdlib.h>
#include "function.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int main(int argc, char *argv[]) {
	loadCategories();
	int choice;
	while (1) {
    printf("\n============================================\n");
    printf("|      *** Store Management System ***     |\n");
    printf("============================================\n");
    printf("| 1  - Show Category List                  |\n");
    printf("| 2  - Add Category                        |\n");
    printf("| 3  - Edit Category                       |\n");
    printf("| 4  - Delete Category                     |\n");
    printf("| 5  - Find Category By Name               |\n");
    printf("| 6  - Sort Category By Name               |\n");
    printf("| 7  - Product Menu                        |\n");
    printf("| 8  - Exit                                |\n");
    printf("============================================\n");
    printf("Choose your option: ");
	scanf("%d", &choice);
		switch (choice) {
			case 1: 
			system ("cls");
			showCategories();
			returnMenu();
			break;
			case 2:
			system ("cls");
			addCategory();
			returnMenu();
			break;
			case 3:
			system ("cls");
			editCategory();
			returnMenu();
			break;
			case 4:
			system ("cls");
			deleteCategory();
			returnMenu();
			break;
			case 5:
			system ("cls");
			findCategory();
			returnMenu();
			break;
			case 6:
			system ("cls");
			sortCategory();
			returnMenu();
			break;
			case 7:
			system ("cls");
			//productMenu();
			returnMenu();
			case 8:
			system ("cls");
			printf("\nExiting the program...\n");
			return 0;
			default:
			printf("Invalid choice, try again!\n");
			break;
		}
	}
	return 0;
}
