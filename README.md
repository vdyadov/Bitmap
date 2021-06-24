# Bitmap

## Makefile
Makefile автоматизирован, сборку объектных файлов выполняет в папку obj/, сборку исполняемых файлов в папку bin/

#### Запуск:  
```make```  

#### Запуск тестов:

Запуск всех тестов:  
```make all_tests```

Запуск конкретного теста:  
```make номер_теста_test```

#### Отчистка созданных файлов и папок:  
```make clean```

#### Добавление тестов в Makefile:
Для добавления нового теста в Makefile необходимо создать цель, и добавить ее в зависимости цели all_test:  
```Makefile
all_tests: номер_теста_test

номер_теста_test:  
    @echo "Запуск определенного теста"
    @./$(BIN_PATH)/$(UNIT_TEST_PATH)/имя_теста.cout
``` 

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
* ```unsigned char *p_bit``` - указатель на переменную, в которую будет записано значение бита.
***
```int bitmap__set_bit(struct Bitmap const *p_bitmap, unsigned short const bit_idx)```
 
 Установка нужного бита. В функцию требуется передать валидный битмап и номер бита, который необходимо установить.

* ```struct Bitmap const *p_bitmap``` - указатель на битовый массив.
* ```unsigned short const bit_idx``` - индекс требуемого бита.
***
```int bitmap__get_size(struct Bitmap const *p_bitmap, unsigned short *p_size)```

Получение размера массива в битах. Битмап должен быть валидным битмапом.

* ```struct Bitmap const *p_bitmap``` - указатель на битовый массив.
* ```unsigned char *p_bit``` - указатель на переменную, в которую будет записан размер
***
```int bitmap__clear_all(struct Bitmap * p_bitmap)```

Обнуление всех битов битового массива.

* ```struct Bitmap * p_bitmap``` - указатель на битовый массив, должен указывать на валидный битмап
***
```int bitmap__invert(struct Bitmap * p_bitmap)```

Побитовая инверсия массива.

* ```struct Bitmap * p_bitmap``` - указатель на объект Bitmap, который будет инвертирован. Должен указывать на валидный битмап.
***
```int bitmap__equal(struct Bitmap * p_bitmap, struct Bitmap * p_bitmap_2)```

Побитовое сравнение двух массивов.

* ```struct Bitmap * p_bitmap``` - указатель на объект Bitmap. Должен указывать на валидный битмап.
* ```struct Bitmap * p_bitmap_2``` - указатель на объект Bitmap, с которым будет производиться сравнение. Должен указывать на валидный битмап.
***
```int bitmap__and(struct Bitmap * p_bitmap, struct Bitmap const * p_bitmap_2)```

Побитовое И двух массивов.

* ```struct Bitmap * p_bitmap``` - указатель на объект Bitmap, который будет изменен. Должен указывать на валидный битмап.
* ```struct Bitmap const * p_bitmap_2``` - указатель на объект Bitmap, с которым будет выполняться побитовое И. Должен указывать на валидный битмап.
***
```int bitmap__or(struct Bitmap * p_bitmap, struct Bitmap const * p_bitmap_2)```

Побитовое ИЛИ двух массивов.

* ```struct Bitmap * p_bitmap``` - указатель на объект Bitmap, который будет изменен. Должен указывать на валидный битмап.
* ```struct Bitmap const * p_bitmap_2``` - указатель на объект Bitmap, с которым будет выполняться побитовое ИЛИ. Должен указывать на валидный битмап.
***
```int bitmap__xor(struct Bitmap * p_bitmap, struct Bitmap const * p_bitmap_2)```

Побитовое исключающее ИЛИ двух массивов.

* ```struct Bitmap * p_bitmap``` - указатель на объект Bitmap, который будет изменен. Должен указывать на валидный битмап.
* ```struct Bitmap const * p_bitmap_2``` - указатель на объект Bitmap, с которым будет выполняться побитовое исключающее ИЛИ. Должен указывать на валидный битмап.
***
```int bitmap__nand(struct Bitmap * p_bitmap, struct Bitmap const * p_bitmap_2)```

Побитовое отрицание И двух массивов.

* ```struct Bitmap * p_bitmap``` - указатель на объект Bitmap, который будет изменен. Должен указывать на валидный битмап.
* ```struct Bitmap const * p_bitmap_2``` - указатель на объект Bitmap, с которым будет выполняться побитовое отрицание И. Должен указывать на валидный битмап.
***
```int bitmap__copy_bit(struct Bitmap * p_bitmap, struct Bitmap const * p_bitmap_2)```

Копирование битов массива 2 в массив 1.

* ```struct Bitmap * p_bitmap``` - указатель на объект Bitmap, который будет изменен. Должен указывать на валидный битмап.
* ```struct Bitmap const * p_bitmap_2``` - указатель на объект Bitmap, из которого будут копироваться биты. Должен указывать на валидный битмап.

## Итератор

Структура итератор позволяет перемещаться п битовому массиву, находя следующие единицы или нули.

```c
typedef struct Bitmap_iterator
{
    // Указатель на битмап, с которым связан итератор
    struct Bitmap *p_bitmap;
    // Индекс бита, на который указывает итератор
    unsigned short bit_idx;
    // Флаг, говорящий о том, что bit_idx указывает за границу массива (биты закончились)
    unsigned char end_flag;
} Bitmap_iterator;
```

### Функции для использования итератора
```int bitmap_iterator__init(struct Bitmap_iterator *p_iter, struct Bitmap *p_bitmap)```

Связать итератор с *p_bitmap и установить bit_idx на ноль
* ```struct Bitmap_iterator *p_iter``` - указатель на итератор

* ```struct Bitmap *p_bitmap``` - указатель на битмап, с которым будет связан итератор
***
```int bitmap_iterator__next_up(struct Bitmap_iterator *p_iter)```

Перейти к следующей единице

* ```struct Bitmap_iterator *p_iter``` - указатель на итератор

***
```int bitmap_iterator__next_down(struct Bitmap_iterator *p_iter)```

Перейти к следующему нулю

* ```struct Bitmap_iterator *p_iter``` - указатель на итератор

***
```int bitmap_iterator__next(struct Bitmap_iterator *p_iter)```

Перейти к следующему биту

* ```struct Bitmap_iterator *p_iter``` - указатель на итератор

***
```int bitmap_iterator__begin_up(struct Bitmap_iterator *p_iter)```

Найти первую единицу в массиве

* ```struct Bitmap_iterator *p_iter``` - указатель на итератор

***
```int bitmap_iterator__begin_down(struct Bitmap_iterator *p_iter)```

Найти первый ноль в массиве

* ```struct Bitmap_iterator *p_iter``` - указатель на итератор
