// stackMain.c
#include <stdio.h>
#include "stack.h"

int main()
{
    stack_t *myStack = newStack();
    push(myStack, 123);
    push(myStack, 99);
    push(myStack, 4444);
    printf("is empty: %d\n", empty(myStack));
    printf("top element: %d\n", top(myStack));
    while (!empty(myStack)) {
    	int value;
    	value = pop(myStack);
    	printf("popped: %d\n", value);
    }
    printf("is empty: %d\n", empty(myStack));
    printf("popped: %d\n", pop(myStack));
    return 0;
}

