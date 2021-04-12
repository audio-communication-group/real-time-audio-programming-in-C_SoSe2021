// 11_unions.c

#include <stdio.h>
#include <string.h>

// In union, the total memory space allocated is equal to the member with largest size. All other members share the same memory space.

union Data {
  int i;
  float f;
  float e;
  char str[40];
};

int main( ) {
  union Data data;
    
//  You can access only that variable whose value is recently stored.
  data.i = 100;
  printf( "data.i: %d\n", data.i);
   
  data.f = 100.5;
  printf( "data.f: %.2f\n", data.f);
  
  strcpy(data.str, "Unions use one variable at a time!");
  printf( "data.str: %s\n", data.str);
  printf( "size of union: %lu\n", sizeof(data));
    
  return 0;
}

/*
Home work:
1.	For holding filter parameters (such as a0, a1, a2, b1, b2), would you use a struct or an union?
2.	For holding filter types (like high_shelf_, low_pass ect.), would you use a struct or an union?
Tip: Think about how the variables will be used at the same time?

1. 	Struct, because you probably need all members at the same time.
2. 	You can use an enumeration here. A union is suitable for storing a data type from a group of different 
	data types in one place.
*/