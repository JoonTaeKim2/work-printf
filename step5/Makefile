.SUFFIXES: .c .o
TARGET 	= main

CC = gcc 

CFLAGS = -Wall -Os -I.
LDFLAGS = 

SRCS = $(wildcard ./*.c)

OBJS = $(SRCS:c=o)

# If you want to see the variables, use error, info
#$(error $(OBJS))

.PHONY: all 


$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

clean:
	rm *.o 
	rm $(TARGET)
