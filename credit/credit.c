#include <cs50.h>
#include <math.h>
#include <stdio.h>

int isCreditCardValid(long long cardNumber);
int lengthOfLong(long longNumber);

int main(void)
{
    long user_input;
    int firstDigit, secondDigit;

    user_input = get_long("Number :");

    if (!(isCreditCardValid(user_input)))
    {
        printf("INVALID\n");
        return 0;
    }
    int length = lengthOfLong(user_input);
    firstDigit = (int) (user_input / pow(10, length - 1));
    secondDigit = (int) (user_input / pow(10, length - 2)) % 10;

    int ID_number = (firstDigit * 10) + secondDigit;

    if (firstDigit == 4 && (length == 13 || length == 16))
    {
        printf("VISA\n");
    }
    else if ((ID_number == 34 || ID_number == 37) && length == 15)
    {
        printf("AMEX\n");
    }
    else if ((ID_number == 51 || ID_number == 52 || ID_number == 53 || ID_number == 54 || ID_number == 55) && length == 16)
    {
        printf("MASTERCARD\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

int isCreditCardValid(long long cardNumber)
{
    int sum_of_alternates = 0, sum_of_multiples = 0;
    bool alternate = true;

    if (lengthOfLong(cardNumber) < 13)
    {
        return false;
    }

    while (cardNumber > 0)
    {

        int current_number = cardNumber % 10;

        if (alternate)
        {
            sum_of_alternates += current_number;
        }
        else
        {
            current_number = current_number * 2;
            if (current_number > 9)
            {
                sum_of_multiples += current_number % 10;
                current_number /= 10;
            }
            sum_of_multiples += current_number;
        }

        alternate = !alternate;
        cardNumber /= 10;
    }
    // printf("Final: %i, %i\n",sum_of_multiples, sum_of_alternates);
    return ((sum_of_multiples + sum_of_alternates) % 10 == 0);
}

int lengthOfLong(long longNumber)
{
    int length = 0;
    while (longNumber != 0)
    {
        longNumber /= 10;
        length++;
    }
    return length++;
}
