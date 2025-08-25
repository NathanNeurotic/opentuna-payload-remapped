TARGET = bin2c
OBJS = bin2c.o

CC = gcc
CFLAGS = -O2 -Wall
LDFLAGS =

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	rm -f $(TARGET) $(OBJS)
