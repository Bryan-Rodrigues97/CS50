#include <cs50.h>
#include <stdio.h>

void renderLeftPyramid(int height);

int main(void)
{
    int pyramidHeight = get_int("Pyramid height: ");

    renderLeftPyramid(pyramidHeight);
}

//A function thats render a left Pyramid based on input parameter
void renderLeftPyramid(int height)
{
    if(height<1){
        printf("You must specify a valid height.\n");
    }
    else
    {
        for(int i=0;i<height;i++){
            for(int j=0;j<=i;j++){
                printf("#");
            }
            printf("\n");
        }
    }
}
