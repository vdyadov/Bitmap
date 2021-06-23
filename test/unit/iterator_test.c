#include "../../include/bitmap.h"
#include "../../include/bitmap_iterator.h"

#include <tap.h>

#include <stdio.h>
#include <malloc.h>
#include <string.h>

//A simple test with libtap
//compile with -l tap
int main(void)
{
    struct Bitmap bmap = {NULL, 0, 0};
    struct Bitmap_iterator iter = {NULL, 0, 0};
    unsigned char expression = 0;

    plan(15);

    //testing init
    ok(-1 == bitmap_iterator__init(NULL, NULL), "init with nullptr fails");
    ok(-2 == bitmap_iterator__init(&iter, &bmap), "fails with wrong magic");
    ok(-3 == bitmap_iterator__init(NULL, &bmap), "fails with -3");

    bmap.magic = BITMAP_MAGIC;
    ok(0 == bitmap_iterator__init(&iter, &bmap), "init succeeds");
    expression = iter.end_flag && (iter.bit_idx == 0);
    ok(expression, "init set the values as expected");

    bmap.bit_array = malloc(sizeof(unsigned long) * 3);
    memset(bmap.bit_array, 0xff, sizeof(unsigned long) * 3);
    bmap.size = (unsigned short)(sizeof(unsigned long) * 8 * 3 - 2);
    ok(0 == bitmap_iterator__init(&iter, &bmap), "init succeeds again");
    expression = (!iter.end_flag) && (iter.bit_idx == 0) && (iter.p_bitmap == &bmap);
    ok(expression, "second init set the values as expected");

    //testing begin_up
    memset(bmap.bit_array, 0xff, sizeof(unsigned long) * 3);
    ok(0 == bitmap_iterator__begin_up(&iter), "begin_up succeeds");
    expression = (!iter.end_flag) && (iter.bit_idx == 0);
    ok(expression, "result of begin_up as expected");

    bmap.bit_array[0] = 0;
    bitmap_iterator__begin_up(&iter);
    expression =  (!iter.end_flag) 
               && (iter.bit_idx == (unsigned short)(sizeof(unsigned long) * 8));
    ok(expression, "result of begin_up as expected");

    bitmap__clear_all(&bmap);
    bitmap_iterator__begin_up(&iter);
    expression = iter.end_flag;
    ok(expression, "result of begin_up as expected");
    
    bitmap_iterator__init(&iter, &bmap); // to clear the end flag
    //testing begin_down
    memset(bmap.bit_array, 0, sizeof(unsigned long) * 3);
    ok(0 == bitmap_iterator__begin_down(&iter), "begin_down succeeds");
    expression = (!iter.end_flag) && (iter.bit_idx == 0);
    ok(expression, "result of begin_down as expected");

    bmap.bit_array[0] = 0xffffffffffffffff;
    bitmap_iterator__begin_down(&iter);
    expression =  (!iter.end_flag) 
               && (iter.bit_idx == (unsigned short)(sizeof(unsigned long) * 8));
    ok(expression, "result of begin_down as expected");

    memset(bmap.bit_array, 0xff, sizeof(unsigned long) * 3);
    bitmap_iterator__begin_down(&iter);
    expression = iter.end_flag;
    ok(expression, "result of begin_down as expected");

    //некст ап и некст даун используются в бегинах,
    //так что я верю, что они работают и сегодня писать для них тесты не буду

    done_testing();
    return 0;
}
