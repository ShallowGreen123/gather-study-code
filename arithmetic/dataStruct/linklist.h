#ifndef __LINKLIST_H__
#define __LINKLIST_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _node_ {
    int            data;
    struct _node_ *pNext;
} linklist_t;

void ListInit(linklist_t **p);
void ListInsertTail(linklist_t *head, int val);
void ListInsert(linklist_t *head, int index, int val);
void ListDelete(linklist_t *head, int index, int *val);
int  ListGetLenght(linklist_t *head);
bool ListEmpty(linklist_t *head);
void ListPrint(linklist_t *head);
void ListClear(linklist_t *head);
bool ListGetValue(linklist_t *head, int index, int *val);

// GetElem(*L，i，e)
// LocateElem(*L，e)

#endif