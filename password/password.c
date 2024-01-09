// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <stdio.h>
#include <ctype.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    int length = 0;
    while (password[length] != '\0'){
        length++;
    }

    bool uppercase = false, lowercase = false, number = false, symbol = false;
    for (int i = 0; i < length; i++ ){

        if (isupper(password[i]) ){
            uppercase = true;
        }
        if (islower(password[i]) ){
            lowercase = true;
        }
        if (isdigit(password[i])){
            number = true;
        }
        if (ispunct(password[i])){
            symbol = true;
        }
    }
    if (uppercase == true && lowercase == true && number == true && symbol == true){
        return true;
    }


    return false;
}
