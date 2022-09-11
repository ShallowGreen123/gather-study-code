/************************************************************************
 * FilePath     : c_class.c
 * Author       : GX.Duan
 * Date         : 2022-09-11 17:37:06
 * LastEditTime : 2022-09-11 17:37:32
 * LastEditors  : ShallowGreen123 2608653986@qq.com
 * Copyright (c): 2022 by GX.Duan, All Rights Reserved.
 * Github       : https://github.com/ShallowGreen123/lvgl_mydemo
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
/************************ 封装 ***********************************/
// typedef struct shape {
//     int x;
//     int y;
// } SHAPE;

// struct shape *shape_create(int x, int y) {
//     struct shape *s = (SHAPE *)malloc(sizeof(SHAPE));
//     s->x            = x;
//     s->y            = y;
//     return s;
// }

// void shape_init(SHAPE *s, int x, int y) {
//     s->x = x;
//     s->y = y;
// }

// void shape_move(SHAPE *s, int x, int y) {
//     s->x = x;
//     s->y = y;
// }
/************************** 继承 *********************************/
// typedef struct rectangle {
//     struct shape base;
//     int          witch;
//     int          hight;
// } RECTANGE;

// struct rectangle *rectangle_create(int x, int y, int w, int h) {
//     struct rectangle *r = (RECTANGE *)malloc(sizeof(RECTANGE));
//     shape_init((struct shape *)r, x, y);
//     r->witch = w;
//     r->hight = h;
//     return r;
// }
/************************** 多态 *********************************/
typedef struct NewShape {
    struct ShapeVtbl {
        void (*postion)(struct NewShape *self);
        void (*size)(struct NewShape *self);
    };
    int x;
    int y;
} NEW_SHAPE;

typedef struct rectangle {
    struct NewShape base;
    int             witch;
    int             hight;
} RECTANGE;

void co_postion(NEW_SHAPE *self) {
    self->postion(self);
}
void co_size(NEW_SHAPE *self) {
    self->size(self);
}

// shape
void shape_pos(NEW_SHAPE *s) {
    printf("shape_pos\n");
}

void shape_size(NEW_SHAPE *s) {
    printf("shape_size\n");
}

struct NewShape *shape_create(int x, int y) {
    struct NewShape *s = (NEW_SHAPE *)malloc(sizeof(NEW_SHAPE));
    s->postion         = shape_pos;
    s->size            = shape_size;
    s->x               = x;
    s->y               = y;
    return s;
}

void shape_init(NEW_SHAPE *s, int x, int y) {
    s->x = x;
    s->y = y;
}

// rectangle
void rectangle_pos(NEW_SHAPE *s) {
    printf("rectangle_pos\n");
}

void rectangle_size(NEW_SHAPE *s) {
    printf("rectangle_size\n");
}

struct rectangle *rectangle_create(int x, int y, int w, int h) {
    struct rectangle *r = (RECTANGE *)malloc(sizeof(RECTANGE));
    shape_init((NEW_SHAPE *)r, x, y);
    r->base.postion = rectangle_pos;
    r->base.size    = rectangle_size;
    r->witch        = w;
    r->hight        = h;
    return r;
}

int main() {
    struct NewShape *s = shape_create(10, 10);
    co_postion(s);
    co_size(s);

    struct rectangle *r = rectangle_create(11, 11, 12, 12);
    co_postion(&r->base);
    co_size(&r->base);

    // SHAPE *shape = shape_create(10, 10);
    // shape_move(shape, 20, 20);
    // printf("x=%d \t y=%d\n", shape->x, shape->y);

    // RECTANGE *r = rectangle_create(10, 10, 11, 11);
    // shape_move((SHAPE *)r, 20, 20);
    // printf("x=%d \t y=%d\n", r->base.x, r->base.y);
    // return 0;
}
