#include "message.h"
#include <iostream>
#include <vector>
#include <limits>
#include "cin.h"

#define NUMERICAL 0
#define BINARY 1
#define TEXT 2
#define UNDEFINED -1

extern bool encr;


int padding(int numbersInMessage){
    return (8 - numbersInMessage%8)%8;
}

void getMessage(std::vector<unsigned char> &message, int inputS){

    // reserve at least 256 bytes (that's reasonable)
    message.reserve(256);

    if(encr)
        std::cout << "Enter the message to encrypt";
    else
        std::cout << "Enter the encrypted message";

    if(inputS == NUMERICAL)
    {
        // -1 is the 'banned number' which will stop the process of obtaining the message (and the '0' will be ignored)
        int get = 1; // to store the user's input
        std::cout <<  " (integers in range <0;255>, -1 will terminate your input):" << std::endl;

        while(true){
            std::cout << "message> ";
            std::cin >> get;

            // check whether the user entered a number
            if(std::cin.fail()) // or if(cin.fail())
            {
                std::cerr << "You must enter an integer!" << std::endl;

                // user didn't input a number
                std::cin.clear(); // reset failbit
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input
                // next, request user reinput
                continue;
            }

            // end the while loop if -1 has been entered
            if(get == -1)
                break;

            // if the user enters a number out of the range <0;255> make him repeat it
            if( !(get>=0 and get<=255) ){
                std::cerr << "Input must be in range <0;255>, try again." << std::endl;
                continue;
            }

            // get is a valid number -> store it in the message
            message.push_back(get);
        }
    }
    else // that means inputS is TEXT
    {
        std::cout << ": " << std::endl;
        std::string input;
        getline(std::cin, input);

        size_t n = input.length();
        for (size_t i = 0; i < n; i++)
            message.push_back( (unsigned char) input[i]);
    }
}

void messageExpand(std::vector<unsigned char> &message){
    int numbersInMessage = message.size();
    int pad = padding(numbersInMessage);
    for(int i = numbersInMessage; i < pad + numbersInMessage; i++){
        message.push_back(0);
    }
}

void messageToBinary(bool binaryMessage[], std::vector<unsigned char> &message, size_t fromPos){

    unsigned char powOf2;
    size_t noOfNumbers = 8;
    for(unsigned int i = 0; i < noOfNumbers; i++){
        bool tank[8] = {0,0,0,0,0,0,0,0};
        unsigned char toProcess = message[i + fromPos];
        // 8 bits -> the biggest possible number (unsigned) is 255
        // the first position represents 128
        int n;
        for(powOf2 = 128, n=0; n<8; powOf2/=2, n++){
            if(powOf2 <= toProcess){
                toProcess -= powOf2;
                tank[n] = 1;
            }
        }

        // copy tank[] to the corresponding position in binaryMessage[]
        for(int j = 0; j < 8; j++)
            binaryMessage[i*8+j] = tank[j];
    }
}
