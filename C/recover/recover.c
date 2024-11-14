#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

#define BLOCK_SIZE 512
#define xFF 255
#define xD8 216
#define xE0 224
#define xEF 239

typedef uint8_t BYTE;

bool is_valid_jpeg_header(BYTE buffer[BLOCK_SIZE]);
FILE* new_file(int filecount);

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Usage: ./recover filename\n");
        return 1;
    }

    char *inputFilename = argv[1];

    // Open input file
    FILE *inputFilePtr = fopen(inputFilename, "r");

    if (inputFilePtr == NULL)
    {
        printf("Could not open %s.\n", inputFilename);
        return 1;
    }

    BYTE buffer[BLOCK_SIZE];
    int fileCount = 0;

    FILE *f = NULL;

    //Cada arquivo gerado deve ser nomeado ###.jpg, onde ###é um número decimal de três dígitos, começando pela 000 primeira imagem e contando.
    while(fread(buffer, sizeof(BYTE), BLOCK_SIZE, inputFilePtr) != 0)
    {
        if(is_valid_jpeg_header(buffer))
        {
            fileCount++;

            if(f == NULL)
            {
                f = new_file(fileCount-1);
                if(f == NULL)
                {
                    fclose(inputFilePtr);
                    return 1;
                }
            }
            else
            {
                fclose(f);

                f = new_file(fileCount-1);
                if(f == NULL)
                {
                    fclose(inputFilePtr);
                    return 1;
                }
            }

            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, f);
        }
        else if(f != NULL)
        {
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, f);
        }
    }

    if(f != NULL)
    {
        fclose(f);
    }

    fclose(inputFilePtr);
}

bool is_valid_jpeg_header(BYTE buffer[BLOCK_SIZE])
{
    return buffer[0] == xFF && buffer[1] == xD8 && buffer[2] == xFF && (buffer[3] >= xE0 || buffer [3] <= 239);
}

FILE* new_file(int filecount)
{
    char fname[10];
    snprintf(fname, sizeof(fname), "%0*d.jpg", 3, filecount);
    FILE *f = fopen(fname, "w");

    return f;
}
