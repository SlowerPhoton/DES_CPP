/** \file
 *  functions that encode/decode a given input using subkeys
 *
 */


#ifndef ENCODEMESSAGE_H_INCLUDED
#define ENCODEMESSAGE_H_INCLUDED

/**
    encodes the message
    @param binaryMessage message of 64 bytes to be encoded
    @param subkeys used to encrypt
    @param encrypted output array to save the encrypted message
    @callergraph
*/
void encodeMessage(bool binaryMessage[64], bool subkeys[16][48], bool encrypted[64]);

/**
    adds two bools together using the XOR addition
    @return result of the addition
*/
bool XOR(bool a, bool b);

/**
    adds two bool arrays together using the XOR addition
    @param where output array to save the result
    @param noOfNumbers how many indexes are in the arrays
*/
void XOR(bool where[], bool arr1[], bool arr2[], int noOfNumbers);

/**
    permute an array according to an array of permutations
    @param toPermute the array to be permuted
    @param permutation the table of permutation
*/
void permutation(int permutation[], bool toPermute[], bool outcome[], int sizeOfPermutation);

/**
    finds with address (array of 6 bits) in S-boxes its corresponding number (array of 4 bits)
    @param which which S-box should we look at
    @param address address used to find the correct index
    @param binaryOutcome array to save the answer
    @return the answer in decimal
*/
int lookUpInSBox(int which, bool address[6], bool binaryOutcome[4]);

/**
    used in the algorithm of encoding message
*/
void f(bool R[32], bool K[48], bool outcome[32]);

#endif // ENCODEMESSAGE_H_INCLUDED
