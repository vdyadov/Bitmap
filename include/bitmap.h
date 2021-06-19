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

typedef enum Bitmap_magic
{
    BITMAP_MAGIC = 0xabababab,
} Bitmap_magic;

void bitmap__creator(struct Bitmap * bitmap, unsigned short len_port);

int bitmap__delete(struct Bitmap * p_bitmap); 

#endif /* BITMAP_H */
