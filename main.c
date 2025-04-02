// main.c
#include "header.h"

static time_t current_time(void)
{
    return time(NULL);
}

static char *format_time(time_t t)
{
    static char buffer[26];
    struct tm *tm_info = localtime(&t);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm_info);
    return buffer;
}

void init_db(Database *db)
{
    printf("Initializing database...\n");
    // Initialize users
    db->users.capacity = 5;
    db->users.count = 0;
    db->users.last_id = 0;
    db->users.items = (User *)malloc(db->users.capacity * sizeof(User));
    if (!db->users.items)
        exit(EXIT_FAILURE);

    // Initialize books
    db->books.capacity = 10;
    db->books.count = 0;
    db->books.last_id = 0;
    db->books.items = (Book *)malloc(db->books.capacity * sizeof(Book));
    if (!db->books.items)
        exit(EXIT_FAILURE);

    // Initialize loans
    db->loans.capacity = 5;
    db->loans.count = 0;
    db->loans.last_id = 0;
    db->loans.items = (Loan *)malloc(db->loans.capacity * sizeof(Loan));
    if (!db->loans.items)
        exit(EXIT_FAILURE);
}

void cleanup_db(Database *db)
{
    for (int i = 0; i < db->users.count; i++)
    {
        free(db->users.items[i].username);
    }
    free(db->users.items);

    for (int i = 0; i < db->books.count; i++)
    {
        free(db->books.items[i].title);
    }
    free(db->books.items);
    free(db->loans.items);
}

User *create_user(UserTable *user_table, const char *username)
{
    if (user_table->count >= user_table->capacity)
    {
        user_table->capacity *= 2;
        User *new_users = (User *)realloc(user_table->items, user_table->capacity * sizeof(User));
        if (!new_users)
            return NULL;
        user_table->items = new_users;
    }

    User *user = &user_table->items[user_table->count];
    user->id = ++user_table->last_id;
    user->username = strdup(username);
    user->is_author = 0;
    user->is_logged_in = 0;
    user->created_at = current_time();
    user->updated_at = user->created_at;
    user_table->count++;
    return user;
}

User *find_user_by_id(const UserTable *user_table, int id)
{
    for (int i = 0; i < user_table->count; i++)
    {
        if (user_table->items[i].id == id)
        {
            return &user_table->items[i];
        }
    }
    return NULL;
}

void print_user(const User *user)
{
    printf("\n\n");
    printf("ID: %d\n", user->id);
    printf("Username: %s\n", user->username);
    printf("Created: %s\n", format_time(user->created_at));
}

void print_all_users(const UserTable *user_table)
{
    for (int i = 0; i < user_table->count; i++)
    {
        print_user(&user_table->items[i]);
    }
}

int main(void)
{
    Database db;
    init_db(&db);

    create_user(&db.users, "Abanda");
    create_user(&db.users, "Okale");
    print_all_users(&db.users);
    cleanup_db(&db);
    return 0;
}