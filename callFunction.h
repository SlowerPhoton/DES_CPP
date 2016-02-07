/**
    @file
    functions used to care for the user commands
*/

#ifndef CALLFUNCTION_H_INCLUDED
#define CALLFUNCTION_H_INCLUDED

#include <iostream>

/** \brief calls corresponding function according to the command line input
 *
 * \param input the command line input
 * \return false if 'end' was typed in, true otherwise
 *
 */

bool callFunction (std::string input);

/** \brief prints the available commands
 *
 *
 */
 void help();

#endif // CALLFUNCTION_H_INCLUDED
