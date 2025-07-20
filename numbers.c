#include <stdio.h>
#include "include/input_utils.h"

#define size 7

void bubble_sort(int numbers[]);
int binarysearch(int target, int numbers[]);

int main (void)
{
    int numbers [size]= {70,93,32,90,7,80,28};
    bubble_sort(numbers);
    int target = get_int("Number to search for: ");
    int index = binarysearch(target, numbers);
    if (index == -1)
    {
        printf("Number not found.\n");
        return 1;
    }
    printf("Number found at index %i in the array.\n", index);
    printf("[ ");
    for (int i = 0; i < size; i++)
        printf("%i ", numbers[i]);
    printf("]\n");
    return 0;
}
void bubble_sort(int numbers[])
{
    int tempstore;
    for (int k = 0; k < size; k++)
    {
        int swap = 0;
        for (int i = 0; i < (size - 1); i++)
        {
            if (numbers[i] > numbers[i+1])
            {
                tempstore = numbers[i];
                numbers[i] = numbers[i+1];
                numbers[i+1] = tempstore;
                swap++;
            }
        }
        if (swap == 0)
            break;
    }
}

int binarysearch(int target, int numbers[])
{
    int high = size - 1, low = 0; 
    while (high >= low){
    int mid = (high + low)/2;
    if (numbers[mid] == target) 
        return mid; 
    else if (numbers[mid] < target)
        low = mid + 1;
    else 
        high = mid - 1;
  
    }
    return -1; 
}