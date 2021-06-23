#include "../../include/bitmap.h"

#include <tap.h>

#include <stdio.h>
#include <malloc.h>

//A simple test with libtap
//compile with -l tap
int main(void)
{
    struct Bitmap bmap = {NULL, 0, 0};
    unsigned short size = 0;
    
    plan(4);

    ok(bitmap__get_size(&bmap, &size) == -2, "accessign an uncreated bitmap fails");
    ok(bitmap__get_size(NULL, &size) == -1, "acessing a NULL fails");
    
    bmap.magic = BITMAP_MAGIC;
    ok(-3 == bitmap__get_size(&bmap, NULL), 
       "accessing a bitmap with p_size == NULL fails");
    
    ok(0 == bitmap__get_size(&bmap, &size) && 0 == size,
       "accessing a bitmap succeeds and the size is correct");

    done_testing();
    return 0;
}
