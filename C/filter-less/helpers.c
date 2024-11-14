#include "helpers.h"
#include <stdlib.h>
#include <math.h>


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE gray = ((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) + 1) / 3;

            image[i][j].rgbtBlue = gray;
            image[i][j].rgbtGreen = gray;
            image[i][j].rgbtRed = gray;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = (int)round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = (int)round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = (int)round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            image[i][j].rgbtBlue = sepiaBlue <= 255 ? sepiaBlue : 255;
            image[i][j].rgbtGreen = sepiaGreen <= 255 ? sepiaGreen : 255;
            image[i][j].rgbtRed = sepiaRed <= 255 ? sepiaRed : 255;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            //swap(height, width, image, i, j, width-1-j);

            int lRed = image[i][j].rgbtRed;
            int lGreen = image[i][j].rgbtGreen;
            int lBlue = image[i][j].rgbtBlue;

            // set the left pixels with the right pixels
            image[i][j].rgbtRed = image[i][width-1-j].rgbtRed;
            image[i][j].rgbtGreen = image[i][width-1-j].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width-1-j].rgbtBlue;

            // set the right pixels with the tmp values
            image[i][width-1-j].rgbtRed = lRed;
            image[i][width-1-j].rgbtGreen = lGreen;
            image[i][width-1-j].rgbtBlue = lBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    float colors[3] = {0, 0, 0};
    int avg = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            colors[0] = 0;
            colors[1] = 0;
            colors[2] = 0;

            avg = 0;

            for(int k = i-1; k <= i+1; k++)
            {
                for(int l = j-1; l <= j+1; l++)
                {
                    if(k < 0 || l < 0 || k >= height || l >= width)
                    {
                        continue;
                    }

                    colors[0] += copy[k][l].rgbtRed;
                    colors[1] += copy[k][l].rgbtGreen;
                    colors[2] += copy[k][l].rgbtBlue;

                    avg++;
                }
            }

            colors[0] = (int)round((colors[0])/avg);
            colors[1] = (int)round((colors[1])/avg);
            colors[2] = (int)round((colors[2])/avg);

            image[i][j].rgbtRed = colors[0];
            image[i][j].rgbtGreen = colors[1];
            image[i][j].rgbtBlue = colors[2];
        }
    }

    return;
}
