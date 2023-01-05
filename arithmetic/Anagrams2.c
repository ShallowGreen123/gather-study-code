
/**
 *  判断一个链表是否是回文结构
 *  快慢指针，注意链表长度是奇数/偶数个的边界问题
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include ".\dataStruct\linklist.h"
#include ".\dataStruct\stack.h"

linklist_t *Mylist;
//
bool ListIsAnagram(linklist_t *head)
{
    if (head == NULL || head->pNext == NULL) {
        return true;
    }

    bool        ret  = true;
    linklist_t *fast = head;
    linklist_t *slow = head;
    linklist_t *tmp  = NULL;

    while ((fast->pNext != NULL)
           && (fast->pNext->pNext != NULL)) { /* 下一个快指针为空 */
        slow = slow->pNext;                   /* 循环结束，慢指针指向中间，快指针指向最后 */
        fast = fast->pNext->pNext;            /* 注意考虑链表长度的奇偶 */
    }                                         /* 循环结束时，slow 指向链表的中点,fast 指向空 */

    fast        = slow->pNext; /* fast 等于中间的下一个节点，反转 fast 后面的节点 */
    slow->pNext = NULL;        /* 中间的 pNext 指向空，是前后遍历链表的结束条件 */

    while (fast != NULL) { /* 将 fast 后面的链表反转 */
        tmp         = fast->pNext;
        fast->pNext = slow;
        slow        = fast; /* slow 向前移动 */
        fast        = tmp;  /* fast 向前移动 */
    }                       /* 循环结束，slow 指向链表最后一个节点上 */

    tmp  = slow;                               /* tmp 记住最后节点，后面恢复链表用 */
    fast = head->pNext;                        /* fast 重新指向第一个节点，head 不记录数据，所以 head->pNext 是第一个节点 */
    while ((slow != NULL) && (fast != NULL)) { /* 链表长度为奇数是，fast 为空，为偶数时最后两个变量都为空 */
        if (slow->data != fast->data) {
            ret = false;
            break;
        }
        slow = slow->pNext; /* slow 从后面往前遍历链表，fast 从前往后遍历链表 */
        fast = fast->pNext; /* 在 slow、fast 有一个为空之前，他们的 data 都相等就是回文结构 */
    }                       /* 循环结束时，fast 依然指向链表的中点 */

    slow       = tmp->pNext;
    tmp->pNext = NULL;
    while (slow != NULL) { /* 将链表还原回来 */
        fast        = slow->pNext;
        slow->pNext = tmp;
        tmp         = slow;
        slow        = fast;
    }
    return ret;
}

int main()
{
    int  lenght, val1, val2;
    bool isAnagrams = true;

    ListInit(&Mylist);

    for (int i = 0; i < 5; i++) {
        ListInsertTail(Mylist, i);
    }
    for (int i = 5; i >= 0; i--) {
        ListInsertTail(Mylist, i);
    }
    ListInsertTail(Mylist, 10);
    lenght = ListGetLenght(Mylist);
    ListPrint(Mylist);

    isAnagrams = ListIsAnagram(Mylist);
    printf("isAnagrams = %d\n", isAnagrams);

    return 0;
}
