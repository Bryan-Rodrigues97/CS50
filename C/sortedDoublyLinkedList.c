#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

typedef struct node
{
    int number;
    struct node *next;
    struct node *prev;
}node;

void add(node *newNode, int n, node **list);
void destroy(node *list);
void print(node *list);
bool find(node *listNode, int n);
void deleteNode(node **list, int n);

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
    bool is50inList = find(list, 2);
    printf("Is the element 2 in the list ? %s\n", is50inList ? "Yes" : "No");

    // removing list elements
    deleteNode(&list, 0);
    deleteNode(&list, 5);
    deleteNode(&list, 2);

    // free the list
    destroy(list);
}

void add(node *newNode, int n, node **list)
{
    newNode->number = n;
    newNode->next = NULL;
    newNode->prev = NULL;

    // Se a lista estiver vazia ou se o novo nó deve ser o primeiro da lista
    if(*list == NULL)
    {
        *list = newNode;
        return;
    }

    if((*list)->number > n)
    {
        newNode->next = *list;
        (*list)->prev = newNode;
        *list = newNode;

        return;
    }

    // Caso contrário, procura o nó que contém um valor maior que n
    for(node *ptr = *list; ptr != NULL; ptr = ptr->next)
    {
        if(ptr->next == NULL)
        {
            ptr->next = newNode;
            newNode->prev = ptr;

            return;
        }

        if(ptr->next->number > newNode->number)
        {
            ptr->next->prev = newNode;
            newNode->next = ptr->next;
            newNode->prev = ptr;
            ptr->next = newNode;

            return;
        }
    }
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

void print(node *list)
{
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

void deleteNode(node **list, int n)
{
    for (node *ptr = *list; ptr != NULL; ptr = ptr->next)
    {
        if(ptr->number == n)
        {
            // first element of the list
            if(ptr->prev == NULL && ptr->next != NULL)
            {
                ptr->next->prev = NULL;
                *list = ptr->next;
            }
            // last element of the list
            else if(ptr->next == NULL && ptr->prev != NULL)
            {
                ptr->prev->next = NULL;
            }
            // middle element
            else if(ptr->prev != NULL && ptr->next != NULL)
            {
                ptr->prev->next = ptr->next;
                ptr->next->prev = ptr->prev;
            }
            // single node list
            else
            {
                *list = NULL;
            }

            free(ptr);
            return;
        }
    }
}
