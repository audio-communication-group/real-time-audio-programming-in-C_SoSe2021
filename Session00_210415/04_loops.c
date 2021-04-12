#include <stdio.h>
#include <math.h>

int main() {

    int length = 5;
    int an_array[length];
    int j = 0;

    // While loop
    while(j < length)               // Condition
    {
        an_array[j] = (int) pow(j,2);
        j++;
    }


    // For loop
    // The scope of i is inside the loop
    for (int i = 0; i < length; i++)    // Condition
    {
        printf("an_array[%d] = %d\n", i, an_array[i]);
    }

    // Do-while loop
    // The scope of i is outside the loop
    // Casting:  (type_name) expression
    int i = ( ( (int)(sizeof(an_array)/sizeof(int)) ) - 1);
    do {
        printf("an_array[%d] = %d\n", i, an_array[i]);
        i--;

    } while (i > 0);                // Condition

    return 0;
}

/*
Home work:
Write a while-loop analogous to the do-while loop that
starts at length-1 and iterates to 0. At index i save the value 'i*i'.
Tip: Use the function pow(), including math.h header with #include after #include <stdio.h>.
*/

