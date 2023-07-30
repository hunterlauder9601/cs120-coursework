#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#define INIT_SIZE 20
#define TEST1 1
#define TEST2 1
#define TEST3 1
#define TEST4 1
#define TEST5 1

#if TEST1
int * test1(int size){
    // get bytes "size of int" on the hardware implementation running
    int size_of_int = sizeof(int);

    // get the size of array in bytes
    int arraySize = size_of_int * size;

    // make memory allocation on the heap of size needed
    int * ptr_array;
    ptr_array = malloc(arraySize);

    // retain the pointer to the memory since we have to return it and we will need to "advance" the other pointer
    int * retrn;

    retrn = ptr_array;

    // loop each occurance...
    for ( int i = 0 ; i < size ; i++) {

        // set "value where ptr_array points to" = -1
        * ptr_array = -1;
        printf("%d",*ptr_array);
        // if we have a "pointer to int" we can move to next position with "++" which is short hand for "ptr_array = ptr_array + 1"
        ptr_array = ptr_array + 1;
        // ptr_array++;


    }
    // return the original pointer position...
    printf("\n");
    return retrn;
}
#endif
#if TEST2
int * test2(int * nums, int size){
    int size_of_int = sizeof(int);

    int arraySize = (size_of_int * size) + 1;

    int * ptr_array = malloc(arraySize);

    int * retrn = ptr_array;

    int * ptr_to_free_memory = nums;

    for ( int i = 0 ; i < size ; i++) {

        *ptr_array = *nums;
        printf("%d",*ptr_array);

        nums++;
        ptr_array++;
    }
    *ptr_array = 1;
    printf("%d",*ptr_array);

    free(ptr_to_free_memory);
    printf("\n");
    return retrn;
}
#endif
#if TEST3
int * test3(int * nums, int size){

    int size_of_nums = sizeof(int) * size;

    int arraySizeNew = size_of_nums * 2;

    int * ptr_array = malloc(arraySizeNew);

    int * retrn = ptr_array;

    int * ptr_to_free_memory = nums;

    for ( int i = 0 ; i < size ; i++) {

        *ptr_array = *nums;
        *(ptr_array+size) = *nums;

        nums++;
        ptr_array++;
    }

    int* ptr_print = retrn;

    for ( int i = 0 ; i < size*2 ; i++) {
        printf("%d",*ptr_print);
        ptr_print++;
    }

    // free unused memory
    free(ptr_to_free_memory);
    // return the new pointer...
    printf("\n");
    return retrn;

}
#endif
#if TEST4
int * test4(int * nums, int size){

    int size_of_nums = sizeof(int) * size;

    int arraySizeNew = size_of_nums / 2;

    int * ptr_array = malloc(arraySizeNew);

    int * retrn = ptr_array;

    int * ptr_to_free_memory = nums;

    for ( int i = 0 ; i < (size/2) ; i++) {

        *ptr_array = *nums;
        printf("%d",*ptr_array);

        nums++;
        ptr_array++;
    }

    free(ptr_to_free_memory);
    printf("\n");
    return retrn;
}
#endif
#if TEST5
int * test5(int * nums, int size){

    int size_of_nums = sizeof(int) * size;

    int arraySizeNew = size_of_nums - sizeof(int);

    int newOccurSize = arraySizeNew/sizeof(int);

    int * ptr_array = malloc(arraySizeNew);

    int * retrn = ptr_array;

    int * ptr_to_free_memory = nums;

    for ( int i = 0 ; i < newOccurSize ; i++) {

        *ptr_array = *(nums+1);
        printf("%d",*ptr_array);

        nums++;
        ptr_array++;
    }

    // free unused memory
    free(ptr_to_free_memory);
    // return the new pointer...
    printf("\n");
    return retrn;
}


#endif
/********************************************************************/
/*    Do not alter Code Past Here                               */
/********************************************************************/


int main(){
    int i = 0;
    srand(time(NULL));
    printf("\t-----------------------------------\n");
    printf("\t-           Dynamic Arrays        -\n");
    printf("\t-----------------------------------\n");
    printf("\t========= After each test you should print our your array using a loop ===========\n");
    printf("\t========= All loops should ONLY use pointer arithmetic to iterate ===========\n\n");
    int * test_array = NULL;
#if TEST1
    printf("\n\t=========Test #1: Create an integer array of size ===========\n");
    printf("\t== Write a function that returns an integer array of INIT_SIZE elements all containing -1 ==\n\n");
    test_array = test1(INIT_SIZE);
    for(int * ptr = test_array; ptr < test_array+INIT_SIZE; ptr++){
        assert(*ptr == -1);
    }
#endif
#if TEST2
    printf("\n\t=========Test #2: 'Grow' the array by 1, and insert the value 1 at the end ===========\n\n");
    int * ptr2 = test2(test_array, INIT_SIZE);
    assert(ptr2 != test_array);
    test_array = ptr2;
    for(; ptr2 < test_array+INIT_SIZE; ptr2++){
        assert(*ptr2 == -1);
    }
    assert(*ptr2 == 1);
#endif
#if TEST3

    printf("\n\t=========Test #3: Double the size of the array ===========\n\n");
    printf("\n\t=========Test #3: Copy the values from the old array to the new array===========\n\n");
    printf("\n\t=========Test #3: Fill the remaining indexes in the new array with the first half values===========\n\n");
    int * ptr3 = test3(test_array, INIT_SIZE+1);
    assert(ptr3 != test_array);
    test_array = ptr3;
    for(int i = 0; i < (INIT_SIZE+1)*2; i++){
        if(i == 20 || i == 41){
            assert(ptr3[i] == 1);
        }else{
            assert(ptr3[i] == -1);
        }
    }
#endif
#if TEST4
    printf("\n\t=========Test #4: Reduce the size of the array by half  ===========\n\n");
    printf("\n\t=========Test #4: Copy over the first half values ===========\n\n");
    int * ptr4 = test4(test_array, (INIT_SIZE+1)*2);
    assert(ptr4 != test_array);
    test_array = ptr4;
    for(; ptr4 < test_array+INIT_SIZE; ptr4++) assert(*ptr4 == -1);
    assert(*ptr4 == 1);

#endif
#if TEST5
    printf("\n\t=========Test #5: Remove a the first element from your array ===========\n\n");
    printf("\n\t=========Test #5: The array size should shrink by exactly 1 ===========\n\n");
    int * ptr5 = test5(test_array, INIT_SIZE+1);
    assert(ptr5 != test_array);
    test_array = ptr5;
    for(; ptr5 < test_array+(INIT_SIZE-1); ptr5++) assert(*ptr5 == -1);
    assert(*ptr5 == 1);
#endif
    free(test_array);
    printf("\n\t=========Run your code with valgrind to ensure there are no errors ===========\n\n");
    return 0;
}
