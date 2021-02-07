#include "funny_text.h"
extern "C"
{
    #include "game/print.h"
}

static const char* sMessages[] = 
{
    "NEAT",						  // 0 - G1
    "YOU FOUND A SECRET",         // 1 - C1
    "IMPORT HABROUR",             // 2 - C1
    "BONK",                       // 3 - C3
    "HOW",            			  // 4 - C4
    "NO CORNER PHYSICS KREYGASM", // 5 - C4
    "IS THIS SPRUCE STEM",        // 6 - C7
    "SHOWERTIE",                  // 7 - C8
    "BANIO KAIOIE",               // 8 - C9
    "NEAT",                       // 9 - G1
    "WORSE THAN ALEIO",           // 10 - G2
    "ACTUAL LIBRARY SECRET",      // 11 - G3
    "EW CARPET",                  // 12 - G3
    "WHEN YOU BYUYUYUYUYUYUYYU",  // 13 - G4
    "THE NOT CARPAL",             // 14 - OW
    "NICE BACKGROUND",            // 15 - OW
    "WHY THIS IS SO LONG",        // 16 - cheeze
    "SORRIE",                     // 17 - B2
    "EGYPTIAN",                   // 18 - MC
    "I ADORE UNLEASHED",          // 19 - HF
    "BSA MOMENT",                 // 20 - PW
    "TRUE CEILING ISSUES",        // 21 - KAZE
    "YEP",                        // 22 - CW
    "PIE BUG  PIE BUG  PIE BUG",  // 23 - PIE
    "YOU SPIN ME RIGHT ROUND",    // 24 - C3
    "EGGMANLAND",                 // 25 - B3
    "PRESS L NOW",                // 26 - B1
};

void FunnyText::Step()
{
    if (oTimer > 100)
        activeFlags = 0;

    print_text_centered(160, 50, sMessages[oBehParams1]);
}

uintptr_t FunnyText::Behavior[] = 
{
    0x08000000,
    0x0C000000, (uintptr_t) sStep,
    0x09000000
};