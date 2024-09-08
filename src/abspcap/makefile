.PHONY: all clean

CC=gcc
CFLAGS= -Wall -g -O -fPIC
BINDIR= ../../bin
TARGET= $(BINDIR)/libabspcap.so

all: $(TARGET)

$(TARGET): abspcap.o
	$(LINK.c) -shared $^ -o $@

clean:
	rm -f *.o $(TARGET)

