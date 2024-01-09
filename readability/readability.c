#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

float grade(string sentence);

int main(void)
{
    string sentence = get_string("Text: ");
    int result = round(grade(sentence));
    if (result > 15)
    {
        printf("Grade 16+\n");
    }
    else if (result < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", result);
    }
}

float grade(string sentence)
{
    int letters = 0, sentences = 0, words = 1;

    for (int i = 0; i < strlen(sentence); i++)
    {
        // checking for words
        if (sentence[i] == ' ')
        {
            words++;
        }
        // checking for end of sentences
        if (sentence[i] == '.' || sentence[i] == '?' || sentence[i] == '!')
        {
            sentences++;
        }
        if (isalpha(sentence[i]))
        {
            letters++;
        }
    }
    // printf("Letters: %i, words: %i, sentences: %i\n",letters, words, sentences);

    float L = (float) letters / words * 100;
    float S = (float) sentences / words * 100;

    // printf("L: %f, S: %f",L,S);

    float return_value = 0.0588 * L - 0.296 * S - 15.8;
    return return_value;
}
