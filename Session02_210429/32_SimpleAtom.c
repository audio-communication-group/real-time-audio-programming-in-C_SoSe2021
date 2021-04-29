
/*************************************************************/
/**
 *  @file SimpleAtom.c
 *  @brief Example of a simple atom type that is used in Pure Data
 *  @author Thomas Resch, thomas.resch@campus.tu-berlin.de\n
 *          Markus Hädrich, markus.haedrich@tu-berlin.de
 *
 *  @discussion Course: Real-Time Audio Programing in C\n
 *  Supervisors: Thomas Resch, Markus Hädrich, (TU-Berlin)\n
 *  "Object oriented programming in C - session 01"
 *
 *  @date 09.05.19. – first implementation
 *
 *  @bug You found one? Please report it!
 *
 *  @version 0.42
 **************************************************************/


#include <stdio.h>

/*
 
 Pure Data uses a different approach to achieve similar behaviour.
 It defines a new data type:
 
 t_atom
 
 The t_atom struct contains a member for a float, for a symbol and for
 several other things. It also contains a member for its type and
 corresponding setter functions (implemented as macros), for example
 
 SETFLOAT(atom, f)
 
 and getter functions
 
 t_float atom_getfloat(t_atom *a)
 
 When SETFLOAT is called, the atom’s type is set to float and the value f
 stored in the float member of the atom struct. When atom_getfloat() is called,
 the atom’s type is checked and if it is indeed a float it returns the float
 member of the atom. Among other things this technique allows for working with
 lists of mixed data (usually strings and floats).
 
 
 Task: Pure Data works internally with floats only, but let’s implement our
 own simple atom type which contains three members: the type (int or float as
 an enum value), and a member for a float and a member for an integer. Write
 the corresponding getter and setter functions and a function, that adds all
 elements of an atom array together.
 */

/**
 * @brief Enum that is used in an atom struct type.
 * @enum Holds the defined data types of an atom struct type.
 */
enum simpleAtomTypes {UNDEFINED, INTEGER, FLOAT};

/**
 * @brief A simple atom example.
 * @typedef A simple atom object type.
 */
typedef struct simpleAtom
{
    int type;           /**< Holding class type from @c simpleAtomTypes */
    int intVal;         /**< @c simpleAtom data: @c int variable. */
    float floatVal;     /**< @c simpleAtom data: @c float variable. */
} simpleAtom;
/**
 * @brief Function that sets the @c float var of a atom type.
 * @param a Pointer to an atom type object.
 * @param fVal @c float var
 */
void simpleAtom_setFloat(simpleAtom *a, float fVal)
{
    a->type = FLOAT;        /**< Set type */
    a->floatVal = fVal;     /**< Set data */
}

/**
 * @brief Function that sets the @c int var of a atom type.
 * @param a Pointer to an atom type object.
 * @param iVal @c int var
 */
void simpleAtom_setInt(simpleAtom *a, int iVal)
{

}

/**
 * @brief Function that gets the @c float var of a atom type.
 * @param a Pointer to an atom type object.
 * @return @c float var of the atom type.
 */
float simpleAtom_getFloat(simpleAtom *a)
{
    // check type, if type is float, return value..
}

/**
 * @brief Function that gets the @c int var of a atom type.
 * @param a Pointer to an atom type object.
 * @return @c int var of the atom type.
 */
int simpleAtom_getInt(simpleAtom *a)
{
    
}


/**
 * @brief Function that adds the elements of a atom type.
 * @param a Pointer to an atom type object.
 * @param size Length of the atom type.
 * @return @c int var of the atom type.
 */
float simpleAtom_addAll(simpleAtom *a, int size)
{
    
}

int main() {
    // Length of the atom type
    const int size = 2;
    
    // Var to hold the result
    float result = 0;
    
    // Declare a atom type
    simpleAtom myAtom[size];
    
    // Initialize the float var
    simpleAtom_setFloat(&myAtom[0], 5.5);
    // Initialize the int var
    simpleAtom_setInt(&myAtom[1], 67);
    
    // Call the function that adds all elements of the atom type
    result = simpleAtom_addAll(myAtom, size);
    
    // Print the result
    printf("%f\n", result);
    
    return 0;
}

/*
 Output:
 72.500000
 */

