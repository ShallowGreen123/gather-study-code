
#include "linklist2.h"
#include <string.h>

#define DEF_NODE_P_SIZE          (sizeof(_node_p_ *) + sizeof(_node_p_ *))
#define DEF_PREV_NODE_OFFS(ll_p) (ll_p->size)
#define DEF_NEXT_NODE_OFFS(ll_p) (ll_p->size + sizeof(_node_p_ *))
#define DEF_MALLOC(s)            malloc(s)

static void list_node_p_set_prev(linklist2_t *p, _node_p_ *act, _node_p_ *prev);
static void list_node_p_set_next(linklist2_t *p, _node_p_ *act, _node_p_ *next);

//
linklist2_t mylist2;

struct data {
    int   age;
    char  name[16];
    float soc;
};

int arr[5] = {1, 3, 2, 4, 5};

//
int main()
{
    struct data stu = {.age = 23, .name = "nike", .soc = 89.7};

    list_init_2(&mylist2, sizeof(struct data));

    struct data *p = list_ins_head_2(&mylist2);
    *p             = stu;

    int          age;
    char         name[16];
    float        soc;

    struct data *stu1 = (struct data *)(mylist2.head);
    age               = stu1->age;
    strcpy(name, stu1->name);
    soc = stu1->soc;

    printf("name=%s  age=%d  soc=%0.2f\n", name, age, soc);

    return 0;
}
//
void list_init_2(linklist2_t *p, uint32_t size)
{
#ifdef DEF_BYTE_ALIGN_8
    size = (size + 7) & (~0x7);
#else
    size = (size + 3) & (~0x3);
#endif
    p->head = NULL;
    p->tail = NULL;
    p->size = size;
}

void *list_ins_head_2(linklist2_t *list)
{
    _node_p_ *new_node = DEF_MALLOC(list->size + DEF_NODE_P_SIZE);

    if (new_node == NULL) return NULL;

    list_node_p_set_prev(list, new_node, NULL);
    list_node_p_set_next(list, new_node, list->head);

    if (list->head != NULL) {
        list_node_p_set_prev(list, list->head, new_node);
    }

    list->head = new_node;
    if (list->tail == NULL) {
        list->tail = new_node;
    }
    return new_node;
}

void *list_ins_prev_2(linklist2_t *list, void *act)
{
    _node_p_ *new_node;

    if (list == NULL || act == NULL) return NULL;

    if (list_get_head_2(list) == NULL) {
        new_node = list_ins_head_2(list);
        if (new_node == NULL) return NULL;
    } else {
        new_node = DEF_MALLOC(list->size + DEF_NODE_P_SIZE);
        if (new_node == NULL) return;

        _node_p_ *prev;
        prev = list_get_prev_2(list, act);
        list_node_p_set_next(list, prev, new_node);
        list_node_p_set_prev(list, new_node, prev);
        list_node_p_set_prev(list, act, new_node);
        list_node_p_set_next(list, new_node, act);
    }

    return new_node;
}

void *list_ins_tail_2(linklist2_t *list)
{
}

void list_remove_node_2(linklist2_t *list, void *node)
{
}

void list_clear_2(linklist2_t *list)
{
}

void list_chg_list_2(linklist2_t *ll_ori_p, linklist2_t *ll_new_p, void *node, bool head)
{
}

void *list_get_head_2(const linklist2_t *list)
{
    if (list == NULL) return NULL;
    return list->head;
}

void *list_get_tail_2(const linklist2_t *list)
{
    if (list == NULL) return NULL;
    return list->tail;
}

void *list_get_next_2(const linklist2_t *list, const void *n_act)
{
    if (list == NULL || n_act == NULL) return;
    const linklist2_t *next_n = n_act;
    next_n += DEF_NEXT_NODE_OFFS(list);
    return *((_node_p_ **)next_n);
}

void *list_get_prev_2(const linklist2_t *list, const void *n_act)
{
    if (list == NULL || n_act == NULL) return;
    const linklist2_t *prev_n = n_act;
    prev_n += DEF_PREV_NODE_OFFS(list);
    return *((_node_p_ **)prev_n);
}

uint32_t list_get_len_2(const linklist2_t *ll_p)
{
    uint32_t len = 0;
    void    *node;

    for (node = list_get_head_2; node != NULL; node = list_get_next_2(ll_p, node)) {
        len++;
    }
    return len;
}

bool list_is_empty_2(linklist2_t *list)
{
    if (list == NULL) return true;

    if (list->head == NULL && list->tail == NULL) return true;

    return false;
}

/* staic */
static void list_node_p_set_prev(linklist2_t *p, _node_p_ *act, _node_p_ *prev)
{
    if (act == NULL) return;

    uint8_t *act8 = (uint8_t *)act;

    act8 += DEF_PREV_NODE_OFFS(p);

    _node_p_ **act_node_p_p  = (_node_p_ **)act8;
    _node_p_ **prev_node_p_p = (_node_p_ **)&prev;

    *act_node_p_p            = *prev_node_p_p;
}

static void list_node_p_set_next(linklist2_t *p, _node_p_ *act, _node_p_ *next)
{
    if (act == NULL) return;

    uint8_t *act8 = (uint8_t *)act;

    act8 += DEF_NEXT_NODE_OFFS(p);

    _node_p_ **act_node_p_p  = (_node_p_ **)act8;
    _node_p_ **next_node_p_p = (_node_p_ **)&next;
    *act_node_p_p            = *next_node_p_p;
}