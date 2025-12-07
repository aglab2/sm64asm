#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define BUFFER_SIZE 64 * 1024 * 1024
#define ALIGN_SIZE 0x1000
#define REGION_SIZE 0x32000

int main() {
    // Open the file
    FILE* file = fopen("../zarha.z64", "rb");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    // Allocate memory for the buffer
    unsigned char* buffer = (unsigned char*)malloc(64 * 1024 * 1024);
    if (buffer == NULL) {
        printf("Failed to allocate memory for the buffer.\n");
        fclose(file);
        return 1;
    }

    // Read the file into the buffer
    size_t bytesRead = fread(buffer, BUFFER_SIZE, 1, file);
    printf("Read %d bytes\n", bytesRead);
    if (bytesRead != 1) {
        printf("Failed to read the file into the buffer.\n");
        free(buffer);
        fclose(file);
        return 1;
    }
    
    fclose(file);

    // Find contiguous regions filled with byte 0x1
    int num = 0;
    for (size_t i = 0x1200000; i < BUFFER_SIZE - ALIGN_SIZE; ) {
        // printf("Checking 0x%08x\n", i);
        uint32_t sample = *(uint32_t*)(buffer + i);
        if (sample != 0x01010101)
        {
            i += ALIGN_SIZE;
            continue;
        }

        // Check if the region is filled with 0x1
        bool ok = true;
        for (size_t j = 0; j < REGION_SIZE; j++) {
            if (buffer[i + j] != 0x1) {
                ok = false;
                break;
            }
        }

        if (ok)
        {
            printf("/* %d */ 0x%08x,\n", num, i + ALIGN_SIZE);
            i += REGION_SIZE;
            num++;
        }
        else
        {
            i += ALIGN_SIZE;
            continue;
        }
    }

    // Clean up
    free(buffer);

    return 0;
}
