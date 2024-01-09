#include "helpers.h"
#include <math.h>
#include <stdio.h>

int get_values_for_blur(int i, int j, int height, int width, RGBTRIPLE image[height][width], char value);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, int_width = (int) width / 2; j < int_width; j++)
        {

            int originalRed = image[i][j].rgbtRed, originalGreen = image[i][j].rgbtGreen, originalBlue = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = image[i][-j + width - 1].rgbtRed;
            image[i][j].rgbtGreen = image[i][-j + width - 1].rgbtGreen;
            image[i][j].rgbtBlue = image[i][-j + width - 1].rgbtBlue;

            image[i][-j + width - 1].rgbtRed = originalRed;
            image[i][-j + width - 1].rgbtGreen = originalGreen;
            image[i][-j + width - 1].rgbtBlue = originalBlue;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = get_values_for_blur(i, j, height, width, temp, 'r');
            image[i][j].rgbtGreen = get_values_for_blur(i, j, height, width, temp, 'g');
            image[i][j].rgbtBlue = get_values_for_blur(i, j, height, width, temp, 'b');
        }
    }
    return;
}

// int get_values_for_blur(int i, int j, int height, int width, RGBTRIPLE image[height][width], char value ){
//     int count = 0, sum = 0;

//     if (  ( i == 0 || i == height - 1) && ( j == 0 || j == width - 1) ){
//         if (value == 'r'){
//             sum += image[i][j].rgbtRed;

//         }
//     }
//     else if (i == 0 || i == height - 1){
//         //6 pixels
//     }
//     else if (j == 0 || j == width - 1){
//         //6 pixels
//     }
//     else {
//         //9 pixels
//     }
// }

int get_values_for_blur(int i, int j, int height, int width, RGBTRIPLE image[height][width], char value)
{
    float sum = 0;
    int count = 0;

    for (int row = i - 1; row < i + 2; row++)
    {
        for (int column = j - 1; column < j + 2; column++)
        {
            if (!(row < 0 || row >= height || column < 0 || column >= width))
            {
                if (value == 'r')
                {
                    sum += image[row][column].rgbtRed;
                }
                else if (value == 'g')
                {
                    sum += image[row][column].rgbtGreen;
                }
                else
                {
                    sum += image[row][column].rgbtBlue;
                }
                count++;
            }
        }
    }
    // printf("%i %f",sum,count);
    return round(sum / count);
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int x[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}}, y[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    int rx, gx, bx, ry, gy, by;

    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            continue;
        }
    }

    return;
}
