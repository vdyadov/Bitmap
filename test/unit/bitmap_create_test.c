
#include "../../include/bitmap.h"


#include <tap.h>
#include <malloc.h>
#include <stdio.h> 
#include <stdlib.h> 


int main(void)
{
    plan(1);
    struct Bitmap bmap;

    ok(-1 == bitmap__creator(&bmap,60), "недо­статочно памяти  для выделения битовой карты");

    return 0;
}
