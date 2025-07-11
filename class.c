#include <stdio.h>
#include "include/input_utils.h"
#include <string.h>

typedef struct
{
    char name[50];
    char phone[10];
} Contact;

void add(Contact *contacts, int contactnum);

int main (void)
{
    Contact contacts[6] = {
    { "Alice Johnson",   "555-1234" },
    { "Bob Smith",       "555-2345" },
    { "Carol Martinez",  "555-3456" },
    { "Dave Thompson",   "555-4567" },
    { "Eve Nguyen",      "555-5678" }
    };
    int contactnum = sizeof(contacts) / sizeof(Contact);
    char answer;
    do
    {
        answer = get_char("Do you want to add a contact(Y/n) ");
    }
    while (answer != 'y' && answer != 'Y' && answer != 'n' && answer != 'N');
    if (answer == 'y' || answer =='Y')
    {
        add(contacts, contactnum);
    }
    else
        printf("Okay\n");
    return 0;
}
void add(Contact *contacts, int contactnum)
{
    string namer = get_string("Name: ");
    strcpy (contacts[5].name, namer);
    string phoner = get_string("Phone: ");
    strcpy (contacts[5].phone, phoner);
    printf ("Number of contacts is %i\n", contactnum);
    //Print each member of the above array
    for (int i = 0; i < contactnum; i++)
    {
        printf("%s %s\n",contacts[i].name, contacts[i].phone);
    }
}