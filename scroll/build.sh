CPPFLAGS="-Wall -Wdouble-promotion -Os -mtune=vr4300 -march=mips2 --target=mips-img-elf -fomit-frame-pointer -G0 -I C:/sm64-api/sm64 -I C:/sm64-api/sm64/libc -mno-check-zero-division -fno-exceptions -fno-builtin -fno-rtti -fno-common -mno-abicalls -DTARGET_N64 -mfpxx"

clang++ ${CPPFLAGS} -c ./scroll.cpp -o scroll.o

ld.lld ./scroll.o -L C:/sm64-api/ld --oformat binary -T ldscript -M -o ./scroll.bin