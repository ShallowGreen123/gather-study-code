

#include "queue_malloc.h"

#define DEF_QUEUE_VAL_LEN_INVAILD      0xFFFF          // 队列元素的长度为 0XFFFF 时，为无效值
#define DEF_QUEUE_RESERVE_SIZE(q)      (q->bufSize - q->usedSize)
#define DEF_QUEUE_GET_VAL_SIZE(q, pos) ((0xFF & q->buf[pos]) | ((0xFF & q->buf[pos + 1]) << 8))
#define DEF_QUEUE_SET_VAL_SIZE(q, pos, val)  \
    do {                                     \
        q->buf[pos++] = 0xFF & val;          \
        q->buf[pos++] = (0xFF00 & val) >> 8; \
    } while (0)

void QueueMallocInit(queue_t *q, uint8_t *buf, uint32_t buf_size) {
    if (q != NULL) {
        q->init     = true;
        q->buf      = buf;
        q->bufSize  = buf_size;
        q->front    = 0;
        q->tail     = 0;
        q->elemCnt  = 0;
        q->usedSize = 0;
        memset(q->buf, 0, q->bufSize);
    }
}

void *QueueMallocInput(queue_t *q, void *val, val_size valSize) {
    uint32_t bufPos   = 0;
    uint32_t needSize = valSize + sizeof(val_size);

    if (q->init == false || val == NULL || valSize == 0) {
        return NULL;
    }

    if (q->elemCnt > 0) {
        bufPos = q->tail + DEF_QUEUE_GET_VAL_SIZE(q, q->tail);
        if (q->tail >= q->front) {          // tail 在 front 后面，队列还没有循环
            if (q->bufSize - bufPos < needSize) {
                if (bufPos + sizeof(val_size) <= q->bufSize) {
                    DEF_QUEUE_SET_VAL_SIZE(q, bufPos, DEF_QUEUE_VAL_LEN_INVAILD);
                }
                bufPos = 0;
            }
        } else {          // front 在 tail 后面，队列已经循环
            if (q->front - bufPos < needSize) {
                return NULL;          // 没有空间
            }
        }
    }

    q->tail = bufPos;
    DEF_QUEUE_SET_VAL_SIZE(q, bufPos, needSize);          // bufPos 会 +2，偏移 sizeof(valSize)

    memcpy((void *)&q->buf[bufPos], val, valSize);          // 保存数据 val

    q->usedSize += needSize;
    q->elemCnt++;

    return (void *)&q->buf[bufPos];
}

void *QueueMallocOutput(queue_t *q, val_size *size) {
    void    *value;
    uint32_t dataSize;

    if (q->init == false || q->elemCnt == 0) {
        return NULL;
    }

    if (size) {
        *size = DEF_QUEUE_GET_VAL_SIZE(q, q->front);
    }
    dataSize = DEF_QUEUE_GET_VAL_SIZE(q, q->front);
    value    = &q->buf[q->front + sizeof(val_size)];

    q->front += dataSize;

    q->usedSize -= dataSize;
    q->elemCnt--;

    if ((q->elemCnt == 0)
        || (q->front + sizeof(val_size) >= q->bufSize)
        || (DEF_QUEUE_GET_VAL_SIZE(q, q->front) == DEF_QUEUE_VAL_LEN_INVAILD)) {
        q->front = 0;
    }
    return value;
}

bool QueueMallocSpaceChk(queue_t *q, val_size size) {
    uint32_t bufPos   = 0;
    uint32_t needSize = size + sizeof(val_size);

    if (q->init == false || (DEF_QUEUE_RESERVE_SIZE(q) < needSize)) {
        return false;
    }

    if (q->elemCnt > 0) {
        bufPos = q->tail + DEF_QUEUE_GET_VAL_SIZE(q, q->tail);
        if (q->tail >= q->front) {
            if ((q->bufSize - bufPos < needSize) && (q->front < needSize)) {
                return false;
            }
        } else {
            if (q->front - bufPos < needSize) {
                return false;
            }
        }
    }
    return true;
}

void *QueueMallocPeek(queue_t *q, val_size *size) {
    if (q->init == false || q->elemCnt == 0) {
        return NULL;
    }

    if (size) {
        *size = DEF_QUEUE_GET_VAL_SIZE(q, q->front);
    }
    return (void *)&q->buf[q->front + sizeof(val_size)];
}

void *QueueMallocPeekAfter(queue_t *q, void *cur_item, val_size *size) {
    uint32_t bufPos = (uint8_t *)cur_item - q->buf - sizeof(val_size);
    uint32_t itemSize;

    if (q->init == false || q->elemCnt == 0 || q->tail == bufPos) {
        return NULL;
    }

    if (bufPos + sizeof(val_size) >= q->bufSize) {
        bufPos = 0;
    }

    bufPos   = bufPos + DEF_QUEUE_GET_VAL_SIZE(q, bufPos);
    itemSize = DEF_QUEUE_GET_VAL_SIZE(q, bufPos);
    if (itemSize == DEF_QUEUE_VAL_LEN_INVAILD) {
        bufPos   = 0;
        itemSize = DEF_QUEUE_GET_VAL_SIZE(q, bufPos);
    }

    if (size) {
        *size = itemSize;
    }
    return (void *)&q->buf[bufPos + sizeof(val_size)];
}

void QueueMallocClear(queue_t *q) {
    q->front    = 0;
    q->tail     = 0;
    q->elemCnt  = 0;
    q->usedSize = 0;
}

uint32_t QueueMallocGetCnt(queue_t *q) {
    return q->elemCnt;
}

/****************************** test ***************************************/
// config
#define DEF_QUEUE_BUF_SIZE 1024

#if 0

// test
queue_t que1;
uint8_t buff[DEF_QUEUE_BUF_SIZE];
//
int main() {
    uint16_t size;
    char    *sp;
    char     str1[12] = "hello!";
    char     str2[16] = "world124";
    char     str3[16] = "Abcdefg";

    // init
    QueueMallocInit(&que1, buff, sizeof(buff));

    // push
    sp = QueueMallocInput(&que1, str1, strlen(str1) + 1);
    printf("str1 = %s, used=%d/%d, tail=%d\n", sp, que1.usedSize, que1.bufSize, que1.tail);

    sp = QueueMallocInput(&que1, str2, strlen(str2) + 1);
    if (sp)
        printf("v = %s, used=%d/%d, tail=%d\n", sp, que1.usedSize, que1.bufSize, que1.tail);

    if (QueueMallocSpaceChk(&que1, strlen(str3) + 1)) {
        sp = QueueMallocInput(&que1, str3, strlen(str3) + 1);
        printf("v = %s, used=%d/%d, tail=%d\n", sp, que1.usedSize, que1.bufSize, que1.tail);
    }

    sp = QueueMallocPeek(&que1, NULL);
    printf("peek = %s\n", sp);

    sp = QueueMallocPeekAfter(&que1, sp, NULL);
    printf("peek after = %s\n", sp);

    sp = QueueMallocPeekAfter(&que1, sp, NULL);
    printf("peek after = %s\n", sp);

    printf("******* pop *****\n");
    // pop

    sp = QueueMallocOutput(&que1, &size);
    printf("size=%d, str1=%s, cnt=%d\n", size, sp, QueueMallocGetCnt(&que1));

    return 0;
}
#endif