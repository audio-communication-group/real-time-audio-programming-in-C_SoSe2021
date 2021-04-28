//
//  22_memset.c
//  Einführung in C
//

// http://users.ece.cmu.edu/~eno/coding/CCodingStandard.html

#include <stdio.h>
#include <stdlib.h> // Needed by malloc()
#include <string.h> // Needed by memset()

void fillWithMemset()
{
  char str[50] = "Real time audio programming in C"; 
  printf("\nBefore memset(): %s\n", str);

  // Fill 8 characters starting from str[13] with '.'
  // memset(start_pointer, var, var_count * sizeof(var))
  // Example: 
  // int arr[5] = {1,2,3,4,5};
  // memset(arr + 2, 0, 2*sizeof(int));
  memset(str + 10, '.', 5*sizeof(char));

  printf("After memset():  %s", str);
}

int main() {
    float *p_memory;
    int size = sizeof(float) * 5;
    p_memory = malloc(size);
    
    /* memset() takes value as (any) ASCII! Zero is a special case! */
    memset(p_memory, 0, (size));

    for (int i=0; i<5; i++) {
        printf("memory [%d]: %f\n", i, *(p_memory+i));
    }
    
    fillWithMemset();

    return 0;
}
