CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.c strsplit.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=ft_shield

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)