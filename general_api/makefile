
MAKE_PATH	:= $(shell pwd)
INCLUDE_PATH	:= $(MAKE_PATH)/include
SRC_PATH	:= $(MAKE_PATH)/src
RELEASE_PATH	:= $(MAKE_PATH)/release
TARGET		:= libgeneralapi.a

.PHONY: all clean

all: 
	$(MAKE) -C $(SRC_PATH)
	cp $(SRC_PATH)/$(TARGET) $(RELEASE_PATH)
	
clean:
	rm -f $(SRC_PATH)/*.o $(SRC_PATH)/*.a $(RELEASE_PATH)/*.a