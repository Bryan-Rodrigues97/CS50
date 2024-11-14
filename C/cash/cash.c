#include <cs50.h>
#include <stdio.h>

int getChangeOwned(int value);
int nextCoin(int coin);

int main(void)
{
    int changeOwned;

    do
    {
        changeOwned = get_int("Change Owned: ");
    }while(changeOwned<0);

    changeOwned = getChangeOwned(changeOwned);

    printf("%i\n",changeOwned);
}

int getChangeOwned(int value)
{
    int changeOwned = 0;
    int coinValue   = 25;

    if(value<0)
        return changeOwned;

    while(value>0){
        if(coinValue>value){
            coinValue = nextCoin(coinValue);
            continue;
        }

        value-=coinValue;
        changeOwned++;
    }

    return changeOwned;
}

int nextCoin(int coin)
{
    if(coin==25)
        return 10;
    else if(coin==10)
        return 5;

    return 1;
}
