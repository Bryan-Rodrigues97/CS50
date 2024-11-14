#include <stdio.h>
#include <cs50.h>

void renderLineWithGap(int length, int spaces);
void renderLine(int length, int spaces, bool ltr);

int main(void)
{
    int height;

    do
    {
        height = get_int("Height: ");
    }while(height<1 || height>8);

    for(int i=0;i<height;i++){
        renderLineWithGap(height,height-1-i);
    }
}

void renderLineWithGap(int length, int spaces)
{
    renderLine(length,spaces,true);
    printf("  ");
    renderLine(length,spaces,false);
    printf("\n");
}

//Prints a line with the char'#'.
void renderLine(int length, int spaces, bool ltr)
{
    for (int i = 0; i < length; i++)
    {
        if(ltr)
        {
            printf("%c", i<spaces ? ' ' : '#');
        }
        else
        {
            if(i<(length-spaces))
            {
                printf("#");
            }
            else
            {
                break;
            }
        }
    }
}
