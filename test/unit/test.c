#include "../../include/bitmap.h"

#include <tap.h>

#include <stdio.h>
#include <malloc.h>

//A simple test with libtap
//compile with -l tap
int main(void)
{
    struct Bitmap bmap = {NULL, 0, 0};
    
    plan(4);

    ok(-2 == bitmap__delete(&bmap), "deleting an uncreated bitmap fails with -2");

    bmap.magic = BITMAP_MAGIC;
    ok(0 == bitmap__delete(&bmap), "deleting a bitmap with correct magic succeds");

    ok(-1 == bitmap__delete(NULL), "deleting a NULL fails with -1");

    bmap.magic = BITMAP_MAGIC;
    bmap.bit_array = malloc(sizeof(unsigned long));
    ok(0 == bitmap__delete(&bmap), "deleting a bitmap with an allocated"
                                   " buffer succeeds");

    return 0;
}
