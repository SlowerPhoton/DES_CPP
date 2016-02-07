#include "subkeys.h"
#include "binary.h" // divideBinary

void createSubkeys(bool binaryKey[8*8], bool subkeys[16][48]){

    int pc_1[56] = {
        57, 49, 41, 33, 25, 17,  9,
         1, 58, 50, 42, 34, 26, 18,
        10,  2, 59, 51, 43, 35, 27,
        19, 11,  3, 60, 52, 44, 36,
        63, 55, 47, 39, 31, 23, 15,
         7, 62, 54, 46, 38, 30, 22,
        14,  6, 61, 53, 45, 37, 29,
        21, 13,  5, 28, 20, 12,  4
    };
    bool keyPermutation[56];

    // according to pc_1 create from 64-bit key 56-bit keyPermutation
    for(int i = 0; i < 56; i++){
        keyPermutation[i] = binaryKey[pc_1[i]-1];
    }

    // C and D will be saved here: [C/D] [index] [28 bools]
    bool CD[2][16+1][56/2];

    // divide keyPermutation into halves to C0 a D0 - each consists of 28 bits
    divideBinary(keyPermutation, 56, CD[0][0], CD[1][0]);

    // from C0, D0 and shifts make C1, D1 -> C16, D16
    int shifts[16] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };
    for(int i = 1; i < 17; i++){
        leftShift(CD[0][i-1], shifts[i-1], CD[0][i]);
        leftShift(CD[1][i-1], shifts[i-1], CD[1][i]);
    }

    // each subKey out of 16 is made from one out of 16 CD with the use of pc_2
    int pc_2[48] = {
        14,    17,   11,    24,     1,    5,
         3,    28,   15,     6,    21,   10,
        23,    19,   12,     4,    26,    8,
        16,     7,   27,    20,    13,    2,
        41,    52,   31,    37,    47,   55,
        30,    40,   51,    45,    33,   48,
        44,    49,   39,    56,    34,   53,
        46,    42,   50,    36,    29,   32
    };

    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 48; j++){

            // find out which part of CD we should look at - that means C, or D? for C CorD is 0, for D 1
            int where = pc_2[j] - 1;
            bool CorD = 0;
            if(where >= 56/2){
                CorD = 1;
                where-=56/2; // subtract 28, to start indexing from 0 again in case of D
            }

            subkeys[i][j] = CD[CorD][i+1][where];
        }
    }
}

void leftShift(bool toShift[28], int noOfShifts, bool destination[28]){

    for(int i = 0; i < 28; i++){
        destination[(i - noOfShifts + 28)%28] = toShift[i];
    }
}
