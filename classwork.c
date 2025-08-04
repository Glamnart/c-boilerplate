#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    int *num = malloc(4 * sizeof(int));
    for (int i = 0; num[i] != '\0'; i++)
        num[i] = i;
    for (int i = 0; i < 4; i++)
        printf("%i ", num[i]);
    printf("\n");
    free(num);
}