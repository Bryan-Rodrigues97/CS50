#include <stdio.h>

// prints the string in reverse orer
void strReverse(char *s, int i);

int main(void)
{
    char *name = "Bryan";

    strReverse(name,0);
    printf("\n");
}

void strReverse(char *s, int i)
{
    if(*(s+i) != '\0')
    {
        strReverse(s, i+1);
        
        printf("%c",*(s + i));
    }
}
