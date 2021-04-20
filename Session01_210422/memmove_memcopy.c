#include <string.h>
#include <stdio.h>

char str1[50] = "I am going from Delhi to Gorakhpur";
char str2[50] = "I am going from Gorakhpur to Delhi";


int main( void )
{
    
    //Use of memmove
    printf( "Function:\tmemmove with overlap\n" );
    
    printf( "Original :\t%s\n",str1);
    
    printf( "Source:\t\t%s\n", str1 + 5 );
    
    printf( "Destination:\t%s\n", str1 + 11 );
    
    memmove( str1 + 11, str1 + 5, 29 );
    
    printf( "Result:\t\t%s\n", str1 );
    
    printf( "Length:\t\t%lu characters\n\n", strlen( str1 ) );
    
    
    //Use of memcpy
    printf( "Function:\tmemcpy with overlap\n" );
    
    printf( "Original :\t%s\n",str2);
    
    printf( "Source:\t\t%s\n", str2 + 5 );
    
    printf( "Destination:\t%s\n", str2 + 11 );
    
    memcpy( str2 + 11, str2 + 5, 29 );
    
    printf( "Result:\t\t%s\n", str2 );
    
    printf( "Length:\t\t%lu characters\n\n", strlen( str2 ) );
    
    
    return 0;
}
