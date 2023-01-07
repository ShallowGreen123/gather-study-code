
#include "queue.h"

void QueueInit(queue_t *q) {
    if (q != NULL) {
        q->front = 0;
        q->tail  = 0;
    }
}

void QueueInput(queue_t *q, int val) {
    if ((q->tail + 1) % DEF_RING_QUEUE_SIZE == q->front) {
        return;          // 队列满
    }
    q->buf[q->tail] = val;
    q->tail         = (q->tail + 1) % DEF_RING_QUEUE_SIZE;
}

void QueueOutput(queue_t *q, int *val) {
    if ((q->front + 1) % DEF_RING_QUEUE_SIZE == q->tail) {
        return;          // 队列空
    }
    *val     = q->buf[q->front];
    q->front = (q->front + 1) % DEF_RING_QUEUE_SIZE;
}

void QueuePrint(queue_t *q) {
    int i = q->front;

    while (i != q->tail) {
        printf("%d ", q->buf[i]);
        i = (i + 1) % DEF_RING_QUEUE_SIZE;
    }
    printf("\n");
}

//
queue_t que;
//
int main() {
    int val;

    QueueInit(&que);

    QueueInput(&que, 100);
    QueueInput(&que, 101);
    QueueInput(&que, 102);
    QueueInput(&que, 103);

    QueuePrint(&que);

    QueueOutput(&que, &val);
    printf("val = %d\n", val);

    val = 0;
    QueueOutput(&que, &val);
    printf("val = %d\n", val);

    val = 0;
    QueueOutput(&que, &val);
    printf("val = %d\n", val);

    val = 0;
    QueueOutput(&que, &val);
    printf("val = %d\n", val);

    QueuePrint(&que);

    return 0;
}