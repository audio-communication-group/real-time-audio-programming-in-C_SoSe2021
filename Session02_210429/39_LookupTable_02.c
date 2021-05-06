/*************************************************************/
/**
 *  @file LookupTable_02.c
 *  @brief Example 2/3 of pointer to functions in a lookup table\n
 *
 *  @author Thomas Resch, thomas.resch@campus.tu-berlin.de\n
 *          Markus Hädrich, markus.haedrich@tu-berlin.de
 *
 *  @discussion Course: Real-Time Audio Programing in C\n
 *  Supervisors: Thomas Resch, Markus Hädrich, (TU-Berlin)\n
 *  "Object oriented programming in C - session 02"\n
 *
 *  @b Task: Add a member for a bling method to the @c registeredObject @c struct \n
 *  and a function for adding the bling method. Our bling method does not return \n
 *  anything and gets its instance as void pointer.
 *
 *  @code
 *         typedef void (*bling)(void *);
 *  @endcode
 *
 *  Also implement the bling method for @c t_one_int & @c t_two_int which should \n
 *  simply print their member values to the command line and attach them to \n
 *  the objects. Instead of calling @c printf call the bling methods from \n
 *  inside the main function.
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

/** @const n-1 chars that can be used to name the object type */
#define MAXOBJECTNAMESIZE 24

/** @const Number of objects that can be created */
#define MAXNUMBEROFOBJECTS 10

/** @typedef @c void pointer to a @c void function. */
typedef void* (*new)(void);

/** @typedef @c void pointer to a function, that takes one @c int parameter. */
typedef void* (*methodInt)(int);

/** @typedef @c void pointer to a function, that takes two @c int parameter. */
typedef void* (*methodIntInt)(int, int);


/** @typedef @c void function, that takes a function pointer */
typedef void (*bling)(void *);


/** @typedef struct holding an @c bling object. */
typedef struct _registeredIntObject
{
    char name[MAXOBJECTNAMESIZE]; /**< @c char array for the object name. */
    new newMethod;                /**< Pointer to the constructor method. */
    bling blingMethod;            /**< Pointer to the later added @c bling method. */
    int argc;                     /**< Arguments count. */
} t_registeredIntObject;


/** @brief Lookup table for your objects. */
t_registeredIntObject objectLookupTable[MAXNUMBEROFOBJECTS];

/** @var Just count the number of objects added to the lookup table later */
int currentIndex = 0;


/** @typedef struct with one @c int element only. */
typedef struct _one_int
{
    int val1;                   /**< Struct @c t_one_int variable. */
} t_one_int;


/**
 *  @brief Constructor function that takes a @c int value and returns a pointer\n
 *  to a new @c t_one_int struct.
 *  @param v1 @c int value of the new struct element.
 *  @return x @c void pointer to the new @c t_one_int object.
 */
void *one_int_new(int v1)
{   /**< Allocate memory for object @c x */
    t_one_int *x = (t_one_int *)malloc(sizeof(t_one_int));
    x->val1 = v1;                       /**< Set value */
    
    return (void *)x;                   /**< Cast @c x to @c void pointer */
}

/**
 *  @brief Method to print the data of a @c t_one_int object.
 *  @param x @c void pointer to an @c t_one_int object.
 */
void one_int_bling(void *x)
{
    printf("%d\n", ((t_one_int *)x)->val1);
}

/** @typedef struct with two @c int elements. */
typedef struct _two_int
{
    int val1;                       /**< Struct @c t_two_int variable. */
    int val2;                       /**< Struct @c t_two_int variable. */
} t_two_int;

/**
 *  @brief Constructor function for a @c t_two_int object, that takes two @c int\n
 *  values and returns a pointer to a new @c t_one_int struct object.
 *  @param v1 @c int value of the new struct element.
 *  @param v2 @c int value of the new struct element.
 *  @return x @c void pointer to the new @c t_one_int object.
 */
void *two_int_new(int v1, int v2)
{   /**< Allocate memory for object @c x */
    t_two_int *x = (t_two_int *)malloc(sizeof(t_two_int));
    
    x->val1 = v1;           /**< Set value */
    x->val2 = v2;           /**< Set value */
    
    return (void *)x;       /**< Cast @c x to @c void pointer */
}

/**
 *  @brief Method to print the data of a @c t_two_int object.
 *  @param x @c void pointer to an @c t_two_int object.
 */
void two_int_bling(void *x)
{
    printf("%d, %d\n", ((t_two_int *)x)->val1, ((t_two_int *)x)->val2);
}

/**
 *  @brief Function to register an object in the lookup table
 *  @param name @c char pointer to an array with the object name.
 *  @param m Method to initialize the new object.
 *  @param argc Lookup table index as arguments count.
 */
void registerObject(char *name, new m, int argc)
{
    strcpy(objectLookupTable[currentIndex].name, name);
    objectLookupTable[currentIndex].newMethod = (new)m;
    objectLookupTable[currentIndex].argc = argc;
    currentIndex++;
}

/**
 *  @brief Function to add a method of an object to the lookup table.
 *  @param name @c char pointer to an array with the object name.
 *  @param b Method of the object.
 *  @todo Error handling if object is not found in the lookup table.
 */
void addBling(char *name, bling b)
{
    // Get the index of the object in the lookup table
    int i = 0;
    while(i<MAXNUMBEROFOBJECTS)
    {
        if(!strcmp(name, objectLookupTable[i].name))
            break;
        
        i++;
    }
    
    // Add the method to the object
    objectLookupTable[i].blingMethod = b;
}

/**
 *  @brief Function that calls the @c blingMethod of a given object.
 *  @param name @c char pointer to an array with the object name.
 *  @param x @c void pointer to the given object.
 *  @todo Error handling if object is not found in the lookup table.
 */
void object_bling(char *name, void *x)
{
    // Get the index of the object in the lookup table
    int i = 0;
    while(i<MAXNUMBEROFOBJECTS)
    {
        if(!strcmp(name, objectLookupTable[i].name))
            break;
        i++;
    }
    
    // Call the @c blingMethod of the object pointed by @c x
    (objectLookupTable[i].blingMethod)(x);
}

/**
 *  @brief General initializer function.
 *  @param name @c char pointer to an array with the object name.
 *  @param argv Pointer to the arguments array (argument vector).
 *  @return @c void pointer to the new object.
 *  @todo Error handling if function returns @c NULL \n
 *  or @c i >= MAXNUMBEROFOBJECTS.
 */
void *newObject(char *name, int *argv)
{
    // Get the index of the object in the lookup table
    int i = 0;
    while (i<MAXNUMBEROFOBJECTS)
    {
        if(!strcmp(name, objectLookupTable[i].name))
            break;
        i++;
    }
    
    // Routines for each case
    if (objectLookupTable[i].argc == 1)
    {
        // Get the pointer to the matching initializer function.
        void* (*new_ptr)(int) =
        (methodInt)objectLookupTable[i].newMethod;
        
        // Call the initializer via the function pointer.
        return (new_ptr)(argv[0]);
    }
    
    else if (objectLookupTable[i].argc == 2)
    {
        // Get the pointer to the matching initializer function.
        void* (*new_ptr)(int, int) =
        (methodIntInt)objectLookupTable[i].newMethod;
        
        // Call the initializer via the function pointer.
        return (new_ptr)(argv[0], argv[1]);
    }
    
    else return NULL;
}





int main()
{
    // Imitation of setup in PD style
    // ==============================
    
    // Declaration of the Arrays that hold object data.
    int oneElementArray[1];
    int twoElementsArray[2];
    
    // Initialization of the Arrays with object data.
    oneElementArray[0] = 1;
    twoElementsArray[0] = 2;
    twoElementsArray[1] = 4;
    
    // Register object in the lookup table.
    registerObject("one_int",            // Name of the object
                   (new)one_int_new,     // Back casted new method pointer
                   1);                  // Number of arguments resp. argc
    
    // Cast back and add the method pointer to the lookup table object
    addBling("one_int",                  // Name of the object
             (bling)one_int_bling);      // Back casted bling method pointer
    
    // Register object in the lookup table.
    registerObject("two_int",            // Name of the object
                   (new)two_int_new,     // Back casted new method pointer
                   2);                  // Number of arguments resp. argc
    
    // Add method pointer to the lookup table object
    addBling("two_int",                  // Name of the object
             (bling)two_int_bling);      // Back casted bling method pointer
    
    
    
    // Imitation of new in PD style
    // ============================
    
    // Initialize the new objects and cast back the pointer
    t_one_int *a = (t_one_int*)newObject("one_int",            // Name of the object
                                       oneElementArray);    // Pointer to the arguments list resp. argv
    
    t_two_int *b = (t_two_int*)newObject("two_int",            // Name of the object
                                       twoElementsArray);   // Pointer to the arguments list resp. argv
    
    // Call the bling method to print the objects data to console.
    object_bling("one_int", a);
    object_bling("two_int", b);
    
    return 0;
}



/*
 *  Output:
 *      1
 *      2, 4
 */

