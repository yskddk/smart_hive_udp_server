
CC = gcc
RM = rm -f

INCLUDES = 
#CFLAGS = -DDEBUG -g -O2 $(INCLUDES)
CFLAGS = -DNDEBUG -O2 $(INCLUDES)
LDFLAGS = 
LIBS = 

CSRCS = $(shell ls *.c)
OBJS = $(CSRCS:%.c=%.o)
#DEPENDS = $(OBJS:%.o=%.d)



.PHONY: clean

all: test_sender

%.o: %.c
	gcc -o $@ -c $(CFLAGS) $<

test_sender: test_sender.o
	gcc -o $@ $< $(LDFLAGS) $(LIBS)

clean:
	$(RM) *.o test_sender
