#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

typedef struct node
{
    int number;
    struct node *next;
}node;

void add(node *newNode, int n, node **list);
void destroy(node *list);
void print(node *list);
bool find(node *listNode, int n);

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("Usage: ./linkedlist [1,2,3,...]\n");
        return 1;
    }

    node *list = NULL;

    for(int i = 1; i < argc; i++)
    {
        int number = atoi(argv[i]);

        node *n = malloc(sizeof(node));
        if(n == NULL)
        {
            destroy(list);
            return 1;
        }
        add(n, number, &list);
    }

    // prints all elements of a list
    print(list);

    // check if the number 50 is in the list
    bool is50inList = find(list, 50);
    printf("Is the element 50 in the list ? %s\n", is50inList ? "Yes" : "No");

    // free the list
    destroy(list);
}

void add(node *newNode, int n, node **list)
{
    newNode->number = n;
    newNode->next = NULL;

    // Se a lista estiver vazia ou se o novo nó deve ser o primeiro da lista
    if(*list == NULL || (*list)->number > n)
    {
        newNode->next = *list;
        *list = newNode;
        return;
    }

    // Caso contrário, procura o nó que contém um valor maior que n
    for(node *ptr = *list; ptr != NULL; ptr = ptr->next)
    {
        if(ptr->next == NULL)
        {
            ptr->next = newNode;
            return;
        }

        if(ptr->next->number > newNode->number)
        {
            newNode->next = ptr->next;
            ptr->next = newNode;
            return;
        }
    }
}

void destroy(node *list)
{
    // free the list
    //node *ptr = list;
    //while (ptr != NULL)
    //{
        //node *tmp = ptr->next;
        //free(ptr);
        //ptr = tmp;
    //}
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

void print(node *list)
{
    // print all list elements
    //node *ptr = list;
    //while (ptr != NULL)
    //{
        //printf("%i\n",ptr->number);
        //ptr = ptr->next;
    //}
    if(list == NULL)
    {
        return;
    }

    printf("%i\n", list->number);
    print(list->next);
}

bool find(node *listNode, int n)
{
    if(listNode == NULL)
    {
        return false;
    }

    if(listNode->number != n)
    {
        return find(listNode->next, n);
    }

    return true;
}
