#include <stdio.h>
#include <stdbool.h>
#define STACK_SIZE 100

typedef struct {
    int items[STACK_SIZE];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

bool isStackEmpty(Stack *s) {
    return (s->top == -1);
}

bool isStackFull(Stack *s) {
    return (s->top == STACK_SIZE - 1);
}

void push(Stack *s, int value) {
    if (isStackFull(s)) {
        printf("Stack Overflow\n");
        return;
    }
    s->items[++s->top] = value;
}

int pop(Stack *s) {
    if (isStackEmpty(s)) {
        printf("Stack Underflow\n");
        return -1;
    }
    return s->items[s->top--];
}

typedef struct {
    Stack s1;
    Stack s2;
} QueueUsingStacks;

void initQueueStacks(QueueUsingStacks *q) {
    initStack(&q->s1);
    initStack(&q->s2);
}

void enqueueStack(QueueUsingStacks *q, int value) {
    push(&q->s1, value);
    printf("%d enqueued to queue\n", value);
}

int dequeueStack(QueueUsingStacks *q) {
    if (isStackEmpty(&q->s1) && isStackEmpty(&q->s2)) {
        printf("Queue is empty\n");
        return -1;
    }
    
    if (isStackEmpty(&q->s2)) {
        while (!isStackEmpty(&q->s1)) {
            push(&q->s2, pop(&q->s1));
        }
    }
    
    return pop(&q->s2);
}

void displayQueueStacks(QueueUsingStacks *q) {
    if (isStackEmpty(&q->s1) && isStackEmpty(&q->s2)) {
        printf("Queue is empty\n");
        return;
    }
    
    printf("Queue elements: ");
    for (int i = q->s2.top; i >= 0; i--) {
        printf("%d ", q->s2.items[i]);
    }
    for (int i = 0; i <= q->s1.top; i++) {
        printf("%d ", q->s1.items[i]);
    }
    printf("\n");
}

int main() {
    printf("========================================\n");
    printf("Name: Lavesh Kumar\n");
    printf("Roll No: 25/A03/059\n");
    printf("========================================\n\n");
    
    printf("QUESTION 26: Queue Implementation using Two Stacks\n");
    printf("------------------------------------------------\n");
    
    QueueUsingStacks qs;
    initQueueStacks(&qs);
    
    enqueueStack(&qs, 100);
    enqueueStack(&qs, 200);
    enqueueStack(&qs, 300);
    
    displayQueueStacks(&qs);
    
    printf("Dequeued: %d\n", dequeueStack(&qs));
    printf("Dequeued: %d\n", dequeueStack(&qs));
    
    enqueueStack(&qs, 400);
    enqueueStack(&qs, 500);
    
    displayQueueStacks(&qs);
    
    return 0;
}