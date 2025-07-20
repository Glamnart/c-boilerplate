#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 

#define MAX_LEN 1024
#define ALPHA 26

int check_for_correct_CLA(int argc, char*argv[]);
int is_key_number_correct(int key);
void encrypt(char text[], int key);
void vowelratio(char text[]);

int main(int argc, char* argv[])
{
    char text[MAX_LEN+1];
    if (check_for_correct_CLA(argc, argv) == 1)
        return 1;
    int key = atoi(argv[1]);
    if (is_key_number_correct(key) == 1)
        return 1;
    printf("plaintext:  ");
    fgets(text, MAX_LEN + 1, stdin);
    vowelratio(text);
    encrypt(text, key);
    
}
int check_for_correct_CLA(int argc, char*argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s KEY\n", argv[0]);
        return 1;
    }
    return 0;
}
int is_key_number_correct(int key)
{
    if (key <= 0 || key >= ALPHA)
    {
        printf("The key cannot be less than 1 or greater than 25\n");
        return 1;
    } 
    return 0; 
}
void encrypt(char text[], int key)
{
    text[MAX_LEN] = '\0';   
    text[strcspn(text, "\n")] = '\0';
    for (int i = 0; i < MAX_LEN; i++) 
    {
    char c = text[i];
    if (isupper(c))  
        c = 'A' + (c - 'A' + key)%ALPHA;
    else if (islower(c)) 
        c = 'a' + (c - 'a' + key)%ALPHA;
    text[i] = c;
    }
    printf("ciphertext: %s\n", text);
}
void vowelratio(char text[])
{
    text[MAX_LEN] = '\0';   
    text[strcspn(text, "\n")] = '\0';
    int i, total = 0,vowels = 0;
    for(i = 0; text[i] != '\0'; i++)
    {
        if (isalpha(text[i]))
        {
            if (text[i] == 'a' || text[i] == 'e' || text[i] == 'i' || 
                text[i] == 'o' || text[i] == 'u' || text[i] == 'A' || 
                text[i] == 'E' || text[i] == 'I' || text[i] == 'O' || 
                text[i] == 'U' )
                vowels++;
            total++;
        }
    }
    float ratio = 100.0 * vowels/total; 
    printf("Vowels: %d/%d  (%.2f%%)\n", vowels, total, ratio);
}