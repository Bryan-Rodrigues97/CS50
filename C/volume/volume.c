// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;
typedef int16_t BYTE2;

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

void copyHeader(FILE *input, FILE *output);
void copySamples(FILE *input, FILE *output, float factor);

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "rb");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "wb");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // The first function will copie the header file
    // The second one will copie each sample
    copyHeader(input, output);
    copySamples(input, output, factor);

    // Close files
    fclose(input);
    fclose(output);
}

void copyHeader(FILE *input, FILE *output)
{
    BYTE buffer[HEADER_SIZE];

    fread(buffer, sizeof(BYTE), HEADER_SIZE, input);
    fwrite(buffer, sizeof(BYTE), HEADER_SIZE, output);
}

void copySamples(FILE *input, FILE *output, float factor)
{
    BYTE2 sample;

    while (fread(&sample, sizeof(BYTE2), 1, input) != 0)
    {
        sample *= factor;
        fwrite(&sample, sizeof(BYTE2), 1, output);
    }
}
