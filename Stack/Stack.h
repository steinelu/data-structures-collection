//
// Created by lukas on 10.01.2019.
//

#ifndef STACK_H
#define STACK_H

typedef struct StackNodeStruct
{
    void * value;
    struct StackNodeStruct* node;
} StackNode;

typedef struct
{
    StackNode* node;
    unsigned int size;
} Stack;

// Prototypes
StackNode* stack_node_create(void*, StackNode*);
void stack_node_destroy(StackNode*);

Stack* stack_create();
int stack_destroy(Stack*);
void stack_push(Stack*, void *);
void* stack_pop(Stack*);
void* stack_peek(Stack*);
unsigned int stack_size(Stack*);

#endif //STACK_H
