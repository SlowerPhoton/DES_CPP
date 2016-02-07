#include "callFunction.h"
#include "cin.h"
#include "encrypt.h"

#include <iostream>
#include <string>

using namespace std;

void help()
{
    cout << "Encrypt your data using the DES algorithm." << endl << endl;
    cout << "Available commands:" << endl;
    cout << "'encrypt' or 'e' \t" << "Encrypts data, input and output can be specified by flags:" << endl;
        cout << "\t /ic or -ic \t" << "console input" << endl;
        cout << "\t /if or -if \t" << "file input" << endl;
        cout << "\t /ib or -ib \t" << "binary input" << endl;
        cout << "\t /in or -in \t" << "numerical input" << endl;
        cout << "\t /it or -it \t" << "text input" << endl << endl;
        cout << "\t /oc or -oc \t" << "console output" << endl;
        cout << "\t /of or -of \t" << "file output" << endl;
        cout << "\t /ob or -ob \t" << "binary output" << endl;
        cout << "\t /on or -on \t" << "numerical output" << endl;
        cout << "\t /ot or -ot \t" << "text output" << endl << endl;
        cout << "\t /cd or -cd \t" << "changes default settings to the last used settings" << endl << endl;
        cout << "\t If a flag is not specified, default settings is used." << endl;
        cout << "\t Example usage: " << "e /if /ib /oc /ot" << endl;
    cout << "'decrypt' or 'd' \t" << "Decrypts data, input and output can be specified by flags:" << endl;
        cout << "\t" << "The flags are completely the same as in 'encrypt' command." << endl;
    cout << "'print_default' or 'pd' \t" << "Prints the default settings." << endl;
    cout << "'print_root' or 'pr' \t" << "Prints the current root for file input/output." << endl;
    cout << "'change_root' or 'cr' \t" << "Changes the root for file input/output." << endl;
    cout << "'help' or 'h' \t" << "Prints the available commands." << endl;
    cout << "'end' \t" << "Ends the application." << endl;

}

bool callFunction (std::string input){

    input = trim(input);

    if (input.compare("end") == 0)
        return false;
    else if (input.compare(0, 7, "decrypt") == 0 or input.compare(0, 1, "d") == 0)
        encryptFlags(input, false);
    else if (input.compare(0, 7, "encrypt") == 0 or input.compare(0, 1, "e") == 0)
        encryptFlags(input, true);
    else if (input.compare("help") == 0 or input.compare("h") == 0)
        help();
    else if (input.compare("change_root") == 0 or input.compare("cr") == 0)
        changeRoot();
    else if (input.compare("print_root") == 0 or input.compare("pr") == 0)
        printRoot();
    else if (input.compare("print_default") == 0 or input.compare("pd") == 0)
        printDefaultSettings();
    else
        std::cout << "Command unrecognized." << std::endl;

    return true;
}
