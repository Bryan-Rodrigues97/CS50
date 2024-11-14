#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// function prototypes used in main
string cipher(string plaintext, string cipher);
int find_alpha_idx(char c);
bool has_duplicates(string s);
bool only_alpha(string s);

int main(int argc, string argv[])
{
    // check if the command line arguments are valid
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // check if the cli argument has 26 caracters
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters\n");
        return 1;
    }
    // check if the cli argumnent is alphabetical
    else if (!only_alpha(argv[1]))
    {
        printf("Key must have only letters\n");
        return 1;
    }
    // check if the cli argument has no duplicated letters
    else if (has_duplicates(argv[1]))
    {
        printf("Each letter of key must be unique\n");
        return 1;
    }

    // prompts the user for a plaintext and prints on the screen the ciphertext
    string phrase = get_string("plaintext:  ");
    printf("ciphertext: %s\n",cipher(phrase, argv[1]));
}

// A function to check if all characters of a string are alphabetical
bool only_alpha(string s)
{
    for (int i = 0, len = strlen(s) ; i < len; i++)
    {
        if (!isalpha(s[i]))
        {
            return false;
        }
    }

    return true;
}

// A function to check if all characters of a string are unique
bool has_duplicates(string s)
{
    char checkKeyArr[26] = {0};

    for (int i = 0, len = strlen(s); i < len; i++)
    {
        if (i != 0)
        {
            for (int j=0; j <= i; j++)
            {
                if (toupper(checkKeyArr[j]) == toupper(s[i]))
                {
                    return true;
                }
            }
        }

        checkKeyArr[i] = toupper(s[i]);
    }

    return false;
}

// a function thar receives a plaintext and returns the ciphertext
string cipher(string plaintext, string cipher)
{
    for (int i=0, len = strlen(plaintext); i < len; i++)
    {
        if (isalpha(plaintext[i]))
        {
            int idx = find_alpha_idx(plaintext[i]);

            if(idx >= 0)
            {
                plaintext[i] = plaintext[i] <= 90 ? toupper(cipher[idx]) : tolower(cipher[idx]);
            }
        }
    }

    return plaintext;
}

// a function that finds the index of a char in alphabetical order
int find_alpha_idx(char c)
{
    string alpha  = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    c = toupper(c);

    for (int i=0, len = strlen(alpha); i < len; i++)
    {
        if(alpha[i] == c)
        {
            return i;
        }
    }

    return -1;
}
