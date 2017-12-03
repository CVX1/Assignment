#ifndef __READER_H__
#define __READER_H__
#include <iostream>
#include <string>
#include <cstring>
#include "composite.h"

using namespace std;

class Reader {
    public:
        string userInput;
        
        char* tok2;
        char* tok1;

        CmdString CS;

        Reader();
        ~Reader();
     
        Command* createCommand(char* str);
        Connector* createConnector(char* str);
    
        // reads input, parses input, calls create function //
        void read();

        // displays command line entry //
        void display();
};

#endif // __READER_H__
