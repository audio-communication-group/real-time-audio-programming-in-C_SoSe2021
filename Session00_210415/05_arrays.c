#include <stdio.h>

int main() {

    char greeting[6] = {'H', 'e', 'l', 'l', 'o', '\0'};
    printf("\n%s \n", greeting); // %s is format specifier
    
    
    for(int i = 0; i < sizeof(greeting)/sizeof(char); i++) {
        printf("%c,", greeting[i]);
    }
   
    char book_title[100] = "The C programming language";
    printf("\n%s \n", book_title); // %s is format specifier

    for(int i = 0; i < sizeof(book_title)/sizeof(char); i++) {
        printf("%c,", book_title[i]);
    }

    printf("\n");
    
    // Array with integers
    int int_array[10] = {0,1,2,3,4,5,6,7,8,9}; // Initialisation
    
    // starting point, condition
    int i;
	int len = sizeof(int_array)/sizeof(int);
    
    for(i = 0; i < len; i++) {
        printf("%d,", int_array[i]);
    }
    
    printf("\n");
    
    return(0);
}
