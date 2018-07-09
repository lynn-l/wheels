
MAKE_PATH	:= $(shell pwd)/..
INCLUDE_PATH	:= $(MAKE_PATH)/include
SRC_PATH	:= $(MAKE_PATH)/src
RELEASE_PATH	:= $(MAKE_PATH)/release
TARGET		:= libgeneralapi.a

CC=gcc
CFLAGS= -g -I. -I../include
AR=ar
ARFLAGS= -cr

.PHONY: all clean

all: $(TARGET)

$(TARGET): general_api.o
	@echo "== Generate target: [$@] =="
	@$(AR) $(ARFLAGS) $@ $^
	@echo "== Done. =="

*.o: %.o:%.c
	@echo "== Compile object: [$@] =="
	@$(CC) -c -o $@ $< $(CFLAGS)
	@echo "== Done. =="
	
clean:
	rm -f *.o *.a