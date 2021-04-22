// 14_enums.c

// http://users.ece.cmu.edu/~eno/coding/CCodingStandard.html

#include <stdio.h>

// Enumerations
enum Filters {
    BQ_TYPE_LOWPASS = 0,
    BQ_TYPE_HIGHPASS,
    BQ_TYPE_BANDPASS,
    BQ_TYPE_NOTCH,
    BQ_TYPE_PEAK,
    BQ_TYPE_LOWSHELF,
    BQ_TYPE_HIGHSHELF
};

enum States {
    ACTIVE_MODE,
    STAND_BY_MODE,
    EDIT_MODE,
};


int main() {
   enum Filters currentFilter = BQ_TYPE_HIGHSHELF;
   printf("currentFilter: %d\n", currentFilter);

   return 0;
}

/*
Homework:
Write a function 'printFilterType(enum Filters *filter)' that prints the filter type instead of the enum number!
Tip: Use the 'switch' statement!

void printFilterType(enum Filters *filter) {
	switch(*filter) {
		case 0:
		printf("BQ_TYPE_LOWPASS");
		break;
		
		case 1:
		printf("BQ_TYPE_HIGHPASS");
		break;
		
		case 2:
		printf("BQ_TYPE_BANDPASS");
		break;
		
		case 3:
		printf("BQ_TYPE_NOTCH");
		break;
		
		case 4:
		printf("BQ_TYPE_PEAK");
		break;
		
		case 5:
		printf("BQ_TYPE_LOWSHELF");
		break;
		
		case 6:
		printf("BQ_TYPE_HIGHSHELF");
		break;
		
		default: printf("that should not happen, filter not defined.");
	}
}
*/