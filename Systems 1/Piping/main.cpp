#include <iostream>
#include <csignal>
#include <cstring>
#include <sys/wait.h>
#include <list>

#include <unistd.h>

#include "Command.hpp"
/*****************************************************
 *  Example usage of the Command class for project 1 *
 *****************************************************/
int pipeOutput = -1;
list<int> backgroundPID;
list<string> backgroundName;
int pid;
int numArgs;
int num=1; // keep track of number of commands.
Command com;
int executeCommand(){
  FILE *in;
  FILE *out;
  if(!backgroundPID.empty() ){//if something has been backgrounded, check if it's done, if it is, print a report.
      if(backgroundPID.front()==waitpid(backgroundPID.front(),NULL,WNOHANG)){
      cout << endl << "a backgrounded command has been completed! Name: " << backgroundName.front() << " pid: " << backgroundPID.front() << endl;
      backgroundPID.pop_front();
      backgroundName.pop_front();
    }
  }
  if (com.name() == "cd"){ // if it's cd, it doesn't have to be execvp, so doesnt need a fork.
    chdir(com.args()[1].c_str());
    cout << num++ << ")" << com << endl;
    cout << ">>>> ";
    com.read(); 
  }else{//everything else does need to be forked
          int pipefd[2];
          int status;
          if(com.pipeOut()||pipeOutput!=-1){//if I need a pipe, either to read or write, create a pipe
            status = pipe(pipefd);
            if (status!=0){
              cout << "pipe failed!" << endl;
            }
          }
        pid=fork();
        if(pid==-1){
          cout <<"Fork failed!"<<endl;
        }else if (pid==0){//child process
          if(pipeOutput!=-1){ //If the last command piped out, I need to take it's output as this command's input
            dup2(pipeOutput,fileno(stdin));
          }
          if(com.pipeOut()){ //If this command needs to pipeout, pipe out to the reader.
            dup2(pipefd[1],fileno(stdout));
          }else{ //Otherwise, close the reader
            close(pipefd[1]);
          }
            if(com.inputRedirectFile()!=""){//if theres an input redirect file, open it and dup2
              in = fopen(com.inputRedirectFile().c_str(),"r");
              dup2(fileno(in),fileno(stdin));
            }
            if (com.outputRedirectFile()!=""){//if theres an output redirect file, open it and dup2;
              out = fopen(com.outputRedirectFile().c_str(),"w");
              dup2(fileno(out),fileno(stdout));
            }
            numArgs=com.numArgs()+1;//number of args including null at the end
            const char** cstrArgs=new const char*[numArgs];//a new array with args
            for(int i=0;i<numArgs-1;i++){//copy com.args into args but as char
              cstrArgs[i]=(com.args()[i].c_str());
            }
            cstrArgs[numArgs-1]=nullptr;//add nullptr at the end
            execvp(com.name().c_str(), const_cast<char* const*>(cstrArgs));//execvp the command
            //delete[] cstrArgs;
        }else{//in parent function
          if (!com.backgrounded()){//if its not backgrounded, wait
            waitpid(pid,NULL,0);
          }else{ //if it is backgrounded, add it to my linked list to be checked on later
            backgroundPID.push_back(pid);
            backgroundName.push_front(com.name());
	  }
	  if(com.pipeOut()){//If I piped out, close the writer, and save the output as pipeOutput
	    pipeOutput=pipefd[0];
	    close(pipefd[1]);
	  }else{//otherwise, pipeOutput is -1 to tell the next command this one did not pipeout
	    pipeOutput=-1;
	  }
	  if(!com.pipeOut()){ //if com piped out, there is no need to "prompt" for next command as it has already been entered, but otherwise I should.
	    cout << ">>>> ";
	  }
      }
    }
    return 0;
}

int main(void)
{
    // prompt for and read in first command. 
    cout << ">>>> ";
    com.read();
    while(com.name() != "exit"){
      executeCommand();
      com.read();
      num++;
    }
  cout << "Thank you for using mini-shell. We now return you to your regularly scheduled shell!" << endl;
} 
