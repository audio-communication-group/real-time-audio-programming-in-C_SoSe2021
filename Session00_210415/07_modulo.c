// 07_modulo.c

#include <stdio.h>

int main()
{
    int num;
    printf("Type an integer value:");
    scanf("%d", &num);

    // num % 2 computes the remainder when num is divided by 2
    if ( num % 2 == 0 ) {
        printf("%d is even \n", num);
    } else {
        printf("%d is odd \n", num);
    }

    return 0;
}

/*
Home work:
What is '985824 % 23471'?


42
*/