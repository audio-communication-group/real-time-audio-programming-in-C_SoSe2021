//
//  04ControlStructuresLogicOperatorsAndFunctions.c
//  Einführung in C
//

// http://users.ece.cmu.edu/~eno/coding/CCodingStandard.html


#include <stdio.h>
#include <stdbool.h>
#include "17_static_"

// Global variables
bool sunshine = false;
bool bike_is_broken = true;
bool is_weekend = false;

// Custom data types
typedef enum Activities {
    LEARNING_TO_CODE = 1,
    CYCLING,
    CELEBRATING,
    WALKING,
    CHILLING
} activities_t;

// Function declaration
void print_what_to_do(activities_t x);

int main() {
	// Declaration struct
    activities_t to_do_today;

    // if - else
    if (is_weekend == true) {
        printf("I go into the park.\n");
        to_do_today = CHILLING;
    } else {
        printf("I go to the programming seminar.\n");
        to_do_today = LEARNING_TO_CODE;
    }

    print_what_to_do(to_do_today);
    
    if  ((bike_is_broken == true) || (is_weekend == true)) {
        to_do_today = WALKING;
    } else if (is_weekend && !bike_is_broken && sunshine) {
            to_do_today = CYCLING;
    } else {
        to_do_today = CHILLING;
    };

    // Function call
    print_what_to_do(to_do_today);

    // Ternary operator
    (!bike_is_broken) ? (to_do_today = CYCLING) : (to_do_today = WALKING);

    // Function call
    print_what_to_do(to_do_today);

    return 0;
}

// Function implementation
void print_what_to_do(activities_t x) {
    // Switch case
    switch(x) {
        case LEARNING_TO_CODE:
            printf("My activity today: %d LEARNING_TO_CODE\n", x);
            break;
        case CYCLING:
            printf("My activity today: %d CYCLING\n", x);
            break;
        case CELEBRATING:
            printf("My activity today: %d CELEBRATING\n", x);
            break;
        case WALKING:
            printf("My activity today: %d WALKING\n", x);
            break;
        case CHILLING:
            printf("My activity today: %d CHILLING\n", x);
            break;
        default:
            printf("My activity today: no idea\n");
            break;
    }
}

// Homework: Implement the function "print_what_to_do" with if-statements only.

