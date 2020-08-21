SRC_DIR = src
OBJ_DIR = obj

# Alter these 4 variables according to your need
CPP_FILES = main
ROM = ../sst.z64
INCLUDE_PATH = C:\n64chain\sm64
LIBRARY_PATH = C:\n64chain\ld

# 18907136 = 0x1208000
ROM_OFFSET = 18907136

SRC_FILES = $(patsubst %, $(SRC_DIR)/%.cpp, $(CPP_FILES))
OBJ_FILES = $(patsubst %, $(OBJ_DIR)/%.o, $(CPP_FILES))

CC = clang++
AR = llvm-ar
LD = ld.lld
CFLAGS = -Wall -Wdouble-promotion -Os -mtune=vr4300 -march=mips2 --target=mips-img-elf -fomit-frame-pointer -G0 -I $(INCLUDE_PATH) -mno-check-zero-division -fno-exceptions -fno-builtin -fno-rtti -fno-common -mno-abicalls -flto -mfp32

all: $(OBJ_DIR) libmill.a inject

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) $< -c -o $@ $(CFLAGS)

libmill.a: $(OBJ_FILES)
	$(AR) $(ARFLAGS) $@ $^
	
inject:
	$(LD) -o tmp -lmill -L. -L $(LIBRARY_PATH) --oformat binary -T ldscript -M obj\main.o
	dd bs=1 seek=$(ROM_OFFSET) if=tmp of=$(ROM) conv=notrunc
	rm tmp

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)
	rm -f libmill.a
