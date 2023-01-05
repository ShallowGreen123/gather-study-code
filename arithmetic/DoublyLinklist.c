
/**
 * 反转双向链表

 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _node_ {
    int            data;
    struct _node_ *pNext;
    struct _node_ *pPrev;
} linklist_t;

void LinkCreateHead(linklist_t **head);
void LinkInserTail(linklist_t *head, int val);
void ListPrint(linklist_t *head);

void LinkInvert(linklist_t *head)
{
    linklist_t    *next;
    linklist_t    *pre;
    struct _node_ *swap;

    if (head->pNext->pNext != NULL) {
        next = head->pNext->pNext;
        pre  = head->pNext;
    } else {
        return; /* 链表中只有一个节点 */
    }

    pre->pPrev = NULL;
    while (next != NULL) {
        swap       = pre->pPrev;
        pre->pPrev = pre->pNext;
        pre->pNext = swap;
        pre        = next;
        next       = next->pNext;
    }
    swap        = pre->pPrev;
    pre->pPrev  = head;
    pre->pNext  = swap;
    head->pNext = pre;
    head->pPrev = NULL;
}
//
linklist_t *MyListHead;
//
int main()
{
    LinkCreateHead(&MyListHead);
    LinkInserTail(MyListHead, 100);
    LinkInserTail(MyListHead, 22);
    LinkInserTail(MyListHead, 33);
    LinkInserTail(MyListHead, 44);

    // LinkInvert(MyListHead);

    ListPrint(MyListHead);
    return 0;
}

void LinkCreateHead(linklist_t **head)
{
    *head = (linklist_t *)malloc(sizeof(linklist_t));
    if (*head == NULL) {
        return;
    }
    (*head)->pPrev = NULL;
    (*head)->pNext = NULL;
}

void LinkInserTail(linklist_t *head, int val)
{
    linklist_t *p;
    linklist_t *node = (linklist_t *)malloc(sizeof(linklist_t));

    if (node == NULL) {
        return;
    }

    p = head;
    while (p->pNext != NULL) { /* 找到双向链表的最后一个节点 */
        p = p->pNext;
    }
    node->data  = val;
    node->pNext = NULL;
    node->pPrev = p;
    p->pNext    = node;
}

void ListPrint(linklist_t *head)
{
    linklist_t *p = head->pNext;
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->pNext;
    }
    printf("\n-----------------------\n");
}
