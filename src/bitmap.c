#include "../include/bitmap.h"

#include <malloc.h>
#include <stdio.h>


/* Функция создания битового массива определенной размерности для n-разрядной машины
*/
void bitmap__creator(struct Bitmap * bitmap, unsigned short len_port)
{
   unsigned short temp_celiy; 
   unsigned short temp_drob;
   unsigned short size_mashina;
	
	bitmap->magic =  BITMAP_MAGIC;
	bitmap->size = len_port;
	
	/// определение разрядности машины 
	size_mashina = sizeof(unsigned long) * 8;
	
	/// определение необходимого количества разрядов порта
	temp_celiy = bitmap->size / size_mashina;
	temp_drob = bitmap->size % size_mashina;
	
	if (0 == temp_drob)
	{
	     bitmap->bit_array = (unsigned long*)calloc(temp_celiy,sizeof(unsigned long)); 
	}
	 else
	  {
          bitmap->bit_array = (unsigned long*)calloc(temp_celiy+1,sizeof(unsigned long));
      }		    
    
    if (NULL == bitmap->bit_array) 
    {
		// недо­статочно памяти  для выделения битовой карты
		perror("callok error");
		exit(2);
	}    	 
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
