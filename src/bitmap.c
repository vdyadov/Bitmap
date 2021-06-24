#include "../include/bitmap.h"

#include <malloc.h>
#include <stdio.h>
#include <string.h>

// Функция создания битового массива определенной размерности для n-разрядной машины
int bitmap__create(
    struct Bitmap * p_bitmap,
    unsigned short len_port)
{
    unsigned long amount_ports = 0; 
    unsigned short correction = 0;

    int ret = 0;

    if (NULL == p_bitmap) 
    {
        ret = -1;
        fprintf(stderr, "%s: указатель битовой карты не проинициализирован ", __func__ );
        goto finally;
    }

    p_bitmap->magic = BITMAP_MAGIC;
    p_bitmap->size = len_port;

    /// определение количества разрядности выделяемой памяти,для хранения состояния портов
    ((p_bitmap->size % sizeof(unsigned long)) == 0) ? (correction = 0) : (correction = 1);
    amount_ports = (unsigned short)
                    (p_bitmap->size / (sizeof(unsigned long) * 8) + correction);
	
    p_bitmap->bit_array = calloc(amount_ports, sizeof(unsigned long));	    

    if (NULL == p_bitmap->bit_array) 
    {
        // недостаточно памяти  для выделения битовой карты
        fprintf(stderr, "%s: недо­статочно памяти  для выделения битовой карты",
                __func__ );
        ret = -2;
        goto finally;
    } 

 finally:

    return ret; 
}

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
    unsigned short long_idx = 0;
    unsigned long target_long = 0;
    unsigned short bit_offset = 0;
    unsigned long mask = 0;

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

// Функция установки конкретного бита
int bitmap__set_bit(
    struct Bitmap * const p_bitmap,
    unsigned short const bit_idx) 
{  
    int ret = 0;
    unsigned short long_idx = 0;
    unsigned short bit_offset = 0;
    unsigned long mask = 0;

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

    // Вычисление позиции целевого бита в масиве
    // sizof(long) умножается на 8, потому что нужен размер в битах
    long_idx = bit_idx / (sizeof(unsigned long) * 8);
    bit_offset = bit_idx % (sizeof(unsigned long) * 8);
    /** Сдвигаем 1 влево в нужную позицию
    * для первого бита (bit_offset == 0) сдвиг будет на sizeof(long) * 8 - 1
    * Для последнего бита bit_offset == sizeof(long) * 8 - 1
    * Поэтому сдвигаем на sizeof(long) * 8 - (sizeof(long) * 8 - 1) - 1 == 0
    */
    mask = (unsigned long) 1 << (sizeof(unsigned long) * 8 - bit_offset - 1);
    p_bitmap->bit_array[long_idx] |= mask;

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

//Функция для обнуления всех битов битового массива.
int bitmap__clear_all(struct Bitmap * const p_bitmap)
{
    int ret = 0;
    unsigned short size_allocated = 0;
    unsigned short correction = 0;

    if (NULL == p_bitmap) 
    {
        ret = -1;
        fprintf(stderr, "%s: arg is nullptr\n", __func__);
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

    ((p_bitmap->size % sizeof(unsigned long)) == 0) ? (correction = 0) : (correction = 1);
    size_allocated = (unsigned short)
                     (p_bitmap->size / (sizeof(unsigned long) * 8) + correction);
    memset(p_bitmap->bit_array, 0, sizeof(unsigned long) * size_allocated);

 finally:

    return ret;
}

// Побитовая инверсия массива
int bitmap__invert(struct Bitmap * const p_bitmap)
{
    int ret = 0;
    unsigned short size_allocated = 0;
    unsigned short correction = 0;

    if (NULL == p_bitmap) 
    {
        ret = -1;
        fprintf(stderr, "%s: arg is nullptr\n", __func__);
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

    ((p_bitmap->size % sizeof(unsigned long)) == 0) ? (correction = 0) : (correction = 1);
    size_allocated = (unsigned short)
                     (p_bitmap->size / (sizeof(unsigned long) * 8) + correction);
    for (unsigned short i = 0; i < size_allocated; ++i)
    {
        /* это флипает лишние биты в конце, если размер не кратен размеру лонга,
        но я не думаю, что стоит это ограничивать. До них нельзя доступиться 
        функциями доступа, так что юзеру должно быть абсолютно наплевать, нули там или
        не нули
        */
        p_bitmap->bit_array[i] = ~p_bitmap->bit_array[i];
    }

 finally:

    return ret;
}

// Побитовое сравнение двух массивов.
int bitmap__equal(
    struct Bitmap const * const p_bitmap,
    struct Bitmap const * const p_bitmap_2)
{
    int ret = 0;
    int check = 1;
    unsigned short size_allocated = 0;
    unsigned short correction = 0;

    if (NULL == p_bitmap) 
    {
        ret = -1;
        fprintf(stderr, "%s: arg is nullptr\n", __func__);
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
    else if (NULL == p_bitmap_2) 
    {
        ret = -4;
        fprintf(stderr, "%s: second bitmap is nullptr\n", __func__);
        goto finally;
    }
    else if (BITMAP_MAGIC != p_bitmap_2->magic) 
    {
        ret = -5;
        fprintf(stderr, "%s: wrong magic in second bitmap\n", __func__);
        goto finally;
    }
    else if (NULL == p_bitmap_2->bit_array)
    {
        ret = -6;
        fprintf(stderr, "%s: in second bitmap bit array pointer is nullptr\n", __func__);
        goto finally;
    }
    else if (p_bitmap->size != p_bitmap_2->size)
    {
        ret = -7;
        fprintf(stderr, "%s: these bitmaps have different sizes", __func__);
        goto finally;
    }
    
    ((p_bitmap->size % sizeof(unsigned long)) == 0) ? (correction = 0) : (correction = 1);
    size_allocated = (unsigned short)
                     (p_bitmap->size / (sizeof(unsigned long) * 8) + correction);

    for (int i = 0; i < size_allocated; ++i)
    {
        if (p_bitmap->bit_array[i] == p_bitmap_2->bit_array[i])
        {
            check = 0;
        }
        else 
        {
            check = 1;
            break;
        }
    }

    ret = check;

 finally:

    return ret;
}

// Побитовое AND для массивов, результат записывается в первый аргумент.
int bitmap__and(
    struct Bitmap * const p_bitmap,
    struct Bitmap const * const p_bitmap_2)
{
    int ret = 0;
    unsigned short size_allocated = 0;
    unsigned short correction = 0;

    if (NULL == p_bitmap) 
    {
        ret = -1;
        fprintf(stderr, "%s: arg is nullptr\n", __func__);
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
    else if (NULL == p_bitmap_2) 
    {
        ret = -4;
        fprintf(stderr, "%s: second bitmap is nullptr\n", __func__);
        goto finally;
    }
    else if (BITMAP_MAGIC != p_bitmap_2->magic) 
    {
        ret = -5;
        fprintf(stderr, "%s: wrong magic in second bitmap\n", __func__);
        goto finally;
    }
    else if (NULL == p_bitmap_2->bit_array)
    {
        ret = -6;
        fprintf(stderr, "%s: in second bitmap bit array pointer is nullptr\n", __func__);
        goto finally;
    }
    else if (p_bitmap->size != p_bitmap_2->size)
    {
        ret = -7;
        fprintf(stderr, "%s: these bitmaps have different sizes", __func__);
        goto finally;
    }
    
    ((p_bitmap->size % sizeof(unsigned long)) == 0) ? (correction = 0) : (correction = 1);
    size_allocated = (unsigned short)
                     (p_bitmap->size / (sizeof(unsigned long) * 8) + correction);

    for (int i = 0; i < size_allocated; ++i)
    {
        p_bitmap->bit_array[i] &= p_bitmap_2->bit_array[i];
    }

 finally:

    return ret;
}

// Побитовое ИЛИ, результат записывается в первый аргумент
int bitmap__or(
    struct Bitmap * const p_bitmap,
    struct Bitmap const * const p_bitmap_2)
{
    int ret = 0;
    unsigned short size_allocated = 0;
    unsigned short correction = 0;

    if (NULL == p_bitmap) 
    {
        ret = -1;
        fprintf(stderr, "%s: arg is nullptr\n", __func__);
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
    else if (NULL == p_bitmap_2) 
    {
        ret = -4;
        fprintf(stderr, "%s: second bitmap is nullptr\n", __func__);
        goto finally;
    }
    else if (BITMAP_MAGIC != p_bitmap_2->magic) 
    {
        ret = -5;
        fprintf(stderr, "%s: wrong magic in second bitmap\n", __func__);
        goto finally;
    }
    else if (NULL == p_bitmap_2->bit_array)
    {
        ret = -6;
        fprintf(stderr, "%s: in second bitmap bit array pointer is nullptr\n", __func__);
        goto finally;
    }
    else if (p_bitmap->size != p_bitmap_2->size)
    {
        ret = -7;
        fprintf(stderr, "%s: these bitmaps have different sizes", __func__);
        goto finally;
    }

    ((p_bitmap->size % sizeof(unsigned long)) == 0) ? (correction = 0) : (correction = 1);
    size_allocated = (unsigned short)
                     (p_bitmap->size / (sizeof(unsigned long) * 8) + correction);

    for (unsigned short i = 0; i < size_allocated; ++i)
    {
        p_bitmap->bit_array[i] |= p_bitmap_2->bit_array[i];
    }

 finally:

    return ret;    
}

// Побитовое исключающее или, результат записывается в первый аргумент
int bitmap__xor(
    struct Bitmap * const p_bitmap,
    struct Bitmap const * const p_bitmap_2)
{
    int ret = 0;
    unsigned short size_allocated = 0;
    unsigned short correction = 0;

    if (NULL == p_bitmap) 
    {
        ret = -1;
        fprintf(stderr, "%s: arg is nullptr\n", __func__);
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
    else if (NULL == p_bitmap_2) 
    {
        ret = -4;
        fprintf(stderr, "%s: second bitmap is nullptr\n", __func__);
        goto finally;
    }
    else if (BITMAP_MAGIC != p_bitmap_2->magic) 
    {
        ret = -5;
        fprintf(stderr, "%s: wrong magic in second bitmap\n", __func__);
        goto finally;
    }
    else if (NULL == p_bitmap_2->bit_array)
    {
        ret = -6;
        fprintf(stderr, "%s: in second bitmap bit array pointer is nullptr\n", __func__);
        goto finally;
    }
    else if (p_bitmap->size != p_bitmap_2->size)
    {
        ret = -7;
        fprintf(stderr, "%s: these bitmaps have different sizes", __func__);
        goto finally;
    }

    ((p_bitmap->size % sizeof(unsigned long)) == 0) ? (correction = 0) : (correction = 1);
    size_allocated = (unsigned short)
                     (p_bitmap->size / (sizeof(unsigned long) * 8) + correction);

    for (unsigned short i = 0; i < size_allocated; ++i)
    {
        p_bitmap->bit_array[i] ^= p_bitmap_2->bit_array[i];
    }

 finally:

    return ret;    
}
// Побитовое отрицание И, результат записывается в первый аргумент
int bitmap__nand(
    struct Bitmap * const p_bitmap,
    struct Bitmap const * const p_bitmap_2)
{
    int ret = 0;
    unsigned short size_allocated = 0;
    unsigned short correction = 0;

    if (NULL == p_bitmap) 
    {
        ret = -1;
        fprintf(stderr, "%s: arg is nullptr\n", __func__);
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
    else if (NULL == p_bitmap_2) 
    {
        ret = -4;
        fprintf(stderr, "%s: second bitmap is nullptr\n", __func__);
        goto finally;
    }
    else if (BITMAP_MAGIC != p_bitmap_2->magic) 
    {
        ret = -5;
        fprintf(stderr, "%s: wrong magic in second bitmap\n", __func__);
        goto finally;
    }
    else if (NULL == p_bitmap_2->bit_array)
    {
        ret = -6;
        fprintf(stderr, "%s: in second bitmap bit array pointer is nullptr\n", __func__);
        goto finally;
    }
    else if (p_bitmap->size != p_bitmap_2->size)
    {
        ret = -7;
        fprintf(stderr, "%s: these bitmaps have different sizes", __func__);
        goto finally;
    }

    ((p_bitmap->size % sizeof(unsigned long)) == 0) ? (correction = 0) : (correction = 1);
    size_allocated = (unsigned short)
                     (p_bitmap->size / (sizeof(unsigned long) * 8) + correction);

    for (unsigned short i = 0; i < size_allocated; ++i)
    {
        p_bitmap->bit_array[i] = ~(p_bitmap->bit_array[i] & p_bitmap_2->bit_array[i]);
    }

 finally:

    return ret;    
}

// Копирование битов из одного битмапа в другой, результат записывается в первый аргумент
int bitmap__copy_bit(
    struct Bitmap * const p_bitmap,
    struct Bitmap const * const p_bitmap_2)
{ 
    int ret = 0;
    unsigned short size_allocated = 0;
    unsigned short correction = 0;

    if (NULL == p_bitmap) 
    {
        ret = -1;
        fprintf(stderr, "%s: arg is nullptr\n", __func__);
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
    else if (NULL == p_bitmap_2) 
    {
        ret = -4;
        fprintf(stderr, "%s: second bitmap is nullptr\n", __func__);
        goto finally;
    }
    else if (BITMAP_MAGIC != p_bitmap_2->magic) 
    {
        ret = -5;
        fprintf(stderr, "%s: wrong magic in second bitmap\n", __func__);
        goto finally;
    }
    else if (NULL == p_bitmap_2->bit_array)
    {
        ret = -6;
        fprintf(stderr, "%s: in second bitmap bit array pointer is nullptr\n", __func__);
        goto finally;
    }
    else if (p_bitmap->size != p_bitmap_2->size)
    {
        ret = -7;
        fprintf(stderr, "%s: these bitmaps have different sizes", __func__);
        goto finally;
    }

    ((p_bitmap->size % sizeof(unsigned long)) == 0) ? (correction = 0) : (correction = 1);
    size_allocated = (unsigned short)
                     (p_bitmap->size / (sizeof(unsigned long) * 8) + correction);

    for (unsigned short i = 0; i < size_allocated; ++i)
    {
        p_bitmap->bit_array[i] = p_bitmap_2->bit_array[i];
     }

 finally:

    return ret;    
}

// Создать новую битмапу по первому аргументу и скопировать в нее массив из второго
int bitmap__copy_create(
    struct Bitmap * const p_new,
    struct Bitmap const * const p_old)
{
    int ret = 0;
    unsigned short bitmap_size = 0;

    if (NULL == p_old) 
    {
        ret = -1;
        fprintf(stderr, "%s: arg is nullptr\n", __func__);
        goto finally;
    }
    else if (BITMAP_MAGIC != p_old->magic) 
    {
        ret = -2;
        fprintf(stderr, "%s: wrong magic\n", __func__);
        goto finally;
    }
    else if (NULL == p_new)
    {
        ret = -4;
        fprintf(stderr, "%s: arg is nullptr\n", __func__);
        goto finally;
    }
    else if (NULL == p_old->bit_array)
    {
        ret = -3;
        fprintf(stderr, "%s: bit array pointer is nullptr\n", __func__);
        goto finally;
    }
    else if (p_old == p_new)
    {
        ret = -5;
        fprintf(stderr, "%s: trying to copy-construct a bitmap into itself\n", __func__);
        goto finally;
    }

    if (BITMAP_MAGIC == p_new->magic)
    {
        bitmap__delete(p_new);
    }
    bitmap__get_size(p_old, &bitmap_size);
    bitmap__create(p_new, bitmap_size);
    bitmap__copy_bit(p_new, p_old);

 finally:

    return ret;
}