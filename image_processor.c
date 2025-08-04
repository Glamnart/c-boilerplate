#include "include/input_utils.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BITMAPFILEHEADER_size 14 // BITMAPFILEHEADER is always 14 bytes

typedef struct
{
    uint8_t B;
    uint8_t G;
    uint8_t R;
} colour; // new struct for colours

int main(void)
{
    FILE *initial_photo = fopen("picture.bmp", "rb"); // Opening the picture
    FILE *final_photo = fopen("pic.bmp", "wb");

    if (initial_photo == NULL || final_photo == NULL) // Checking for success while opening
    {
        printf("Error opening picture.bmp\n");
        return 1;
    }

    uint8_t BITMAPFILEHEADER[BITMAPFILEHEADER_size]; // Initialising space for the first header
    uint8_t BIHsize[sizeof(int)]; // Initialising space for the first info from second header

    if (fread(BITMAPFILEHEADER, BITMAPFILEHEADER_size, 1, initial_photo) !=
        1) // Checking success in reading
    {
        printf("Error with file\n");
        return 1;
    }
    fwrite(BITMAPFILEHEADER, BITMAPFILEHEADER_size, 1, final_photo); // Writing the header in the new file
    
    char type[3] = {BITMAPFILEHEADER[0], BITMAPFILEHEADER[1], '\0'}; // Saving the first values of the header in a variable
    if (strcmp(type, "BM") != 0) // Making sure it's a BMP file.
    {
        printf("This is not a BMP file\n");
        return 1;
    }

    int header_length, pic_width, bit_per_pixel; // Initialising:
    // length of 2nd header, the number of columns of pixel, the no of bit per pixel respectively.

    if (fread(BIHsize, sizeof(int), 1, initial_photo) != 1) // Checking success in reading
    {
        printf("Error in File\n");
    }
    fwrite(BIHsize, sizeof(int), 1, final_photo); // Writing the header in the new file

    memcpy(&header_length, &BIHsize, 4);          // Writing values

    uint8_t BITMAPV5HEADER[header_length - sizeof(int)];
    if (fread(BITMAPV5HEADER, (header_length - sizeof(int)), 1, initial_photo) !=
        1) // Checking success in reading
    {
        printf("Error in File\n");
        return 1;
    }
    fwrite(BITMAPV5HEADER, (header_length - sizeof(int)), 1,final_photo);   // Writing the header in the new file

    memcpy(&pic_width, &BITMAPV5HEADER[0], 4); // Writing values from header
    memcpy(&bit_per_pixel, &BITMAPV5HEADER[10], 2);

    if (bit_per_pixel != 24) // Rejecting images with pixels that are not of size 24 bits
    {
        printf("Error: Not the type of pixels we are looking for\n");
        return 1;
    }
    printf ("Everything is up and running\n");
    int action; // Asking user for the action they want to carry out.
    do
    {
        printf("What do you want to do today?\n"
                         "Grayscale (1)\n"
                         "Invert    (2)\n"
                         "Mirror    (3)\n");
        scanf("%i", &action);
    }
    while (action > 3 || action < 1);

    int pad = (4 - (pic_width * sizeof(colour)) % 4) % 4; // Calculating the amount of padding needed per row of pixels 
    uint8_t padding[3]= {0}; // Initialising padding values 

    colour *pixelrow = malloc(sizeof(colour) * pic_width); // Allocating memory to dstore the rows of pixeldata

    while (fread(pixelrow, sizeof(colour), pic_width, initial_photo) > 0) // Reading each row of pixel one at sa tim into our alloc memory
    {
        fread(padding, 1, pad, initial_photo); // Reading the padding after each row too
        if (action == 1) // If user wants to grayscale
        {
            for (int j = 0; j < pic_width; j++) // Loops through row to change values to greyscale equivalent
            {
            int value = (pixelrow[j].R * 0.299) + (pixelrow[j].G * 0.587) +
                        (pixelrow[j].B * 0.114); // NTSC formula for greyscaling.
            pixelrow[j].R = value;
            pixelrow[j].G = value;
            pixelrow[j].B = value;
            }
        }
        else if (action == 2)
        {
            for (int j = 0; j < pic_width; j++) // Loops through row to change values to invert equivalent
            {
            pixelrow[j].R = 255 - pixelrow[j].R; // white - colour = invert
            pixelrow[j].G = 255 - pixelrow[j].G;
            pixelrow[j].B = 255 - pixelrow[j].B;
            }
        }
        else
        {
            for (int j = 0, k = pic_width - 1; j < k; j++, k--) // Loops through row to rearrange / flip.
            {
                colour temp = pixelrow[j];
                pixelrow[j] = pixelrow[k];
                pixelrow[k] = temp;
            }
        }
        fwrite(pixelrow, sizeof(colour), pic_width, final_photo); // Reads the enhanced row into the new file 
        fwrite(padding, 1, pad, final_photo); // Adds the necessary padding

    }
    printf("Successful Editing. Check new picture\n");
    free(pixelrow);// frees memory
    fclose(initial_photo); // Closing them
    fclose(final_photo);
    return 0;
}
