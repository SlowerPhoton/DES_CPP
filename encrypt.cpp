#include "encrypt.h"
#include "binary.h"
#include "message.h"
#include "encrypt.h"
#include "encodeMessage.h"
#include "key.h"
#include "typeConverter.h"
#include "subkeys.h"
#include "cin.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <limits>
#include <string>

#define NUMERICAL 0
#define BINARY 1
#define TEXT 2
#define UNDEFINED -1

bool encr;

using namespace std;

string root = "C://Users//HP//Desktop//";

int defInputS = BINARY;
int defOutputS = BINARY;
bool defFileIN = true;
bool defFileOUT = true;

void unknownFlag (string invalidFlag, bool isFlag){

    if ( isFlag ) invalidFlag = '/' + invalidFlag;

    cout << "Unknown flag '" << invalidFlag << "'!" << endl;

}

void encrypt (int inputS, int outputS, bool fileIN, bool fileOUT)
{
    // to store the message
    vector<unsigned char> message;
    message.reserve(6000);

    // for console input (and output)
    if (!fileIN)
    {
        // console does not support binary input
        if (inputS == BINARY){
            cout << "Can not read binary input in console!" << endl;
            return;
        }

        // otherwise get the message from the user
        getMessage(message, inputS);
    }
    if (!fileOUT){
        // binary output is not supported in the console
        if (outputS == BINARY){
            cout << "Can not output in binary for console input!" << endl;
            return;
        }
    }

    // will open only if there is file input
    ifstream in;
    if (fileIN)
    {
        // get the input file's name
        if(encr)
            cout << "Enter the name of the file to encrypt: ";
        else
            cout << "Enter the name of the file to decrypt: ";
        string fileN;
        cin >> fileN;
        //clearBuffer();
        fileN = root + fileN;

        // open the input file and make sure we have succeeded
        if (inputS == BINARY)
            in.open(fileN.c_str(), ios::binary | ios::in);
        else
            in.open(fileN.c_str());

        if (!in)
        {
            cout << "File could not be opened. Process aborted." << endl;
            return;
        }
    }

    // will open only if there is file output
    ofstream out;
    if (fileOUT)
    {
        // get the output file name
        cout << "Enter the name of the output file: ";
        string fileN;
        fileN = "";
        cin >> fileN;
        fileN = root + fileN;

        // open the output file and make sure we have succeeded
        if (outputS == BINARY)
            out.open(fileN.c_str(), ios::binary | ios::out);
        else
            out.open(fileN.c_str());

        if (!out)
        {
            cout << "File could not be opened. Process aborted." << endl;
            return;
        }
    }

    // get the key and transform it into binary
    int key[8];
    getKey(key);
    bool binaryKey[8*8];
    toBinary(key, binaryKey, 8);

    /// Step 1: Create 16 subkeys, each of which is 48-bits long.
    bool subkeys[16][48];
    createSubkeys(binaryKey, subkeys);

    // get the input from the input file
    if (fileIN)
    {
        if (inputS == NUMERICAL){
            string numS;
            while (in >> numS)
            {
                if (!is_number(numS)){
                    cout << "File is not numerical! Process aborted." << endl;
                    return;
                }
                int num = atoi(numS.c_str());
                if (num > UCHAR_MAX or num < 0){
                    cout << "Numbers are out of range! Process aborted." << endl;
                    return;
                }
                message.push_back((unsigned char) num);
            }
        }
        else if (inputS == TEXT) {
            char c;
            while (in.get(c)){
                message.push_back((unsigned char) c);
            }
        }
        else
        {
            unsigned char num;
            while ( in.read( (char *) &num, sizeof(char) ) ){
                message.push_back((unsigned char) num);
            }
        }
    }

    // make message 8*k bytes long, where k is a natural number
    messageExpand(message);

    /// Step 2: Encode each 64-bit block of data.
    size_t length = message.size();
    for(size_t i = 0; i < length; i+=8)
    {
        // transform corresponding piece of message into binary
        bool binaryMessage[64];
        messageToBinary(binaryMessage, message, i);

        bool C[64]; // to store the encrypted message
        encodeMessage(binaryMessage, subkeys, C);

        // output the encrypted message
        for(int j = 0; j < 64; j+=8)
        {
            int a = toDecimal(C+j, 8);
            if (fileOUT)
            {
                if (outputS == NUMERICAL){
                    out << a;
                    out << '\t';
                }
                else if (outputS == TEXT){
                    out << (char) a;
                }
                else
                {
                    out.write( (char *) &a, sizeof(char) );
                }
            }
            else
            {
                if (outputS == NUMERICAL){
                    cout << a;
                    cout << '\t';
                }
                else {
                    cout << (char) a;
                }
            }
        }

        if (outputS == NUMERICAL)
        {
            if (fileOUT)
                out << endl;
            else
                cout << endl;
        }
    }

    // if the output was console text, print a new line
    if (!fileOUT and inputS == TEXT)
        cout << endl;

    // close the files that were opened
    if (fileIN)
        in.close();
    if (fileOUT)
        out.close();
}

void changeDefaultSettings(int inputS, int outputS, bool fileIN, bool fileOUT){
    defInputS = inputS;
    defOutputS = outputS;
    defFileIN = fileIN;
    defFileOUT = fileOUT;
}

void printDefaultSettings(){
    cout << "Input is being taken from ";
    if (defFileIN)
        cout << "a file";
    else
        cout << "the console";
    cout << " and treated ";
    if (defInputS == NUMERICAL)
        cout << "as numerical";
    else if (defInputS == TEXT)
        cout << "as a text";
    else
        cout << "as binary";
    cout << "." << endl;

    cout << "Output is being uploaded to ";
    if (defFileOUT)
        cout << "a file";
    else
        cout << "the console";
    cout << " and treated ";
    if (defOutputS == NUMERICAL)
        cout << "as numerical";
    else if (defOutputS == TEXT)
        cout << "as a text";
    else
        cout << "as binary";
    cout << "." << endl;
}

void changeRoot(){
    cout << "Enter the new root: ";
    string newRoot;
    cin >> newRoot;
    clearBuffer();
    root = newRoot;
}

void printRoot(){
    cout << "The current root is: " << root << endl;
}


void encryptFlags(string call, bool encrNew){

    int input = defInputS;
    int output = defOutputS;
    bool fileIN = defFileIN;
    bool fileOUT = defFileOUT;
    bool changeDefault = false;

    size_t spPos = 0;
    while(spPos != UINT_MAX){
        spPos = call.find(' ', spPos+1);
        int nextPos = call.find(' ', spPos+1);

        string toProcess;
        if (nextPos != -1){
                toProcess = call.substr(spPos+1, nextPos-spPos);
        }
        else {
            toProcess = call.substr(spPos+1);
            spPos = UINT_MAX;
        }

        // to tolerate multiple spaces trim all spaces from left and right, if the string is empty, continue
        toProcess = trim(toProcess);
        if (toProcess.length() == 0)
            continue;

        // if there are no flags, this happens, escape the loop
        if ( toProcess.compare("e") == 0 or toProcess.compare("encrypt") == 0 )
            break;

        // make sure it really is a flag
        if (toProcess.length() < 2){
            unknownFlag(toProcess, false);
            return;
        }
        if (toProcess[0] != '/' and toProcess[0] != '-'){
            unknownFlag(toProcess, false);
            return;
        }

        // trim the '/' or '-' at the beginning
        toProcess = toProcess.substr(1);

        // make the flag lower case for better comparing
        for (size_t i = 0, n = toProcess.length(); i < n; i++){
            toProcess[i] = tolower(toProcess[i]);
        }

        if (toProcess.compare("in") == 0)
            input = NUMERICAL;
        else if (toProcess.compare("ib") == 0)
            input = BINARY;
        else if (toProcess.compare("it") == 0)
            input = TEXT;
        else if (toProcess.compare("on") == 0)
            output = NUMERICAL;
        else if (toProcess.compare("ob") == 0)
            output = BINARY;
        else if (toProcess.compare("ot") == 0)
            output = TEXT;
        else if (toProcess.compare("if") == 0)
            fileIN = true;
        else if (toProcess.compare("ic") == 0)
            fileIN = false;
        else if (toProcess.compare("of") == 0)
            fileOUT = true;
        else if (toProcess.compare("oc") == 0)
            fileOUT = false;
        else if (toProcess.compare("cd") == 0)
            changeDefault = true;
        else {
            unknownFlag(toProcess, true);
            return;
        }
    }

    // set encr accordingly
    encr = encrNew;

    // change the default settings if the user asked for it
    if (changeDefault)
        changeDefaultSettings(input, output, fileIN, fileOUT);

    // pass the settings to encrypt, which will do the rest
    encrypt(input, output, fileIN, fileOUT);
}
