
#include "types.h"

#define WORLD_SCALE 4

void _start(s16* dst, float* src) {
    float scale = 65536.0f / WORLD_SCALE;
    // Iterate over pairs of values in the input matrix
    for (int i = 0; i < 8; i++)
    {
        // Read the first input in the current pair
        float a = src[2 * i + 0];

        // Convert the first input to fixed
        s32 a_int = (s32)(a * scale);
        dst[2 * i +  0] = (s16)(a_int >> 16);
        dst[2 * i + 16] = (s16)(a_int >>  0);

        // If this is the left half of the matrix, convert the second input to fixed
        if ((i & 1) == 0)
        {
            // Read the second input in the current pair
            float b = src[2 * i + 1];
            s32 b_int = (s32)(b * scale);
            dst[2 * i +  1] = (s16)(b_int >> 16);
            dst[2 * i + 17] = (s16)(b_int >>  0);
        }
        // Otherwise, skip the second input because column 4 will always be zero
        // Row 4 column 4 is handled after the loop.
        else
        {
            dst[2 * i +  1] = 0;
            dst[2 * i + 17] = 0;
        }

    }
    // Write 1.0 to the bottom right entry in the output matrix
    // The low half was already set to zero in the loop, so we only need
    //  to set the top half.
    dst[15] = 1;
}
