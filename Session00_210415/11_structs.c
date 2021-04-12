#include <stdio.h>

// Structures that are holding filter parameters
// In structure each member get separate space in memory
struct Biquad {
    float fs;          // Sample rate
    float fc;          // Cut off frequency
    float q;           // Quality
    float gain;        // Gain for peak and shelving
    float a0;          // Filter parameter
    float a1;          // Filter parameter
    float a2;          // Filter parameter
    float b1;          // Filter parameter
    float b2;          // Filter parameter
} biquad_01, biquad_02, biquad_03; // Declaration of three structs biquad_01, biquad_02, biquad_03


int main() {
    biquad_02.fs = 441000;

    struct Biquad biquad_04; // Declaration
    biquad_04.fc = 10000;    // Initialisation of biquad_04 struct member fc

    struct Biquad biquad_05 = {441000, 8000 };
    biquad_05.q = 0.7071;
    
    printf("biquad_05: %f,%.1f,%.1f,%.1f\n", biquad_05.fs, biquad_05.fc, biquad_05.q, biquad_05.gain);
    // Auto initialized: 0 for integers, 0.0 for floating-point, and NULL for pointers
    
    return 0;
}

/*
Home work:
Complete the missing parameters for biquad_01 through biquad_05 with realistic values for
lowpass, highpass, bandpass, notch and peak filters! 
Tip: Take a look at: https://www.earlevel.com/main/2013/10/13/biquad-calculator-v2/

// Lowpass
biquad_01.fs = 441000;		// Sample rate	
biquad_01.fc = 10000; 		// Hz
biquad_01.q = 0.7071; 		// Q
biquad_01.gain = 6;  		// dB
biquad_01.a0 = 0.251379;	// Parameter a0
biquad_01.a1 = 0.502758;	// Parameter a1
biquad_01.a2 = 0.251379;	// Parameter a2
biquad_01.b1 = -0.171241;	// Parameter b1
biquad_01.b2 = 0.1767567;	// Parameter b2
printf("Lowpass (biquad_01): \n%.f,\n%.f,\n%f,\n%.f,\n%f,\n%f,\n%f,\n%f,\n%f\n\n", biquad_01.fs, biquad_01.fc, biquad_01.q, biquad_01.gain, biquad_01.a0, biquad_01.a1, biquad_01.a2, biquad_01.b1, biquad_01.b2);


*/