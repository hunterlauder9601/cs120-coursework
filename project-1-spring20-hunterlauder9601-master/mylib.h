#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* You may add any additional C libraries above you may find helpful */

struct stack{
    int * stk;
    int top;
    int max_size;
};

/* You will need to implement the following functions */
struct stack * newStack(int size)
{
    struct stack* myStack = (struct stack*)malloc(sizeof(struct stack));
    myStack->max_size = size;
    myStack->stk = (int*)malloc(sizeof(int) * size);
    myStack->top = -1;
    return myStack;
}

void deleteStack(struct stack * s)
{
    free(s->stk);
}
int push(struct stack * s, int data)
{
    if ((s->max_size)-1 == s->top) {
        return -1;
    }
    else
    {
        int myTop = s->top;
        s->stk[++myTop]=data;
        s->top=myTop;
        return 0;
    }
}
int pop(struct stack * s)
{
    if (-1 == s->top) {
        return -1;
    }
    else
    {
        int data = s->stk[s->top];
        s->top--;
        return data;
    }
}
void display(struct stack * s)
{
    printf("%d\n", s->top);
    printf("%d\n", s->max_size);
    for(int i = 0; i <= s->top; i++)
    {
        printf("%d\n", s->stk[i]);
    }
}
void stringReverse(char * str, struct stack * s)
{
    int len = strlen(str); //gets the length of the string
    for(int i = 0; i < len; i++)
    {
        push(s, str[i]);
    }
    for(int i = 0; i < len; i++)
    {
        str[i] = pop(s);
    }
}
