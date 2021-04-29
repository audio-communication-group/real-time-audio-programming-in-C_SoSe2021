/*************************************************************/
/**
 *  @file LookupTable_03.c
 *  @brief Example 3/3 how to use a lookup table in PD style \n
 *
 *  @author Thomas Resch, thomas.resch@campus.tu-berlin.de\n
 *          Markus Hädrich, markus.haedrich@tu-berlin.de
 *
 *  @discussion Course: Real-Time Audio Programing in C\n
 *  Supervisors: Thomas Resch, Markus Hädrich, (TU-Berlin)\n
 *  "Object oriented programming in C - session 02"\n
 *
 *  @b Task: Now we have to pass the class name together with the object to the \n
 *  @c object_bling() function which is not really necessary. Instead use the \n
 *  described inheritance mechanism and create a base class object which only \n
 *  holds the class name as a @c char array. Add the class name member to both \n
 *  @c structs @c intOne and @c intTwo too.
 *  In the @c newObject() function you store the name argument in the class \n
 *  name member.
 *
 *  @code
 *         typedef void (*bling)(void *);
 *  @endcode
 *
 *  Also implement the bling method for t_oneInt & t_twoInt which should simply \n
 *  print their member values to the command line and attach them to the \n
 *  objects. Instead of calling printf call the bling methods from inside the \n
 *  main function.
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


/** @const  n-1 chars that can be used to name the object type */
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
typedef void (*bling)(void*);


/** @typedef struct holding an @c bling object. */
typedef struct _registeredIntObject
{
    char name[MAXOBJECTNAMESIZE];           /**< @c char array for the object name. */
    new newMethod;                          /**< Pointer to the constructor method. */
    bling blingMethod;                      /**< Pointer to the later added @c bling method. */
    int argc;                               /**< Arguments count. */
} t_registeredIntObject;

/** @typedef struct holding an @c bling object. */
t_registeredIntObject objectLookupTable[MAXNUMBEROFOBJECTS];

/** @var Just count the number of objects added to the lookup table later */
int currentIndex = 0;


/** @typedef base class struct type */
typedef struct _object
{
    char className[MAXOBJECTNAMESIZE];  /**< @c char array holding class name*/
} t_object;

/** @typedef inherited resp. child class with one @c int element */
typedef struct _oneInt
{
    char className[MAXOBJECTNAMESIZE];  /**< @c char array holding class name*/
    int val1;                           /**< Class data */
} t_oneInt;


/**
 *  @brief Constructor function that takes a @c int value and returns a pointer\n
 *  to a new @c t_oneInt struct.
 *  @param v1 @c int value of the new struct element.
 *  @return x @c void pointer to the new @c t_oneInt object. This object has \n
 *  to been casted back before use.
 */
void *oneInt_new(int v1)
{   /**< Allocate memory for object @c x */
    t_oneInt *x = (t_oneInt *)malloc(sizeof(t_oneInt));
    x->val1 = v1;                       /**< Set value */
    
    return (void *)x;                   /**< Cast @c x to @c void pointer */
}


/**
 *  @brief Method to print the data of a @c t_oneInt object.
 *  @param x @c void pointer to an @c t_oneInt object.
 */
void oneInt_bling(void *x)
{
    /**< Casting @c x back to original @c t_oneInt before use. */
    printf("%d\n", ((t_oneInt *)x)->val1);
}


/** @typedef inherited resp. child class with two @c int elements */
typedef struct _twoInt
{
    char className[MAXOBJECTNAMESIZE];  /**< @c char array holding class name*/
    int val1;                           /**< Class data */
    int val2;                           /**< Class data */
} t_twoInt;


/**
 *  @brief Constructor function for a @c t_twoInt object, that takes two @c int \n
 *  values and returns a pointer to a new @c t_oneInt struct object.
 *  @param v1 @c int value of the new struct element.
 *  @param v2 @c int value of the new struct element.
 *  @return x @c void pointer to the new @c t_oneInt object. This object has \n
 *  to been casted back before use.
 */
void *twoInt_new(int v1, int v2)
{   /**< Allocate memory for object @c x */
    t_twoInt *x = (t_twoInt *)malloc(sizeof(t_twoInt));
    x->val1 = v1;                       /**< Set value */
    x->val2 = v2;                       /**< Set value */
    
    return (void *)x;                   /**< Cast @c x to @c void pointer */
}

/**
 *  @brief Method to print the data of a @c t_twoInt object.
 *  @param x @c void pointer to an @c t_twoInt object.
 */
void twoInt_bling(void *x)
{
    printf("%d, %d\n", ((t_twoInt *)x)->val1, ((t_twoInt *)x)->val2);
}


/**
 *  @brief Function to register an object in the lookup table.
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
        if(!strcmp(name, objectLookupTable[i].name)) {
            
            // Add the method to the object
            objectLookupTable[i].blingMethod = b;
            break;
        }
        
        i++;
    }
}


/**
 *  @brief Function that calls the @c blingMethod of a given object.
 *  @param x Pointer to the given object.
 *  @todo Error handling if object is not found in the lookup table.
 */
void object_bling(void *x)
{
    // Get the index of the object in the lookup table
    int i = 0;
    while(i<MAXNUMBEROFOBJECTS)
    {
        if(!strcmp(((t_object *)x)->className, objectLookupTable[i].name)) {
            
            // Call the @c blingMethod of the object pointed by @c x
            (objectLookupTable[i].blingMethod)(x);
            break;
        }
        i++;
    }
}

/**
 *  @brief General initializer function.
 *  @param name @c char pointer to an array with the object name.
 *  @param argv Pointer to the arguments array (argument vector).
 *  @return x @c void pointer to the new object.
 *  @todo Error handling if function returns @c NULL \n
 *  or @code i >= MAXNUMBEROFOBJECTS. @endcode
 */
void *newObject(char *name, int *argv)
{
    // Void pointer for holding new object pointer.
    void *x = NULL;
    
    // Get the index of the object in the lookup table.
    int i = 0;
    while(i<MAXNUMBEROFOBJECTS)
    {
        if(!strcmp(name, objectLookupTable[i].name))
            break;
        i++;
    }
    
    // Routines for each case.
    if (objectLookupTable[i].argc == 1)
    {
        // Get the pointer to the matching initializer function.
        void* (*new_ptr)(int) =
        (methodInt) objectLookupTable[i].newMethod;
        
        // Call the initializer via the function pointer.
        x = (new_ptr)(argv[0]);
        strcpy(((t_object *)x)->className, name);
    }
    
    if (objectLookupTable[i].argc == 2)
    {
        // Get the pointer to the matching initializer function.
        void* (*new_ptr)(int, int) =
        (methodIntInt)objectLookupTable[i].newMethod;
        
        // Call the initializer via the function pointer.
        x = (new_ptr)(argv[0], argv[1]);
        strcpy(((t_object *)x)->className, name);
    }
    
    // Return pointer to the new object.
    return x;
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
    
    // Register objects in the lookup table.
    registerObject("oneint",                // Name of the object
                   (new)oneInt_new,         // Back casted new method pointer
                   1);                      // Number of arguments resp. argc
    
    addBling("oneint",                      // Name of the object
             (bling)oneInt_bling);          // Back casted bling method pointer
    
    registerObject("twoint",
                   (new)twoInt_new,         // Back casted new method pointer
                   2);                      // Number of arguments resp. argc
    
    // Add method pointer to the lookup table object
    addBling("twoint",                      // Name of the object
             (bling)twoInt_bling);          // Back casted bling method pointer
    
    // Initialize the new objects
    t_oneInt *a = (t_oneInt*)newObject("oneint",    // Name of the object
                                       oneElementArray);         // Pointer to the arguments
    // list resp. argv
    
    t_twoInt *b = (t_twoInt*)newObject("twoint",    // Name of the object
                                       twoElementsArray);        // Pointer to the arguments
    // list resp. argv
    
    // Call method that prints the object data to console.
    object_bling(a);
    object_bling(b);
    
    return 0;
}



/*
 Output:
 1
 2, 4
 */



