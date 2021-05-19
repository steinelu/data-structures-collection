//
// Created by lukas on 10.01.2019.
//

#include "stack.h"


#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

StackNode* stack_node_create(void* value, StackNode* down)
{
    StackNode* node = malloc(sizeof(StackNode));
    if(node == NULL)
    {
        fprintf(stderr, "Error:["__FILE__":%d] malloc\n", __LINE__);
        return NULL;
    }
    node->value = value;
    node->node = down;
    return node;
}

void stack_node_destroy(StackNode* node)
{
    if (node != NULL)
    {
        stack_node_destroy(node->node);
        free(node);
    }
}

Stack* stack_create()
{
    Stack* stack = malloc(sizeof(Stack));
    if(stack == NULL)
    {
        fprintf(stderr, "Error:["__FILE__":%d] malloc\n", __LINE__);
        return NULL;
    }

    stack->size = 0;
    stack->node = NULL;
    return stack;
}

int stack_destroy(Stack* stack)
{
    stack_node_destroy(stack->node);
    free(stack);
}

void stack_push(Stack* stack, void* value)
{
    StackNode *tmp = stack_node_create(value, stack->node);
    stack->node = tmp;
    stack->size++;
}

void* stack_pop(Stack* stack)
{
    void* value;
    if(stack->node == NULL)
    {
        fprintf(stderr, "Error:["__FILE__":%d] Stack empty!\n", __LINE__);
        return NULL;
    }
    StackNode* tmp = stack->node;
    stack->node = tmp->node;
    tmp->node = NULL;
    value = tmp->value;
    stack_node_destroy(tmp);
    stack->size--;
    return value;
}

void* stack_peek(Stack* stack)
{
    if(stack->node == NULL)
    {
        fprintf(stderr, "Error:["__FILE__":%d] Stack empty!\n", __LINE__);
        return NULL;
    }
    return stack->node->value;
}

unsigned int stack_size(Stack* stack)
{
    return stack->size;
}
