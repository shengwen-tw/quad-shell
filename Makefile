EXECUTABLE=shell

CFLAGS=-I./

SRC=shell.c \
	parser.c \
	main.c

all: $(SRC)
	gcc -o $(EXECUTABLE) $(CFLAGS) $^
