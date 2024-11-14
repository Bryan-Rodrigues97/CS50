#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string name = get_string("Contact name: ");
    string phone = get_string("Phone: ");
    int age = get_int("Age: ");

    printf("\nContact Info:\nName: \t%s\nAge: \t%s\nPhone: \t%i\n",name,phone,age);
}
