#include <stdio.h>
#include <string.h>

int main(void)
{
    char *hello = "hello, world";


    printf("A string is an Char Array. Consider the char pointer named hello\n");
    printf("The length of (%s) is %lu\n", hello, strlen(hello));
    printf("The adress in memory is %p\n", hello);
    printf("Wich is the same address of hello[0]. %p\n", &hello[0]);
}
