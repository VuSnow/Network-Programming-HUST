#include<stdio.h>

int main(){
    int *ptr; // declare a pointer variable
    int val = 1;
    ptr = &val;
    int defer = *ptr;
    printf("Before change, the value of the defer is: %d\n", defer);
    printf("Before change, the value stored in pointer is: %d\n", *ptr);
    *ptr = 2;
    printf("After change, the value stored in pointer is: %d\n", *ptr);
    printf("After change, the value of defer is: %d\n", defer);


    // tham chiếu ngược một pointer
    // declare int ival and int pointer iptr.  Assign address of ival to iptr.
    int ival = 1;
    int *iptr = &ival;

 	// dereference iptr to get value pointed to, ival, which is 1
    int get = *iptr;
    printf("*iptr = %d\n", get);

     	
    // dereference iptr to set value pointed to, changes ival to 2
    *iptr = 2;
    int set = *iptr;
    printf("*iptr = %d\n", set);
    printf("ival = %d\n", ival);
}