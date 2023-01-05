

/**
 * 打印两个有序链表的公共部分

 */
#include ".\dataStruct\linklist.h"

linklist_t *Mylist1;
linklist_t *Mylist2;

//
void PrintCommom(linklist_t *head1, linklist_t *head2)
{
    linklist_t *p1 = head1->pNext;
    linklist_t *p2 = head2->pNext;

    printf("********* Common *********\n");
    while ((p1 != NULL) && (p2 != NULL)) {
        if (p1->data == p2->data) {
            printf("%d ", p1->data);
            p1 = p1->pNext;
            p2 = p2->pNext;
        } else {
            p1 = p1->pNext;
        }
    }
    printf("\n*********\n");
}

int main()
{
    int i;
    int val = -1;

    ListInit(&Mylist1);
    ListInit(&Mylist2);

    for (i = 0; i < 10; i++) {
        ListInsertTail(Mylist1, i);
    }
    for (i = 5; i < 15; i++) {
        ListInsertTail(Mylist2, i);
    }

    PrintCommom(Mylist1, Mylist2);

    ListPrint(Mylist1);
    ListPrint(Mylist2);

    return 0;
}
