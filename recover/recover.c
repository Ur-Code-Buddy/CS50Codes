#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Invalid name\n");
        return 1;
    }

    BYTE buffer[512];
    int images = 0;

    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL)
    {
        printf("file didnt open\n");
        fclose(input_file);
        return 1;
    }

    FILE *output = NULL;
    char *filename = malloc(8 * sizeof(char));

    while (fread(buffer, sizeof(BYTE), 512, input_file))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (images > 0)
            {
                fclose(output);
            }
            sprintf(filename, "%03i.jpg", images);
            output = fopen(filename, "w");
            images++;
        }
        if (output != NULL)
        {
            fwrite(buffer, sizeof(char), 512, output);
        }
    }

    free(filename);
    fclose(output);
    fclose(input_file);
    return 0;
}
