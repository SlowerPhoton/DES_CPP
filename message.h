/**
    @file
    functions used to get and prepare the message
*/

#ifndef MESSAGE_H_INCLUDED
#define MESSAGE_H_INCLUDED

#include <iostream>
#include <vector>



/**
    @return how many characters we need to add to the message in order to be a multiple of 8 characters long (64 bits)
    @param elementsInMessage how many elements the message contains
*/
int padding(int elementsInMessage);

/**
    get the message from the user, character after character <unsigned char>
    @param message an array to store the message
    @param numbersInMessage the size of the message (in bytes)

*/
void getMessage(std::vector<unsigned char> &message, int inputS);

/**
    expands the message in order to be a multiple of 8 ints (bytes) long
    @n adds @c 0 in the empty indexes
*/
void messageExpand(std::vector<unsigned char> &message);

/** \brief converts the message in form of unsigned chars into 64-bit binary message
 *
 * @param binaryMessage to store the output
 * @param &message the message to be converted
 * @param fromPos to specify from which element of message to start
 */
void messageToBinary(bool binaryMessage[64], std::vector<unsigned char> &message, size_t fromPos);

#endif // MESSAGE_H_INCLUDED
