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

        bool get_ex() {return ex;}

        bool runNext(bool exec, Instruction* conn) {
            if (strcmp(conn->str, ";") == 0) {
                return true;
            }
            else if (conn->exec == exec)
                return true;
            else
                return false;
        }

        void setCS(CmdString cs) {CS = cs;}

        bool execute(CmdString cs) {
            //cout << "EXECUTE" << endl;
            unsigned int count = 0;
            unsigned int tmp; // temporarily holds value of count / used in CmdString Recursion algorithm
            unsigned int paraC; // count for number of "(" enclosures / used in CmdString Recursion algorithm
            CmdString CSrec;
            string str;

            pid_t pid, w;
            int status;
            bool run = true;
            ex = false;                              
            bool result;
            bool replace;

            vector<Instruction*>::iterator it;
            vector<Instruction*>::iterator it2;

            char tc[] = "true";
            char fc[] = "false";
            char* t = tc;
            char* f = fc;



            do {
                //std::cout << "inside while" << endl;
                //cout << "testFor:" << endl;
                //for (int i = 0; i < cs.V.size(); i++) {
                    
                //    cout << cs.V[i]->str << endl;
                //}
                //cout << "end testFor" << endl;
                

                //cout << "Exit Test: " << cs.V[count]->str << endl;
                if ((strcmp(cs.V[count]->str, "exit") == 0 || strcmp(cs.V[count]->str, "Exit") == 0 
                    || strcmp(cs.V[count]->str, " exit") == 0 || strcmp(cs.V[count]->str, " Exit") == 0) && run == true) {
                    ex = true;
                }

                
                
                paraC = 0;
                tmp = count;
                int tmp2 = 0;
                
                //The following if statement takes care of parentheses by cutting out 
                //the appropriate segment from cs.V and passing it to a recursive call
                //of this same function. Once it finishes it will have returned a bool
                //which then takes place of the parentheses.
                //
                //Ex: (echo a && echo b); echo c -> true; echo c
                

                if (strcmp(cs.V[tmp]->str, "(") == 0) {
                    while (tmp < cs.V.size()) {
                        if (paraC == 1 && strcmp(cs.V[tmp]->str, ")") == 0) {
                            tmp2 = tmp;
                            break;
                        }
                        if (strcmp(cs.V[tmp]->str, "(") == 0) {
                            paraC++;
                        }
                        if (strcmp(cs.V[tmp]->str, ")") == 0) {
                            paraC--;
                        }
                        tmp++;
                    }

                    /*
                    cout << "count: " << count << endl;
                    cout << "tmp: " << tmp << endl;
                    cout << "tmp2: " << tmp2 << endl;
                    */
                    it = cs.V.begin();
                    it2 = cs.V.begin();
                    advance(it, count + 1);
                    advance(it2, tmp2);
                    /*
                    cout << "For Assign: " << endl;
                    cout << "it: "  << (*it)->str << endl;
                    cout << "it2: " << (*it2)->str << endl;
                    */

                    CSrec.V.assign(it, it2);

                    it = cs.V.begin();
                    it2 = cs.V.begin();
                    advance(it, count);
                    if (tmp2 + 1 != cs.V.size())
                        advance(it2, tmp2 + 1);
                    else
                        advance(it2, cs.V.size() - 1);

                    /*
                    cout << "For Erase: " << endl;
                    cout << "it: " << (*it)->str << endl;
                    cout << "it2: " << (*it2)->str << endl;
                    */
                    cs.V.erase(it, it2); 
                    // this for loop is for testing purposes only. Will be removed later
                    /*
                    for (int i = 0; i < CSrec.V.size(); i++) {
                        cout << "CSrec.V[" << i << "]: "  << CSrec.V[i]->str << endl;
                    }
                    */
                    if (run) {
                        replace = execute(CSrec);
                    }
                    else {replace = true;}
                    
                    // replace section between () with true/false based on value of replace
                    if (replace) { 
                        cs.V.insert(it, new Command(t));
                    }
                    else {
                        cs.V.insert(it, new Command(f));
                        //cout << "insert false" << endl;
                    }    
                }
                /*
                cout << endl << "Count: " << count << endl;
                cout << endl << "Before Fork: " << endl;
                for (int i = 0; i < cs.V.size(); i++) {
                    cout << cs.V[i]->str << endl;
                }
                */
                pid = fork();
            
                //cout << "right before pid if statements" << endl;
 
                if (pid > 0) {
                    // parent fork
                    //cout << "parent" << endl;
                    w = wait(&status);
                    //cout << "wait: " << w << endl;
                    //parser for individual commands//
                    if (status == 0) {
                        cs.V[count]->exec = true;
                    }
                    else
                        cs.V[count]->exec = false;

                    if (count < cs.V.size() - 1) {
                        if (strcmp(cs.V[count+1]->str, ")") == 0 && count < cs.V.size() - 2) { 
                            run = runNext(cs.V[count]->exec, cs.V[count+2]);
                        } 
                        else { 
                            run = runNext(cs.V[count]->exec, cs.V[count+1]);
                        }
                    }
                }
                else if (pid == 0) {           // !! It is probably possible to simplify this code by replacing the vector<char*> with the char** already being used

                    //cout << "child - parse" << endl;

                    // must parse Command in CmdString at current position
                    str = cs.V[count]->str;
                    char* ch = new char[str.length()];
                    strcpy(ch, str.c_str());
                    vector<char*> vch;
                    
                    char* tok = strtok(ch, " ");
                    
                    while (tok != NULL) {
                        vch.push_back(tok);
                        tok = strtok(NULL, " ");    
                    }
                    vch.push_back('\0');       
          
                    //intending to instantiate array of char pointers
                    int vsize = vch.size();
                    char** charr = new char* [vsize];
                    for (unsigned int j = 0; j < vch.size(); j++) {
                        charr[j] = vch[j];
                    }

                     
                    if (run) { 
                        if(strcmp(vch[0], "test") == 0 || strcmp(vch[0], "[") == 0) {
                          //compare the string entered by the user
                            int count_tmp=0;
                            string flag="";
                            //std::cout<< vch[1] << std::endl; //seeout

                            if(strcmp(vch[1], "-e") == 0){
                                count_tmp=2;
                                flag = "-e";
                            }

                            else if(strcmp(vch[1], "-d") == 0){
                                count_tmp=2;
                                flag = "-d";
                            }

                            else if(strcmp(vch[1], "-f")==0){
                                count_tmp=2;
                                flag = "-f";
                            }
                            else count_tmp=1; //this creates an error when someone puts an incorrect flag

                            //std::cout<< count_tmp << std::endl; //seeout
                            const char* path = vch[count_tmp]; 
                            struct stat file_info;

                            if(stat(path, &file_info) != 0) {
                                if(errno == ENOENT) {
                                    //std::cout<< "The file doesn't exist"<<std::endl;
                                    std::cout<< "(False)" <<std::endl;
                                } 
                                else if(errno == EACCES) {
                                    //std::cout<< "We don't have permission to know if it is a file"<<std::endl;
                                    std::cout<< "(False)" <<std::endl;
                                } 
                                else {
                                    //std::cout<< "An undefined error occured"<<std::endl;
                                    std::cout<< "(False)" <<std::endl;
                                }
                                exit(EXIT_FAILURE);
                            }
                            else if(stat(path, &file_info) == 0) {
                                if(flag == ""){
                                    std::cout<< "(True)" <<std::endl;
                                }
                                else if(flag == "-e"){
                                    //std::cout<<"The file does exist"<<std::endl;
                                    std::cout<< "(True)" <<std::endl;
                                }
                                else if(flag == "-f" || S_ISREG(file_info.st_size)) {
                                    //std::cout<<"The file is a regular one"<<std::endl;
                                    std::cout<< "(True)" <<std::endl;
                                } 
                                else if(flag == "-d" || S_ISDIR(file_info.st_mode)) {
                                    //std::cout<<"The file is actually a directory"<<std::endl;
                                    std::cout<< "(True)" <<std::endl;
                                } 
                                else {
                                    std::cout<< "Please enter a valid argument to the test command" <<std::endl;
                                }
                                exit(0);
                            }
                        }
                        
                        if (strcmp(charr[0], "exit") == 0 || strcmp(charr[0], "Exit") == 0){
                            exit(0);
                        }   
                        else {
                            
                            execvp(charr[0], charr);
                            perror(*charr);
                            exit(EXIT_FAILURE);
                        }  
                        
                    }
                    else {
                        cs.V[count]->exec = true;
                        run = true;
                    }
                }
                else {
                    std::cout << "fork failed" << std::endl;
                }
                count += 2;
                /*
                if (strcmp(cs.V[count]->str, ")") == 0) {
                    count++;
                    while (strcmp(cs.V[count]->str, "&&") == 0 || strcmp(cs.V[count]->str, "||") == 0 || 
                           strcmp(cs.V[count]->str, ";") == 0 || strcmp(cs.V[count]->str, ")") == 0) {
                               count++;
                           }
                }
                */

                //cout << "count: " << count << endl;
                //cout << "ex: " << ex << endl;
                //if (count <= cs.V.size() -1 && ex == false) {cout << "no break" << endl;}
                //else {cout << "break" << endl;}
            } while (count <= cs.V.size() - 1 && ex == false);
            
            result = cs.V[cs.V.size()-1]->exec;
            cs.V.clear();
            return result;
        }  
};
#endif //__COMMANDER_H__
