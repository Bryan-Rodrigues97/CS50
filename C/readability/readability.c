#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

// Function prototypes used inside main
int getLettersCount(string text);
int getSentencesCount(string text);
int getWordsCount(string text);

int main(void)
{
    // Gets the Text input from user
    string text = get_string("Text: ");

    //
    int letters = getLettersCount(text);
    int words = getWordsCount(text);
    int sentences = getSentencesCount(text);

    float l = ((float)letters/words) * 100;
    float s = ((float)sentences/words) * 100;

    // Coleman-Liau index
    // index = 0.0588 * L - 0.296 * S - 15.8
    // L is the average number of letters per 100 words in the text
    // S is the average number of sentences per 100 words in the text.
    int index = (int)round(0.0588 * l - 0.296 * s - 15.8);

    // Prints on the Output what is the Grade level based on the Coleman-Liau index
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n",index);
    }

}

// Returns the number o letters in a text
int getLettersCount(string text)
{
    int letters = 0;

    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
    }

    return letters;
}

// Returns the number of words in a text
int getWordsCount(string text)
{
    int spaces = 0;

    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (text[i] == ' ')
        {
            spaces++;
        }
    }

    return spaces + 1;
}

// Returns the number of senteces in a text
int getSentencesCount(string text)
{
    int sentences = 0;

    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sentences++;
        }
    }

    return sentences;
}
