/**
  @file
  functions used for converting between different data types
*/

#ifndef TYPECONVERTER_H_INCLUDED
#define TYPECONVERTER_H_INCLUDED


/**
    converts binary to decimal
    @return converted decimal number
*/
int toDecimal(bool binary[], int noOfNumbers);

/**
    converts decimal to binary and stores it in a given array
*/
void toBinary(int origin[], bool binary[], int noOfNumbers);

#endif // TYPECONVERTER_H_INCLUDED
