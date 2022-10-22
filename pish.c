#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int MAXLINE = 1024;
char prompt[] = "pish%";

struct command {
  int argc; //number of arguments passed in
  char *argv[128]; //list of arguments
};



int checkRedirection(char *buffer) {
  for(int i = 0; i < sizeof(buffer); i++) {
    char c = buffer[i];
    if(&c == "<"); {
      printf("Redirect to standard Input\n");
      return i;
      //add a method redirectionToStdIn;
    }
    if(&c == ">") {
      printf("Redirect the standard output to a file\n");
      return i;
    //add a method that creates and writes to a file. Overrides the contents of a file
    }
    if(&c == ">") {
	if(&buffer[i+1] == ">") {
      		printf("Redirect output to file without overriding contents\n");
		return (i+1);
	}
    }
    //add a method that adds to contents of a file.
  }
}

void executeTextFile(int num, char *buffer) {
    char temp[100];
    for(int j = num; num < sizeof(buffer); num++){
	temp[j] = buffer[num];
    }
    printf("redirection successful");
    
    //redirecting file using dup2. FIX
    //int redirect_fd = open("redirect_fd.txt", O_CREAT | O_TRUNC | O_WRONLY);
    //dup2(redirect_fd, STDOUT_FILENO);
    //close(redirect_fd);
}

void parse(char* buffer) {
	//DOESN'T WORK 
	char* piece = strtok(buffer, "<");
	//printf("Prints strtok %s\n", piece);
	piece = strtok(buffer, "<;");
	piece = strtok(buffer, "<;");
	printf("Prints strtok %s\n", piece);
}

int main(int argc, char* argv[]) {
  while (1) {
    char buffer[100];
    char* cmdLine;

    int pid = vfork();

    //printf("Some instructions at beginning\n");
     if(strcmp(buffer, "quit") == 0){
         printf("You have quitted the process\n");
         exit(1);
      }
    printf("%s", prompt);
    if(!vfork()){
      // child
      //execlp("ls","ls", "-l", NULL); // child is replaced

     //prompts the user
      //printf("%s", prompt);
      scanf("%[^\n]%*c", buffer);
      if(strcmp(buffer, "quit") != 0){
        printf("Your command: %s\n", buffer);
	parse(buffer);
	execl("/bin/sh", "/bin/sh", "-c", buffer, 0);
	printf("%s", prompt);
	//exit(1);
      }
      //execl("/bin/sh", "/bin/sh", "-c", buffer, 0);
      //checkRedirection(buffer);
    }

	//fix if the user doesn't enter quit then the prompt still doesn't show up on the screen.
   }
  return 1;
}
