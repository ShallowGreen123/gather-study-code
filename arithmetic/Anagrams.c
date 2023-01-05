

/**
 *  判断一个链表是否是回文结构
 *  放入栈中，然后依次弹出与原链表作对比
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include ".\dataStruct\linklist.h"
#include ".\dataStruct\stack.h"

linklist_t *Mylist;
stack_t    *Mystack;
//
int main()
{
    int  lenght, val1, val2;
    bool isAnagrams = true;

    ListInit(&Mylist);
    StackInit(&Mystack);

    for (int i = 0; i < 5; i++) {
        ListInsertTail(Mylist, i);
    }
    for (int i = 5; i >= 0; i--) {
        ListInsertTail(Mylist, i);
    }
    lenght = ListGetLenght(Mylist);
    ListPrint(Mylist);

    // 将链表的元素放到栈中
    for (int i = 0; i < lenght; i++) {
        ListGetValue(Mylist, i, &val1);
        StackPush(Mystack, val1);
    }
    StackPrint(Mystack);

    for (int i = 0; i < lenght; i++) {
        ListGetValue(Mylist, i, &val1);
        StackPop(Mystack, &val2);
        if (val1 != val2) {
            isAnagrams = false;
            break;
        }
    }

    printf("linklist %s anagram\n", isAnagrams ? "true" : "false");

    return 0;
}
