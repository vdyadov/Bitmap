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

int bitmap__creator(
    struct Bitmap * p_bitmap,
    unsigned short len_port);
    
int bitmap__delete(struct Bitmap * p_bitmap); 

int bitmap__get_bit(
    struct Bitmap const *p_bitmap,
    unsigned short const bit_idx,
    unsigned char *p_bit);

int bitmap__set_bit(
    struct Bitmap *p_bitmap,
    unsigned short const bit_idx);


int bitmap__get_size(
    struct Bitmap const *p_bitmap,
    unsigned short *p_size);

#endif /* BITMAP_H */
