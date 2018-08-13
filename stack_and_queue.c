#include <stdio.h>
#include <stdlib.h>

int stack[10];
int top = 0;

void print_array(int* array) {
    for (size_t i = 0; i < sizeof(array)/sizeof(array[0]); i++) {
        printf("%i\n", array[i]);
    }
}

int stack_empty(int* stack) {
    return top == 0 ? 1 : 0;
}

void push(int* stack, int value) {
    top++;
    stack[top] = value;
}

int pop(int* stack) {
    if (!stack_empty(stack)) {
        int value = stack[top];
        stack[top] = 0;
        top--;
        printf("Deleted: %i\n", value);
        return value;
    } else {
        printf("The stack is empty\n");
        return -1;
    }
}

//////////////////////////////////////////////////////////////////

int queue[10];
int head = 1;
int tail = 1;

int queue_empty(int* queue) {
    return head == tail ? 1 : 0;
}

int queue_full(int* queue) {
    return head == tail + 1 ? 1 : 0;
}

void enqueue(int* queue, int value) {
    if (queue_full(queue)) {
        printf("The queue is full");
    } else {
        queue[tail] = value;
        if (tail == sizeof(queue)/sizeof(queue[0]))
            tail = 1;
        else tail++;
    }
}

int dequeue(int* queue) {
    int value;
    if (queue_empty(queue)) {
        printf("The queue is empty\n");
        return -1;
    } else {
        value = queue[head];
        printf("Deleted %i\n", value);
        queue[head] = 0;
        if (head == sizeof(queue)/sizeof(queue[0]))
            head = 1;
        else head++;
    }
    return value;
}


int main() {
    // STACK
    printf("\n---------STACK---------\n");
    print_array(stack);
    printf("\n");
    push(stack, 2);
    print_array(stack);
    printf("\n");
    pop(stack);
    print_array(stack);
    printf("\n");
    pop(stack);

    // QUEUE
    printf("\n---------QUEUE---------\n");
    print_array(queue);
    printf("\n");
    enqueue(queue, 3);
    print_array(queue);
    printf("\n");
    dequeue(queue);
    print_array(queue);
    printf("\n");
    dequeue(queue);
}