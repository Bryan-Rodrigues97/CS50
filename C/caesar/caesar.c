#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// function prototypes used inside main
string cipher(string plain, int key);
bool only_digits(string s);
char rotate(char c, int n);
char get_next_char(char currentChar, int rotation, int limit);

int main(int argc, string argv[])
{
    // check if the command line arguments are valid
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else if(!only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // converts the cli argument to int
    int key = atoi(argv[1]);

    // prompt the user for plaintext input and prints the ciphertext
    string plaintext = get_string("plaintext:  ");
    printf("ciphertext: %s\n",cipher(plaintext, key));
}

// check if all digits of a string are numeric
bool only_digits(string s)
{
    for(int i = 0, len = strlen(s); i < len; i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }

    return true;
}

// function to cipher a sting
string cipher(string plain, int key)
{
    for(int i = 0, len = strlen(plain); i < len; i++)
    {
        plain[i] = rotate(plain[i],key);
    }

    return plain;
}

// find the character based on rotation value
char rotate(char c, int n)
{
    // Function prototypes used inside main
    n -= (n/26) * 26;

    // check if c is a alphabetical letter
    if (isalpha(c))
    {
        // boundary limits for capital letters
        if (c <= 90)
        {
            c = get_next_char(c,n,90);
        }
        // boundary limits for non capital letters
        else
        {
            c = get_next_char(c,n,122);
        }
    }

    return c;
}

char get_next_char(char currentChar, int rotation, int limit)
{
    if ((currentChar + rotation) > limit)
    {
        return currentChar + rotation - 26;
    }

    return currentChar + rotation;
}
