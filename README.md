# Bitmap

## Функции

```int bitmap__delete(struct Bitmap * p_bitmap)```

Удаление объекта битмап. Битмап должен быть
валидным битмапом. Функция создания битмапа выделяет диннамическую память, поэтому созданный 
битмап всегда должен быть удален с помощью bitmap__delete для избжания утечки памяти.

* ```struct Bitmap * p_bitmap``` - указатель на объект, который будет удален.
***
```int bitmap__get_bit(struct Bitmap const *p_bitmap, unsigned short const bit_idx, unsigned char *p_bit)```

 Получение значения бита.

* ```struct Bitmap const *p_bitmap``` - указатель на битовый массив.
* ```unsigned short const bit_idx``` - индекс требуемого бита
* ```unsigned char *p_bit``` - указатель на ппеременную, в которую будет записано значение бита.