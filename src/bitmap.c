#include "../include/bitmap.h"

#include <malloc.h>
#include <stdio.h>

/* Функция удаления битового массива.
Битовый массив должен быть создан с помощью функции создания перед удалением  
*/
int bitmap__delete(struct Bitmap * const p_bitmap)
{
    int ret = 0;
    
    if (NULL == p_bitmap) 
    {
        ret = -1;
        fprintf(stderr, "%s: arg is nullptr\n", __func__);
        goto finally;
    }
    if (BITMAP_MAGIC != p_bitmap->magic) 
    {
        ret = -2;
        fprintf(stderr, "%s: wrong magic\n", __func__);
        goto finally;
    }

    free(p_bitmap->bit_array);
    p_bitmap->bit_array = NULL;
    p_bitmap->size = 0;
    p_bitmap->magic = 0;

 finally:

    return ret; 
}

// Функция получения значения бита.
int bitmap__get_bit(
    struct Bitmap const * const p_bitmap, 
    unsigned short const bit_idx,
    unsigned char * const p_bit)
{
    int ret = 0;
    
    if (NULL == p_bitmap)
    {
        ret = -1;
        fprintf(stderr, "%s: p_bitmap is nullptr\n", __func__);
        goto finally;
    }
    else if (BITMAP_MAGIC != p_bitmap->magic)
    {
        ret = -2;
        fprintf(stderr, "%s: wrong magic\n", __func__);
        goto finally;        
    }
    else if (NULL == p_bitmap->bit_array)
    {
        ret = -3;
        fprintf(stderr, "%s: bit array pointer is nullptr\n", __func__);
        goto finally;
    }
    else if (bit_idx >= p_bitmap->size)
    {
        ret = -4;
        fprintf(stderr, "%s: bit index is out of range\n", __func__);
        goto finally;
    }
    else if (NULL == p_bit)
    {
        ret = -5;
        fprintf(stderr, "%s: p_bit is nullptr\n", __func__);
        goto finally;        
    }

    unsigned short long_idx = 0;
    unsigned long target_long = 0;
    unsigned short bit_offset = 0;
    unsigned long mask = 0;
    // Вычисление позиции целевого бита в масиве
    // sizof(long) умножается на 8, потому что нужен размер в битах
    long_idx = bit_idx / (sizeof(unsigned long) * 8);
    target_long = p_bitmap->bit_array[long_idx];
    bit_offset = bit_idx % (sizeof(unsigned long) * 8);
    /*Сдвигаем 1 влево в нужную позицию
    для первого бита (bit_offset == 0) сдвиг будет на sizeof(long) * 8 - 1
    Для последнего бита bit_offset == sizeof(long) * 8 - 1
    Поэтому сдвигаем на sizeof(long) * 8 - (sizeof(long) * 8 - 1) - 1 == 0
    */
    mask = (unsigned long)1 << (sizeof(unsigned long) * 8 - bit_offset - 1);
    *p_bit = ((target_long & mask) != 0);

 finally:
    
    return ret;
}

// Функция для узнавания размера битмапа
int bitmap__get_size(
    struct Bitmap const * const p_bitmap, 
    unsigned short * const p_size)
{
    int ret = 0;
    
    if (NULL == p_bitmap) 
    {
        ret = -1;
        fprintf(stderr, "%s: p_bitmap is nullptr\n", __func__);
        goto finally;
    }
    else if (BITMAP_MAGIC != p_bitmap->magic) 
    {
        ret = -2;
        fprintf(stderr, "%s: wrong magic\n", __func__);
        goto finally;
    }
    else if (NULL == p_size)
    {
        ret = -3;
        fprintf(stderr, "%s: p_size is nullptr\n", __func__);
        goto finally;
    }

    *p_size = p_bitmap->size;

 finally:
    
    return ret;
}