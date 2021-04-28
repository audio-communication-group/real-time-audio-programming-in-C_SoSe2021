//
//  20_Calloc.c
//  Einführung in C
//

// http://users.ece.cmu.edu/~eno/coding/CCodingStandard.html

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, *ptr, sum = 0;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    
	// Calloc inits with zero
    ptr = (int*) calloc(n, sizeof(int));
    
    // Before writing to the memory
    for (int i=0; i<n; i++) {
        printf("value in memory %d\n", *(ptr+n));
    }
    
    // Error handling
    if(ptr == NULL) {
        printf("Error! memory not allocated.");
        exit(0);
    }
    
    printf("Enter elements:\n");
    for(int i=0; i<n; i++)
    {
        scanf("%d", ptr + i);
        sum += *(ptr + i);
    }
    
    printf("Sum = %d\n", sum);
    
    // After writing to the memory
    for (int i=0; i<n; i++) {
        printf("value in memory: %d\n", *(ptr+i));
    }
    
    free(ptr);
    
    return 0;
}

// Homework: Write a function that allocates memory for
// integers with calloc and returns the allocated
// memory as an int pointer.
// The function should have two int arguments:
// the number of integers to allocate, and a
// default value. Every int field of the allocated memory
// should be initialized with this default value.
// call this function from main instead of calling calloc
// directly.



