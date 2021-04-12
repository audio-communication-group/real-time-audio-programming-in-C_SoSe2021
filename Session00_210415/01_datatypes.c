#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

// Every c program has exact one main() funcuz
int main()
{
    short short_type = 255;      					// Declaration and initialization of short type (both in one step)
    int integer_type;           					// Declaration of integer type
    integer_type = 1000000;      					// Initialization of integer type
    
    float float_type = 0.000001;					// Declaration and initialization of float type
    double double_type = 0.000000000000002;			// Declaration and initialization of double type
    long double long_double_type = 0.3;				// Declaration and initialization of long double type
    
    char char_type = 'c';							// Declaration and initialization of char type
    
    bool bool_type = true;        					// Declaration and initialization of bool type
													// C99, without #include <stdbool.h>
    
    // Sizeof operator is used to evaluate the size of a variable
    printf("Size of short: %lu bytes\n",sizeof(short_type));
    // SHRT_MIN, SHRT_MAX are macros defined in header limits.h
    printf("Short min: %d, max: %d bytes\n", SHRT_MIN, SHRT_MAX);
    
    printf("Size of int: %ld bytes\n",sizeof(integer_type));
    printf("Size of float: %ld bytes\n",sizeof(float_type));
    printf("Size of double: %ld bytes\n",sizeof(double_type));
    printf("Size of long double: %ld bytes\n",sizeof(long_double_type));
    printf("Size of bool: %ld byte\n",sizeof(bool_type));
    printf("Size of char: %ld byte\n",sizeof(char_type));
    
    return 0;
}

/*
Home work:
Add printf statements that output the values of the 8 variables.
Float values can be formatted with % f. With '% .4f' the accuracy can be limited to 4 decimal places, for example.
Bool can also be formatted with %d, char either with %c or %d (see the different output)
*/

