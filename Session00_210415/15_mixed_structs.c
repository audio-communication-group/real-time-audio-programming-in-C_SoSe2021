// 15_mixed_structs.c

#include <stdio.h>

// Enumeration
enum States {
    active_mode = 0,
    standby_mode,
    edit_mode,
} state;

//// This can also be made to a type_t
// typedef enum States {
//     active_mode = 0,
//     standby_mode,
//     edit_mode,
// } state_t;

typedef enum Filters {
  bq_type_lowpass = 0,
  bq_type_highpass,
  bq_type_bandpass,
  bq_type_notch,
  bq_type_peak,
  bq_type_lowshelf,
  bq_type_highshelf
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
  currentFilter.state = edit_mode;
  currentFilter.type = bq_type_lowshelf;
  printf("currentFilter.type: %d\n", currentFilter.type);
  printf("currentFilter.state: %d\n", currentFilter.state);
  
  // Lowpass
  biquad_t homeworkFilter;
  homeworkFilter.state = standby_mode;
  homeworkFilter.type = bq_type_lowpass;
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
    case active_mode:
    printf("active_mode");
    break;

    case standby_mode:
    printf("standby_mode");
    break;

    case edit_mode:
    printf("edit_mode");
    break;
	  
    default:
    printf("undefined state");
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
      case active_mode:
      printf("active_mode");
      break;

      case standby_mode:
      printf("standby_mode");
      break;

      case edit_mode:
      printf("edit_mode");
      break;
	  
      default:
      printf("undefined state");
      break;
    }
	
	printf("\n");
	switch(filter->type) {
		case bq_type_lowpass:
		printf("bq_type_lowpass");
		break;
		
		case bq_type_highpass:
		printf("bq_type_highpass");
		break;
		
		case bq_type_bandpass:
		printf("bq_type_bandpass");
		break;
		
		case bq_type_notch:
		printf("bq_type_notch");
		break;
		
		case bq_type_peak:
		printf("bq_type_peak");
		break;
		
		case bq_type_lowshelf:
		printf("bq_type_lowshelf");
		break;
		
		case bq_type_highshelf:
		printf("bq_type_highshelf");
		break;
		
		default: printf("that should not happen, filter not defined.");
	}
}

*/
