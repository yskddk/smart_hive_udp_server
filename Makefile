
TARGET = smart_hive_udp_server

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

all: $(TARGET)

%.o: %.c
	gcc -o $@ -c $(CFLAGS) $<

$(TARGET): $(OBJS)
	gcc -o $@ $< $(LDFLAGS) $(LIBS)

clean:
	$(RM) *.o $(TARGET)
