#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTACTS 100

typedef struct {
    char *name;
    char *phone;
    char *email;
} Contact;

Contact *contacts = NULL;
int contact_count = 0;

// Function Prototypes
void load_contacts(const char *filename);
void save_contacts(const char *filename);
void add_contact();
void view_contacts();
void update_contact();
void delete_contact();
void free_contacts();

int main(void) {
    const char *filename = "contacts.csv";
    load_contacts(filename);

    int choice;
    do {
        printf("\n==== Contacts Menu ====\n");
        printf("1. View Contacts\n");
        printf("2. Add Contact\n");
        printf("3. Update Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Save & Exit\n");
        printf("=======================\n");
        printf("Choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice) {
            case 1: view_contacts(); break;
            case 2: add_contact(); break;
            case 3: update_contact(); break;
            case 4: delete_contact(); break;
            case 5: save_contacts(filename); break;
            default: printf("Invalid option\n");
        }
    } while (choice != 5);

    free_contacts();
    return 0;
}

void load_contacts(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return;

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        contacts = realloc(contacts, sizeof(Contact) * (contact_count + 1));

        char *name = strtok(line, ",\n");
        char *phone = strtok(NULL, ",\n");
        char *email = strtok(NULL, ",\n");

        contacts[contact_count].name = malloc(strlen(name) + 1);
        strcpy(contacts[contact_count].name, name);
        contacts[contact_count].phone = malloc(strlen(phone) + 1);
        strcpy(contacts[contact_count].phone, phone);
        contacts[contact_count].email = malloc(strlen(email) + 1);
        strcpy(contacts[contact_count].email, email);

        contact_count++;
    }
    fclose(file);
}

void save_contacts(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) return;

    for (int i = 0; i < contact_count; i++) {
        fprintf(file, "%s,%s,%s\n", contacts[i].name, contacts[i].phone, contacts[i].email);
    }
    fclose(file);
}

void add_contact() {
    char name[100], phone[100], email[100];

    printf("Enter name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    printf("Enter phone: ");
    fgets(phone, sizeof(phone), stdin);
    phone[strcspn(phone, "\n")] = 0;

    printf("Enter email: ");
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\n")] = 0;

    contacts = realloc(contacts, sizeof(Contact) * (contact_count + 1));

    contacts[contact_count].name = malloc(strlen(name) + 1);
    strcpy(contacts[contact_count].name, name);
    contacts[contact_count].phone = malloc(strlen(phone) + 1);
    strcpy(contacts[contact_count].phone, phone);
    contacts[contact_count].email = malloc(strlen(email) + 1);
    strcpy(contacts[contact_count].email, email);

    contact_count++;
}

void view_contacts() {
    if (contact_count == 0) {
        printf("No contacts available.\n");
        return;
    }
    for (int i = 0; i < contact_count; i++) {
        printf("%d. %s | %s | %s\n", i + 1, contacts[i].name, contacts[i].phone, contacts[i].email);
    }
}

void update_contact() {
    view_contacts();
    if (contact_count == 0) return;

    int index;
    printf("Enter contact number to update: ");
    scanf("%d", &index);
    getchar();

    if (index < 1 || index > contact_count) {
        printf("Invalid index.\n");
        return;
    }
    index--;

    char name[100], phone[100], email[100];
    printf("Enter new name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    printf("Enter new phone: ");
    fgets(phone, sizeof(phone), stdin);
    phone[strcspn(phone, "\n")] = 0;

    printf("Enter new email: ");
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\n")] = 0;

    free(contacts[index].name);
    free(contacts[index].phone);
    free(contacts[index].email);

    contacts[index].name = malloc(strlen(name) + 1);
    strcpy(contacts[index].name, name);
    contacts[index].phone = malloc(strlen(phone) + 1);
    strcpy(contacts[index].phone, phone);
    contacts[index].email = malloc(strlen(email) + 1);
    strcpy(contacts[index].email, email);
}

void delete_contact() {
    view_contacts();
    if (contact_count == 0) return;

    int index;
    printf("Enter contact number to delete: ");
    scanf("%d", &index);
    getchar();

    if (index < 1 || index > contact_count) {
        printf("Invalid index.\n");
        return;
    }
    index--;

    free(contacts[index].name);
    free(contacts[index].phone);
    free(contacts[index].email);

    for (int i = index; i < contact_count - 1; i++) {
        contacts[i] = contacts[i + 1];
    }
    contact_count--;
    contacts = realloc(contacts, sizeof(Contact) * contact_count);
}

void free_contacts() {
    for (int i = 0; i < contact_count; i++) {
        free(contacts[i].name);
        free(contacts[i].phone);
        free(contacts[i].email);
    }
    free(contacts);
}