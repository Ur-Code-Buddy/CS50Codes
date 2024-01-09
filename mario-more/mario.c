#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int user_input;
    do
    {
        user_input = get_int("Height: ") + 1;
    }
    while (user_input < 2 || user_input > 9);

    for (int height = 1; height < user_input; height++)
    {

        for (int i = 1; i < user_input - height; i++)
        {
            printf(" ");
        }
        for (int i = 0; i < height; i++)
        {
            printf("#");
        }
        printf("  ");

        for (int i = 0; i < height; i++)
        {
            printf("#");
        }
        printf("\n");
    }
}
