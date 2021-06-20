#include "../include/bitmap.h"

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h> 

/* Функция создания битового массива определенной размерности для n-разрядной машины
*/
int bitmap__creator(
                     struct Bitmap * bitmap,
                     unsigned short len_port)
{
   unsigned short amount_ports; 
   unsigned short check_divide_ports;
   unsigned short size_mashina;
   int ret = 0;
   
	bitmap->magic =  BITMAP_MAGIC;
	bitmap->size = len_port;
	
	/// определение разрядности машины 
	size_mashina = sizeof(unsigned long) * 8;
	
	/// определение количества разрядности выделяемой памяти,для хранения состояния портов
	amount_ports = bitmap->size / size_mashina;
	check_divide_ports = bitmap->size % size_mashina;
	
	if (0 == check_divide_ports)
	{
	     bitmap->bit_array = (unsigned long*)calloc(amount_ports,sizeof(unsigned long)); 
	}
	 else
	  {
          bitmap->bit_array = (unsigned long*)calloc(amount_ports+1,sizeof(unsigned long));
      }		    
    
    if (NULL == bitmap->bit_array) 
    {
		// недо­статочно памяти  для выделения битовой карты
		printf("недо­статочно памяти  для выделения битовой карты");
		ret=-1;
	}    
		 
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
