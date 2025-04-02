// header.h
#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct
{
    int id;
    char *username;
    int is_author;
    int is_logged_in;
    time_t created_at;
    time_t updated_at;
} User;

typedef struct
{
    int id;
    int ownerId;
    int isbn;
    char *title;
    int number_available;
    time_t created_at;
    time_t updated_at;
} Book;

typedef struct
{
    int id;
    int user_id;
    int book_id;
    time_t due_date;
    time_t date_loaned;
} Loan;

typedef struct
{
    User *items;
    int count;
    int capacity;
    int last_id;
} UserTable;

typedef struct
{
    Book *items;
    int count;
    int capacity;
    int last_id;
} BookTable;

typedef struct
{
    Loan *items;
    int count;
    int capacity;
    int last_id;
} LoanTable;

typedef struct
{
    BookTable books;
    UserTable users;
    LoanTable loans;
} Database;

// Function prototypes
static time_t current_time(void);
static char *format_time(time_t t);
void init_db(Database *db);
void cleanup_db(Database *db);
User *create_user(UserTable *, const char *username);
User *find_user_by_id(const UserTable *, int id);
void print_user(const User *user);
void print_all_users(const UserTable *);

#endif // HEADER_H