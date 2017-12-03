#ifndef __COMPOSITE_H__
#define __COMPOSITE_H__
#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

class Instruction {
    public:
        char* str;
        bool exec;

        Instruction();
        Instruction(char* s);

        //virtual void execute() = 0;
    
        void setString(char* s);

        virtual void print() = 0;
};

class Command : public Instruction {
    public:
        Command();
        Command(char* s);
        ~Command();
        /*
        void execute() {
            // execute using execvp and vipid //
            // and assign to exec             

            
        }
        */
        void print();
};

class Connector : public Instruction {
    public:
        Connector();
        Connector(char* s);
        ~Connector();

        //void execute() {}

        void print() {cout << str << " ";}
};

class CmdString : public Instruction {
    public:
        vector<Instruction*> V;

        CmdString();
        ~CmdString();
        void addInstruction(Instruction* i);

        //void execute() {}
        
        void print();
};


#endif //__COMPOSITE_H__
