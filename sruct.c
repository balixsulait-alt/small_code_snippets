#include <stdio.h>
#include <string.h>

// Structure definition
struct Book {
    char title[50];
    char author[50];
    char subject[100];
    int book_id;
};

int main() {
    struct Book books[5];   // Array to store 3 books

    // -------- Book 1 --------
    strcpy(books[0].title, "C Programming");
    strcpy(books[0].author, "Dennis Ritchie");
    strcpy(books[0].subject, "Programming Language");
    books[0].book_id = 101;

    // -------- Book 2 --------
    strcpy(books[1].title, "Data Structures in C");
    strcpy(books[1].author, "Mark Weiss");
    strcpy(books[1].subject, "Data Structures");
    books[1].book_id = 102;

    // -------- Book 3 --------
    strcpy(books[2].title, "Computer Networks");
    strcpy(books[2].author, "Andrew Tanenbaum");
    strcpy(books[2].subject, "Networking Concepts");
    books[2].book_id = 103;
    
    //book bin
    strcpy(books[4].title, "bin");
    strcpy(books[4].author, "bin");
    strcpy(books[4].subject, "bin");
 	books[4].book_id=234;

    // Display all books
    for (int i = 0; i < 5; i++) {
        printf("\nBOOK %d DETAILS\n", i + 1);
        printf("Title: %s\n", books[i].title);
        printf("Author: %s\n", books[i].author);
        printf("Subject: %s\n", books[i].subject);
        printf("Book ID: %d\n", books[i].book_id);
    }

    return 0;
}

//other structs  tests
/*typedef struct we{
	char nam[23];
	int age;
};

int main(){
	
	struct we first;

//	strcpy(first.nam,"bin");
    scanf("%[^\n]", first.nam);
//	printf("enter age %s" first.nam);
	scanf("%d", &first.age);
	printf("%d", first.age);
	printf("%s", first.nam);

return 0;*/

//BIN SULA SNIPPET

/*typedef struct {
    char title[50];
    char author[50];
    char subject[100];
    int book_id;
} Book;

int main() {
    Book b1;
    Book *wee = &b1;    // pointer to structure

    strcpy(wee->title, "Algorithms");
    strcpy(wee->author, "CLRS");
    strcpy(wee->subject, "Computer Science");
    wee->book_id = 200;

    printf("Title: %s\n", wee->title);
    printf("Author: %s\n", wee->author);
    printf("Subject: %s\n", wee->subject);
    printf("Book ID: %d\n", wee->book_id);

    return 0;
}*/
