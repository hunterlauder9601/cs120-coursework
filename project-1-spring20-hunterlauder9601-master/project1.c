/*
 * Project 1 for CS120: Implementing a Stack
 */
#include "mylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#define STACK_SIZE 10

#define TEST1 1
#define TEST2 1
#define TEST3 1
#define TEST4 1
#define TEST5 1
#define TEST6 1
#define TEST7 1
#define TEST8 1
#define TEST9 1
#define TEST10 1
#define TEST11 1
#define TEST12 1
#define TEST13 1

int main (){
    /******************** Test #1 **************************/
    {
        printf("\n =========== Test # 1: Stack creation =========== \n");
        struct stack * s = newStack(STACK_SIZE);
        assert(s->stk != 0);
        assert(s->top == -1);
        assert(s->max_size == STACK_SIZE);
        deleteStack(s);
        printf("Please check valgrind to make sure you do not have memory leaks or errors.");
    }
    /******************** Test #2 **************************/
    {
        struct stack * s = newStack(STACK_SIZE);
        printf("\n =========== Test # 2: push 1 value onto the stack =========== \n");
        assert(push(s, 5) != -1);
        display(s);
        assert(s->stk[0] == 5);
        assert(s->top == 0);
        assert(s->max_size == STACK_SIZE);
        printf("\t...Test # 3 passed\n");
        deleteStack(s);
    }
    /******************** Test #3 **************************/
    {
        printf("\n =========== Test # 3: push 2nd value onto the stack =========== \n");
        struct stack * s = newStack(STACK_SIZE);
        int nums[] = {5,7};
        for(int i = 0; i < sizeof(nums) / sizeof(int); i++)
            assert(push(s, nums[i]) != -1);
        display(s);
        assert(s->stk[0] == 5);
        assert(s->stk[1] == 7);
        assert(s->top == 1);
        assert(s->max_size == STACK_SIZE);
        deleteStack(s);
        printf("\t...Test # 3 passed\n");
    }
    /******************** Test #4 **************************/
    {
        printf("\n =========== Test # 4: fill the stack =========== \n");
        struct stack * s = newStack(STACK_SIZE);
        for(int i = 0; i < STACK_SIZE/2; i+=2){
            assert(push(s, i) != -1);
            assert(push(s, i+STACK_SIZE) != -1);
            assert(s->top == i+1);
            display(s);
        }
        for(int i = 0; i < STACK_SIZE/2; i+=2){
            assert(s->stk[i] == i);
            assert(s->stk[i+1] == i+STACK_SIZE);
            assert(s->max_size == STACK_SIZE);
        }
        deleteStack(s);
        printf("\t...Test # 4 passed\n");
    }
    /******************** Test #5 **************************/
    {
        printf("\n =========== Test # 5: insert into full stack =========== \n");
        struct stack * s = newStack(STACK_SIZE);
        for(int i = 0; i < STACK_SIZE; i++) assert(push(s, i) != -1);
        assert(push(s, STACK_SIZE) == -1);
        assert(s->top == STACK_SIZE-1);
        assert(s->max_size == STACK_SIZE);
        deleteStack(s);
        printf("\t...Test # 5 passed\n");
    }
    /******************** Test #6 **************************/
    {
        printf("\n =========== Test # 6: pop 1 value off the stack =========== \n");
        struct stack * s = newStack(STACK_SIZE);
        for(int i = 0; i < STACK_SIZE; i++) assert(push(s, i) != -1);
        assert(pop(s) == 9);
        display(s);
        assert(s->top == 8);
        assert(s->max_size == 10);
        deleteStack(s);
        printf("\t...Test # 6 passed\n");
    }
    /******************** Test #7 **************************/
    {
        printf("\n =========== Test # 7: pop 2nd value off the stack =========== \n");
        struct stack * s = newStack(STACK_SIZE);
        for(int i = 0; i < STACK_SIZE; i++) assert(push(s, i) != -1);
        assert(pop(s) == 9);
        assert(pop(s) == 8);
        display(s);
        assert(s->stk[s->top] == 7);
        assert(s->top == 7);
        assert(s->max_size == 10);
        deleteStack(s);
        printf("\t...Test # 7 passed\n");
    }
    /******************** Test #8 **************************/
    {
        printf("\n =========== Test # 8: push value onto the stack after pop =========== \n");
        struct stack * s = newStack(STACK_SIZE);
        for(int i = 0; i < STACK_SIZE; i++) assert(push(s, i) != -1);
        pop(s); pop(s);
        assert(push(s, 20) != -1);
        assert(push(s, 21) != -1);
        display(s);
        assert(s->stk[s->top] == 21);
        assert(s->top == 9);
        assert(s->max_size == 10);
        deleteStack(s);
        printf("\t...Test # 8 passed\n");
    }
    /******************** Test #9 **************************/
    {
        printf("\n =========== Test # 9: remove remaining elements from the stack =========== \n");
        struct stack * s = newStack(STACK_SIZE);
        int array[10] = {5, 7, 12, 13, 14, 15, 16, 17, 20, 21};
        for(int i = 0; i < 10; i++) assert(push(s, array[i]) != -1);
        for(int i = 0; i < 5; i++) pop(s);
        for(int i = 99; i < 101; i++) push(s, i);
        pop(s); pop(s);
        push(s, 1000);
        //current state should be
        int res[] = {1000, 14, 13, 12, 7, 5};
        for(int i = 0; i < 6; i++){
            assert(pop(s) == res[i]);
            assert(s->max_size == STACK_SIZE);
        }
        deleteStack(s);
        printf("\t...Test #9 passed\n");
    }
    /******************** Test #10 **************************/
    {
        printf("\n =========== Test # 10: pop from an empty stack =========== \n");
        struct stack * s = newStack(STACK_SIZE);
        for(int i = 0; i < STACK_SIZE; i++) push(s, i);
        for(int i = 0; i < STACK_SIZE; i++) pop(s);
        assert(pop(s) == -1);
        assert(s->top == -1);
        assert(s->max_size == 10);
        deleteStack(s);
        printf("\t...Test # 10 passed\n");
    }
    /******************** Test #11 **************************/
    {
        printf("\n =========== Test # 11: random elements into a random sized stack =========== \n");
        srand(time(NULL));
        int stack_size = (rand() % 500) + 5;
        struct stack * rand_stack = newStack(stack_size);
        int stest = -1;
        int direction = 2;
        for(int i = 0; i < stack_size * 10; i++){
            if(rand() % 10 <= direction){
                (pop(rand_stack) == -1) ? direction = 2 : stest--;
                assert(rand_stack->top == stest);
            }else{
                (push(rand_stack, rand() % 100) == -1) ? direction = 8 : stest++;
                assert(rand_stack->top == stest);
            }
            assert(rand_stack->max_size == stack_size);
        }
        deleteStack(rand_stack);
        printf("\t...Test #11 passed\n");
    }
    /******************** Test #12 **************************/
    {
        printf("\n=========== TEST #12: Reverse a string ===========\n");

        char str1[] = "Hello";
        struct stack * str_stack1 = newStack(sizeof(str1));
        printf("%s => ", str1);
        stringReverse(str1, str_stack1);
        printf("%s\n", str1);

        char str2[] = "";
        struct stack * str_stack2 = newStack(sizeof(str2));
        printf("%s => ", str2);
        stringReverse(str2, str_stack2);
        printf("%s\n", str2);

        char str3[] = "Computer Science";
        struct stack * str_stack3 = newStack(sizeof(str3));
        printf("%s => ", str3);
        stringReverse(str3, str_stack3);
        printf("%s\n", str3);

        deleteStack(str_stack1);
        deleteStack(str_stack2);
        deleteStack(str_stack3);
        printf("\t...Test #12 passed\n");
    }
    printf("Tests passed! Don't forget to submit to MyCourses.\n");
}
