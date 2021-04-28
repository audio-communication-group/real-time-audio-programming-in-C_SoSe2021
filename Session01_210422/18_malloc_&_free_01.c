//
//  17_Malloc.c
//  Einführung in C
//
//  Created by mr.markuese on 10.04.19.
//  Copyright © 2019 mr.markuese. All rights reserved.
//

// http://users.ece.cmu.edu/~eno/coding/CCodingStandard.html

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int n, i, *ptr, sum = 0;
	printf("%p",ptr);
	
    printf("Enter number of elements: ");
    scanf("%d", &n);

    ptr = (int*) malloc(n * sizeof(int));


    // Before writing to the memory
    for (int i=0; i<n; i++) {
        printf("memory initialized with %d\taddress: %p\n", *(ptr+i), (ptr+i));
    }

    // Error handling
    if(ptr == NULL) {
        printf("Error! memory not allocated.");
        exit(0);
    }

    printf("Enter elements: \n");
    for(i = 0; i < n; ++i) {
        scanf("%d", ptr + i);
        sum += *(ptr + i);
    }

    printf("Sum = %d\n", sum);

    // After writing to the memory
    for (int i=0; i<n; i++) {
        printf("value in memory: %d\taddress: %p\n", *(ptr+i), (ptr+i));
		
    }
	
	// Release memory (important!)
    free(ptr);
   

    return 0;
}


