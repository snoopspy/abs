.PHONY: all clean

CPPFLAGS=-Wall -g -O2 -fPIC
LDLIBS=-lpcap
BINDIR=../bin
TARGET=$(BINDIR)/abs

all: $(TARGET)

$(TARGET): abs.o
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) -o $@

clean:
	rm -f *.o $(TARGET)
