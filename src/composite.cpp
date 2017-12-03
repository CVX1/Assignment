#ifndef __COMPOSITE_CPP__
#define __COMPOSITE_CPP__
#include "composite.h"

//--------------------------------------------------------------------------
// Instruction Class
//--------------------------------------------------------------------------
Instruction::Instruction(): {exec = false;}
Instruction::Instruction(char* s) : {str = s;}

void Instruction::setString(char* s) {str = s;}

//--------------------------------------------------------------------------
// Command Class
//--------------------------------------------------------------------------
Command::Command() : Instruction(), {}
Command::Command(char* s) : Instruction(), Instruction(s) {};
Command::~Command() : Instruction(), {}
        /*
        void execute() {
            // execute using execvp and vipid //
            // and assign to exec             

            
        }
        */

void Command::print() {cout << str << " ";}

//--------------------------------------------------------------------------
// Connector Class
//--------------------------------------------------------------------------
Connector::Connector() : Instruction(), {}
Connector::Connector(char* s) : Instruction(), Instruction(s) {
    if (strcmp(s, ";") == 0) {exec = true;}
    else if (strcmp(s, "&&") == 0) {exec = true;}
    else if (strcmp(s, "||") == 0) {exec = false;}
    else {exec = true;}
}
Connector::~Connector() : Instruction(), {
        
        }

void Connector::print() {cout << str << " ";}

//void execute() {}

//--------------------------------------------------------------------------
// CmdString Class
//--------------------------------------------------------------------------
CmdString::CmdString() : Instruction(), {}
CmdString::~CmdString() : Instruction(), {
            for (int i = 0; i < V.size(); i++) {
                V[i] = NULL;
                delete V[i];
            }
        }

void CmdString::addInstruction(Instruction* i) {V.push_back(i);}

//void execute() {}

void CmdString::print() {
            for (unsigned int i = 0; i < V.size(); i++) {
                V[i]->print();
                cout << endl;
            }
        }

#endif //__COMPOSITE_CPP__