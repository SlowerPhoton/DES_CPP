#include "typeConverter.h"

int toDecimal(bool binary[], int noOfNumbers){
    int powOf2 = 1;
    int decimal = 0;

    for(int i = noOfNumbers-1; i >= 0; i--){
        decimal += powOf2*binary[i];
        powOf2*=2;
    }

    return decimal;
}

void toBinary(int origin[], bool binary[], int noOfNumbers){
    int powOf2;
    for(int i = 0; i < noOfNumbers; i++){
        bool tank[8] = {0,0,0,0,0,0,0,0};
        int toProcess = origin[i];
        // 8 bits -> the biggest possible number (unsigned) is 255
        // the first position represents 128
        int n;
        for(powOf2 = 128, n=0; n<8; powOf2/=2, n++){
            if(powOf2 <= toProcess){
                toProcess -= powOf2;
                tank[n] = 1;
            }
        }

        // copy tank[] to the corresponding position in binary[]
        for(int j = 0; j < 8; j++)
            binary[i*8+j] = tank[j];
    }
}
