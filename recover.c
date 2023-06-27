#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{

    if (argc < 2 || argc > 2)
    {
        // If provided arguments are more or less than 2
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open the provided file and save in variable
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        // If file is emppty return
        return 2;
    }

    // Create counter so that you can name every image increasing
    int counter = 0;
    // Create a buffer where we can store the found jpeg bytes
    BYTE bytes[512];
    // Create a filename big enough to store the jpeg filenames
    char filename[8];
    // Create a empty file pointer where we can store the output data from input
    FILE *filejpeg = NULL;
    // Read the input file aslong as not empty and store it in bytes
    while (fread(bytes, 1, 512, file) != 0)
    {
        // Look for the first standard bytes of the jpeg file
        if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] & 0xf0) == 0xe0)
        {
            if (filejpeg != NULL)
            {
                fclose(filejpeg);
            }
            // Create filename with three digits and update counter and store the found jpeg
            sprintf(filename, "%03i.jpg", counter++);
            // Use the created filename from above to write in the file
            filejpeg = fopen(filename, "w");
        }
        // Write aslong as the temporarily file is not empty
        if (filejpeg != NULL)
        {
            fwrite(bytes, 1, 512, filejpeg);
        }
    }
    if (filejpeg != NULL)
    {
        fclose(filejpeg);
    }
    fclose(file);
    return 0;
}