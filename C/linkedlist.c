#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
}node;

void addStart(node *newNode, int n, node **list);
void addEnd(node *newNode, int n, node **list);
void destroy(node *list);
void print(node *list);

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
        addEnd(n, number, &list);
    }

    // prints all elements of a list
    print(list);
    // free the list
    destroy(list);
}

void addStart(node *newNode, int n, node **list)
{
    newNode->number = n;
    newNode->next = *list;

    *list = newNode;
}

void addEnd(node *newNode, int n, node **list)
{
    newNode->number = n;
    newNode->next = NULL;

    if(*list == NULL)
    {
        *list  = newNode;
        return;
    }

    for(node *ptr = *list; ptr != NULL; ptr = ptr->next)
    {
        if(ptr->next == NULL)
        {
            newNode->number = n;
            newNode->next = NULL;

            ptr->next = newNode;
            return;
        }
    }
}

void destroy(node *list)
{
    // free the list
    node *ptr = list;
    while (ptr != NULL)
    {
        node *tmp = ptr->next;
        free(ptr);
        ptr = tmp;
    }
}

void print(node *list)
{
    // print all list elements
    node *ptr = list;
    while (ptr != NULL)
    {
        printf("%i\n",ptr->number);
        ptr = ptr->next;
    }
}
