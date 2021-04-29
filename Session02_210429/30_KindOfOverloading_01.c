

/*************************************************************/
/**
 *  @file KindOfOverloading_01.c
 *  @brief Example 1/2 how to implement overloading in C
 *  @author Thomas Resch, thomas.resch@campus.tu-berlin.de\n
 *          Markus Hädrich, markus.haedrich@tu-berlin.de
 *
 *  @discussion Course: Real-Time Audio Programing in C\n
 *  Supervisors: Thomas Resch, Markus Hädrich, (TU-Berlin)\n
 *  "Object oriented programming in C - session 01"
 *
 *  However, overloading for your own functions is not supported in C.
 *  There are different approaches for achieving this kind of behavior,
 *  all have advantages and disadvantages, depending on what you are trying
 *  to do.
 *
 *  @date 09.05.19. – first implementation
 *
 *  @bug You found one? Please report it!
 *
 *  @version 0.42
 **************************************************************/



#include <stdio.h>

/**
 * @brief Function that adds all elements of an @c int array
 * @param myArray Pointer to an @c int array
 * @param size Length of the array
 * @return int Sum of the array elements
 */
int addArray_int(int *myArray, int size) {
    int sum = 0;
    for (int i=0; i<size;i++)
        sum+=myArray[i];
    
    return sum;
}

/**
 * @brief Function that adds all elements of an @c float array
 * @param myArray Pointer to an @c float array
 * @param size Length of the array
 * @return int Sum of the array elements
 */
float addArray_float(float *myArray, int size) {
    float sum = 0;
    for (int i=0; i<size;i++)
        sum+=myArray[i];
    
    return sum;
}


int main() {
    // Generating data
    const int arraySize = 2;
    float floatArray[arraySize] = {1.1, 2.2};
    int intArray[arraySize] = {1, 2};
    
    // Working with the data
    printf("%f\n", addArray_float(floatArray, arraySize));
    printf("%d\n", addArray_int(intArray, arraySize));
    
    return 0;
}

/*
 Output:
 3.300000
 3
 */
