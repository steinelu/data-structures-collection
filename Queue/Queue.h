//
// Created by lukas on 11.01.2019.
//

#ifndef QUEUE_H
#define QUEUE_H

typedef struct QueueNodeStruct
{
    struct QueueNodeStruct* node;
    void *value;
} QueueNode;

typedef struct
{
    QueueNode* first;
    QueueNode* last;
    unsigned int size;
} Queue;

// Prototypes

QueueNode* queue_node_create(void*);
void queue_node_destroy(QueueNode* node);

Queue* queue_create();
void queue_destroy(Queue*);
void queue_enqueue(Queue*, void*);
void* queue_dequeue(Queue*);
void* queue_peek(Queue*);
unsigned int size();

#endif //QUEUE_H
