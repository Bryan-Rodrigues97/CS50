#include <stdio.h>
#include <cs50.h>

void renderLine(int lenght, int spaces);

int main(void)
{
    int height;

    do
    {
        height = get_int("Height: ");
    }while(height<1);

    for(int i=0;i<height;i++){
        renderLine(height,height-1-i);
        printf("\n");
    }
}

void renderLine(int length, int spaces)
{
    for (int i = 0; i < length; i++)
    {
        printf("%c", i<spaces ? ' ' : '#');
    }
}
