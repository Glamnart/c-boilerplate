#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FALSE 0
#define TRUE 1
#define UNITPAY 100000
#define MAX_LINE_LEN 512
#define MAX_NAME_LEN 50
#define MAX_NUM_LEN 20

// Struct for keeping members info
typedef struct {
    char name[MAX_NAME_LEN + 1];
    char phone[MAX_NUM_LEN + 1];
    char AccountNumber[MAX_NUM_LEN + 1];
    char BankName[MAX_NAME_LEN + 1];
    double ToPay;
    int paid; // bool
} members;

// Struct for singly linked lists 
typedef struct Track {
    char name[MAX_NAME_LEN];
    double ToPay;
    int position;
    struct Track* next;
} Track;

Track *TrackList  = NULL; // queue pointer set to NULL
members person;

// Functions' prototypes arranged alphabetically.
    int Menue();

    void AddMember();
    void DeleteMember();
    void EditMember();
    void MemberFunction();
    void ViewAllMembers();
    
    void ListPaid();
    void ListUnPaid();
    void MarkPayment(); 
    void ResetPayment();
    void Payment();
    
    void DefineTracking();
    void DequeueList();
    void MakeList();
    void TrackingList();
    void ViewList();
    void ViewMemberInfo();
    
    void NewSeason();
//

// Main files used
const char *MemberFile = "Member.csv";
const char *TrackingFile = "TrackingList.csv";  

int main(int argc, char *argv[])
{
    int menue;
    if (argc != 1)
        printf("No command line arguement needed\nJust %s.\n", argv[0]);
    // Goes to main menue, then moves based on user's choice
    do{
        menue = Menue();
        switch (menue) {
            case 1: MemberFunction(); break;
            case 2: Payment(); break;
            case 3: TrackingList(); break;
            case 4: NewSeason(); break;
            case 5: printf("EXITING....\n");break;           
        }
    }
    while (menue != 5);
    return 0;
}

// Function that displays the main menue
int Menue()
{
    int choice;
    do{
    printf("_________Welcome to Contributions manager_________\n\n"

            "What would you like to do?\n"
            "1.) Add / Delete / Edit / View Member Information\n"
            "2.) Confirm Payment\n"
            "3.) Trackling List Options\n"
            "4.) New Season\n"
            "5.) Save & Exit\n"
            "____________________________________________________\n"
            "Choice: ");
    // Pick user input
    scanf("%d", &choice);
    getchar(); // consume newline
    // Preventing wrong answers
    if (choice < 1 || choice > 5)
        printf("Invalid Choice\n");    
    } 
    while(choice < 1 || choice > 5);

    return choice;        
}

// Function that displays the members menue
void MemberFunction()
{
    int choice;
    do{
    printf("______________________\n\n"

            "Do you want to :\n"
           "1.) Add a member\n"
           "2.) Delete a member\n"
           "3.) Edit member info\n"
           "4.) View member Info\n"
           "5.) View All members\n"
           "6.) Back\n"
           "_______________________\n"
           "Choice: ");
    scanf("%d", &choice);
    getchar(); // consume newline
    if (choice < 1 || choice > 6)
        printf("Invalid Choice\n");    
    } 
    while(choice < 1 || choice > 6);
    // Choosing paths
    switch (choice) {
        case 1: AddMember(); break;
        case 2: DeleteMember(); break;
        case 3: EditMember(); break;
        case 4: ViewMemberInfo(); break;
        case 5: ViewAllMembers(); break;
        case 6: return;     
    }
    return;
} 

// Function that adds a member
void AddMember()
{
    FILE* file = fopen(MemberFile, "a"); // Open member file
    if (!file)
        printf("File Error\n");
    else{ 
        //Getting the info from the user

        printf( "Do not exceed the maximum length for each field.\n"
                "If you type more than the maximum, your input will be cut.\n"
                "You will also need to press ENTER to continue the program.\n\n"
            
                "Enter name (Max: %d): ", MAX_NAME_LEN);
        fgets(person.name, sizeof(person.name), stdin);

        if (!strchr(person.name, '\n'))
        {
            person.name[MAX_NAME_LEN] = '\0';
            int c;
            while ((c = getchar()) != '\n' && (c = getchar()) != EOF); // Ensures no memory leaks
        }
        else
            person.name[strcspn(person.name, "\n")] = 0;

        printf("Enter phone (Max: %d): ", MAX_NUM_LEN);
        fgets(person.phone, sizeof(person.phone), stdin);

        if (!strchr(person.phone, '\n'))
        {
            person.phone[MAX_NUM_LEN] = '\0';
            int c;
            while ((c = getchar()) != '\n' && (c = getchar()) != EOF); // Ensures no memory leaks
        }
        else
            person.phone[strcspn(person.phone, "\n")] = 0;
        
        printf("Enter Account Number (Max: %d): ", MAX_NUM_LEN);
        fgets(person.AccountNumber, sizeof(person.AccountNumber), stdin);
          
        if (!strchr(person.AccountNumber, '\n'))
        {
            person.AccountNumber[MAX_NUM_LEN] = '\0';
            int c;
            while ((c = getchar()) != '\n' && (c = getchar()) != EOF); // Ensures no memory leaks
        }
        else
            person.AccountNumber[strcspn(person.AccountNumber, "\n")] = 0;

        printf("Enter Bank Name (Max: %d): ", MAX_NAME_LEN);
        fgets(person.BankName, sizeof(person.BankName), stdin);

        if (!strchr(person.BankName, '\n'))
        {
            person.BankName[MAX_NAME_LEN] = '\0';
            int c;
            while ((c = getchar()) != '\n' && (c = getchar()) != EOF); // Ensures no memory leaks
        }
        else
            person.BankName[strcspn(person.BankName, "\n")] = 0;


        printf("Enter Amount To Pay: ");
        scanf("%le", &person.ToPay);
        getchar(); // consume newline
         
        person.paid = FALSE; 

        fprintf(
            file,
            "%s,%s,%s,%s,%.2f,%i\n", 
            person.name, person.phone, person.AccountNumber, person.BankName, person.ToPay, person.paid
        ); // Sending it to the member file's  end
        printf ("Member Successfully Added\n");
        fclose(file);
    }

    // Going back
    char back;
    do {
    printf ("Would you like to go back to the menue you just came back from (Y/n)? ");
    scanf("%s", &back);
    getchar(); // consume newline
    }
    while(back != 'Y' && back != 'y' && back != 'N' && back != 'n');
    if (back == 'Y' || back == 'y')
        MemberFunction();
    else 
        printf("GOING BACK TO MAIN MENUE....\n");
    return;
}

// Function that deletes a member
void DeleteMember()
{
    printf("Who do you want to remove?\n");
    char line[MAX_LINE_LEN]; // lines loaded from the file
    int members_count = 0;

    // Opening the file
    FILE *file = fopen(MemberFile, "r");
    if (!file)
    {
        printf("File Error\n");
        return;
    }

    // printing names from the file for selection
    while(fgets(line, sizeof(line), file))
    {
        printf("%i.) %s\n", ++members_count, strtok(line, ",\n"));
    }
    printf("0.) Back\n");

    fclose(file); // Closing file 

    if (members_count == 0)// When file is empty
        printf("There are no members here.\n");
    else{
        int choice, check = 1;

        do // Getting member choice from user
        {
            printf("Choice: ");
            scanf("%d", &choice);
            getchar(); // consume newline

            if (choice > members_count || choice < 0)
                printf("Invalid Choice\n");
        }
        while(choice > members_count || choice < 0);

        if (choice == 0) // Going back if user chooses
            MemberFunction();
        else
        {
            // Opening member file and a temporary storage file
            FILE *file= fopen(MemberFile, "r");
            FILE *temp = fopen("temp.csv", "w");
            
            if (!file || !temp)
            {
                printf("File Error\n");
                return;
            }
            
            while (fgets(line, sizeof(line), file)) // While reading file line by line
            { 
                if (choice != check) // Will not print into file if choice is same as current line number.
                    fwrite(line, strlen(line), 1, temp);
                check++;
            }

            // Closing both files
            fclose(file); 
            fclose(temp);

            // Deleting current member file and replacing with temp file
            remove(MemberFile);
            rename("temp.csv", MemberFile);

            printf("Member Successfully Deleted\n");
        }
    }

    // Going back
    char back;
    do 
    {
        printf("Would you like to go back to the menue you just came back from (Y/n)? ");
        scanf("%s", &back);
        getchar(); // consume newline
    }
    while(back != 'Y' && back != 'y' && back != 'N' && back != 'n');

    if (back == 'Y' || back == 'y')
        MemberFunction();
    else 
        printf("GOING BACK TO MAIN MENUE....\n");
    return; 
}

// Function in charge of editing specific member information.
void EditMember()
{
    printf("Whose information do you want to edit?\n");
    char line[MAX_LINE_LEN];// lines loaded from the file
    int members_count = 0;

    // Opening the file
    FILE *file = fopen(MemberFile, "r");
    if (!file)
    {
        printf("File Error\n");
        return;
    }
    
    // printing names from the file for selection
    while(fgets(line, sizeof(line), file))
    {
        printf("%i.) %s\n", ++members_count, strtok(line, ",\n"));
    }

    fclose(file); // Closing file

    printf("0.) Back\n");

    if (members_count == 0){ // When file is empty
        printf("There are no members here.\n");
    }
    else{
        int choice1, choice2, check1 = 1; //Choice1 is user's member choice while choice2 is field choice

        do // Getting choice1
        {
            printf("Choice: ");
            scanf("%d", &choice1);
            getchar(); // consume newline

            if (choice1 > members_count || choice1 < 0)
                printf("Invalid Choice\n");
        }     
        while(choice1 > members_count || choice1 < 0);

        if (choice1 == 0) // Back
            MemberFunction();
        else
        {
            do //Getting choice2
            {
                printf("What information do you want to change?\n"
                        "1.) Name\n"
                        "2.) Phone Number\n"
                        "3.) Account Number\n"
                        "4.) Bank Name\n"
                        "5.) Amount to Pay\n"
                        "0.) Back\n"
                        "Choice: "
                    );
                scanf("%d", &choice2);
                getchar(); // consume newline

                if (choice2 > 5 || choice2 < 0)
                    printf("Invalid Choice\n");
            }
            while(choice2 > 5 || choice2 < 0);

            if (choice2 == 0) 
                EditMember(); // Back
            else
            {
                // Opening member file and a temporary storage file
                FILE *file= fopen(MemberFile, "r");
                FILE *temp = fopen("temp.csv", "w");
                if (!file || !temp)
                {
                    printf("File Error\n");
                    return;
                }
                
                while (fgets(line, sizeof(line), file)) // While reading file line by line
                { 
                    if (choice1 == check1) // When it sees the member that was chosen
                    {
                        strcpy(person.name, strtok(line, ",\n")); // Saves name
                        strcpy(person.phone, strtok(NULL, ",\n")); // Saves Phone Number
                        strcpy(person.AccountNumber, strtok(NULL, ",\n")); // Saves Account Number
                        strcpy(person.BankName, strtok(NULL, ",\n")); // Saves Bank Name
                        person.ToPay = atoi(strtok(NULL, ",\n")); // Saves Amount to Pay
                        char *rest = strtok(NULL, "\n"); // Saves the rest
                        
                        printf("Enter new data: "); // Gets the new data
                        switch(choice2)
                        {
                            case 1: fgets(person.name, MAX_NAME_LEN, stdin); person.name[strcspn(person.name, "\n")] = 0; break; // Replaces name if chosen
                            case 2: fgets(person.phone, MAX_NUM_LEN, stdin); person.phone[strcspn(person.phone, "\n")] = 0; break; // Replaces Phone if chosen
                            case 3: fgets(person.AccountNumber, MAX_NUM_LEN, stdin); person.AccountNumber[strcspn(person.AccountNumber, "\n")] = 0; break; // Replaces Account Number if chosen
                            case 4: fgets(person.BankName, MAX_NUM_LEN, stdin); person.BankName[strcspn(person.BankName, "\n")] = 0; break; // Replaces Bank Name if chosen
                            case 5: scanf("%le", &person.ToPay); getchar(); break; // Replaces Amount to Pay if chosen
                        }
                        fprintf(temp, "%s,%s,%s,%s,%.2f,%s\n", person.name, person.phone, person.AccountNumber, person.BankName, person.ToPay, rest); // Prints to temp file.
                    }
                    else 
                    {
                        fprintf(temp, "%s", line); // Prints to temp file.
                    }
                    check1++;
                }

                // Closing both files
                fclose(file);
                fclose(temp);

                // Deleting current member file and replacing with temp file
                remove(MemberFile);
                rename("temp.csv", MemberFile);

                printf("Field Successfully Edited\n");

                // Going back
                char back;
                do {
                    printf ("Would you like to go back to the menue you just came back from (Y/n)? ");
                    scanf("%s", &back);
                    getchar(); // consume newline
                }
                while(back != 'Y' && back != 'y' && back != 'N' && back != 'n');
                if (back == 'Y' || back == 'y')
                    MemberFunction();
                else 
                    printf("GOING BACK TO MAIN MENUE....\n");
            }
        }
    }
    
    return;
}

// Function that shows members specific information
void ViewMemberInfo()
{
    printf("Whose information do you want to see?\n");
    char line[MAX_LINE_LEN]; // lines loaded from the file
    int members_count = 0;

    FILE *file = fopen(MemberFile, "r");  // Opening the file

    if (!file)
    {
        printf("File Error\n");
        return;
    }
    
    // printing names from the file for selection
    while(fgets(line, sizeof(line), file))
    {
        printf("%i.) %s\n", ++members_count, strtok(line, ",\n"));
    } 
    printf("0.) Back\n");
    fclose(file);
   
    
    if (members_count == 0){ // When file is empty
        printf("There are no members here.\n");
    }

    int choice1, choice2, check1 = 1; //Choice1 is user's member choice while choice2 is field choice

    do // Getting choice1
    {
        printf("Choice: ");
        scanf("%d", &choice1);
        getchar(); // consume newline

        if (choice1 > members_count || choice1 < 0)
            printf("Invalid Choice\n");
    }     
    while(choice1 > members_count || choice1 < 0);

    if (choice1 == 0) // Back
        MemberFunction();
    else
    {
        do //Getting choice2
        {
            printf("What information do you want to see?\n"
                    "1.) Phone Number\n"
                    "2.) Account Details\n"
                    "3.) Amount to Pay\n"
                    "0.) Back\n"
                    "Choice: "
                );
            scanf("%d", &choice2);
            getchar(); // consume newline

            if (choice2 > 3 || choice2 < 0)
                printf("Invalid Choice\n");  
        }
        while(choice2 > 3 || choice2 < 0);

        if (choice2 == 0)
            ViewMemberInfo(); // Back
        else
        {
            // Opening member file
            FILE *file= fopen(MemberFile, "r");
            if (!file)
            {
                printf("File Error\n");
                return;
            }

            while (fgets(line, sizeof(line), file)) // While reading file line by line
            { 
                if (choice1 == check1) // When it sees the member that was chosen
                {
                    strcpy(person.name, strtok(line, ",\n")); // Saves name
                    strcpy(person.phone, strtok(NULL, ",\n"));  // Saves Phone Number
                    strcpy(person.AccountNumber, strtok(NULL, ",\n")); // Saves Account Number
                    strcpy(person.BankName, strtok(NULL, ",\n")); // Saves Bank Name
                    person.ToPay = atoi(strtok(NULL, ",\n")); // Saves Amount to Pay

                    printf("%s: ", person.name);

                    switch(choice2)
                    {
                        case 1: printf("%s\n", person.phone); break; // Prints name if asked
                        case 2: printf("%s (%s)\n", person.BankName, person.AccountNumber); break; // Prints Account Details if asked
                        case 3: printf("%.2f\n", person.ToPay); break; // Prints Amount to Pay if asked
                    }
                    break;
                }
                check1++;
            }
            fclose(file);

            // Going back
            char back;
            do {
                printf ("Would you like to go back to the menue you just came back from (Y/n)? ");
                scanf("%s", &back);
                getchar(); // consume newline
            }
            while(back != 'Y' && back != 'y' && back != 'N' && back != 'n');
            if (back == 'Y' || back == 'y')
                MemberFunction();
            else 
                printf("GOING BACK TO MAIN MENUE....\n");
        }
    }
    return;
}

void ViewAllMembers()
{
    char line[MAX_LINE_LEN]; // lines loaded from the file
    int members_count = 0;

    FILE *file = fopen(MemberFile, "r"); // Opening the file
    if (!file)
    {
        printf("File Error\n");
        return;
    }

    // Printing all
    printf("Name||Phone Number||Account Number||Bank Name||Amount to Pay\n");

    while(fgets(line, sizeof(line), file))
    {
        strcpy(person.name, strtok(line, ",\n")); // Saves name
        strcpy(person.phone, strtok(NULL, ",\n"));  // Saves Phone Number
        strcpy(person.AccountNumber, strtok(NULL, ",\n")); // Saves Account Number
        strcpy(person.BankName, strtok(NULL, ",\n")); // Saves Bank Name
        person.ToPay = atoi(strtok(NULL, ",\n")); // Saves Amount to Pay

        printf("%s||%s||%s||%s||%.2f\n", person.name, person.phone, person.AccountNumber, person.BankName, person.ToPay);
        members_count++;
    }

    fclose(file);

    if(members_count == 0) // When file is empty
        printf("No member is here\n");
    // Going back
    char back;
    do {
        printf ("Would you like to go back to the menue you just came back from (Y/n)? ");
        scanf(" %c", &back);
        getchar(); // consume newline
    }
    while(back != 'Y' && back != 'y' && back != 'N' && back != 'n');
    if (back == 'Y' || back == 'y')
        MemberFunction();
    else 
        printf("GOING BACK TO MAIN MENUE....\n"); 
    return;
}

void Payment()
{
    // Payment menue
    int choice;
    do{
    printf("______________________\n\n"

            "Do you want to :\n"
           "1.) View list of Paid Members\n"
           "2.) View list of unpaid Members\n"
           "3.) Mark as payed\n"
           "4.) Reset Payment Status of All Members\n"
           "0.) Back\n"
           "_______________________\n"
           "Choice: ");
    scanf("%d", &choice);
    getchar(); // consume newline
    if (choice > 4 || choice < 0)
        printf("Invalid Choice\n");    
    } 
    while(choice > 4 || choice < 0);
    switch (choice) {
        case 1: ListPaid(); break;
        case 2: ListUnPaid(); break;
        case 3: MarkPayment(); break;
        case 4: ResetPayment(); break;
        case 0: return;       
    }
    return;
}

void ListPaid()
{
    int i = 0;

    FILE *file = fopen(MemberFile, "r"); // Opening the file
    if (!file)
    {
        printf("File Error\n");
        return;
    }

    char line[MAX_LINE_LEN]; // lines loaded from the file

    while (fgets(line, sizeof(line), file))
    { 
        // Saving
        strcpy(person.name, strtok(line, ",\n"));// Saves name
        strcpy(person.phone, strtok(NULL, ",\n"));
        strcpy(person.AccountNumber, strtok(NULL, ",\n"));
        strcpy(person.BankName, strtok(NULL, ",\n"));
        person.ToPay = atoi(strtok(NULL, ",\n"));
        person.paid = atoi(strtok(NULL, ",\n"));
        
        if (person.paid == TRUE) // Checking
            printf("%i.) %s\n", ++i, person.name);
    }
    fclose(file);
    
    if (i == 0)
        printf("No one has paid yet\n");
    // Going back
    char back;
    do {
        printf ("Would you like to go back to the menue you just came back from (Y/n)? ");
        scanf("%s", &back);
        getchar(); // consume newline
    }
    while(back != 'Y' && back != 'y' && back != 'N' && back != 'n');
    if (back == 'Y' || back == 'y')
        Payment();
    else 
        printf("GOING BACK TO MAIN MENUE....\n"); 
    return;
}

void ListUnPaid()
{
    int i = 0;
    FILE *file = fopen(MemberFile, "r");
    if (!file)
    {
        printf("File Error\n");
        return;
    }
    char line[MAX_LINE_LEN]; // lines loaded from the file
    while (fgets(line, sizeof(line), file))
    { 
        // Saving
        strcpy(person.name, strtok(line, ",\n")); // Saves name
        strcpy(person.phone, strtok(NULL, ",\n"));
        strcpy(person.AccountNumber, strtok(NULL, ",\n"));
        strcpy(person.BankName, strtok(NULL, ",\n"));
        person.ToPay = atoi(strtok(NULL, ",\n"));
        person.paid = atoi(strtok(NULL, ",\n"));
        
        if (person.paid == FALSE) // Checking
            printf("%i.) %s\n", ++i, person.name);
    }
    fclose(file);
    if (i == 0)
        printf("Everyone has paid\n");
    char back;
    do {
        printf ("Would you like to go back to the menue you just came back from (Y/n)? ");
        scanf("%s", &back);
        getchar(); // consume newline
    }
    while(back != 'Y' && back != 'y' && back != 'N' && back != 'n');
    if (back == 'Y' || back == 'y')
        Payment();
    else 
        printf("GOING BACK TO MAIN MENUE....\n"); 
    return;
}

void MarkPayment()
{
    printf("Who paid?\n");
    char line[MAX_LINE_LEN]; // lines loaded from the file
    int members_count = 0;

    FILE *file = fopen(MemberFile, "r");
    if (!file)
    {
        printf("File Error\n");
        return;
    }
    
    while(fgets(line, sizeof(line), file))
    {
        printf("%i.) %s\n", ++members_count, strtok(line, ",\n"));
    }
    fclose(file);

    printf("0.) Back\n");
    if (members_count == 0){
        printf("There are no members here.\n");
    }
    int choice, check = 1;
    do
    {
        printf("Choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        if (choice > members_count || choice < 0)
            printf("Invalid Choice\n");
    }     
    while(choice > members_count || choice < 0);
    if (choice == 0)
        Payment();
    else
    {
        FILE *file= fopen(MemberFile, "r");
        FILE *temp = fopen("temp.csv", "w");
        if (!file || !temp)
        {
            printf("File Error\n");
            return;
        }
            
        while (fgets(line, sizeof(line), file))
        { 
            if (choice == check)
            {
                // Saving
                strcpy(person.name, strtok(line, ",\n")); // Saves name
                strcpy(person.phone, strtok(NULL, ",\n"));
                strcpy(person.AccountNumber, strtok(NULL, ",\n"));
                strcpy(person.BankName, strtok(NULL, ",\n"));
                person.ToPay = atoi(strtok(NULL, ",\n"));
                person.paid = atoi(strtok(NULL, ",\n"));

                person.paid = TRUE;

                fprintf(temp, "%s,%s,%s,%s,%.2f,%i\n", person.name, person.phone, person.AccountNumber, person.BankName, person.ToPay, person.paid);
            }
            else 
            {
                fprintf(temp, "%s", line);
            }
            check++;
        }
        fclose(file);
        fclose(temp);
        
        remove(MemberFile);
        rename("temp.csv", MemberFile);

        printf("Confirmed \n");
        char back;
        do {
            printf ("Would you like to go back to the menue you just came back from (Y/n)? ");
            scanf("%s", &back);
            getchar(); // consume newline
        }
        while(back != 'Y' && back != 'y' && back != 'N' && back != 'n');
        if (back == 'Y' || back == 'y')
            Payment();
        else 
            printf("GOING BACK TO MAIN MENUE...\n");
    }
    return;
}

void ResetPayment()
{
    char line[MAX_LINE_LEN]; // lines loaded from the file
    FILE *file= fopen(MemberFile, "r");
    FILE *temp = fopen("temp.csv", "w");
    if (!file || !temp)
    {
        printf("File Error\n");
        return;
    }
        
    while (fgets(line, sizeof(line), file))
    { 
        // Saving
        strcpy(person.name, strtok(line, ",\n")); // Saves name
        strcpy(person.phone, strtok(NULL, ",\n"));
        strcpy(person.AccountNumber, strtok(NULL, ",\n"));
        strcpy(person.BankName, strtok(NULL, ",\n"));
        person.ToPay = atoi(strtok(NULL, ",\n"));
        person.paid = atoi(strtok(NULL, ",\n"));

        person.paid = FALSE;

        fprintf(temp, "%s,%s,%s,%s,%.2f,%i\n", person.name, person.phone, person.AccountNumber, person.BankName, person.ToPay, person.paid);
    }
    fclose(file);
    fclose(temp);
    
    remove(MemberFile);
    rename("temp.csv", MemberFile);

    printf("All have been reset\n");

    char back;
    do {
        printf ("Would you like to go back to the menue you just came back from (Y/n)? ");
        scanf("%s", &back);
        getchar(); // consume newline
    }
    while(back != 'Y' && back != 'y' && back != 'N' && back != 'n');
    if (back == 'Y' || back == 'y')
        Payment();
    else 
        printf("GOING BACK TO MAIN MENUE....\n");
    return;
}

void TrackingList()
{
    int choice;
    do{
    printf("______________________\n\n"

            "Do you want to :\n"
           "1.) View Tracking list\n"
           "2.) Make Tracking List\n"
           "3.) Who's next on the list?\n"
           "4.) What is a 'Tracking List'?\n"
           "0.) Back\n"
           "_______________________\n"
           "Choice: ");
    scanf("%d", &choice);
    getchar(); // consume newline
    if (choice > 4 || choice < 0)
        printf("Invalid Choice\n");   
    } 
    while(choice > 4 || choice < 0);
    switch (choice) {
        case 1: ViewList(); break;
        case 2: MakeList(); break;
        case 3: DequeueList(); break;
        case 4: DefineTracking(); break;
        case 0: return;       
    }
    return;
}

void ViewList()
{
    char line[MAX_NAME_LEN];
    int k = 0;
    FILE *file = fopen(TrackingFile, "r");
    if (!file)
    {
        printf("File Error\n");
        return;
    }

    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\n")] = '\0';
        printf("%i.) %s\n", ++k, line);
    }
    if (k == 0)
        printf("No List has been generated \n");
    fclose(file);

    char back;
    do {
        printf ("Would you like to go back to the menue you just came back from (Y/n)? ");
        scanf("%s", &back);
        getchar(); // consume newline
    }
    while(back != 'Y' && back != 'y' && back != 'N' && back != 'n');
    if (back == 'Y' || back == 'y')
        TrackingList();
    else 
        printf("GOING BACK TO MAIN MENUE....\n");
    return;
}

void RandomList();
void WeightedList();

void MakeList()
{
    int choice;
    do{
    printf("______________________\n"

            "What method do you want to use:\n"
           "1.) Random List Generation\n"
           "2.) Weighted List Generation\n"
           "0.) Back\n"
           "_______________________\n"
           "Choice: ");
    scanf("%d", &choice);
    getchar(); // consume newline
    if (choice > 2 || choice < 0)
        printf("Invalid Choice\n");   
    } 
    while(choice > 2 || choice < 0);

    switch (choice) {
        case 1: RandomList(); break;
        case 2: WeightedList(); break;
        case 0: TrackingList(); break;       
    }
    return;
}

void RandomList()
{
    srandom(time(NULL));    
    FILE *member =  fopen(MemberFile, "r");
    FILE *list = fopen(TrackingFile, "w");
    if (!list || !member)
    {
        printf("File Error\n");
        return;
    }
    
    char line[MAX_LINE_LEN]; // lines loaded from the file
    int members_count = 0;
    
    Track* current = TrackList;
    Track *temp;

    while (fgets(line, sizeof(line), member))
    { 
        Track *t = malloc(sizeof(Track)); 
        if (t == NULL)
        {
            printf("Error in memory\n");
            return;
        }
        // Saving
        strcpy(t->name, strtok(line, ",\n")); // Saves name
        strcpy(person.phone, strtok(NULL, ",\n"));
        strcpy(person.AccountNumber, strtok(NULL, ",\n"));
        strcpy(person.BankName, strtok(NULL, ",\n"));
        t->ToPay = atoi(strtok(NULL, ",\n"));
        t->next = NULL;
        if (TrackList == NULL) // If queue is empty
            TrackList = t;
        else
        {
            current = TrackList; // Initialising a pointer that wil tranverse through the queue
            while (current->next != NULL) // Till it reaches close to the end
            {
                current = current->next;
            }
            current->next = t; // Connects the node}
        } 
        members_count++; 
    }

    if (members_count == 0) 
        printf("No members to list.\n");
    else
    {
        current = TrackList;

        int positions[members_count];

        for (int i = 0; i < members_count; i++) 
            positions[i] = i + 1; 
        for (int i = members_count - 1; i > 0; i--) 
        {
            int j = random() % (i + 1);
            int temp = positions[i];
            positions[i] = positions[j];
            positions[j] = temp;
        }
        for(int i = 0; current != NULL; i++, current = current->next)
            current->position = positions[i];
        //bubble sort
        int swapped;
        do 
        {
            swapped = 0;
            current = TrackList;
            Track* lastpoint = NULL;
            while(current->next != lastpoint)
            {
                int p = current->position, q = current->next->position;
                if(q < p)
                {
                    char tempName[MAX_NAME_LEN];

                    int tempPos = current->position;
                    strcpy(tempName, current->name);
                    int tempPaid = current->ToPay;

                    current->position = current->next->position;
                    strcpy(current->name, current->next->name);
                    current->ToPay = current->next->ToPay;

                    current->next->position = tempPos;
                    strcpy(current->next->name, tempName);
                    current->next->ToPay = tempPaid;

                    swapped = 1;
                }
                current = current->next;
            }
            lastpoint = current;
        }
        while(swapped == 1);

        current = TrackList;
        while (current != NULL) // Till it reaches the end
        {
            fprintf(list, "%s\n", current->name);
            current = current->next;
        }
        
        current = TrackList;
        while (current != NULL) // Till it reaches the end
        {
            if(current->ToPay == (2 * UNITPAY))
                fprintf(list, "%s\n", current->name);
            current = current->next;
        }
        printf("List Successfully Generated\n");
    }

    fclose(member);
    fclose(list);

    // free all
    current = TrackList;
    while (current != NULL)
    {
        temp = current->next;
        free(current);
        current = temp;
    }

    TrackList = NULL;

    char back;
    do {
        printf ("Would you like to go back to the menue you just came back from (Y/n)? ");
        scanf("%s", &back);
        getchar(); // consume newline
    }
    while(back != 'Y' && back != 'y' && back != 'N' && back != 'n');
    if (back == 'Y' || back == 'y')
        TrackingList();
    else 
        printf("GOING BACK TO MAIN MENUE....\n");
    return;
}

void WeightedList()
{
    FILE *member =  fopen(MemberFile, "r");
    FILE *list = fopen(TrackingFile, "w");

    if (!list || !member)
    {
        printf("File Error\n");
        return;
    }

    char line[MAX_LINE_LEN]; // lines loaded from the file
    int members_count = 0, twice = 0;

    Track* current = TrackList;
    Track *temp;

    while (fgets(line, sizeof(line), member))
    { 
        Track *t = malloc(sizeof(Track)); 

         if (t == NULL)
        {
            printf("Error in memory\n");
            return;
        }

        // Saving
        strcpy(t->name, strtok(line, ",\n")); // Saves name
        strcpy(person.phone, strtok(NULL, ",\n"));
        strcpy(person.AccountNumber, strtok(NULL, ",\n"));
        strcpy(person.BankName, strtok(NULL, ",\n"));
        t->ToPay = atoi(strtok(NULL, ",\n"));
        t->next = NULL;
        if (TrackList == NULL) // If queue is empty
            TrackList = t;
        else
        {
            current = TrackList; // Initialising a pointer that wil tranverse through the queue
            while (current->next != NULL) // Till it reaches close to the end
            {
                current = current->next;
            }
            current->next = t; // Connects the node}
        } 
        members_count++; 
    }

    while (current != NULL) // Till it reaches close to the end
    {
        if(current->ToPay == (2 * UNITPAY))
            twice++;
        current = current->next;
    }

    //bubble sort
    int swapped;
    do 
    {
        swapped = 0;
        current = TrackList;
        Track* lastpoint = NULL;
        while(current->next != lastpoint)
        {
            int p = current->ToPay, q = current->next->ToPay;
            if(p < q)
            {
                char tempName[MAX_NAME_LEN];

                strcpy(tempName, current->name);
                int tempPaid = current->ToPay;

                strcpy(current->name, current->next->name);
                current->ToPay = current->next->ToPay;

                strcpy(current->next->name, tempName);
                current->next->ToPay = tempPaid;

                swapped = 1;
            }
            current = current->next;
        }
        lastpoint = current;
    }
    while(swapped == 1);

    current = TrackList;
    while (current != NULL) // Till it reaches the end
    {
        fprintf(list, "%s\n", current->name);
        current = current->next;
    }

    current = TrackList;
    while (current != NULL) // Till it reaches the end
    {
        if(current->ToPay == (2 * UNITPAY))
            fprintf(list, "%s\n", current->name);
        current = current->next;
    }

    fclose(member);
    fclose(list);

    current = TrackList;
    while (current != NULL)
    {
        temp = current->next;
        free(current);
        current = temp;
    }

    TrackList = NULL;

    printf("List Successfully Generated\n");

    char back;
    do {
        printf ("Would you like to go back to the menue you just came back from (Y/n)? ");
        scanf("%s", &back);
        getchar(); // consume newline
    }
    while(back != 'Y' && back != 'y' && back != 'N' && back != 'n');
    if (back == 'Y' || back == 'y')
        TrackingList();
    else 
        printf("GOING BACK TO MAIN MENUE....\n");
    return;
}

void DequeueList()
{
    FILE *list = fopen(TrackingFile, "r");
    FILE *temp = fopen("temp.csv", "w");

    if (!list || !temp)
        printf("Error opening file.\n");
    else
    {
        char line[MAX_NAME_LEN], past[MAX_NAME_LEN], next[MAX_NAME_LEN];
        int i = 1;

        while(fgets(line, sizeof(line), list))
        {
            if (i == 1)
                strcpy(past, strtok(line, "\n"));
            else if( i == 2)
            {
                strcpy(next, strtok(line, "\n")); 
                fprintf(temp, "%s\n", next);
            }
            else
                fprintf(temp, "%s\n", strtok(line, "\n"));
            i++;
        }
        if ( i == 1)
            printf("No one is here.\n");
        else if (i == 2)
            printf("%s was paid\nThat's all.\n", past);
        else
            printf("%s was paid\nNext member: %s\n", past, next);

        fclose(list);
        fclose(temp);

        remove(TrackingFile);
        rename("temp.csv", TrackingFile);
    }
    char back;
    do {
        printf ("Would you like to go back to the menue you just came back from (Y/n)? ");
        scanf("%s", &back);
        getchar(); // consume newline
    }
    while(back != 'Y' && back != 'y' && back != 'N' && back != 'n');
    if (back == 'Y' || back == 'y')
        TrackingList();
    else 
        printf("GOING BACK TO MAIN MENUE....\n");
    return;
}

void DefineTracking()
{
    printf("____________________________________________________________________________________________\n\n"
    
           "Tracking List:\n"
           "  This list allocates the turns for recieveing the total contributions in a season.\n"
           "Weighted List:\n"
           "  This arrangement is based on how much the members paid (Descending order)(Bigger payers first).\n"
           "Random List:\n"
           "  This arrangement gives random positions to the members.\n\n"
           "Note:\n"
           "  According to the case study used to create this system members who pay 2 times the base amount are repeated twice on the list\n"
           "Current base amount : %d\n"
           "____________________________________________________________________________________________\n", UNITPAY);

    char back;
    do {
        printf ("Would you like to go back to the menue you just came back from (Y/n)? ");
        scanf("%s", &back);
        getchar(); // consume newline
    }
    while(back != 'Y' && back != 'y' && back != 'N' && back != 'n');
    if (back == 'Y' || back == 'y')
        TrackingList();
    else 
        printf("GOING BACK TO MAIN MENUE...\n");
    return;
}

void NewSeason()
{
    int choice;
    do {
        printf ("______________________\n\n"

                "A new season means:\n"
                "1.) New Tracking List.\n"
                "2.) Member changes\n"
                "3.) Reset Payment Status of All Members\n"
                "0.) Back\n"
                "______________________\n"
                "Choice: ");
        scanf("%i", &choice);
        getchar(); // consume newline
    
        if (choice > 3 || choice < 0)
            printf("Invalid Choice\n");   
    } 
    while(choice > 3 || choice < 0);

    switch (choice) {
        case 1: MakeList(); break;
        case 2: MemberFunction(); break;
        case 3: ResetPayment(); break;
        case 0: return;       
    }
}

/*  
The random list generation works by first creating random numbers 
Assigning it to the members available
Then arranging them in the list using bubble sort
note: special members come twice
*/
// They both use  singly linked lists
/*
The weighted list generation is made by using bubble sort to arrange the members based on pay
note: special members come twice
*/