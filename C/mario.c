#include <stdio.h>
#include <cs50.h>

void printBlock(int l, int c);

int main(void)
{
    int l = get_int("lines: ");
    int c = get_int("columns: ");

    printBlock(l,c);
}

void printBlock(int l, int c)
{
    for(int i=0;i<l;i++){
        for(int j=0;j<c;j++){
            printf("#");
        }
        printf("\n");
    }
}
