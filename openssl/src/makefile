
MAIN_PATH	:= $(shell pwd)/..
INCLUDE_PATH	:= $(MAIN_PATH)/include
SRC_PATH	:= $(MAIN_PATH)/src
RELEASE_PATH	:= $(MAIN_PATH)/release
TARGET		:= cli serv

CC=gcc
CFLAGS= -g -I. -I../include -I$(MAIN_PATH)/../general_api/include
LINKFLAGS= -lssl -lcrypto -lpthread -ldl -lgeneralapi -L$(MAIN_PATH)/../general_api/release

.PHONY: all clean

all: $(TARGET)

cli: cli.o ssl_api.o
	@echo "== Generate target: [$@] =="
	@$(CC) -o $@ $^ $(LINKFLAGS)
	@echo "== Done. =="
	
serv: serv.o ssl_api.o
	@echo "== Generate target: [$@] =="
	@$(CC) -o $@ $^ $(LINKFLAGS)
	@echo "== Done. =="
	
*.o: %.o:%.c
	@echo "== Compile object: [$@] =="
	@$(CC) -c -o $@ $< $(CFLAGS)
	@echo "== Done. =="
	
clean:
	rm -f *.o $(TARGET)