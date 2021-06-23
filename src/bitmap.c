#include "../include/bitmap.h"

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h> 

// Функция создания битового массива определенной размерности для n-разрядной машины
int bitmap__creator(
    struct Bitmap * p_bitmap,
    unsigned short len_port)
{
    unsigned short amount_ports = 0; 
    unsigned short check_divide_ports = 0;
    unsigned short size_mashina = 0;
    
    int ret = 0;
    
    if (NULL == p_bitmap) 
    {
        ret = -1;
        fprintf(stderr, "%s: указатель битовой карты не проинициализирован ", __func__ );
        goto finally;
    }
   
	p_bitmap->magic = BITMAP_MAGIC;
	p_bitmap->size = len_port;
	
	/// определение разрядности машины 
	size_mashina = sizeof(unsigned long) * 8;
	
	/// определение количества разрядности выделяемой памяти,для хранения состояния портов
	amount_ports = p_bitmap->size / size_mashina;
	check_divide_ports = p_bitmap->size % size_mashina;
	   
	if (0 == check_divide_ports)
	{
	     p_bitmap->bit_array = (unsigned long*)calloc(amount_ports,sizeof(unsigned long)); 
	}
	else
	{
         p_bitmap->bit_array = (unsigned long*)calloc(amount_ports+1,sizeof(unsigned long));
    }		    
    
    if (NULL == p_bitmap->bit_array) 
    {
		 // недо­статочно памяти  для выделения битовой карты
		 fprintf(stderr, "%s: недо­статочно памяти  для выделения битовой карты", __func__ );
		 ret = -2;
		 goto finally;
	}    
		 
 finally:

    return ret; 
}	


// Функция обнуления конкретного бита
int bitmap__setNull_bit(
    struct Bitmap * p_bitmap,
    unsigned short bit_idx) 
{  
	unsigned short size_mashina = 0;
	unsigned short full_sector = 0;
    unsigned short bit_offset = 0;
    unsigned long mask = 0;
	
    int ret = 0;

    if (NULL == p_bitmap)
    {
        ret = -1;
        fprintf(stderr, "%s: указатель битовой карты не проинициализирован", __func__);
        goto finally;
    }
    else if (BITMAP_MAGIC != p_bitmap->magic)
    { 
        ret = -2;
        fprintf(stderr, "%s: магическое число изменено \n", __func__);
        goto finally;
    }
    else if (NULL == p_bitmap->bit_array)
    { 
        ret = -3;
        fprintf(stderr, "%s:  недо­статочно памяти  для выделения портов битовой карты \n", __func__);
        goto finally;
    }
    else if (bit_idx >= p_bitmap->size)
    {
        ret = -4;
        fprintf(stderr, "%s: номер бита для обнуления больше количества портов битовой карты \n", __func__);
        goto finally;
    }
    
    // Вычисление позиции целевого бита в масcиве ячеек памяти битовой карты и вычисление маски
    
    /// определение разрядности машины 
	size_mashina = sizeof(unsigned long) * 8;
	
	/** для определение координаты обнуляемого бита,найдём количество заполненных ячеек памяти 
	* с учетом разрядности машины,т.е.индекс в массиве bit_array битовой карты
	*/
	full_sector  = bit_idx / size_mashina;
	
	/// позиция бита в незаполненной ячейке памяти
	bit_offset = bit_idx % size_mashina;
	
	/// накладываемая маска для обнуления соответствующего бита	
    mask = (unsigned long) (1 << bit_offset);
    
    // операция обнуления конкретного бита
    p_bitmap->bit_array[full_sector] &=~ mask;
   
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

// Функция установки конкретного бита
int bitmap__set_bit(
    struct Bitmap * const p_bitmap,
    unsigned short const bit_idx) 
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
    
    unsigned short long_idx = 0;
    unsigned short bit_offset = 0;
    unsigned long mask = 0;

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
