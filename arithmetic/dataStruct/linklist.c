
#include "linklist.h"

void ListPrint(linklist_t *head)
{
    linklist_t *p = head->pNext;
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->pNext;
    }
    printf("\n-----------------------\n");
}

void ListClear(linklist_t *head)
{
    linklist_t *next;
    linklist_t *pre;

    if (head->pNext->pNext != NULL) {
        next = head->pNext->pNext;
        pre  = head->pNext;
    } else {
        free(head->pNext);
        head->pNext = NULL;
        return;
    }

    while (next != NULL) {
        free(pre);
        pre  = next;
        next = next->pNext;
    }
    head->pNext = NULL;
}

bool ListEmpty(linklist_t *head)
{
    if (head->pNext == NULL) {
        return true;
    }
    return false;
}

int ListGetLenght(linklist_t *head)
{
    int         len = -1;
    linklist_t *p   = head;
    while (p != NULL) {
        len++;
        p = p->pNext;
    }
    return len;
}

void ListDelete(linklist_t *head, int index, int *val)
{
    linklist_t *p = head;
    linklist_t *tmp;
    int         i = -1;

    while (p != NULL) {
        i++;
        if (index == i) {
            break;
        }
        p = p->pNext;
    }
    if (p->pNext != NULL) {
        if (p->pNext->pNext != NULL) { /* 被删除元素后面还有节点 */
            tmp = p->pNext->pNext;
            if (val != NULL) {
                *val = p->pNext->data;
            }
            free(p->pNext);
            p->pNext = tmp;
        } else { /* 被删除元素后面没有节点 */
            if (val != NULL) {
                *val = p->pNext->data;
            }
            free(p->pNext);
            p->pNext = NULL;
        }
    }
}

void ListInsert(linklist_t *head, int index, int val)
{
    linklist_t *p = head->pNext;          // index 后面插入
    // linklist_t *p    = head;                 // index 前面插入
    int         i    = -1;
    linklist_t *node = (linklist_t *)malloc(sizeof(linklist_t));

    if (node == NULL) {
        return;
    }

    node->data  = val;
    node->pNext = NULL;

    while (p != NULL) {
        i++;
        if (index == i) {
            break;
        }
        p->pNext;
    }

    node->pNext = p->pNext;
    p->pNext    = node;
}

void ListInit(linklist_t **p)
{
    *p = (linklist_t *)malloc(sizeof(linklist_t));
    if (*p == NULL) {
        return;
    }
    (*p)->pNext = NULL;
}

void ListInsertTail(linklist_t *head, int val)
{
    linklist_t *node;
    linklist_t *p;

    node = (linklist_t *)malloc(sizeof(linklist_t));
    if (node == NULL) {
        return;
    }

    p = head;
    while (p->pNext != NULL) {
        p = p->pNext;
    }
    node->data  = val;
    node->pNext = NULL;
    p->pNext    = node;
}

bool ListGetValue(linklist_t *head, int index, int *val)
{
    linklist_t *p   = head->pNext;
    int         i   = -1;
    bool        ret = false;
    while (p != NULL) {
        i++;
        if (index == i) {
            if (val) {
                *val = p->data;
            }
            ret = true;
        }
        p = p->pNext;
    }
    return ret;
}