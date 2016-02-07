/**
    @file
    functions used to manipulate with binary data
*/

#ifndef BINARY_H_INCLUDED
#define BINARY_H_INCLUDED

/**
    divides a binary array into halves
    @param LB first half
    @param RB second half
*/
void divideBinary(bool binary[], int sizeOfBinary, bool LB[], bool RB[]);

/**
    overwrites one array with another
    @param what what you want to overwrite
    @param with what you want to overwrite it
    @param noOfIndexes how many indexes you want to overwrite
*/
void overwrite(bool what[], bool with[], int noOfIndexes);

#endif // BINARY_H_INCLUDED
