#include "include/input_utils.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
 
#define command argv[1] // The first cl argument is always the command 
#define NAME argv[2] // The second cl argument is always the name
#define PHONE argv[3] // The third cl argument is always the phone number
#define EMAIL argv[4] // The fourth cl argument is always the email
#define CONTACTSPACE 4
#define USEDSPACE 3
#define MATCH 0
#define FAIL 1
#define RUNnCOMMAND 2 // means run and command : abstracts the counting of the command line arguments


typedef struct{
    char name[50];
    char phone[20];
    char email[50];
} contact; // Type that keeps name, phone and email.

void add (string *argv, contact *person);
int is_correct_input(int argc);
void list (contact *person);
void search(string *argv, contact *person);
void cancel(string *argv, contact *person);

int main(int argc, string argv[]) // Collecting CLA 
{
    // Variable that stores the default contacts and extra space.
    contact person[CONTACTSPACE] = {
                        {"John Thomas", "08098765464", "johnthm@yahoo.com"},
                        {"Anne Hall", "09136525564", "hallofanne@gmail.com"},
                        {"Hassan Usman", "08198245894", "husman@yahoo.com"},
                        {"", "", ""}
                        };              
    
    // Checking for a command                   
    if (is_correct_input(argc) == FAIL) // Using my function for checking at least one command line argument (CLA)
        return FAIL;
    else
    {
        if (strcmp(command, "add") == MATCH) // Checking if user wants to add a contact
        { 
            if (argc != (3 + RUNnCOMMAND)) // Making sure the add command is  properly used, it takes 3 inputs
            {
                printf("Usage: ./contact add 'FULL NAME' PHONE EMAIL\n");
                return FAIL;
            }
            else 
            {
                if (strlen(PHONE) > 20) // Checks so that boundaries are not exceeded
                {
                    printf("Too many numbers as phone\n");
                    return FAIL;
                }
                else 
                    add (argv, person); // Function call that adds the contact to the storage
            }
        } 
        else if (strcmp(command, "list") == MATCH) // Checking if user wants to see available contacts
        {
            if (argc != RUNnCOMMAND) // Making sure the lists command is  properly used, it takes no input
            {
                printf("Usage: ./contact list \n");
                return FAIL;
            }
            else
                list (person); // Function call that lists the contacts in the storage
        }
        else if (strcmp(command, "search") == MATCH) // Checking if user wants to search for a contact
        {
            if (argc != (RUNnCOMMAND + 1)) // Making sure the search command is  properly used, it takes 1 input
            {
                printf("Usage: ./contact search FIRSTNAME\n");
                return FAIL;
            }  
            else
                search(argv, person); // Function call that searches the contact in the storage

        }
        else if (strcmp(command, "number_of_contacts") == MATCH ) // Checking if user wants to know number of contacts available
        {
            if (argc != RUNnCOMMAND) // Making sure the number_of_contacts command is  properly used, it takes no input
            {
                printf("Usage: ./contact number_of_contacts\n");
                return FAIL;   
            }  
            else
                printf("Your total number of available contacts is %li.\n", (sizeof(person) / sizeof(contact)) - 1);

        }
        else if (strcmp(command, "remove") == MATCH ) // Checking if user wants to remove a contact
        {
            if (argc != (RUNnCOMMAND + 1)) // Making sure the remove command is  properly used, it takes 1 input
            {
                printf("Usage: ./contact remove FIRSTNAME\n");
                return FAIL;   
            }  
            else
                cancel(argv, person); // Function call that cancels the contact from the storage
        }
        else
        {
            // When the correct commands aren't written 
            printf ("Not a valid command.\nCommand(add 'FULL NAME' PHONE EMAIL/ list / search FIRSTNAME / number_of_contacts / remove FIRSTNAME)\n");
            return FAIL;
        }
    }
    return 0;
}
 
// Function that checks for at least a command 
int is_correct_input(int argc)
{
    if (argc < RUNnCOMMAND)
    {
        printf("Usage: ./contact Command(add 'FULL NAME' PHONE EMAIL/ list / search FIRSTNAME / number_of_contacts / remove FIRSTNAME)\n");
        return FAIL;
    }
    return 0;
}

// Function that adds new contact
void add (string *argv, contact *person)
{
    // Copies the user's input into it's corresponding category in the empty space in person
    strcpy(person[USEDSPACE].name, NAME); 
    strcpy(person[USEDSPACE].phone, PHONE);
    strcpy(person[USEDSPACE].email, EMAIL);
    char list;
    do 
    {
        list = get_char("Would like to see full list?(Y/n): "); // Checks if they want to see the new contact list
    }
    while (list != 'y' && list != 'Y' && list != 'n' && list != 'N');
    if (list == 'y' || list == 'Y')
    {
        printf ("The contacts available:\n");
        for (int i = 0; i < CONTACTSPACE; i++)
        {
            printf ("%s  %s  %s\n", person[i].name, person[i].phone, person[i].email); // prints each string and array in person line by line.
        }
    }
}

//Function that lists contacts
void list (contact *person)
{
    
    printf ("The contacts available:\n");
    for (int i = 0; i < USEDSPACE; i++)
    {
        printf ("%s  %s  %s\n", person[i].name, person[i].phone, person[i].email); // Prints out the available items in person
    }
}

/*
Searches for the contact the user is looking for
It first seperates the firstname from the last name in both the user input and the available contacts 
To allow the user to just type in the firstname if they like
Then it turns everything to lowercase to prevent case from making the strcmp function malfunction
Compares the user input to the available contact
Then prints the corresponding contact
*/
void search(string *argv, contact *person)
{
    // Firstname for user input
    int i, j,k;
    char firstname[CONTACTSPACE][50]; 
    for (i  =  0, j = strlen(NAME), k = 0; i < j; i++)
    {
        if (isspace(NAME[i]) || NAME[i] == '\0')
            break;
        else 
        {
            firstname[0][k] = NAME[i];
            k++;
        }
    }
    firstname[0][k] = '\0';

    // Firstname for available contacts
    int a, b,c;
    for (int d = 0; d < 3; d++)
    {
        for (a  =  0, b = strlen(person[d].name), c = 0; a < b; a++)
        {
            if (isspace(person[d].name[a]) || person[d].name[a] == '\0')
                break;
            else 
            {
                firstname[d+1][c] = person[d].name[a];
                c++;
            }
        }
        firstname[d+1][c] = '\0';
    }

    // Changes everything to lowercase
    for (int d = 0; d < CONTACTSPACE; d++)
    {
        for (int y = 0; firstname[d][y] != '\0'; y++)
        {
            firstname[d][y] = tolower(firstname[d][y]);
        }
    }

    // Compares 
    int d;
    for (d = 1; d < CONTACTSPACE; d++)
    {
        if (strcmp(firstname[0], firstname[d]) == MATCH)
        {
            printf("Is the name your searching for?\n%s  %s  %s\n", person[d-1].name, person[d-1].phone, person[d-1].email); 
            // It's D-1 because their positons in firstname is not the same as available contact (The user in put is also in firstname)
            break;
        }
        else 
            continue;
    }
    if (d == CONTACTSPACE)
        printf("The person you are looking for is not saved here.\n");
}

/*
Searches for the contact the user is trying to delete 
It first seperates the firstname from the last name in both the user input and the available contacts 
This allows the user to just type in the firstname if they like
Then it turns everything to lowercase to prevent case from making the strcmp function malfunction
Compares the user input to the available contact
Asks the user if their sure about the deletion 
Asks them if they'd like to see the updated contacts list
Then prints the contacts skipping over the one the user 'deleted'
*/
void cancel(string *argv, contact *person)
{
    // Seperating...
    int i, j,k;
    char firstname[CONTACTSPACE][50]; 
    for (i  =  0, j = strlen(NAME), k = 0; i < j; i++)
    {
        if (isspace(NAME[i]) || NAME[i] == '\0')
            break;
        else 
        {
            firstname[0][k] = NAME[i];
            k++;
        }
    }
    firstname[0][k] = '\0';

    // Seperating...
    int a, b,c;
    for (int d = 0; d < USEDSPACE; d++)
    {
        for (a  =  0, b = strlen(person[d].name), c = 0; a < b; a++)
        {
            if (isspace(person[d].name[a]) || person[d].name[a] == '\0')
                break;
            else 
            {
                firstname[d+1][c] = person[d].name[a];
                c++;
            }
        }
        firstname[d+1][c] = '\0';
    }

    // Lowercasing ...
    for (int d = 0; d < CONTACTSPACE; d++)
    {
        for (int y = 0; firstname[d][y] != '\0'; y++)
        {
            firstname[d][y] = tolower(firstname[d][y]);
        }
    }

    // Fake deleting .....
    int d;
    char sure, list;
    for (d = 1; d < CONTACTSPACE; d++)
    {
        if (strcmp(firstname[0], firstname[d]) == MATCH)
        {
            do
            {
                sure = get_char("Are you sure? (Y/n): "); // asks for affirmation
            }
            while (sure != 'y' && sure != 'Y' && sure != 'N' && sure != 'n');
            if (sure == 'y' || sure == 'Y') 
            {
                do
                {
                    list = get_char("Do you want a list of the remaining contacts? (Y/n): "); // Asks if they want evidence
                }
                while (list != 'y' && list != 'Y' && list != 'N' && list != 'n');
                if (list == 'y' || list == 'Y') 
                {
                    printf("Available Contacts:\n"); 
                    for (int f = 0; f < USEDSPACE; f++)
                    {
                        if (f != d-1) // Prints the names skipping the fake deleted name
                            printf ("%s \n", person[f].name); 
                        else
                            continue;
                    }
                    break;
                }
                else
                {
                    printf ("Ok\n");
                    break;
                }
                
            }
            else
            {
                printf("Sure!\n");
                break;
            }
        }
        else 
            continue;
    }
    if (d == CONTACTSPACE)
        printf("The person you are trying to remove is not saved here.\n");
}
