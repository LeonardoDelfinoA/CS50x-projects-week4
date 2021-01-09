#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int i = 0;
    int j = 0;

    for (i = 0; i < height; i++)
    {
        for ( j = 0; j < width; j++)

        {
            int media = round((float)(image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3);

            if (media >= 255)
            {
                media = 255;
            }

            if (media <= 0)
            {
                media = 0;
            }

            image[i][j].rgbtRed = media;
            image[i][j].rgbtGreen = media;
            image[i][j].rgbtBlue = media;

        }
    }

}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = round(.393 * (float)image[i][j].rgbtRed + .769 * (float)image[i][j].rgbtGreen + .189 * (float)image[i][j].rgbtBlue);
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            int sepiaGreen = round(.349 * (float)image[i][j].rgbtRed + .686 * (float)image[i][j].rgbtGreen + .168 * (float)image[i][j].rgbtBlue);
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            int sepiaBlue = round(.272 * (float)image[i][j].rgbtRed + .534 * (float)image[i][j].rgbtGreen + .131 * (float)image[i][j].rgbtBlue);
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }


            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    int metade = 0;

    if ( width % 2 == 1)
    {
        metade = round((float)width / 2);
    }

    else if (width % 2 == 0)
    {
        metade = width / 2;
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < metade; j++)
        {

            temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;

        }

    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blured[height][width];
    RGBTRIPLE tempblur;
    int up;
    int down;
    int left;
    int right;
    int totalpixel;
    int totalred;
    int totalgreen;
    int totalblue;
    int i;
    int j;


    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            up = 0;
            down = 0;
            left = 0;
            right = 0;
            totalpixel = 1;
            totalred = image[i][j].rgbtRed;
            totalgreen = image[i][j].rgbtGreen;
            totalblue = image[i][j].rgbtBlue;



            if (i - 1 >= 0)
            {

                up++;

            }

            if (i + 1 <= height - 1)
            {

                down++;

            }

            if (j - 1 >= 0)
            {

                left++;
                totalpixel ++;
                totalred += image[i][j - 1].rgbtRed;
                totalgreen += image[i][j - 1].rgbtGreen;
                totalblue += image[i][j - 1].rgbtBlue;

            }
            if (j + 1 <= width - 1)
            {

                right++;
                totalpixel ++;

                totalred += image[i][j + 1].rgbtRed;
                totalgreen += image[i][j + 1].rgbtGreen;
                totalblue += image[i][j + 1].rgbtBlue;
            }

            if ( up == 1)
            {
                totalred += image[i - 1][j].rgbtRed;
                totalgreen += image[i - 1][j].rgbtGreen;
                totalblue += image[i - 1][j].rgbtBlue;

                totalpixel++;

                if (left == 1)
                {
                    totalred += image[i - 1][j - 1].rgbtRed;
                    totalgreen += image[i - 1][j - 1].rgbtGreen;
                    totalblue += image[i - 1][j - 1].rgbtBlue;

                    totalpixel ++;

                }

                if (right == 1)
                {

                    totalred += image[i - 1][j + 1].rgbtRed;
                    totalgreen += image[i - 1][j + 1].rgbtGreen;
                    totalblue += image[i - 1][j + 1].rgbtBlue;

                    totalpixel++;

                }

            }

            if (down == 1)
            {

                totalred += image[i + 1][j].rgbtRed;
                totalgreen += image[i + 1][j].rgbtGreen;
                totalblue += image[i + 1][j].rgbtBlue;

                totalpixel++;

                if (left == 1)
                {

                    totalred += image[i + 1][j - 1].rgbtRed;
                    totalgreen += image[i + 1][j - 1].rgbtGreen;
                    totalblue += image[i + 1][j - 1].rgbtBlue;

                    totalpixel++;

                }

                if (right == 1)
                {

                    totalred += image[i + 1][j + 1].rgbtRed;
                    totalgreen += image[i + 1][j + 1].rgbtGreen;
                    totalblue += image[i + 1][j + 1].rgbtBlue;

                    totalpixel++;

                }
            }

            blured[i][j].rgbtRed = round((float)totalred / totalpixel);
            blured[i][j].rgbtGreen = round((float)totalgreen / totalpixel);
            blured[i][j].rgbtBlue = round((float)totalblue / totalpixel);

        }
    }

    for (int h = 0; h < height; h++)
    {
        for (int k = 0; k < width; k++)
        {

            tempblur = blured[h][k];
            image[h][k] = tempblur;

        }
    }
    return;
}
