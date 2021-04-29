/*************************************************************/
/**
 *  @file KindOfOverloading_02.c
 *  @brief Example 2/2 how to implement overloading in C
 *  @author Thomas Resch, thomas.resch@campus.tu-berlin.de\n
 *          Markus Hädrich, markus.haedrich@tu-berlin.de
 *
 *  @discussion Course: Real-Time Audio Programing in C\n
 *  Supervisors: Thomas Resch, Markus Hädrich, (TU-Berlin)\n
 *  "Object oriented programming in C - session 01"
 *
 *  Task: Write a function, which takes the type as a first \n
 *  argument (a char pointer) and then chooses between the int \n
 *  and float version.\n
 *
 *  Hint: The array itself must be passed as a void pointer and \n#
 *  you also need to pass a void pointer for the result.\n
 *
 *  @date 09.05.19. – first implementation
 *
 *  @bug You found one? Please report it!
 *
 *  @version 0.42
 ************************************************************/


#include <stdio.h>
#include <string.h>


/**
 *  @brief Function that adds all elements of an @c int array in respect of
 *  the type parameter.
 *  @param type String that defines the array type.
 *  @param myArray Pointer to an @c int array.
 *  @param size Length of the array.
 *  @param result @c void pointer to the variable, where to write the result.
 */
void addArray(char *type, void *myArray, unsigned int size, void *result)
{
    //check type, sum all elements of the array and write it to result..
}


int main() {
    // Size of arrays
    const unsigned int size = 3;
    
    // Init arrays
    int i_arr[size] = {1, 2, 3};
    float f_arr[size] = {1., 2., 3.};
    
    // Result var
    int i_result;
    float f_result;
    
    // Call add functions
    addArray("int", (void*)(i_arr), size, &i_result);
    addArray("float", (void*)(f_arr), size, &f_result);
    
    // Write the results
    printf("Sum of int array: %d\n", i_result);
    printf("Sum of float array: %f\n", f_result);
    
    return 0;
}




