clang -flto -Wall -Wdouble-promotion -Os -mfix4300 -march=mips2 --target=mips-img-elf -fomit-frame-pointer -G0 -I C:/sm64-api/sm64 -I C:/sm64-api/sm64/libc -mno-check-zero-division -fno-exceptions -fno-builtin -fno-rtti -fno-common -mno-abicalls -DTARGET_N64 -mfpxx world_scale.c -c -o world_scale.o
ld.lld -o world_scale -L. -L C:/sm64-api/ld --oformat binary -T ldscript -M world_scale.o
