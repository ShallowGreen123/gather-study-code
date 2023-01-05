#include "stack.h"

void StackInit(stack_t **s)
{
    *s         = (stack_t *)malloc(sizeof(stack_t));
    (*s)->head = (stack_node *)malloc(sizeof(stack_node));
    if ((*s)->head == NULL) {
        return;
    }
    (*s)->tail        = (*s)->head;
    (*s)->head->pNext = NULL;
}

bool StackIsEmpty(stack_t *s)
{
    if (s == NULL) return true;
    if (s->head == s->tail) {
        return true;
    } else {
        return false;
    }
}

void StackPush(stack_t *s, int val)
{
    if (s == NULL) return;

    stack_node *node = (stack_node *)malloc(sizeof(stack_node));
    if (node == NULL) {
        return;
    }

    node->data  = val;
    node->pNext = s->head;
    s->head     = node;
}

bool StackPop(stack_t *s, int *val)
{
    if (s == NULL || StackIsEmpty(s)) {
        return false;
    }

    stack_node *h = s->head;
    if (val) {
        *val = h->data;
    }
    s->head = h->pNext;
    free(h);
    return true;
}

void StackPrint(stack_t *s)
{
    stack_node *p = s->head;
    while (p != s->tail) {
        printf("%d ", p->data);
        p = p->pNext;
    }
    printf("\n-----------------------\n");
}
