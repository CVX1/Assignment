//--------------------------------------------------------------------------
// Reader Class
//--------------------------------------------------------------------------
Reader::Reader() : {}
Reader::~Reader() : {
    delete tok2;
    delete tok1;

    tok2 = NULL;
    tok1 = NULL;
}

Command* Reader::createCommand(char* str) {
            // create Command //
            Command* cmd = new Command();
            cmd->setString(str);
            return cmd;
};

Connector* Reader::createConnector(char* str) {
            // create Connector //
            return new Connector(str);
};

// reads input, parses input, calls create function //

void Reader::read() {
    // Use strspn in order to find any '#' character //
    // and remove it and everything after it //
    getline(cin, userInput);
   
    int finder;
    int finder2;
    int count;

    char p[] = "#";
    finder = strcspn(userInput.c_str(), p);
    finder2 = strcspn(userInput.c_str(), "[]-()abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ./");

    userInput = userInput.substr(finder2,finder);

    size_t loc;
    int cnt = 0;
    while (loc != string::npos && count < 10000) {
        loc = userInput.find("((");
        //cout << "loc: " << loc << endl;
        loc++;
        if (loc != string::npos)
            userInput.insert(loc, " ");
        count++;
    }

    count = 0;
    do {
        loc = userInput.find("))");
        //cout << "loc: " << loc << endl;
        loc++;
        if (loc != string::npos)
            userInput.insert(loc, " ");
        count++;
    } while (loc != string::npos && count < 10000); 

    count = 0;
    while (loc != string::npos && count < 10000) {
        loc = userInput.find(");");
        //cout << "loc: " << loc << endl;
        loc++;
        if (loc != string::npos)
            userInput.insert(loc, " ");
        count++;
    }

    loc = userInput.find_first_not_of(" ");
    userInput = userInput.substr(loc, userInput.size() - 1);
  
    // converts the substring into two c_str pointers //
    char* ch1 = new char[userInput.size()];
    strcpy(ch1, userInput.c_str());

    char* ch2 = new char [userInput.size()];
    strcpy(ch2, userInput.c_str());
    //cout << "3" << endl;
    

    // takes two c_str pointers and takes relevant characters //
                
    vector<char*> v1;
    vector<char*> v2;

    tok1 = strtok(ch1, ";&|()");
    while (tok1 != NULL) {
        if (strcmp(tok1, " ") != 0 && strcmp(tok1, "  ") != 0 && strcmp(tok1, "   ") != 0) {
            v1.push_back(tok1);
            //cout << tok1 << endl; 
        }
        tok1 = strtok(NULL, ";&|()"); 
    }

    tok2 = strtok(ch2, " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ[]-<>./\"");
    while (tok2 != NULL) {
        v2.push_back(tok2);
        //cout << tok2 << endl;
        tok2 = strtok(NULL, " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ[]-<>./\"");

    }
    unsigned int c1 = 0;
    unsigned int c2 = 0;

    //cout << "v1 size: " << v1.size() << endl;
    //cout << "v2 size: " << v2.size() << endl;
    /* For loop for testing contents of v1
    for (int i = 0; i < v1.size(); i++) {
        cout << "v1[" << i << "]: " << v1[i] << endl;
    }
    */
    if (v1.size() > 1) {
        
        while (c1 < v1.size()) {
            while (c2 < v2.size() && strcmp(v2[c2], "(") == 0) {
                CS.addInstruction(createConnector(v2[c2]));
                c2++;
            }        
            CS.addInstruction(createCommand(v1[c1]));
            if (c2 < v2.size() && strcmp(v2[c2], ")") != 0) {CS.addInstruction(createConnector(v2[c2]));}
            else {
                while (c2 < v2.size() && strcmp(v2[c2], ")") == 0) {
                    CS.addInstruction(createConnector(v2[c2]));
                    c2++;
                }
                if (c2 < v2.size()) {
                    CS.addInstruction(createConnector(v2[c2]));
                }
            }
            c1++;
            c2++;
            
        }
        
        /*
        while (c2 < v2.size() || c1 < v1.size()) {
            //cout << "while - addInstructions" << endl;
            if (c2 < v2.size()) { 
                if (strcmp(v2[c2], "(") == 0 || strcmp(v2[c2], ")") == 0) {
                    //cout << "while - addInstructions - if" << endl;
                    CS.addInstruction(createConnector(v2[c2]));
                    //cout << "after addInstruction" << endl;
                    c2++;
                }
                else {
                    //cout << "while - addInstructions - else" << endl;
                    CS.addInstruction(createCommand(v1[c1]));
                    if (c2 < v2.size()) {CS.addInstruction(createConnector(v2[c2]));}
                    //cout << "after addInstruction2" << endl;
                }
            }
            else {
                CS.addInstruction(createCommand(v1[c1]));
            }
            c1++;
            c2++;
            //cout << "c++" << endl;
        }
        */
    }
    else {CS.addInstruction(createCommand(v1[0]));}
}

void Reader::display() {
    cout << "$ ";
    read();
}
