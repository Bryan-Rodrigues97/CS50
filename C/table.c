#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string.h>

#define TABLE_SIZE 27

typedef struct node
{
    string phrase;
    struct node *next;
}
node;

// [0...25 = A...Z]
// [26 = non alphabetical chars]
node *table[TABLE_SIZE];

int hash(string phrase);
bool add(string phrase, int index);
void initialize();
void finalizeDictionary();
void destroy(node *list);
bool find(string phrase);
bool findNode(node *list, string phrase);

int main(void)
{
    // sets all table indexes to NULL
    initialize();

    // Add items
    for (int i = 0; i < 3; i++)
    {
        string phrase = get_string("Enter a new phrase: ");

        // Find phrase bucket
        int bucket = hash(phrase);
        printf("%s hashes to %i\n", phrase, bucket);

        if(add(phrase, bucket) == false)
        {
            finalizeDictionary();
            return 1;
        }
    }

    if(find("bryan"))
    {
        printf("Yes, bryan is in the dictionary!\n");
    }

    finalizeDictionary();
}

void finalizeDictionary()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        node *list = table[i];

        if(list != NULL)
        {
            destroy(table[i]);
            table[i] = NULL;
        }
    }
}

bool find(string phrase)
{
    int idx = hash(phrase);

    return findNode(table[idx], phrase);
}

bool findNode(node *list, string phrase)
{
    if(list == NULL)
    {
        return false;
    }

    if (strcmp(list->phrase, phrase))
    {
        return true;
    }

    return findNode(list->next, phrase);
}

void destroy(node *list)
{
    if(list == NULL)
    {
        return;
    }

    if(list->next != NULL)
    {
        destroy(list->next);
    }

    free(list);
}

void initialize()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        table[i] = NULL;
    }
}

bool add(string phrase, int index)
{
    node *newNode = malloc(sizeof(node));
    if (newNode == NULL)
    {
        return false;
    }

    newNode->phrase = phrase;
    newNode->next = table[index];
    table[index] = newNode;

    return true;
}

int hash(string phrase)
{
    if(isalpha(phrase[0]))
    {
        return toupper((phrase[0])) - 'A';
    }
    else
    {
        return 26;
    }
}
