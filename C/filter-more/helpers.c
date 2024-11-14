#include "helpers.h"
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
            copy[i][j] = image[i][j];
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

void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Cria uma cópia da imagem
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    int gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int gy[3][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float gxColors[3] = {0, 0, 0};
            float gyColors[3] = {0, 0, 0};


            for(int k = i-1, ki = 0; k <= i+1; k++, ki++)
            {
                for(int l = j-1, kj = 0; l <= j+1; l++, kj++)
                {
                    if(k < 0 || l < 0 || k >= height || l >= width)
                    {
                        continue;
                    }

                    gxColors[0] += gx[ki][kj] * copy[k][l].rgbtRed;
                    gxColors[1] += gx[ki][kj] * copy[k][l].rgbtGreen;
                    gxColors[2] += gx[ki][kj] * copy[k][l].rgbtBlue;

                    gyColors[0] += gy[ki][kj] * copy[k][l].rgbtRed;
                    gyColors[1] += gy[ki][kj] * copy[k][l].rgbtGreen;
                    gyColors[2] += gy[ki][kj] * copy[k][l].rgbtBlue;
                }
            }

            int r = (int) round(sqrt(pow(gxColors[0],2) + pow(gyColors[0],2)));
            int g = (int) round(sqrt(pow(gxColors[1],2) + pow(gyColors[1],2)));
            int b = (int) round(sqrt(pow(gxColors[2],2) + pow(gyColors[2],2)));

            r = r > 255 ? 255 : r;
            g = g > 255 ? 255 : g;
            b = b > 255 ? 255 : b;

            image[i][j].rgbtRed = r;
            image[i][j].rgbtGreen = g;
            image[i][j].rgbtBlue = b;
        }
    }
}
