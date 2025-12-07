#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

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

const char path[] = "./dmgha.z64";

int main() {
    unsigned char* buffer = readWholeFile(path, 64 * 1024 * 1024);
    for (int i = 0; i < 42; i++)
    {
        char pathBuf[256];
        sprintf(pathBuf, "./hints_converted/%d.png.bin", i + 1);
        unsigned char* imgBuf = readWholeFile(pathBuf, 0x30000);
        uint32_t romPtr = 0x03000000;
        romPtr += i * 0x30000;
        memcpy(buffer + romPtr, imgBuf, 0x30000);
        free(imgBuf);
    }

    FILE* file = fopen(path, "wb");
    fwrite(buffer, 64 * 1024 * 1024, 1, file);
    fclose(file);

    free(buffer);

    return 0;
}
