// 13_typedefs.c

#include <stdio.h>

// Typedef structure
typedef struct Biquad {
	float fs;   // Sample rate
    float fc;   // Cut off frequency
    float q;    // Quality
    float gain; // Gain for peak and shelving
    float a0;   // Filter parameter
    float a1;   // Filter parameter
    float a2;   // Filter parameter
    float b1;   // Filter parameter
    float b2;   // Filter parameter
} biquad_t;     // Define a Biquad type appending "_t"

// Helper function for printing struct parameters
void printParameters(biquad_t *filter) {
  	// Show parameters
    printf("\n\nfilter parameters:\nfs = %.2f\nfc = %.2f\nq = %.2f\ngain = %.2f\na0 = %f\na1 = %f\na2 = %f\nb1 = %f\nb2 = %f", filter->fs, filter->fc, filter->q, filter->gain, filter->a0, filter->a1, filter->a2, filter->b1, filter->b2);
}

int main() {
    // Instead of using "struct Biquad low_pass" we can use now "biquad_t" 
    biquad_t low_pass;      // Declaration
    low_pass.fc = 880.0;    // Initialisation of struct member fc
    low_pass.fs = 44100.0;  // Initialisation of struct member fs
    // ...

    // Initialisation of all struct members
    biquad_t high_shelf = {44100.0, 10000.0, 0.7071, 6.0, 1.505212, -0.842049, 0.342357, -0.171241, 0.176761};
    
    // Show parameters
    printParameters(&high_shelf);
    
    // Overwriting of struct member
    high_shelf.fc = 12000.0;

    // Show parameters
    printParameters(&high_shelf);

    return 0;
}

/*
Home work:
1. Write a function 'void resetFilter(biquad_t *filter)' that sets all struct members to zero!
2. Call this function at the end of the main(), put &high_shelf as parameter into it and print the filter coeffcients!

void setToZero(biquad_t *filter) {
	filter->fs = 0;
	filter->fc = 0;
	filter->q = 0;
	filter->gain = 0;
	filter->a0 = 0;
	filter->a1 = 0;
	filter->a2 = 0;
	filter->b1 = 0;
	filter->b2 = 0;
}
*/