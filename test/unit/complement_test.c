#include "../../include/bitmap.h"

#include <tap.h>

#include <stdio.h>
#include <malloc.h>

//A simple test with libtap
//compile with -l tap
int main(void)
{
    struct Bitmap bmap = {NULL, 0, 0};
    char expression = 0;

    plan(5);

    ok(bitmap__invert(&bmap) == -2, "accessign an uncreated bitmap fails");
    ok(bitmap__invert(NULL) == -1, "acessing a NULL fails");
    
    bmap.magic = BITMAP_MAGIC;
    ok(-3 == bitmap__invert(&bmap), 
       "accessing a bitmap with bit_array == NULL fails");
    
    bmap.bit_array = malloc(3 * sizeof(unsigned long));
    ok(0 == bitmap__invert(&bmap), "accessing a bitmap succeeds");

    bmap.size = sizeof(unsigned long) * 3 * 8 - 2;
    bmap.bit_array[0] = 0xffffabab1212;
    bmap.bit_array[1] = 2;
    bmap.bit_array[2] = 4;
    bitmap__invert(&bmap);
    
    expression = (  bmap.bit_array[0] == (unsigned long)~0xffffabab1212
                 && bmap.bit_array[1] == (unsigned long)~2
                 && bmap.bit_array[2] == (unsigned long)~4);
    ok(expression, "bitmap is inverted");

    free(bmap.bit_array);
    done_testing();
    return 0;
}
