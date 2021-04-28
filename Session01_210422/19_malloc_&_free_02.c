#include <stdio.h>
#include <stdlib.h>

// http://users.ece.cmu.edu/~eno/coding/CCodingStandard.html

void *theImpermanenceOfTheStack()
{
    int anIntArray[10];
    for (int i = 0;i < 10; i++)
        anIntArray[i] = i;

    int *ptr2IntArray = anIntArray;
    return NULL; // returning the ptr2Array pointer back
    // to main and accessing it from there would crash the
    // the programm. Try it!
}

void *thePermanentHeap()
{
    int *aHeapPointer = (int *)malloc(sizeof(int) * 10);
    if(aHeapPointer != NULL)
    {
        for (int i = 0;i < 10; i++)
            aHeapPointer[i] = i;
        return aHeapPointer;
    }
    else
        return NULL;
}

int main()
{
    int *ptr = (int *) thePermanentHeap();
    if(ptr != NULL)
    {
        printf("I can allocate memory somewhere else and access it here!\n");
        printf("%d\n", ptr[4]);
        free(ptr);
    }
    
    return 0;
}

// Homework: Write thePermanentHeap() function with pointer
// arithmetic instead of the array index access method:
// *aHeapPointer++ = i;
// In the main function print out all values instead of
// the index 4 only. Be careful
// what you return in thePermanentHeap() function!
