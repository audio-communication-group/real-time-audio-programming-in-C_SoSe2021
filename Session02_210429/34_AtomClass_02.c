/*************************************************************/
/**
 *  @file AtomClass_02.c
 *  @brief Example how to implement and use a constructors and destructors\n
 *  in PD style
 *  @author Thomas Resch, thomas.resch@campus.tu-berlin.de\n
 *          Markus Hädrich, markus.haedrich@tu-berlin.de
 *
 *  @discussion Course: Real-Time Audio Programing in C\n
 *  Supervisors: Thomas Resch, Markus Hädrich, (TU-Berlin)\n
 *  "Object oriented programming in C - session 02"
 *
 *  So far, our written C structs/classes neither have a constructor nor a\n
 *  destructor, we created them on the stack without dynamic memory allocation.\n
 *  So either we do it every time manually using @c malloc() and @c free() or\n
 *  we write a constructor/destructor function, that returns a pointer to our \n
 *  object. We can also use the constructor to initialize our members with \n
 *  default values.
 *
 *  @date 09.05.19. – first implementation
 *
 *  @bug You found one? Please report it!
 *
 *  @version 0.42
 **************************************************************/


#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Enum that is used in an atom struct type.
 * @enum Holds the defined data types of an atom struct type.
 */
enum simpleAtomTypes {UNDEFINED, INTEGER, FLOAT};

/**
 * @brief A simple class example.
 * @typedef @c struct type as workaround for the missing class feature in C
 */
typedef struct myClass {
    int type;               /**< Holding class type from @c simpleAtomTypes */
    float floatVal;         /**< Class data */
    int intVal;
} myClass;

/**
 * @brief Constructor function for myClass.
 * @return Pointer to the initialized myClass object.
 */
myClass *myClass_new()
{   /**< Allocate memory for object @c x */
    myClass *x = (myClass *)malloc(sizeof(myClass));
    
    x->type = FLOAT;        /**< Set class type */
    x->floatVal = 0.0;      /**< Set value */
    
    return x;
}

/*
 Task: Write the corresponding destructor which calls the free()
 function on our class. Write a class function that prints out "floatVal" or
 intVal, depending on the type..
 */

/**
 * @brief Destructor function for myClass.
 * @param x Pointer to myClass object to be freed.
 */
void myClass_free(myClass *x)
{

}

void myClass_print(myClass *x)
{

}


int main() {
    // Initialize a new object of myClass
    myClass *classInstance = myClass_new();
    
    // Use the object
    printf("%d\n", classInstance->type);
    
    // Free the object
    myClass_free(classInstance);
    
    return 0;
}


/*
    Output:
    2
 */
