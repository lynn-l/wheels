
MAIN_PATH	:= $(shell pwd)
INCLUDE_PATH	:= $(MAIN_PATH)/include
SRC_PATH	:= $(MAIN_PATH)/src
RELEASE_PATH	:= $(MAIN_PATH)/release
TARGET		:= $(SRC_PATH)/cli $(SRC_PATH)/serv

.PHONY: all clean

all: 
	$(MAKE) -C $(SRC_PATH)
	cp $(TARGET) $(RELEASE_PATH)
	
clean:
	rm -f $(SRC_PATH)/*.o $(TARGET) $(RELEASE_PATH)/*