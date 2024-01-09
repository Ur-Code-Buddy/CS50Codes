// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>

void replaceV(string word, int length);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Invalid arguments\n");
        return 1;
    }
    int length = 0;

    while (argv[1][length] != '\0') {
        length++;
    }
    string output = argv[1];
    replaceV(output, length);
    printf("%s\n", output);
}

void replaceV(string word, int length)
{
    for (int i = 0; i < length; i++)
    {
        switch (word[i])
        {
            case 'a':
                word[i] = '6';
                break;

            case 'e':
                word[i] = '3';
                break;

            case 'i':
                word[i] = '1';
                break;

            case 'o':
                word[i] = '0';
                break;
        }
    }
}
