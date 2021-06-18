#include "../../include/bitmap.h"

#include <tap.h>

#include <stdio.h>
#include <malloc.h>

//A simple test with libtap
//compile with -l tap
int main(void)
{
    plan(9);
    struct Bitmap bmap = {NULL, 0, 0};
    unsigned char bit = 0;

    ok(-2 == bitmap__get_bit(&bmap, 0, &bit), 
                             "acessing an uncreated bitmap fails with -2");

    bmap.magic = BITMAP_MAGIC;
    ok(-3 == bitmap__get_bit(&bmap, 0, &bit), "acessing bitmap with bit_array == NULL"
                                              " fails with -3");
    ok(-1 == bitmap__get_bit(NULL, 0, &bit), "acessing a NULL fails with -1");

    bmap.bit_array = malloc(sizeof(unsigned long));
    ok(-4 == bitmap__get_bit(&bmap, 0, &bit), "acessing a bitmap with allocated bit_array"
                                              " but with size == 0 fails with -4");

    bmap.size = sizeof(unsigned long) * 8;
    ok(-5 == bitmap__get_bit(&bmap, 0, NULL),
                             "acessing a bitmap with p_bit == NULL fails with -5");

    (*bmap.bit_array) = 0;
    unsigned char expression = (bitmap__get_bit(&bmap, 0, &bit) == 0);
    ok(expression && (bit == 0), 
        "acessing succeeds and returns correct bit value");
    
    //0101000... is how I want the number to look
    (*bmap.bit_array) |= (unsigned long)1 << (sizeof(unsigned long) * 8 - 1 - 1);
    (*bmap.bit_array) |= (unsigned long)1 << (sizeof(unsigned long) * 8 - 1 - 3);


    bitmap__get_bit(&bmap, 1, &bit);
    ok(bit, "bit 1 extracted correctly");
    bitmap__get_bit(&bmap, 2, &bit);
    ok(0 == bit, "bit 2 extracted correctly");
    bitmap__get_bit(&bmap, 3, &bit);
    ok(bit, "bit 3 extracted correctly");

    free(bmap.bit_array);
    return 0;
}
