//
// Created by lukas on 11.01.2019.
//

#include "queue.h"

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

QueueNode* queue_node_create(void* value)
{
    QueueNode* node = malloc(sizeof(QueueNode));
    if(node == NULL)
    {
        fprintf(stderr, "Error:["__FILE__":%d] malloc\n", __LINE__);
        return NULL;
    }
    node->value = value;
    node->node = NULL;
    return node;
}

void queue_node_destroy(QueueNode* node)
{
    if(node == NULL)
        return;
    node->node = NULL;
    node->value = NULL;
    free(node);
}

Queue* queue_create()
{
    Queue* queue = malloc(sizeof(queue));
    if(queue == NULL)
    {
        fprintf(stderr, "Error:["__FILE__":%d] malloc\n", __LINE__);
        return NULL;
    }
    queue->size = 0;
    queue->first = NULL;
    queue->last = NULL;
    return queue;
}

void queue_destroy(Queue* queue)
{
    queue->last = NULL;
    queue_node_destroy(queue->first);
    queue->first = NULL;
    free(queue);
}

void queue_enqueue(Queue* queue, void* value)
{
    QueueNode* node = queue_node_create(value);
    if(queue->last == NULL)
    {
        queue->last = node;
        queue->first = node;
    }
    else{
        queue->last->node = node;
        queue->last = node;
    }
    queue->size++;
}

void* queue_dequeue(Queue* queue)
{
    if(queue->first == NULL)
        return NULL;

    void *value = queue->first->value;
    QueueNode* del = queue->first;
    queue->first = del->node;
    free(del);
    queue->size--;
    return value;
}

void* queue_peek(Queue* queue)
{
    if(queue->first == NULL)
        return NULL;
    return queue->first->value;
}
unsigned int size();