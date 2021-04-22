// 15_mixed_structs.c

// http://users.ece.cmu.edu/~eno/coding/CCodingStandard.html


#include <stdio.h>

// Enumerations
enum States {
    ACTIVE_MODE,
    STAND_BY_MODE,
    EDIT_MODE,
};

//// This can also be made to a type_t
// typedef enum States {
	// ACTIVE_MODE,
	// STAND_BY_MODE,
	// EDIT_MODE,
// } state_t;



typedef enum Filters {
    BQ_TYPE_LOWPASS = 0,
    BQ_TYPE_HIGHPASS,
    BQ_TYPE_BANDPASS,
    BQ_TYPE_NOTCH,
    BQ_TYPE_PEAK,
    BQ_TYPE_LOWSHELF,
    BQ_TYPE_HIGHSHELF
} filter_t;

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

  // Both declarations are possible
  //enum Filters type;
  filter_t type;
  enum States state;
  //state_t state;
  
} biquad_t;     // Define a Biquad type appending "_t"

// Declaration of function (this could move to a file.h header file later)
void printState(biquad_t *filter);
void printAllFilterParams(biquad_t *filter);


int main() {
  biquad_t currentFilter;
  currentFilter.state = EDIT_MODE;
  currentFilter.type = BQ_TYPE_LOWSHELF;
  printf("currentFilter.type: %d\n", currentFilter.type);
  printf("currentFilter.state: %d\n", currentFilter.state);
  
  // Lowpass
  biquad_t homeworkFilter;
  homeworkFilter.state = STAND_BY_MODE;
  homeworkFilter.type = BQ_TYPE_LOWPASS;
  homeworkFilter.fs = 441000;		// Sample rate	
  homeworkFilter.fc = 10000; 		// Hz
  homeworkFilter.q = 0.7071; 		// Q
  homeworkFilter.gain = 6;  			// dB
  homeworkFilter.a0 = 0.251379;		// Parameter a0
  homeworkFilter.a1 = 0.502758;		// Parameter a1
  homeworkFilter.a2 = 0.251379;		// Parameter a2
  homeworkFilter.b1 = -0.171241;		// Parameter b1
  homeworkFilter.b2 = 0.1767567;		// Parameter b2
  
  printState(&currentFilter);
  //printAllFilterParams(&homeworkFilter);
  return 0;
}


// Implementation of function (this could move to a file.c later)
void printState(biquad_t *filter) {
  //*state is just a number
  //printf("%d\n",filter->state);
  switch(filter->state) {
	printf("State: ");
    case ACTIVE_MODE:
    printf("ACTIVE_MODE");
    break;

    case STAND_BY_MODE:
    printf("STAND_BY_MODE");
    break;

    case EDIT_MODE:
    printf("EDIT_MODE");
    break;
	  
    default:
    printf("undefined");
    break;
  }
}



/*
Home work:
Expand the 'void printParameters(biquad_t *filter)' from 13_typedefs.c in such a way that it also outputs the filter state and the filter type!

void printAllFilterParams(biquad_t *filter) {
	printf("\n");
	printf("\nFilter parameter: \n%.f,\n%.f,\n%f,\n%.f,\n%f,\n%f,\n%f,\n%f,\n%f", 
	filter->fs, filter->fc, filter->q, filter->gain, filter->a0, filter->a1, filter->a2, filter->b1, filter->b2);
	
	printf("\n");
    switch(filter->state) {
      case ACTIVE_MODE:
      printf("ACTIVE_MODE");
      break;

      case STAND_BY_MODE:
      printf("STAND_BY_MODE");
      break;

      case EDIT_MODE:
      printf("EDIT_MODE");
      break;
	  
      default:
      printf("undefined state");
      break;
    }
	
	printf("\n");
	switch(filter->type) {
		case BQ_TYPE_LOWPASS:
		printf("BQ_TYPE_LOWPASS");
		break;
		
		case BQ_TYPE_HIGHPASS:
		printf("BQ_TYPE_HIGHPASS");
		break;
		
		case BQ_TYPE_BANDPASS:
		printf("BQ_TYPE_BANDPASS");
		break;
		
		case BQ_TYPE_NOTCH:
		printf("BQ_TYPE_NOTCH");
		break;
		
		case BQ_TYPE_PEAK:
		printf("BQ_TYPE_PEAK");
		break;
		
		case BQ_TYPE_LOWSHELF:
		printf("BQ_TYPE_LOWSHELF");
		break;
		
		case BQ_TYPE_HIGHSHELF:
		printf("BQ_TYPE_HIGHSHELF");
		break;
		
		default: printf("that should not happen, filter not defined.");
	}
}

*/
