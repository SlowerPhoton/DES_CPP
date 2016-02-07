/**
    @file
    functions used to get and prepare the key
*/

#ifndef KEY_H_INCLUDED
#define KEY_H_INCLUDED

/**
    gets string from the user and calls keyTo8Bytes to convert it into key
    @param key array to save the key
    @callergraph
*/
void getKey(int key[8]);

/**
    converts a string to 8-byte key
    @param keyWord the string to be converted
    @param key array of 8 bytes to save the key
*/
void keyTo8Bytes(char keyWord[], int key[8]);

#endif // KEY_H_INCLUDED
