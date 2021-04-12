#include <stdio.h>

int main(void) {

    int length = 5;			// Length of array
    int anArray[length];	// Initialization
    int i = 0;				// Index of array
	
	/*
	condition is true {
		do something
	}
	*/
		

    while(i < length)					
    {
        anArray[i] = i;
        printf("%d %d\n", i, anArray[i]);
        i++;
    }


    for(i = 0; i < length; i++)
    {
        anArray[i] = i;
        printf("%d %d\n", i, anArray[i]);
    }

    return 0;
}

/*
Home work:
Write a 'while' and a 'for loop' that stores and outputs the value 'length - i' at the index i of the array.
*/

