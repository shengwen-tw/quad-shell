EXECUTABLE=shell

CFLAGS=-I./

SRC=shell.c \
	main.c

all: $(SRC)
	gcc -o $(EXECUTABLE) $(CFLAGS) $^
