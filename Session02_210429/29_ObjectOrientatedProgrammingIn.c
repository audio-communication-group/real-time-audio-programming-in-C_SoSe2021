/*************************************************************/
/**
 *  @file ObjectOrientatedProgrammingIn.c
 *  @brief Example how to use structs
 *  @author Thomas Resch, thomas.resch@campus.tu-berlin.de
 *
 *  @discussion Course: Real-Time Audio Programing in C\n
 *  Supervisors: Thomas Resch, Markus Hädrich, (TU-Berlin)\n
 *  "Object oriented programming in C - session 01"
 *
 *  C has no classes and therefore no class member functions. But structs \n
 *  are basically classes and have struct members (variables). They can be \n
 *  accessed with the . (dot/point) or the -> (arrow) operator, depending on \n
 *  whether a pointer or a value is dereferenced.
 *
 *  @date 09.05.19. – first implementation
 *
 *  @bug You found one? Please report it!
 *  @version 0.42
 **************************************************************/



#include <stdio.h>


/**
 * @typedef struct that holds two @c int vars.
 * @brief Use customized (and nested) structs to simulate objects in C.
 * @discussion A typedef of a node of a circular doubly linked list.
 */
typedef struct AStruct {
    int memberOne;      /**< object variable one. */
    int memberTwo;      /**< object variable one. */
} aStruct;

/**
 * @brief Function to insert a new node at given index.
 * @param x pointer to a struct of type aStruct.
 * @discussion In object-oriented programming it is possible to define member
 * functions. In C that would mean defining a function inside a struct. That
 * is not possible. Instead we have to imitate, what compilers in object-
 * oriented programming languages do for us and pass our struct as a pointer
 * argument to our class function.
 */
void aStruct_aMemberFunctionThatPrints(aStruct *x)
{
    printf("member one: %d\n", x->memberOne);
    printf("member two: %d\n", x->memberTwo);
}

int main()
{
    // Declaration
    aStruct myStruct01, myStruct02;
    
    // Initialization of the struct elememts
    myStruct01.memberOne = 1;
    myStruct01.memberTwo = 2;
    
    // Access the struct elements
    printf("\nmyStruct01:\n");
    printf("member one: %d\n", myStruct01.memberOne);
    printf("member two: %d\n", (&myStruct01)->memberTwo);
    
    // Initialization of the struct elememts
    myStruct02.memberOne = 3;
    myStruct02.memberTwo = 4;
    printf("\nmyStruct02:\n");
    
    // Call a function that accesses the struct elements
    aStruct_aMemberFunctionThatPrints(&myStruct02);
    
    return 0;
}

/*
 Output:
 myStruct01:
 Member one: 1
 Member two: 2
 
 myStruct02:
 Member one: 3
 Member two: 4
 */






