typedef struct
{
    int capacity;
    int * array;
    int size;
} stack_t;

int pop(stack_t *stack_p);
void push(stack_t *stack_p, int value);
int top(stack_t *stack_p);
stack_t *newStack(void);
int empty(stack_t *stack_p);
