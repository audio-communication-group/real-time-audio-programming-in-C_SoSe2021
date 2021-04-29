
/*************************************************************/
/**
 * @file PointerToFunctions_03.c
 * @brief Example 3/3 how pointer to functions are used in PD\n
 *
 * @author Thomas Resch, thomas.resch@campus.tu-berlin.de\n
 *         Markus Hädrich, markus.haedrich@tu-berlin.de
 *
 * @discussion Course: Real-Time Audio Programing in C\n
 * Supervisors: Thomas Resch, Markus Hädrich, (TU-Berlin)\n
 * "Object oriented programming in C - session 02"\n
 *
 * @date 09.05.19. – first implementation
 *
 * @bug You found one? Please report it!
 *
 * @version 0.42
 **************************************************************/



#include <stdio.h>
#include <stdlib.h>


/** @typedef @c void pointer to a @c void function. */
typedef void* (*new)(void);

/** @typedef @c void pointer to a function, that takes one @c int parameter. */
typedef void* (*methodInt)(int);

/** @typedef @c void pointer to a function, that takes two @c int parameter. */
typedef void* (*methodIntInt)(int, int);


/** @typedef struct with one @c int element only. */
typedef struct _oneInt
{
    int val1;   /**< Struct @c int variable. */
} t_oneInt;


/**
 *  @brief Constructor function that takes a @c int value and returns a pointer\n
 *  to a new @c t_oneInt struct.
 *  @param v1 @c int value of the new struct element
 *  @return @c void pointer to the new struct.
 */
void *oneInt_new(int v1)
{   /**< Allocate memory for object @c x */
    t_oneInt *x = (t_oneInt *)malloc(sizeof(t_oneInt));
    x->val1 = v1;                   /**< Set value */
    
    return (void *)x;               /**< Cast @c x to @c void pointer */
}


/** @typedef struct with two @c int elements. */
typedef struct _twoInt
{
    int val1;                       /**< Struct @c int variable. */
    int val2;                       /**< Struct @c int variable. */
} t_twoInt;


/**
 *  @brief Constructor function that takes two @c int values and returns a\n
 *  pointer to a new @c t_twoInt struct.
 *  @param v1 @c int value of the new struct element.
 *  @param v2 @c int value of the new struct element.
 *  @return @c void pointer to the new struct.
 */
void *twoInt_new(int v1, int v2)
{   /**< Allocate memory for object @c x */
    t_twoInt *x = (t_twoInt *)malloc(sizeof(t_twoInt));
    x->val1 = v1;                   /**< Set value */
    x->val2 = v2;                   /**< Set value */
    return (void *)x;               /**< Cast @c x to @c void pointer */
}

/**
 *  @brief Constructor function that takes a pointer to a constructor function\n
 *  and an argument list/count
 *  @param m The objects method pointer.
 *  @param argv Arguments list used at function call.
 *  @param argc Arguments count of argument list used at function call.
 *  @return @c void pointer to the new struct object depending on arguments count @c argc.
 *  @todo Error handling if x = NULL
 */

void *intObject_new(new m, int *argv, int argc)
{
    if(argc == 1)
    {
        void* (*new_ptr)(int) = (methodInt)m;
        return (new_ptr)(argv[0]);
    }
    
    else if(argc == 2)
    {
        void* (*new_ptr)(int, int) = (methodIntInt)m;
        return (new_ptr)(argv[0], argv[1]);
    }
    
    else return NULL;
}

int main()
{
    // Prepare data to pass to to the initializer function.
    int oneElementArray[1];
    int twoElementsArray[2];
    
    oneElementArray[0] = 1;
    twoElementsArray[0] = 2;
    twoElementsArray[1] = 4;
    
    // Call init functions of t_oneInt and t_twoInt objects.
    t_oneInt *a = intObject_new((new)oneInt_new,    // Back casted new method pointer
                                oneElementArray,    // Pointer to the argumuents list resp. argv
                                1);                 // Number of arguments resp. argc
    
    t_twoInt *b = intObject_new((new)twoInt_new,    // Back casted new method pointer
                                twoElementsArray,   // Pointer to the argumuents list resp. argv
                                2);                 // Number of arguments resp. argc
    
    // Print results.
    printf("%d\n", a->val1);
    printf("%d, %d\n", b->val1, b->val2);
    
    return 0;
}


/*
    Output:
    1
    2, 4
 */
