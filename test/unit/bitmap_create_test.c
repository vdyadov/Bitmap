#include "../../include/bitmap.h"

#include <tap.h>
#include <malloc.h>
#include <stdio.h> 
#include <stdlib.h> 

int main(void)
{   
    struct Bitmap bmap = {NULL, 0, 0};
    
    plan(2);

    ok(-1 == bitmap__create(NULL, 60), "указатель битовой карты не проинициализирован");

    ok(-2 == bitmap__create(&bmap, 60), "недо­статочно памяти  для выделения битовой карты");

    return 0;
}
