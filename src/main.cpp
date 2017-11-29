#include <iostream>
#include "composite.h"
#include "reader.h"
#include "commander.h"

int main() {

    Reader reader;
    Commander commander;
  
    bool exit = false;
    
    while (exit != true) {
        reader.CS.V.clear();
        commander.CS.V.clear();
        reader.display();
        commander.setCS(reader.CS); 
        commander.execute(commander.CS);
        exit = commander.get_ex();
    }
}
