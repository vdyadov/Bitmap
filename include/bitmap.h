#ifndef BITMAP_H
#define BITMAP_H

typedef struct Bitmap 
{
    unsigned long *bit_array;
    /// Размер для выделения памяти *bit_array
    unsigned short size;
    /// Поле для проверки целостности структуры.
    int magic;
} Bitmap;

#endif /* BITMAP_H */
