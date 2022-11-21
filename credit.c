// The program for checking the bank card number for validity

#include <stdio.h>

int luhn_alg(long n);
long step_one(long n);
int step_two(long n);
int step_three(long n);
int check_first_numbers(long n);
const char* check_issuer(int first_numbers, int number_length, int value_luhn_alg);
void check_credit_card(long credit_number);

// Checking a number for length
int check_length(long n)
{
    int count = 0;

    do
    {
        n /= 10;
        count++;
    }
    while (n != 0);

    return count;
}

// Checking the first numbers of a number
int check_first_numbers(long n)
{
    long first_numbers = n;
    do
    {
        first_numbers /= 10;
    }
    while (first_numbers > 100);
// If the first 2 numbers start with 4, then leave only the first number
// This action is necessary because the visa card number starts at 4
    if (first_numbers < 50 && first_numbers >= 40)
    {
        first_numbers /= 10;
    }
    return first_numbers;
}

// Checking the validity of the card and the issuer
const char* check_issuer(int first_numbers, int number_length, int value_luhn_alg)
{
    if (value_luhn_alg == 1)
    {
        if ((first_numbers == 34 || first_numbers == 37) && number_length == 15)
        {
            return "AMEX";
        }
        else if ((first_numbers == 51 || first_numbers == 52 || first_numbers == 53 || first_numbers == 54 || first_numbers == 55)
                 && number_length == 16)
        {
            return "MASTERCARD";
        }
        else if (first_numbers == 4 && (number_length == 13 || number_length == 16))
        {
            return "VISA";
        }
    }
    return "INVALID";
}

// Launch Luhn’s Algorithm
int luhn_alg(long n)
{
    long a = step_one(n);
    int b = step_two(a);
    int c = step_three(n);
    int d = b + c;
// If the total modulo 10 is congruent to 0, the number is valid!
    if (d % 10 == 0)
    {
        return 1;
    }
// Otherwise, the card number is considered invalid
    return 0;
}

// Multiply every second digit by 2, starting with the number’s second-to-last digit
// Required for the Luhn’s Algorithm to work
long step_one(long n)
{
    long number = n;
    int count = 0;
    long result = 0;

    while (number > 0)
    {
        count++;
        if (count % 2 == 0)
        {
            result = result * 10 + ((number % 10) * 2);
        }
        number = number / 10;
    }

    return result;
}

// Add those products’ digits (i.e., not the products themselves) together
// Required for the Luhn’s Algorithm to work
int step_two(long n)
{
    long number = n;
    int result = 0;

    while (number > 0)
    {
        result = result + number % 10;
        number = number / 10;
    }

    return result;
}

// The sum of the digits that were not multiplied by 2 (starting from the end)
// Required for the Luhn’s Algorithm to work
int step_three(long n)
{
    long number = n;
    int count = 0;
    int result = 0;

    while (number > 0)
    {
        count++;
        if (count % 2 != 0)
        {
            result = result + (number % 10);
        }
        number = number / 10;
    }

    return result;
}

// Starting credit card verification
void check_credit_card(long credit_number)
{
    int number_length = check_length(credit_number);
    int first_numbers = check_first_numbers(credit_number);
    int value_luhn_alg = luhn_alg(credit_number);
    const char* issuer = check_issuer(first_numbers, number_length, value_luhn_alg);

    printf("%s\n", issuer);
}

int main(void)
{
    long credit_number;
    printf("Number: ");
    scanf("%ld", &credit_number);
    check_credit_card(credit_number);
}
