

/**
 * 反转单链表 singly linked list

 */

#include ".\dataStruct\linklist.h"

linklist_t *Mylist;

linklist_t *InvertList(linklist_t *head) /* 没有换头的操作 */
{
    linklist_t *next = head->pNext->pNext;
    linklist_t *pre  = head->pNext;
    linklist_t *tmp;

    pre->pNext = NULL;
    while (next != NULL) {
        tmp        = next;
        next       = next->pNext;
        tmp->pNext = pre;
        pre        = tmp;
    }
    head->pNext = pre;
    return pre;
}

int main()
{
    int i;
    int val = -1;

    ListInit(&Mylist);

    for (i = 0; i < 10; i++) {
        ListInsertTail(Mylist, i);
    }
    ListPrint(Mylist);

    InvertList(Mylist);
    ListPrint(Mylist);
    return 0;
}
