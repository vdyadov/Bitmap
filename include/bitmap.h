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
    BITMAP_MAGIC = (int)0xabababab,
} Bitmap_magic;

int bitmap__create(
    struct Bitmap * p_bitmap,
    unsigned short const len_port);

int bitmap__delete(struct Bitmap * p_bitmap); 

int bitmap__get_bit(
    struct Bitmap const *p_bitmap,
    unsigned short const bit_idx,
    unsigned char *p_bit);

int bitmap__set_bit(
    struct Bitmap *p_bitmap,
    unsigned short const bit_idx);
    
int bitmap__clear_bit(
    struct Bitmap *p_bitmap,
    unsigned short const bit_idx);   

int bitmap__get_size(
    struct Bitmap const *p_bitmap,
    unsigned short *p_size);

int bitmap__clear_all(struct Bitmap *p_bitmap);

int bitmap__invert(struct Bitmap *p_bitmap);

int bitmap__equal(
    struct Bitmap const *p_bitmap,
    struct Bitmap const *p_bitmap_2);

int bitmap__and(
    struct Bitmap *p_bitmap,
    struct Bitmap const *p_bitmap_2);

int bitmap__or(
    struct Bitmap *p_bitmap,
    struct Bitmap const *p_bitmap_2);

int bitmap__xor(
    struct Bitmap *p_bitmap,
    struct Bitmap const *p_bitmap_2);

int bitmap__nand(
    struct Bitmap *p_bitmap,
    struct Bitmap const *p_bitmap_2);

int bitmap__copy_bit(
    struct Bitmap *p_bitmap,
    struct Bitmap const *p_bitmap_2);

int bitmap__copy_create(
    struct Bitmap *p_new,
    struct Bitmap const *p_old);

#endif /* BITMAP_H */
