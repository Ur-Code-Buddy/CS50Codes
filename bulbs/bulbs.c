#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    string user_input = get_string("Message: ");

    for (int letters = 0; letters < strlen(user_input); letters++)
    {
        int dec_ascii = user_input[letters]; // dec_ascii is 72 now(H)
        int data[8] = {0};
        for (int index = 0; index < 8; index++)
        {
            data[index] = (dec_ascii % 2);
            dec_ascii /= 2;
        }
        for (int index = 7; index >= 0; index--)
        {
            // printf("%i",data[index]);
            print_bulb(data[index]);
        }

        printf("\n");
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}

