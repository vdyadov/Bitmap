FLAGS = -Werror=all -Werror=extra -pedantic \
		-Wno-error=format-nonliteral -Wformat-nonliteral \
		-Werror=write-strings -Wno-error=discarded-qualifiers \
		-Wno-error=incompatible-pointer-types -Wno-clobbered -fPIE -fstack-check \
		-fstack-protector-all -ftrapv -D_FORTIFY_SOURCE=2 \
		-Wl,-z,relro,-z,now -Wl,-z,noexecstack -Wbad-function-cast -Wcast-align \
		-Werror=cast-qual -Wconversion -Werror=float-equal -Wformat-security \
		-Werror=format-overflow=2 -Wformat-truncation -Winline -Winvalid-pch \
		-Werror=jump-misses-init -Wlogical-op -Wmissing-declarations \
		-Wmissing-prototypes -Wnested-externs -Wold-style-definition \
		-Woverlength-strings -Werror=redundant-decls -Werror=shadow \
		-Werror=strict-overflow=5 -Wsuggest-attribute=const -Werror=switch-default \
		-Wtrampolines -Werror=undef -Werror=unused -Werror=stringop-overflow=4 \
		-Wdeclaration-after-statement

CC = gcc
# Флаги для библиотеки tap
TAP_FLAGS = -l tap
# Путь к исполняемым файлам
BIN_PATH = bin
# Путь к объектным файлам
OBJ_PATH = obj
# Путь к исходным файлам
SRC_PATH = src
# Путь к unit тестам
UNIT_TEST_PATH = test/unit
# Путь к work тестам
#WORK_TEST_PATH = test/work
# Расширение исходников
SRC_EXP = c

SHELL = /bin/bash
# Расширение исполняемых файлов
OUT = out

# Исходники
SOURCES = $(shell find $(SRC_PATH)/ -name '*.$(SRC_EXP)')
UNIT_TEST_SOURCES = $(shell find $(UNIT_TEST_PATH)/ -name '*.$(SRC_EXP)')
#WORK_TEST_SOURCES = $(shell find $(UNIT_TEST_PATH)/ -name '*.$(SRC_EXP)')

# Объектные модули
OBJECTS = $(SOURCES:$(SRC_PATH)/%.$(SRC_EXP)=$(OBJ_PATH)/$(SRC_PATH)/%.o)
UNIT_TEST_OBJECTS = $(UNIT_TEST_SOURCES:$(UNIT_TEST_PATH)/%.$(SRC_EXP)=$(OBJ_PATH)/$(UNIT_TEST_PATH)/%.o)
#WORK_TEST_OBJECTS = $(WORK_TEST_SOURCES:$(WORK_TEST_PATH)/%.$(SRC_EXP)=$(OBJ_PATH)/$(WORK_TEST_PATH)/%.o)

# Исходники тестов
UNIT_TEST = $(UNIT_TEST_SOURCES:$(UNIT_TEST_PATH)/%.$(SRC_EXP)=$(BIN_PATH)/$(UNIT_TEST_PATH)/%.c$(OUT))

all: dirs $(BIN_PATH)/$(SRC_PATH) $(BIN_PATH)/$(UNIT_TEST_PATH) #$(BIN_PATH)/$(WORK_TEST_PATH)

$(BIN_PATH)/$(SRC_PATH): $(OBJECTS)

$(BIN_PATH)/$(UNIT_TEST_PATH): $(UNIT_TEST_OBJECTS)

#$(BIN_PATH)/$(WORK_TEST_PATH): $(WORK_TEST_OBJECTS)

$(OBJ_PATH)/$(SRC_PATH)/%.o: $(SRC_PATH)/%.$(SRC_EXP)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_PATH)/$(UNIT_TEST_PATH)/%.o: $(UNIT_TEST_PATH)/%.$(SRC_EXP)
	$(CC) $(FLAGS) -c $< -o $@
	$(CC) $@ $(OBJECTS) -o $(BIN_PATH)/$<$(OUT) $(TAP_FLAGS)


#$(OBJ_PATH)/$(WORK_TEST_PATH)/%.o: $(WORK_TEST_PATH)/%.$(SRC_EXP)
#	$(CC) -c $< -o $@
#	$(CC) $@ $(OBJECTS) -o $(BIN_PATH)/$< $(TAP_FLAGS)

dirs:
	@mkdir -p $(dir $(BIN_PATH)/$(UNIT_TEST_PATH)/)
	@mkdir -p $(dir $(OBJECTS))
	@mkdir -p $(dir $(UNIT_TEST_OBJECTS))

all_tests: bitmap_get_test bitmap_set_test invert_test get_size_test test \
	bitmap_and_test iterator_test bitmap_equal_test xor_test nand_test \
	bitmap_create_test bitmap_or_test copy_bit_test copy_create_test \
	bitmap_clear_bit_test

bitmap_create_test:
	@echo "Запуск теста по созданию функции"
	@./$(BIN_PATH)/$(UNIT_TEST_PATH)/bitmap_create_test.cout
bitmap_get_test:
	@echo "Запуск первого теста"
	@./$(BIN_PATH)/$(UNIT_TEST_PATH)/bitmap_get_test.cout
bitmap_set_test:
	@echo "Запуск второго теста"
	@./$(BIN_PATH)/$(UNIT_TEST_PATH)/bitmap_set_test.cout
bitmap_clear_bit_test:
	@echo "Запуск теста обнуления бита"
	@./$(BIN_PATH)/$(UNIT_TEST_PATH)/bitmap_clear_bit_test.cout	
invert_test:
	@echo "Запуск третьего теста"
	@./$(BIN_PATH)/$(UNIT_TEST_PATH)/invert_test.cout
get_size_test:
	@echo "Запуск четвертого теста"
	@./$(BIN_PATH)/$(UNIT_TEST_PATH)/get_size_test.cout
test:
	@echo "Запуск пятого теста"
	@./$(BIN_PATH)/$(UNIT_TEST_PATH)/test.cout
bitmap_and_test:
	@echo "Запуск шестого теста"
	@./$(BIN_PATH)/$(UNIT_TEST_PATH)/bitmap_and_test.cout
iterator_test:
	@echo "Запуск теста итератора"
	@./$(BIN_PATH)/$(UNIT_TEST_PATH)/iterator_test.cout
bitmap_equal_test:
	@echo "Запуск теста сравнения двух массивов"
	@./$(BIN_PATH)/$(UNIT_TEST_PATH)/bitmap_equal_test.cout
xor_test:
	@echo "Запуск теста исключающего или"
	@./$(BIN_PATH)/$(UNIT_TEST_PATH)/xor_test.cout
nand_test:
	@echo "Запуск теста NAND"
	@./$(BIN_PATH)/$(UNIT_TEST_PATH)/nand_test.cout
bitmap_or_test:
	@echo "Запуск теста сравнения двух массивов"
	@./$(BIN_PATH)/$(UNIT_TEST_PATH)/bitmap_or_test.cout
copy_bit_test:
	@echo "Запуск теста сравнения двух массивов"
	@./$(BIN_PATH)/$(UNIT_TEST_PATH)/copy_bit_test.cout
copy_create_test:
	@echo "Запуск теста копирующего конструктора"
	@./$(BIN_PATH)/$(UNIT_TEST_PATH)/copy_create_test.cout

clean:
	$(RM) -r $(BIN_PATH) $(OBJ_PATH)

