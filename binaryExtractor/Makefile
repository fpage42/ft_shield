CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=binaryExtractor
ARGS=../ft_shield/ft_shield ../installer/shield.c

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

run: ../installer/shield.c
	./$(EXECUTABLE) $(ARGS)

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)