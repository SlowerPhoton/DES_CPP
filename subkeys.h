/**
    @file
    functions used to create subkeys from the key
*/

#ifndef SUBKEYS_H_INCLUDED
#define SUBKEYS_H_INCLUDED

/**
    creates the subkeys from the key (in binary)
*/
void createSubkeys(bool binaryKey[8*8], bool subkeys[16][48]);

/**
    shifts an array to the left
*/
void leftShift(bool toShift[28], int noOfShifts, bool destination[28]);

#endif // SUBKEYS_H_INCLUDED
