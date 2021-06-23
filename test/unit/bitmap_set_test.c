#include "../../include/bitmap.h"

#include <tap.h>

#include <stdio.h>
#include <malloc.h>

//A simple test with libtap
//compile with -l tap
int main(void)
{
    struct Bitmap bmap = {NULL, 0, 0};
    unsigned char bit = 0;
    
    plan(7);
    
    ok(-1 == bitmap__set_bit(NULL, 0), "acessing a NULL fails with -1");

    ok(-2 == bitmap__set_bit(&bmap, 0), 
                             "acessing an uncreated bitmap fails with -2");

    bmap.magic = BITMAP_MAGIC;
    ok(-3 == bitmap__set_bit(&bmap, 0), "acessing bitmap with bit_array == NULL"
                                        " fails with -3");

    bmap.bit_array = malloc(sizeof(unsigned long));
    bmap.size = sizeof(unsigned long) * 8;
    
    ok(-4 == bitmap__set_bit(&bmap, (unsigned short)(bmap.size + 1)), 
                             "acessing a bitmap with allocated bit_array"
                             " but with size == 0 fails with -4");

    //0101000... is how I want the number to look
    
    bitmap__set_bit(&bmap, 1);
    bitmap__set_bit(&bmap, 3);

    bitmap__get_bit(&bmap, 1, &bit);
    ok(bit, "bit 1 installed correctly");
    bitmap__get_bit(&bmap, 2, &bit);
    ok(0 == bit, "bit 2 extracted correctly");
    bitmap__get_bit(&bmap, 3, &bit);
    ok(bit, "bit 3 installed correctly");

    free(bmap.bit_array);
    return 0;
}
