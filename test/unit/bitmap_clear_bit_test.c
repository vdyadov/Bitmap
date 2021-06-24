#include "../../include/bitmap.h"

#include <tap.h>
#include <malloc.h>
#include <stdio.h> 
#include <stdlib.h> 

int main(void)
{
    struct Bitmap bmap = {NULL, 0, 0};
    unsigned char bit = 0;
 
    plan(6);

    ok(-1 == bitmap__clear_bit(NULL, 2), "казатель битовой карты не проинициализирован: -1");

    ok(-2 == bitmap__clear_bit(&bmap, 2), 
                               "магическое число изменено,битовая карта повреждена: -2");
    
    bmap.magic = BITMAP_MAGIC;
    ok(-3 == bitmap__clear_bit(&bmap, 2), "недостаточно памяти для выделения портов: 3");
    
    bmap.bit_array = calloc(1,sizeof(unsigned long));    
    ok(-4 == bitmap__clear_bit(&bmap, sizeof(unsigned long)*8+2), 
                                      "номер порта для обнуления больше количества портов: -4"); 
    
    bitmap__set_bit(&bmap, 2);
    bitmap__get_bit(&bmap, 2, &bit);
    ok(bit, "бит 2 установлен");
    
    bitmap__clear_bit(&bmap,2);
    bitmap__get_bit(&bmap, 2, &bit);
    ok(0 == bit, "бит 2 очищен");
        
    free(bmap.bit_array);
      
    return 0;
}
    
