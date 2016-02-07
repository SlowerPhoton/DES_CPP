/**
    @file
    functions used to care for the input/output and calling the encodeMessage function
*/

#ifndef ENCRYPT_H_INCLUDED
#define ENCRYPT_H_INCLUDED

#include <iostream>

/** \brief separates and reads the flags from the encrypt/decrypt command, then calls @c encrypt function and passes it the flags as arguments
 *
 * \param call the user command
 * \param encrypt true if user called 'encrypt' or 'e', false if he called 'decrypt' or 'd'
 *
 */

void encryptFlags(std::string call, bool encrypt);

/** \brief prints the default settings
 *
 *
 */

void printDefaultSettings();

/** \brief asks the user to change the root for input/output files
 *
 *
 */

void changeRoot();

/** \brief prints the root for input/output files
 *
 *
 */
void printRoot();
#endif // ENCRYPT_H_INCLUDED
