// Implements a dictionary's functionality

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#include "dictionary.h"


// Number of buckets in hash table
const unsigned int N = 200;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    const int hashNumber = hash(word);
    char lowerWord[LENGTH + 1];
    int i;

    for(i = 0; word[i] != '\0'; i++)
    {
        lowerWord[i] = tolower(word[i]);
    }

    lowerWord[i] = '\0';

    node *list = table[hashNumber];

    while (list != NULL)
    {
        if(strcmp(list->word, lowerWord) == 0)
        {
            return true;
        }

        list = list->next;
    }


    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // ASCII Weighted Sum Hash
    int asciiSum = 0;

    for(int i = 0; word[i] != '\0'; i++)
    {
       asciiSum += toupper(word[i]) * (i+1);
    }

    return asciiSum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *f = fopen(dictionary, "r");
    if(f == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];

    while(fscanf(f,"%s",word) != EOF)
    {
        const int hashNumber = hash(word);

        node *n = malloc(sizeof(node));
        int i;

        for(i = 0; word[i] != '\0'; i++)
        {
            n->word[i] = word[i];
        }

        n->word[i] = '\0';
        n->next = NULL;

        if(table[hashNumber] == NULL)
        {
            table[hashNumber] = n;
        }
        else
        {
            n->next = table[hashNumber];
            table[hashNumber] = n;
        }
    }

    fclose(f);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    int total_words = 0;

    for (int i = 0; i < N; i++)
    {
        node *list = table[i];
        total_words += linkedListLen(list);
    }

    return total_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *list = table[i];

        while (list != NULL)
        {
            node *tmp = list->next;
            free(list);
            list = tmp;
        }
    }

    return true;
}

void destroyNode(node *n)
{
    if(n == NULL)
    {
        return;
    }

    destroyNode(n->next);
    free(n);
}

int linkedListLen(node * n)
{
    if(n == NULL)
    {
        return 0;
    }

    return 1 + linkedListLen(n->next);
}
