#include <stdio.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("Usage: cp origin destination\n");
        return 1;
    }

    // rb = read byte
    // wb = write byte
    FILE *src = fopen(argv[1], "rb");
    FILE *dst = fopen(argv[2], "wb");

    if(src == NULL || dst == NULL)
    {
        return 2;
    }

    BYTE b;

    // copia byte a byte o conteudo do arquivo de origem
    while (fread(&b, sizeof(b), 1, src) != 0)
    {
        fwrite(&b, sizeof(b), 1, dst);
    }

    fclose(dst);
    fclose(src);
}
