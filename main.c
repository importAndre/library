#include <stdio.h>
#include <sys/stat.h>

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

FILE* getFileInfos(char *fileName)
{
    FILE *file = fopen(fileName, "r");
    int listSize = (idGenerator(file) - 1);

    int list[listSize];
    
    char line[255];

    for (int i = 0; i < listSize; i++)
    {
        fgets(line, 255, file);
        printf("%s", line);
    }

    return file;
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
    int id = 0;
    char line[255];
    while (fgets(line, 255, file))
    {
        id++;
    }
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
        FILE* infos = getFileInfos(booksFileName);
    } else if (choice == 2)
    {
        registerBook();
    }

    return 0;
}