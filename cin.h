/** \file
    functions that treat the cin input
 */

#ifndef CIN_H_INCLUDED
#define CIN_H_INCLUDED

#include <iostream>

/** \brief checks if given string is a number
 *
 * \param s string to check
 * \return true if s is a number, false otherwise
 *
 */
bool is_number(const std::string& s);

/** \brief
 * flushes the cin buffer
 *
 */
void clearBuffer();

/** \brief
 *  trims a given string (deletes spaces from the end and beginning)
 * \param string s to trim
 * \return trimmed string
 *
 */
std::string trim(const std::string &s);

#endif // CIN_H_INCLUDED
