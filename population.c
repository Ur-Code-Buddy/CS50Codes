#include <cs50.h>
#include <stdio.h>

int main(void)
{

    int startsize, endsize, years = 0, new_lamas = 0, dead_lamas = 0;

    do
    {
        startsize = get_int("Start size: ");
    }
    while (startsize < 9);

    do
    {
        endsize = get_int("End size: ");
    }
    while (endsize < startsize);

    while (startsize < endsize)
    {
        new_lamas = startsize / 3;
        dead_lamas = startsize / 4;

        startsize = startsize + (new_lamas - dead_lamas);
        years++;
        // printf("years");
    }
    printf("Years: %i\n", years);

    // TODO: Prompt for start size

    // TODO: Prompt for end size

    // TODO: Calculate number of years until we reach threshold

    // TODO: Print number of years
}
