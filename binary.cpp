#include "binary.h"

void divideBinary(bool binary[], int sizeOfBinary, bool LB[], bool RB[]){
    int half = sizeOfBinary/2;
    // LB - first half
    int i = 0;
    for(; i < half; i++){
        LB[i] = binary[i];
    }
    // RB - second half
    for(; i < half*2; i++){
        RB[i - half] = binary[i];
    }
}

void overwrite(bool what[], bool with[], int noOfIndexes){
    for(int i = 0; i < noOfIndexes; i++)
        what[i] = with[i];
}
