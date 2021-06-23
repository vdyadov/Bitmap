#ifndef BITMAP_ITERATOR_H
#define BITMAP_ITERATOR_H

#include "bitmap.h"

#include <stddef.h>
#include <stdio.h>

typedef struct Bitmap_iterator
{
    // Указатель на битмап, с которым связан итератор
    struct Bitmap *p_bitmap;
    // Индекс бита, на который указывает итератор
    unsigned short bit_idx;
    // Флаг, говорящий о том, что bit_idx указывает за границу массива (биты закончились)
    unsigned char end_flag;
} Bitmap_iterator;

// Связать итератор с *p_bitmap и установить bit_idx на ноль
int bitmap_iterator__init(
    struct Bitmap_iterator *p_iter,
    struct Bitmap *p_bitmap);

// Перейти к следующей единице
int bitmap_iterator__next_up(struct Bitmap_iterator *p_iter);

// Перейти к следующему нулю
int bitmap_iterator__next_down(struct Bitmap_iterator *p_iter);

// Перейти к следующему биту
int bitmap_iterator__next(struct Bitmap_iterator *p_iter);

// Найти первую единицу в массиве
int bitmap_iterator__begin_up(struct Bitmap_iterator *p_iter);

// Найти первый ноль в массиве
int bitmap_iterator__begin_down(struct Bitmap_iterator *p_iter);

#endif