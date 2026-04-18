#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct book {
    int id;
    char name[50];
    char author[50];
    int quantity;
    char image[100];
};

void removeNewline(char *str) {
    str[strcspn(str, "\n")] = 0;
}

void addBook() {
    struct book b;
    FILE *fp = fopen("library.txt", "ab");

    if (fp == NULL) {
        printf("File error!\n");
        return;
    }

    printf("Enter Book ID: ");
    scanf("%d", &b.id);
    getchar();

    printf("Enter Book Name: ");
    fgets(b.name, sizeof(b.name), stdin);
    removeNewline(b.name);

    printf("Enter Author Name: ");
    fgets(b.author, sizeof(b.author), stdin);
    removeNewline(b.author);

    printf("Enter Quantity: ");
    scanf("%d", &b.quantity);
    getchar();

    printf("Enter Image Path: ");
    fgets(b.image, sizeof(b.image), stdin);
    removeNewline(b.image);

    fwrite(&b, sizeof(b), 1, fp);

    fclose(fp);

    printf("\nBook Added Successfully!\n");
}

void displayBooks() {
    struct book b;
    FILE *fp = fopen("library.txt", "rb");

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\nID\tName\tAuthor\tQty\tImage\n");
    printf("--------------------------------------------------\n");

    while (fread(&b, sizeof(b), 1, fp)) {
        printf("%d\t%s\t%s\t%d\t%s\n",
               b.id, b.name, b.author, b.quantity, b.image);
    }

    fclose(fp);
}

void searchBook() {
    struct book b;
    FILE *fp = fopen("library.txt", "rb");
    int id, found = 0;

    if (fp == NULL) {
        printf("File not found!\n");
        return;
    }

    printf("Enter Book ID to search: ");
    scanf("%d", &id);

    while (fread(&b, sizeof(b), 1, fp)) {
        if (b.id == id) {
            printf("\nBook Found!\n");
            printf("Name: %s\n", b.name);
            printf("Author: %s\n", b.author);
            printf("Quantity: %d\n", b.quantity);
            printf("Image: %s\n", b.image);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Book not found!\n");

    fclose(fp);
}

void deleteBook() {
    struct book b;
    FILE *fp = fopen("library.txt", "rb");
    FILE *temp = fopen("temp.txt", "wb");
    int id, found = 0;

    if (fp == NULL) {
        printf("File not found!\n");
        return;
    }

    printf("Enter Book ID to delete: ");
    scanf("%d", &id);

    while (fread(&b, sizeof(b), 1, fp)) {
        if (b.id == id) {
            found = 1;
            printf("Book Deleted!\n");
        } else {
            fwrite(&b, sizeof(b), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("library.txt");
    rename("temp.txt", "library.txt");

    if (!found)
        printf("Book not found!\n");
}

void updateBook() {
    struct book b;
    FILE *fp = fopen("library.txt", "rb+");
    int id, found = 0;

    if (fp == NULL) {
        printf("File not found!\n");
        return;
    }

    printf("Enter Book ID to update: ");
    scanf("%d", &id);
    getchar();

    while (fread(&b, sizeof(b), 1, fp)) {
        if (b.id == id) {

            printf("\nEnter New Info:\n");

            printf("New Name: ");
            fgets(b.name, sizeof(b.name), stdin);
            removeNewline(b.name);

            printf("New Author: ");
            fgets(b.author, sizeof(b.author), stdin);
            removeNewline(b.author);

            printf("New Quantity: ");
            scanf("%d", &b.quantity);
            getchar();

            printf("New Image Path: ");
            fgets(b.image, sizeof(b.image), stdin);
            removeNewline(b.image);

            fseek(fp, -sizeof(b), SEEK_CUR);
            fwrite(&b, sizeof(b), 1, fp);

            printf("Book Updated!\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Book not found!\n");

    fclose(fp);
}

int main() {
    int choice;

    while (1) {
        printf("\n===== Library Management System =====\n");
        printf("1. Add Book\n");
        printf("2. Display Books\n");
        printf("3. Search Book\n");
        printf("4. Delete Book\n");
        printf("5. Update Book\n");
        printf("6. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            case 4: deleteBook(); break;
            case 5: updateBook(); break;
            case 6: exit(0);
            default: printf("Invalid choice!\n");
        }
    }

    return 0;
}
