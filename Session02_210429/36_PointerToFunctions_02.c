/*************************************************************/
/**
 * @file PointerToFunctions_02.c
 * @brief Example 2/3 how pointer to functions are used in PD\n
 *
 * @author Thomas Resch, thomas.resch@campus.tu-berlin.de\n
 *         Markus Hädrich, markus.haedrich@tu-berlin.de
 *
 * @discussion Course: Real-Time Audio Programing in C\n
 * Supervisors: Thomas Resch, Markus Hädrich, (TU-Berlin)\n
 * "Object oriented programming in C - session 02"\n\n
 *
 * A function pointer is not compatible with a regular pointer.
 * You are not allowed to cast a function pointer to a simple void pointer.
 * Casting a function pointer to a function pointer of another kind is allowed,
 * however, correct behaviour is only guaranteed if it is casted back to its
 * original type.
 *
 * @date 09.05.19. – first implementation
 *
 * @bug You found one? Please report it!
 *
 * @version 0.42
 **************************************************************/

#include <stdio.h>

/**
 * @brief Function that sums two @c int values.
 * @param a First summand.
 * @param b Second summand.
 * @return int Sum of the both @c int parameter values.
 */
int sum(int a, int b) {
    return a + b;
}


/**
 * @brief Function that multiplies two @c int values.
 * @param a First factor.
 * @param b Second factor.
 * @return @c int product of the both @c int parameter values.
 */
int mul(int a, int b) {
    return a * b;
}


/**
 * @brief Function that takes a pointer to another math function\n
 *        that will process the two other passed parameter values.
 * @param OpType Pointer to a function the takes two @c int as parameter\n
 *        and returns an @c int as result.
 * @param a First @c int paramter to process.
 * @param b Second @c int paramter to process.
 * @return @c int result of the math operation.
 */
int mathOp(int (*OpType)(int, int), int a, int b) {
    return OpType(a, b);
}


int main()
{
    printf("%i,%i\n", mathOp(&sum, 10, 12), mathOp(&mul, 10, 2));
    return 0;
}


/*  Output:
 *  22,20
 */

