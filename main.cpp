/**
 * @mainpage Encryption using the DES algorithm
 * @author Roman Solar
 *
 *
 *
 * @version
 * 7/2/2016
 */


#include <iostream>

#include "callFunction.h"


using namespace std;

int main()
{
    cout << "Type 'help' or 'h' to see what this is." << endl;

    bool a = true;
    while (a){
        cout << "> ";

        string get;
        getline(cin, get);

        a = callFunction(get);
    }


    return 0;
}

