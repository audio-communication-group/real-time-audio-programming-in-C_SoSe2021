// Swapping pointers vs. swapping values
 
#include <stdio.h>
#include <stdlib.h>

// http://users.ece.cmu.edu/~eno/coding/CCodingStandard.html


int main() {
	// Declare some vars and var_ptrs
	int x, y, temp_var, *a, *b, *temp_ptr;
	
	printf("\n------------------------------------\n");
	printf("--------- Swapping pointers --------\n");
	printf("------------------------------------\n\n");
	x = 42;
	y = 84;

	// Write the memory place of the data into the ptrs
	a = &x;
	b = &y;
	// Print the data by dereferencing the ptrs
	printf("*a = %d\t(in memory: %p)\n", *a, a);
	printf("*b = %d\t(in memory: %p)\n", *b, b);
	
	printf("\n\nSwap pointers:\n");
	temp_ptr = a;
	a = b;
	b = temp_ptr;
	
	// Print the data by dereferencing the ptrs again
	printf("*a = %d\t(in memory: %p)\n", *a, a);
	printf("*b = %d\t(in memory: %p)\n", *b, b);
	// Check the result
	printf("Result:\nx: %d\ny: %d\n*a: %d\n*b: %d\n", x, y, *a, *b);
	if (*b == x && *a == y) {
		printf("Pointers swapped!\n");
	} else {
		printf("Pointers not swapped!\n");
	}
	
	
	printf("\n------------------------------------\n");
	printf("--------- Swapping values ----------\n");
	printf("------------------------------------\n\n");
	x = 42;
	y = 84;
	// Write the memory place of the data into the ptrs
	a = &x;
	b = &y;
	// Print the data by dereferencing the ptrs
	printf("*a = %d\t(in memory: %p)\n", *a, a);
	printf("*b = %d\t(in memory: %p)\n", *b, b);

	printf("\n\nSwap values:\n");
	temp_var = *a;
	*a = *b;
	*b = temp_var;
	
	// Print the data by dereferencing the ptrs again
	printf("*a = %d\t(in memory: %p)\n", *a, a);
	printf("*b = %d\t(in memory: %p)\n", *b, b);
	// Check the result
	printf("Result:\nx: %d\ny: %d\n*a: %d\n*b: %d\n", x, y, *a, *b);
	if (*b == x && *a == y) {
		printf("Pointers swapped!\n");
	} else {
		printf("Pointers not swapped!\n");
	}
	
}