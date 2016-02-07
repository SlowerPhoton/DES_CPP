#include "key.h"
#include <iostream>
#include <limits.h>
#include <fstream>
#include <stdio.h>
#include <string.h>

void getKey(int key[8]){

    // clear the buffer after cin used to get the message
    std::cin.clear(); std::cin.ignore(INT_MAX,'\n');

    // get the key
    std::cout << "Enter the key <string>: " << std::endl;
    char keyWord[256];
    fgets(keyWord, 256, stdin);

    // in case the last position of keyWord is '\n' delete it
    if(keyWord[strlen(keyWord) - 1] == '\n'){
        keyWord[strlen(keyWord) - 1] = '\0';
    }

    keyTo8Bytes(keyWord, key);
}

void keyTo8Bytes(char keyWord[], int key[8]){
    // prepare array S with numbers from 0 to 255
    int S[256];
    for(int i = 0; i < 256; i++){
        S[i] = i;
    }

    // shuffle S
    int j = 0;
    int length = strlen(keyWord);
    for(int i = 0; i < 256; i++){
        j = (j + S[i] + keyWord[i % length])%256;
        int pom = S[j];
        S[j] = S[i];
        S[i] = pom;
    }

    // use first 8 indexes from S (and shuffle them again)
    int i = 0;
    j = 0;
    for(int a = 0; a < 8; a++){
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        int pom = S[i];
        S[i] = S[j];
        S[j] = pom;
        int keyByte = S[(S[i] + S[j]) % 256];
        key[a] = keyByte;
    }
}
