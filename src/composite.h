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

        Instruction() {exec = false;}
        Instruction(char* s) {str = s;}

        //virtual void execute() = 0;
    
        void setString(char* s) {str = s;}

        virtual void print() = 0;
};

class Command : public Instruction {
    public:
        Command() {}
        Command(char* s) : Instruction(s) {
        
        };
        ~Command() {}
        /*
        void execute() {
            // execute using execvp and vipid //
            // and assign to exec             

            
        }
        */
        void print() {cout << str << " ";}
};

class Connector : public Instruction {
    public:
        Connector() {}
        Connector(char* s) : Instruction(s) {
            if (strcmp(s, ";") == 0) {exec = true;}
            else if (strcmp(s, "&&") == 0) {exec = true;}
            else if (strcmp(s, "||") == 0) {exec = false;}
            else {exec = true;}
        }
        ~Connector() {
        
        }

        //void execute() {}

        void print() {cout << str << " ";}
};

class CmdString : public Instruction {
    public:
        vector<Instruction*> V;

        CmdString() {}
        ~CmdString() {
            for (int i = 0; i < V.size(); i++) {
                V[i] = NULL;
                delete V[i];
            }
        }
        void addInstruction(Instruction* i) {
            V.push_back(i);
        }

        //void execute() {}
        
        void print() {
            for (unsigned int i = 0; i < V.size(); i++) {
                V[i]->print();
                cout << endl;
            }
        }
};


#endif // __COMPOSITE_H__
