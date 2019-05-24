SRC_DIR = src
OBJ_DIR = obj

# Alter CPP_FILES to add more sources
CPP_FILES = global triplet phase0 phase1 phase2 phase3 phase4 phase5 apple rng angle
SRC_FILES = $(patsubst %, $(SRC_DIR)/%.cpp, $(CPP_FILES))
OBJ_FILES = $(patsubst %, $(OBJ_DIR)/%.o, $(CPP_FILES))
ROM = HumanticC.z64
INCLUDE_PATH = C:\n64chain\sm64
LIBRARY_PATH = C:\n64chain\ld

SM64_INCLUDE = C:\n64chain\sm64
CC = clang++
AR = llvm-ar
LD = ld.lld
CFLAGS = -Wall -Wdouble-promotion -Os -mtune=vr4300 -march=mips32 --target=mips64-linux-elf -mabi=32 -fomit-frame-pointer -G0 -I $(INCLUDE_PATH) -mno-check-zero-division -fno-exceptions -fno-builtin -fno-rtti -fno-common -flto -mno-abicalls

all: $(OBJ_DIR) libhumantic.a inject

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) $< -c -o $@ $(CFLAGS)

libhumantic.a: $(OBJ_FILES)
	$(AR) $(ARFLAGS) $@ $^
	
inject:
	$(LD) -o tmp -lhumantic -L. -L $(LIBRARY_PATH) --oformat binary -T ldscript -M obj\phase0.o
	dd bs=1 seek=19398656 if=tmp of=HumanticC.z64 conv=notrunc
	rm tmp

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)
	rm -f libhumantic.a
