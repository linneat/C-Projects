// stack.c
#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

stack_t *newStack(void)
{
    stack_t *myStack = malloc(sizeof(stack_t)); //making the space for the stack
    myStack->capacity = 1;                      //set the length of the array to 1 (inisalize struck members)
    myStack->array = calloc(1, sizeof(int));    //create the array with the length 1
    myStack->size = 0;                          //set the nr of elements in the stack to be 0
    return myStack;
}

int pop(stack_t *stack_p)
{
    int popVal;
    if (stack_p->size > 0)
    {
        popVal = stack_p->array[stack_p->size - 1];
        stack_p->size = stack_p->size - 1;
        return popVal;
    }
    else
    {
        printf("no elements in stack to pop\n");
        exit(1);
    }
}

void push(stack_t *stack_p, int value)
{

    if (stack_p->capacity > stack_p->size)
    {
        stack_p->array[stack_p->size] = value;
        stack_p->size = stack_p->size + 1;
    }
    else
    {
        int *newArray = calloc(2 * stack_p->capacity, sizeof(int)); //making a new array with the double size
        int i;
        for (i = 0; i <= stack_p->size; i++)
        { //copy all values from array into a temperary array
            newArray[i] = stack_p->array[i];
        }

        free(stack_p->array);      // free what stack_p->array points to
        stack_p->array = newArray; //make stack_p->array point to newArray
        stack_p->capacity = 2 * stack_p->capacity;
        stack_p->array[stack_p->size] = value;
        stack_p->size = stack_p->size + 1;
    }
}

int top(stack_t *stack_p)
{
    return stack_p->array[stack_p->size - 1];
}

int empty(stack_t *stack_p) //takes a pointer that points to a stack
{
    if (stack_p->size == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
