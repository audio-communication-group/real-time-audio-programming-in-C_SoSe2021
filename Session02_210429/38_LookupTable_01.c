/*************************************************************/
/**
 *  @file LookupTable_01.c
 *  @brief Example 1/3 of pointer to functions in a lookup table\n
 *
 *  @author Thomas Resch, thomas.resch@campus.tu-berlin.de\n
 *          Markus Hädrich, markus.haedrich@tu-berlin.de
 *
 *  @discussion Course: Real-Time Audio Programing in C\n
 *  Supervisors: Thomas Resch, Markus Hädrich, (TU-Berlin)\n
 *  "Object oriented programming in C - session 02"\n
 *
 *  @b Task: Instead of calling @c intObject_new() and passing the constructor
 *  directly, implement a global lookup table (with fixed length) where
 *  objects can be registered with their name, their @c new_method() and their
 *  number of arguments. The corresponding @c object_new() function then needs
 *  two arguments: the name of the object and the arguments for the object.
 *  On calling @c object_new() the function searches in the lookup table for the
 *  right object by comparing the char arrays and calls the corresponding
 *  contructor.
 *
 *  A few hints in C and pseudo code (in upper case):
 *  @code
 *         typedef struct RegisteredIntObject {
 *              char name[25];
 *              method newMethod;
 *              int argc;
 *          } _registeredIntObject;
 *
 *          GLOBAL ARRAY registeredObject[10];
 *          GLOBAL INT currentIndex = 0;
 *
 *          REGISTEROBJECT(OBJECT_NAME, NEW_METHOD, ARGC) {
 *              INSERTOBJECT_AT_CURRENT_INDEX_INTO(registeredObjects);
 *              INCREASE_CURRENT_INDEX;
 *          }
 *
 *          NEWOBJECT(OBJECT_NAME, ARGV) {
 *              SEARCH_IN_REGISTEREDOBJECTS_FOR_OBJECT();
 *              CALL_THE_CORRESPONDING_NEW_METHOD_WITH_ARGV();
 *          }
 *  @endcode
 *
 *  @date 09.05.19. – first implementation
 *
 *  @bug You found one? Please report it!
 *
 *  @version 0.42
 **************************************************************/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/** @const Number + 1 chars that can be used to name the object type */
#define MAX_OBJECT_NAME_SIZE 24

/** @const Number of objects that can be created */
#define MAX_NUMBER_OF_OBJECTS 10


/** @typedef @c void pointer to a @c void function. */
typedef void* (*new)(void);

/** @typedef @c void pointer to a function, that takes one @c int parameter. */
typedef void* (*methodInt)(int);

/** @typedef @c void pointer to a function, that takes two @c int parameter. */
typedef void* (*methodIntInt)(int, int);

/** @typedef struct holding an @c int object. */
typedef struct _registeredIntObject
{
    char name[MAX_OBJECT_NAME_SIZE];	/**< @c char array for the object name. */
    new newMethod;                  	/**< Object Constructor */
    int argc;                       	/**< Arguments count */
} t_registeredIntObject;

/** @typedef struct with one @c int element only. */
typedef struct _oneInt {
    int val1;                       /**< Struct @c t_oneInt variable. */
} t_oneInt;

/**
 *  @brief Constructor function that takes a @c int value and returns a pointer\n
 *  to a new @c t_oneInt struct.
 *  @param v1 @c int value of the new struct element.
 *  @return x Pointer to the new struct.
 */
void *oneInt_new(int v1) {
    /**< Allocate memory for object @c x */
    t_oneInt *x = (t_oneInt *)malloc(sizeof(t_oneInt));
    x->val1 = v1;                   /**< Set value */
    return (void *)x;               /**< Cast @c x to @c void pointer */
}


/** @typedef struct with two @c int elements. */
typedef struct _twoInt {
    int val1;                       /**< Struct @c t_twoInt variable. */
    int val2;                       /**< Struct @c t_twoInt variable. */
} t_twoInt;

/**
 *  @brief Constructor function that takes two @c int values and returns \n
 *  pointer to a new @c t_twoInt struct.
 *  @param v1 first @c int value of the new struct element.
 *  @param v2 second @c int value of the new struct element.
 *  @return x @c void pointer to the new struct.
 */
void *twoInt_new(int v1, int v2) {
    /**< Allocate memory for object @c x */
    t_twoInt *x = (t_twoInt *)malloc(sizeof(t_twoInt));
    x->val1 = v1;                   /**< Set value */
    x->val2 = v2;                   /**< Set value */
    
    return (void *)x;               /**< Cast @c x to @c void pointer */
}

/** @brief Lookup table for your objects. */
t_registeredIntObject objectLookupTable[MAX_NUMBER_OF_OBJECTS];

/** @var Just count the number of objects added to the lookup table later */
int currentIndex = 0;

/**
 *  @brief Function that registers your objects in your object lookup table.
 *  @param name Name of the object to register.
 *  @param m @c new method to initialize the object.
 *  @param argc Arguments list passed at function call.
 */
void registerObject(char *name, new m, int argc)
{
    strcpy(objectLookupTable[currentIndex].name, name);
    objectLookupTable[currentIndex].newMethod = (new)m;
    objectLookupTable[currentIndex].argc = argc;
    currentIndex++;
}

/**
 *  @brief Initializer of a new object.
 *  @discussion This function first searches the object for the name in the \n
 *  lookup table. When the object is found, it calls the stored initializer \n
 *  using its function pointer and passes the dedicated initialization values \n
 *  and returns a pointer to the new object. Otherwise, the function returns \
 *  NULL.
 *  @param name Object name.
 *  @param argv Pointer to the @c int arguments array (argument vector).
 *  @return @c void pointer to the new object.
 *  @todo Error handling if function returns @c NULL \n
 *  or @c i >= MAX_NUMBER_OF_OBJECTS.
 */

void *newObject(char *name, int *argv)
{
    // Index of object count
    int i = 0;
    // Finding object index in lookup table
    while(i<MAX_NUMBER_OF_OBJECTS)
    {   /** @brief Find index of the object in the lookup table */
        if(!strcmp(name, objectLookupTable[i].name))
            break;
        
        i++;
    }
   
    
    // Routines for each case
    if(objectLookupTable[i].argc == 1)
    {
        /** @brief Pointer to right initializer function. */
        void* (*new_ptr)(int) =
        (methodInt)objectLookupTable[i].newMethod;
        
        /** @brief Call the initializer via the function pointer. */
        return (new_ptr)(argv[0]);
    }
    
    else if(objectLookupTable[i].argc == 2)
    {
        /** @brief Pointer to right initializer function. */
        void* (*new_ptr)(int, int) =
        (methodIntInt)objectLookupTable[i].newMethod;
        
        /** @brief Call the initializer via the function pointer. */
        return (new_ptr)(argv[0], argv[1]);
    }
    
    else return NULL;
}



int main()
{
    // Declaration of the Arrays that hold object data.
    int oneElementArray[1];
    int twoElementsArray[2];
    
    // Initialization of the Arrays with object data.
    oneElementArray[0] = 1;
    twoElementsArray[0] = 2;
    twoElementsArray[1] = 4;
    
    // Register object in the lookup table.
    registerObject("oneint",            // Name of the object
                   (new)oneInt_new,     // Back casted new method pointer
                   1);                  // Number of arguments resp. argc
    
    // Register object in the lookup table.
    registerObject("twoint",            // Name of the object
                   (new)twoInt_new,     // Back casted new method pointer
                   2);                  // Number of arguments resp. argc
    
    // Initialize the new objects and cast back the pointer
    t_oneInt *a = (t_oneInt*)newObject("oneint",    // Name of the object
                                       oneElementArray);       // Pointer to the argumuents list resp. argv
    
    t_twoInt *b = (t_twoInt*)newObject("twoint",    // Name of the object
                                       twoElementsArray);      // Pointer to the argumuents list resp. argv
    
    // Print objects data to console.
    printf("%d\n", a->val1);
    printf("%d, %d\n", b->val1, b->val2);
    
    return 0;
}


/*
 *  Output:
 *      1
 *      2, 4
 */





