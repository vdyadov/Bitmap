#include "../../include/bitmap.h"

#include <tap.h>

#include <stdio.h>
#include <malloc.h>

//A simple test with libtap
//compile with -l tap
int main(void)
{
    struct Bitmap bmap = {NULL, 0, 0};
    struct Bitmap bmap_2 = {NULL, 0, 0};

    plan(7);
    
    ok(-1 == bitmap__and(NULL, NULL), "acessing a NULL fails with -1");

    ok(-2 == bitmap__and(&bmap, &bmap_2), 
                             "magic number uncorrect fails with -2");
    
    bmap.magic = BITMAP_MAGIC;
    ok(-3 == bitmap__and(&bmap, &bmap_2), "acessing bitmap with bit_array == NULL"
                                        " fails with -3");

    bmap.bit_array = calloc(1, sizeof(unsigned long));
    bmap.size = sizeof(unsigned long) * 8;
    
    ok(-4 == bitmap__and(&bmap, NULL), "acessing a NULL fails with -4");

    ok(-5 == bitmap__and(&bmap, &bmap_2), 
                             "magic number uncorrect fails with -2");

    bmap_2.magic = BITMAP_MAGIC;
    ok(-6 == bitmap__and(&bmap, &bmap_2), "acessing bitmap with bit_array == NULL"
                                        " fails with -6");
    
    bmap_2.bit_array = calloc(1, sizeof(unsigned long));
    bmap_2.size = sizeof(unsigned long) * 8;

    // 01011001... is how I want the number to look
    bitmap__set_bit(&bmap, 1);
    bitmap__set_bit(&bmap, 3);
    bitmap__set_bit(&bmap, 4);
    bitmap__set_bit(&bmap, 7);

    bitmap__copy_bit(&bmap_2, &bmap);
    ok(*bmap.bit_array == *bmap_2.bit_array, "copy bits work correctly");
    
    free(bmap.bit_array);
    return 0;
}
