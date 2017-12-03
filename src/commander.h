#ifndef __COMMANDER_H__
#define __COMMANDER_H__
#include <iostream>
#include <iterator>
#include <string>
#include <cstring>
#include <vector>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include "composite.h"

class Commander {
    private:
        bool ex;

    public:
        CmdString CS;

        bool get_ex();

        bool runNext(bool exec, Instruction* conn);

        void setCS(CmdString cs);

        bool execute(CmdString cs); 
};
#endif //__COMMANDER_H__
