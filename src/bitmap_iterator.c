#include "../include/bitmap_iterator.h"

// Связать итератор с *p_bitmap и установить bit_idx на ноль
int bitmap_iterator__init(
    struct Bitmap_iterator * const p_iter,
    struct Bitmap * const p_bitmap)
{
    int ret = 0;
    unsigned short bitmap_size = 0;

    if (NULL == p_bitmap) 
    {
        ret = -1;
        fprintf(stderr, "%s: p_bitmap is nullptr\n", __func__);
        goto finally;
    }
    else if (NULL == p_iter) 
    {
        ret = -3;
        fprintf(stderr, "%s: p_iter is nullptr\n", __func__);
        goto finally;
    }    
    else if (BITMAP_MAGIC != p_bitmap->magic) 
    {
        ret = -2;
        fprintf(stderr, "%s: wrong magic\n", __func__);
        goto finally;
    }

    p_iter->p_bitmap = p_bitmap;
    p_iter->bit_idx = 0;
    bitmap__get_size(p_bitmap, &bitmap_size);
    (bitmap_size > 0) ? (p_iter->end_flag = 0) : (p_iter->end_flag = 1);

 finally:

    return ret;
}

// Перейти к следующему биту
int bitmap_iterator__next(struct Bitmap_iterator *p_iter)
{
    int ret = 0;
    unsigned short bitmap_size = 0;
    
    if (NULL == p_iter) 
    {
        ret = -3;
        fprintf(stderr, "%s: p_iter is nullptr\n", __func__);
        goto finally;
    }
    else if (p_iter->end_flag)
    {
        ret = -4;
        fprintf(stderr, 
                "%s: incrementing a past-the-end iterator\n",
                __func__);
        goto finally;
    }

    bitmap__get_size(p_iter->p_bitmap, &bitmap_size);
    ++(p_iter->bit_idx);
    if (p_iter->bit_idx >= bitmap_size)
    {
        p_iter->end_flag = 1;
    }

 finally:

    return ret;
}

// Перейти к следующей единице
int bitmap_iterator__next_up(struct Bitmap_iterator * const p_iter)
{
    int ret = 0;
    unsigned short bitmap_size = 0;
    unsigned char bit = 0;

    if (NULL == p_iter) 
    {
        ret = -3;
        fprintf(stderr, "%s: p_iter is nullptr\n", __func__);
        goto finally;
    }
    else if (p_iter->end_flag)
    {
        ret = -4;
        fprintf(stderr, 
                "%s: incrementing a past-the-end iterator\n",
                __func__);
        goto finally;
    }

    bitmap__get_size(p_iter->p_bitmap, &bitmap_size);
    // максимально простая реализация, оптимизировать можно потом
    bitmap_iterator__next(p_iter);
    while (!p_iter->end_flag)
    {
        bitmap__get_bit(p_iter->p_bitmap, p_iter->bit_idx, &bit);
        if (bit)
        {
            break;
        }
        bitmap_iterator__next(p_iter);
    }

 finally:

    return ret;
}

// Перейти к следующему нулю
int bitmap_iterator__next_down(struct Bitmap_iterator * const p_iter)
{
    int ret = 0;
    unsigned short bitmap_size = 0;
    unsigned char bit = 0;

    if (NULL == p_iter) 
    {
        ret = -3;
        fprintf(stderr, "%s: p_iter is nullptr\n", __func__);
        goto finally;
    }
    else if (p_iter->end_flag)
    {
        ret = -4;
        fprintf(stderr, 
                "%s: incrementing a past-the-end iterator\n",
                __func__);
        goto finally;
    }

    bitmap__get_size(p_iter->p_bitmap, &bitmap_size);
    // максимально простая реализация, оптимизировать можно потом
    bitmap_iterator__next(p_iter);
    while (!p_iter->end_flag)
    {
        bitmap__get_bit(p_iter->p_bitmap, p_iter->bit_idx, &bit);
        if (!bit)
        {
            break;
        }
        bitmap_iterator__next(p_iter);
    }

 finally:

    return ret;
}

// Найти первую единицу в массиве
int bitmap_iterator__begin_up(struct Bitmap_iterator *p_iter)
{
    int ret = 0;
    unsigned char bit = 0;
    unsigned short bitmap_size = 0;

    if (NULL == p_iter) 
    {
        ret = -3;
        fprintf(stderr, "%s: p_iter is nullptr\n", __func__);
        goto finally;
    }
    else if (p_iter->end_flag)
    {
        ret = -4;
        fprintf(stderr, 
                "%s: acessing a past-the-end iterator\n",
                __func__);
        goto finally;
    }

    bitmap__get_size(p_iter->p_bitmap, &bitmap_size);
    p_iter->bit_idx = 0;
    if (p_iter->bit_idx >= bitmap_size) 
    {
        p_iter->end_flag = 1;
        goto finally;
    }
    bitmap__get_bit(p_iter->p_bitmap, p_iter->bit_idx, &bit);
    if (!bit)
    {
        bitmap_iterator__next_up(p_iter);
    }


 finally:
    return ret;
}

// Найти первый ноль в массиве
int bitmap_iterator__begin_down(struct Bitmap_iterator *p_iter)
{
    int ret = 0;
    unsigned char bit = 0;
    unsigned short bitmap_size = 0;

    if (NULL == p_iter) 
    {
        ret = -3;
        fprintf(stderr, "%s: p_iter is nullptr\n", __func__);
        goto finally;
    }
    else if (p_iter->end_flag)
    {
        ret = -4;
        fprintf(stderr, 
                "%s: acessing a past-the-end iterator\n",
                __func__);
        goto finally;
    }

    bitmap__get_size(p_iter->p_bitmap, &bitmap_size);
    p_iter->bit_idx = 0;
    if (p_iter->bit_idx >= bitmap_size) 
    {
        p_iter->end_flag = 1;
        goto finally;
    }
    bitmap__get_bit(p_iter->p_bitmap, p_iter->bit_idx, &bit);
    if (bit)
    {
        bitmap_iterator__next_down(p_iter);
    }

 finally:
    return ret;
}
