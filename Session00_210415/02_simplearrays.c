#include <stdio.h>

int main(void) {
	int len = 2;		// Length of array, counting begins with zero
    int anArray[len];	// type name[length]
    anArray[0] = 20;	
    anArray[1] = 50;

    printf("%d %d", anArray[0], anArray[1]);
    return 0;
}

/*
Home work:
Add a second array for 10 floats and save the inverse of the index at index i.
*/

