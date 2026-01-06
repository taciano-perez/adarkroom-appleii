# Makefile for cc65 Apple II target

SOURCES = main.c logic.c ui.c
OBJECTS = $(SOURCES:.c=.o)
PROGRAM = adarkroom
CC = cl65
CFLAGS = -t apple2 -C apple2-raw.cfg

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(PROGRAM) $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(PROGRAM)
