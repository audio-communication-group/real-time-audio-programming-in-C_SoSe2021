//
//  05_1_Static.c
//  Einführung in C
//
// https://en.wikibooks.org/wiki/C_Programming/Variables
// http://users.ece.cmu.edu/~eno/coding/CCodingStandard.html

// gcc -o my_file 17_static_extern.c
// ./my_file

#include <stdio.h>
#include "17_static_extern_global_var.h"

static int j = 0; // j can only be accessed in this file, a global variable without the
//keyword static could also be accessed in other .c files. In order to use it in another file
// the variable has to be declared again with the keyword extern.

void up(void)
{
    /* k is set to 0 when the program starts. The line is then "ignored"
     * for the rest of the program (i.e. k is not set to 0 every time up()
     * is called)
     */
    static int k = 0;
    j++;
    k++;
    printf("up() called.   k= %2d, j= %2d\n", k , j);
}

void down(void)
{
    static int k = 0;
    j--;
    k--;
    printf("down() called. k= %2d, j= %2d\n", k , j);
}

int main(void)
{
    int i;
    
    /* call the up function 3 times, then the down function 2 times */
    for (i = 0; i < 3; i++)
        up();
    for (i = 0; i < 2; i++)
        down();
    
    up();
    
    return 0;
}

// Homework: Move the variable j to the file
// 17_StaticExternGlobalVar.c and access it in main.c with
// the keyword extern.
