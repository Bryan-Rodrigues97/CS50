// Check if a file is a PDF
// pdf file always start with this four-bytes sequence
// 37, 80, 68, 70

#include <stdio.h>
#include <stdint.h>
#include <cs50.h>
#include <string.h>

#define PDF_CHECK_LENGTH 4

typedef uint8_t BYTE;
const BYTE pdfBytes[] = {37,80,68,70};

bool isPdf(FILE *f);

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Usage: ./pdf filename\n");
        return 1;
    }

    char *filename = argv[1];
    FILE *f = fopen(filename, "r");

    if (f == NULL)
    {
        return 2;
    }

    if (isPdf(f))
    {
        printf("The file \"%s\" is a valid PDF.\n", filename);
    }
    else
    {
        printf("The file \"%s\" is not a PDF.\n", filename);
    }

    fclose(f);
}

bool isPdf(FILE *f)
{
    BYTE buffer[PDF_CHECK_LENGTH];

    size_t size = fread(buffer, sizeof(BYTE), PDF_CHECK_LENGTH, f);

    if (size != PDF_CHECK_LENGTH)
    {
        return false;
    }

    for (int i = 0; i < PDF_CHECK_LENGTH; i++)
    {
        if (buffer[i] != pdfBytes[i])
        {
            return false;
        }
    }

    return true;
}
