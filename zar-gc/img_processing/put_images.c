#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

static int sROMPointers[] = {/* 0 */ 0x01441000,
/* 1 */ 0x014d1000,
/* 2 */ 0x01503000,
/* 3 */ 0x01535000,
/* 4 */ 0x01583000,
/* 5 */ 0x015b5000,
/* 6 */ 0x015e7000,
/* 7 */ 0x019e3000,
/* 8 */ 0x01d90000,
/* 9 */ 0x01dc2000,
/* 10 */ 0x01df4000,
/* 11 */ 0x01f64000,
/* 12 */ 0x02044000,
/* 13 */ 0x02076000,
/* 14 */ 0x020a8000,
/* 15 */ 0x020e3000,
/* 16 */ 0x022b1000,
/* 17 */ 0x022e3000,
/* 18 */ 0x02315000,
/* 19 */ 0x02347000,
/* 20 */ 0x02383000,
/* 21 */ 0x024ce000,
/* 22 */ 0x02623000,
/* 23 */ 0x02655000,
/* 24 */ 0x0272f000,
/* 25 */ 0x02761000,
/* 26 */ 0x02793000,
/* 27 */ 0x0285f000,
/* 28 */ 0x028c3000,
/* 29 */ 0x028f5000,
/* 30 */ 0x02a4d000,
/* 31 */ 0x02bb8000,
/* 32 */ 0x02bea000,
/* 33 */ 0x02f92000,
/* 34 */ 0x02fc4000,
/* 35 */ 0x02ff6000,
/* 36 */ 0x03131000,
/* 37 */ 0x03163000,
};

unsigned char* readWholeFile(const char* path, size_t sz)
{
    // Open the file
    FILE* file = fopen(path, "rb");
    if (file == NULL) {
        printf("Failed to open the file %s.\n", path);
        exit(1);
    }

    // Allocate memory for the buffer
    unsigned char* buffer = (unsigned char*)malloc(sz);
    if (buffer == NULL) {
        printf("Failed to allocate memory for the buffer.\n");
        fclose(file);
        exit(1);
    }

    // Read the file into the buffer
    size_t bytesRead = fread(buffer, sz, 1, file);
    printf("Read %d bytes\n", bytesRead);
    if (bytesRead != 1) {
        printf("Failed to read the file into the buffer.\n");
        free(buffer);
        fclose(file);
        exit(1);
    }
    
    fclose(file);

    return buffer;
}

int main() {
    unsigned char* buffer = readWholeFile("../zarha.z64", 64 * 1024 * 1024);
    for (int i = 0; i < 30; i++)
    {
        char pathBuf[256];
        sprintf(pathBuf, "../hints_converted/%d.png.bin", i + 1);
        unsigned char* imgBuf = readWholeFile(pathBuf, 0x30000);
        memcpy(buffer + sROMPointers[i], imgBuf, 0x30000);
        free(imgBuf);
    }

    FILE* file = fopen("../zarha.z64", "wb");
    fwrite(buffer, 64 * 1024 * 1024, 1, file);
    fclose(file);

    free(buffer);

    return 0;
}
