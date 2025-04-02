#ifndef BOOK_H
#define BOOK_H

#include<time.h>

enum SupportedFormats{
    PDF,
};

struct Book
{
    int id;
    char*title;
    char* author;
    char*path;
    time_t date_added;
    bool is_read;
   int rating;
   char * pov;
   SupportedFormats type;
};


struct BookList
{
    Book* Books;
    int count;
};

Book* addBook(BookList*,char*title,char*author,char *path);
void listBooks(BookList*);
bool deleteBook(BookList*,int id);
Book* changeBookTitle(Book*, char*title);
void markAsRead(Book*,bool is_read);
void rateBook(Book*,int rating);
void addBookPov(Book*,char *);

#endif