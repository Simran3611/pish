#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>

int MAXLINE = 1024;
char prompt[] = "pish%";

struct command {
  int argc; //number of arguments passed in
  char *argv[128]; //list of arguments
};

void checkRedirection(char *buffer) {
  for(int i = 0; i < sizeof(buffer); i++) {
    char c = buffer[i];
    if(&c == "<"); {
      printf("Redirect to standard Input");
      //add a method redirectionToStdIn;
    }
    if(&c == ">") {
      printf("Redirect the standard output to a file");
    //add a method that creates and writes to a file. Overrides the contents of a file
    }
    if(&c == ">") {
	if(&buffer[i+1] == ">") {
      		printf("Redirect output to file without overriding contents");
	}
    }
    //add a method that adds to contents of a file.
  }
}

int main(int argc, char* argv[]) {
  while (1) {
    char buffer[100];
    char* cmdLine;
    int pid = vfork();
    //printf("%s", prompt);
    //scanf("%[^\n]%*c", buffer);
    //printf("Buffer: %s\n", buffer);

    //cmdLine = readline();
    //execl("/bin/sh", "/bin/sh", "-c", buffer, 0);
    //int pid = vfork();
    //if(strcmp(buffer, "quit") == 0){
      //printf("You have quitted the process\n");
      //exit(1);
    //}
    //printf("Some instructions at beginning\n");
     if(strcmp(buffer, "quit") == 0){
         printf("You have quitted the process\n");
         exit(1);
      }
    if(!vfork()){
      // child
      //execlp("ls","ls", "-l", NULL); // child is replaced
      printf("%s", prompt);
      scanf("%[^\n]%*c", buffer);
      if(strcmp(buffer, "quit") != 0){
         printf("Your command: %s\n", buffer);
	execl("/bin/sh", "/bin/sh", "-c", buffer, 0);
	//exit(1);
	 }
      execl("/bin/sh", "/bin/sh", "-c", buffer, 0);
      checkRedirection(buffer);
    }
    //printf("%s", prompt);
   // parent continues after child is gone
    //printf("Other instructions\n");
      }
  return 1;
}
