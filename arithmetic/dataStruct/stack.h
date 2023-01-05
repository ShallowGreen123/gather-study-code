#ifndef __STACK_H__
#define __STACK_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _stack_node_ {
    int                  data;
    struct _stack_node_ *pNext;
} stack_node;

typedef struct _stack_ {
    stack_node *head;
    stack_node *tail;
} stack_t;

void StackInit(stack_t **s);
void StackPush(stack_t *s, int val);
bool StackPop(stack_t *s, int *val);
void StackPrint(stack_t *s);
#endif