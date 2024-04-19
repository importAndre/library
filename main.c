#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

// Structs
struct Book
{
    int id;
    char title[100];
    char author[100];
    char subject[100];
    int stock;
    int available;
};

struct Client
{
    int id;
    char name[100];
    int BookRentedId;
};


int menu()
{
    int choice;
    printf("Select action:\n");
    printf("1. See all books\n");
    printf("2. Add a book\n");
    printf("3. Search for a book\n");
    printf("5. Remove book\n");
    scanf("%d", &choice);

    if (choice <= 5)
    {
        return choice;
    } 
    else 
    {
        printf("Invalid choice\n");
        return 0;
    }

}

void createFile(char *fileName)
{
    FILE *file = fopen(fileName, "w");
    if (fileName == "books.csv")
    {
        fprintf(file, "id,title,author,subject,stock,available\n");
    } 
    else if (fileName == "clients.csv")
    {
        fprintf(file, "id,name,BookRentedId\n");
    }
    fclose(file);
}

int idGenerator(FILE *file);

FILE* seeAllBooks(char *fileName)
{
    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
        printf("File not found\n");
        return NULL;
    }

    int listSize = idGenerator(file) - 1;

    char line[255];
    fgets(line, sizeof(line), file);

    printf("Books list:\n");
    for (int i = 0; i < listSize; i++)
    {
        fgets(line, sizeof(line), file);
        printf("%s", line);
    }

    rewind(file);
    fclose(file);
}

void fileChecker(FILE *file, char fileName[])
{
    if (file == NULL)
    {
        createFile(fileName);
    }
}

int idGenerator(FILE *file)
{
    int id = 1;
    char line[255];
    rewind(file);
    
    while (fgets(line, sizeof(line), file))
    {
        id++;
    }
    rewind(file);
    return id;
}

void registerBook()
{
    FILE *file = fopen("books.csv", "r");
    struct Book book;
    book.id = idGenerator(file);
    printf("Enter book title: ");
    scanf("%s", book.title);
    printf("Enter book author: ");
    scanf("%s", book.author);
    printf("Enter book subject: ");
    scanf("%s", book.subject);
    printf("Enter book stock: ");
    scanf("%d", &book.stock);
    printf("Enter book available: ");
    scanf("%d", &book.available);

    FILE *updateFile = fopen("books.csv", "a");
    fprintf(updateFile, "%d,%s,%s,%s,%d,%d\n", book.id, book.title, book.author, book.subject, book.stock, book.available);
};

void searchBook()
{
    FILE *file = fopen("books.csv", "r");
    if (file == NULL)
    {
        printf("File not found\n");
        return;
    }

    int id;
    printf("Enter book id: ");
    scanf("%d", &id);

    char line[255];
    char copy[255];
    int found = 0;

    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file))
    {
        strcpy(copy, line);
        line[strcspn(line, "\n")] = 0;

        char *token = strtok(line, ",");
        int currentId = atoi(token);

        if (currentId == id) {
            printf("Book found: %s\n", copy);
            found = 1;
            return;
        }

    }
    if (!found) {
        printf("Book not found with id %d\n", id);
    }
    fclose(file);
}


int main()
{
    int choice;
    choice = menu();

    char *booksFileName = "books.csv";
    char *clientsFileName = "clients.csv";

    FILE *booksFile = fopen(booksFileName, "r");
    FILE *clientsFile = fopen(clientsFileName, "r");

    fileChecker(booksFile, booksFileName);
    fileChecker(clientsFile, clientsFileName);

    if (choice == 1)
    {
        FILE* infos = seeAllBooks(booksFileName);
    } else if (choice == 2)
    {
        registerBook();
    } else if (choice == 3)
    {
        searchBook();
    }

    return 0;
}