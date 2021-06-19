CC = gcc
FLAGS = -Wextra -Wshadow -Wnon-virtual-dtor\
    -fPIE -fstack-check -fstack-protector-all -ftrapv -D_FORTIFY_SOURCE=2  \
    -Wl,-z,relro,-z,now -Wl,-z,noexecstack -Wnull-dereference -Wold-style-cast \
		-Wcast-align -Woverloaded-virtual -Wuseless-cast \
    -Wcast-align -Wcast-qual -Wconversion \
    -Wsign-conversion -Wfloat-equal -Wformat-nonliteral -Wformat-security \
    -Winline -Winvalid-pch -Wlogical-op -Wmissing-declarations \
    -Wmissing-include-dirs \
    -Woverlength-strings -Wredundant-decls -Wshadow -Wstrict-overflow=4 \
    -Wsuggest-attribute=const -Wswitch-default -Wtrampolines \
    -Wundef -Wunused-local-typedefs -Wwrite-strings -Wno-unused-variable \
		-Wno-unused-parameter -Wno-missing-include-dirs -Weffc++ \
    -Werror=implicit-function-declaration -Werror=address \
    -DUSE_ZLOG \

TAP_FLAGS = -l tap
PREFIX_NAME =
NAME_TEST = $(PREFIX_NAME)test
UNIT_TEST = test/unit/$(NAME_TEST)
SRC = bitmap
SOURCE = src/$(SRC)
OUT = $(NAME_TEST).out

all: $(SOURCE).o $(UNIT_TEST).o
	$(CC) $(NAME_TEST).o $(SRC).o $(FLAGS) -o $(OUT) $(TAP_FLAGS)

$(SOURCE).o: $(SOURCE).c
	$(CC) $(SOURCE).c $(TAP_FLAGS) -c
	
$(UNIT_TEST).o: $(UNIT_TEST).c
	$(CC) $(UNIT_TEST).c $(TAP_FLAGS) -c

run:
	./$(OUT)

clean:
	rm $(NAME_TEST).o $(OUT) $(SRC).o
