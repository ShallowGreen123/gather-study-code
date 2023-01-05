

/**
 *  将单向链表按某个值划分成左边小，中间相等、右边大的形式
 *
 */

#include ".\dataStruct\linklist.h"
#include <time.h>

linklist_t *Mylist1;

linklist_t *ListPartition(linklist_t *head, int val)
{
    linklist_t *sh = NULL;          // small head
    linklist_t *st = NULL;          // small tail
    linklist_t *eh = NULL;          // equal head
    linklist_t *et = NULL;          // equal tail
    linklist_t *bh = NULL;          // big head
    linklist_t *bt = NULL;          // big tail
}

int main()
{
    int randrom;
    srand((unsigned)time(NULL));

    ListInit(&Mylist1);

    for (int i = 0; i < 10; i++) {
        randrom = rand() % 10 + 1;
        ListInsertTail(Mylist1, randrom);
    }
    ListPrint(Mylist1);
    return 0;
}