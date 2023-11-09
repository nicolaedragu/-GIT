#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char username[30];
    char parola[30];
} Utilizator;

typedef struct
{
    Utilizator *users[100];
} hashtable;

int hash(char *key)
{
    int i, h = 0;
    for (i = 0; i < strlen(key); i++)
        h += key[i];
    return h % 100;
}

void insert(hashtable *hashtable, char *username, char *parola)
{
    Utilizator *user = malloc(sizeof(Utilizator));
    strcpy(user->username, username);
    strcpy(user->parola, parola);
    int h = hash(username);
    hashtable->users[h] = user;
}

Utilizator *search(hashtable *hashtable, char *username)
{
    int h = hash(username);
    return hashtable->users[h];
}

int main()
{
    hashtable hashtable;

    insert(&hashtable, "Maria", "cristiano");
    insert(&hashtable, "Ion", "Neculce");
    insert(&hashtable, "David", "basketmbal");

    char nume[50];
    char parola[50];

    printf("Introdu username: ");
    scanf("%s", nume);

    printf("Introdu parola: ");
    scanf("%s", parola);

    Utilizator *user = search(&hashtable, nume);
    if (user != NULL && strcmp(user->parola, parola) == 0)
        printf("Autentificat!\n");
    else
        printf("Eroare!\n");
    return 0;
}