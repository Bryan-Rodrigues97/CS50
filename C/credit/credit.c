#include <cs50.h>
#include <math.h>
#include <stdio.h>

int getCredCardLength(long credCardNumber);
int getNumberSplitSum(int number);

bool isValidCredCardCheckSum(long credCardNumber);

void finCredCardOperator(long credCardNumber, int length);
void validateCredCard(long credCardNumber);

int main(void)
{
    long credCardNumber;

    do
    {
        credCardNumber = get_long("Number: ");
    }while(credCardNumber<1);

    validateCredCard(credCardNumber);
}

//Function that prints on the screen if the credit card number is valid
void validateCredCard(long credCardNumber)
{
    bool isValidCheckSum = isValidCredCardCheckSum(credCardNumber);

    if(isValidCheckSum)
    {
        int length = getCredCardLength(credCardNumber);

        if(length<13 || length>16)
        {
            printf("INVALID\n");
        }
        else
        {
            finCredCardOperator(credCardNumber,length);
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

//Function that finds the operator code of a credit card number based on the first digits and length
void finCredCardOperator(long credCardNumber, int length)
{
    long    divisor = pow(10, length - 2);
    int     code    = credCardNumber / divisor;

    if((code==34 || code==37) && length==15)
    {
        printf("AMEX\n");
    }
    else if(code>=51 && code<=55 && length==16)
    {
        printf("MASTERCARD\n");
    }
    else if(code>=40 && code<=49 && (length==13 || length==16))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}


//Function that returns TRUE if the checksum is valid; otherwise, FALSE.
bool isValidCredCardCheckSum(long credCardNumber)
{
    bool    sum             = false;

    int     productSum      = 0,
            nonProductSum   = 0;

    while(credCardNumber>0)
    {
        int rest = credCardNumber%10;

        if(sum){
            sum         = false;
            productSum  += getNumberSplitSum(2*rest);
        }
        else{
            sum             = true;
            nonProductSum   += rest;
        }

        credCardNumber = credCardNumber/10;
    }

    int checkSum = productSum + nonProductSum;

    if((checkSum%10)==0)
    {
        return true;
    }

    return false;
}

//Function that returns the lenght of a number
int getCredCardLength(long credCardNumber)
{
    return log10(credCardNumber) + 1;
}

//Function that returns the sum of the digits of a number (0-99)
int getNumberSplitSum(int number)
{
    if(number>=10)
    {
        return number/10 + number%10;
    }

    return number;
}
