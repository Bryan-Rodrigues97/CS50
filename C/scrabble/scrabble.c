#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

//Function prototypes used inside main
int gelLetterIdx(char letters[], char charToFind);
string getUserInput(string label);
int getWordScrabblePoints(string word);
string strUpr(string str);

int main (void)
{
    // The players input words
    string player1word = getUserInput("Player 1: ");
    string player2word = getUserInput("Player 2: ");

    // The point value of each word
    int player1points = getWordScrabblePoints(player1word);
    int player2points = getWordScrabblePoints(player2word);

    // Comparison between the word`s point value
    if(player1points > player2points)
    {
        printf("Player 1 wins!\n");
    }
    else if(player2points > player1points)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

// A function that returns the number of points for an input word
int getWordScrabblePoints(string word)
{
    char scrabbleLetters[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    int  scrabllePoints[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

    int points = 0;

    for(int i = 0, len = strlen(word) ; i < len ; i++)
    {
        int letterIdx = gelLetterIdx(scrabbleLetters, word[i]);

        if(letterIdx >= 0)
        {
            points += scrabllePoints[letterIdx];
        }
    }

    return points;
}

// Finds the index of a letter in an array. If the letter is not found, returns -1.
int gelLetterIdx(char letters[], char charToFind)
{
    int index = -1;

    for(int i = 0, len = strlen(letters) ; i < len ; i++)
    {
        if(letters[i] == charToFind)
        {
            index = i;
            break;
        }
    }

    return index;
}

// A function that prompt the user for a string input
string getUserInput(string label)
{
    string userInput = "";

    do
    {
        userInput = get_string("%s",label);
    }
    while(strlen(userInput)==0);

    return strUpr(userInput);
}

// A function that converts a string to upperCase
string strUpr(string str)
{
    for(int i = 0, len = strlen(str) ; i < len ; i++)
    {
        str[i] = toupper(str[i]);
    }

    return str;
}
