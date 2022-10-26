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



void outputRedir(char *found) {
    //printf("File redirection successful\n");
    //redirecting file using dup2. FIX
    int redirect_fd = open(found, O_CREAT | O_TRUNC | O_WRONLY);
    dup2(redirect_fd, STDOUT_FILENO);
    close(redirect_fd);
}
void appendRedir(char *found) {
    //printf("File redirection successful\n");
    //redirecting file using dup2. FIX
    int redirect_fd = open(found, O_CREAT | O_TRUNC | O_WRONLY);
    dup2(redirect_fd, STDOUT_FILENO);
    close(redirect_fd);
}

void parseSpace(char* buffer) {
    	//char str[] = "strtok needs to be called several times to split a string";
	int init_size = strlen(buffer);
	char delim[] = " ";

	char *ptr = strtok(buffer, delim);

	while(ptr != NULL)
	{
		printf("'%s'\n", ptr);
		ptr = strtok(NULL, delim);
	}
	printf("\n");

}
void parseOutputRedir(char* buffer) {
    	//char str[] = "strtok needs to be called several times to split a string";
	int init_size = strlen(buffer);
	char delim[] = ">";

	char *ptr = strtok(buffer, delim);

	while(ptr != NULL)
	{
		printf("'%s'\n", ptr);
		ptr = strtok(NULL, delim);
	}
	printf("\n");

}

void writeInputRedir(char* buffer, char* ptr) {
	int fd;
	int ret;
	fd = open(ptr, O_CREAT | O_APPEND | O_WRONLY);
	if(fd < 0) {
		perror("open");
		exit(1);
	}
	ret = dup2(fd, 1);
	if(ret < 0) {
		perror("dup2");
		exit(1);
	}
	execl("/bin/sh", "/bin/sh", "-c", buffer, 0);
	close(fd);
	//return;
}

void parseInputRedir(char* buffer) {
	FILE *fp;
    	//char str[] = "strtok needs to be called several times to split a string";
	int init_size = strlen(buffer);
	char delim[] = "<";

	char *ptr = strtok(buffer, delim);
	int i = 0;
	while(ptr != NULL)
	{
		printf("'%s'\n", ptr);
		//i++;
		ptr = strtok(NULL, delim);
		printf("'%s'\n", ptr);

		//printf("'%s'\n", ptr);
	}
	printf("\n");

}

void parse(char* buffer, struct command *cmd) {
    cmd->argc = 0;	
    char *found;
    int i = 0;

    found = strtok(buffer,"<");
    if(found==NULL)
    {
        puts("\tNo separators found");
	cmd->argv[i] = NULL;
        //return(1);
    }
    int temp = 0;
    while(found)
    {
        found = strtok(NULL,"<");
	temp++;
	cmd->argv[i] = found;
	if(temp == 1) {
		//printf("File: %s\n",found);
		outputRedir(found);
		return;
	}
	i++;
    }

}


int main(int argc, char* argv[]) {

  while (1) {
    char buffer[100];
    char* cmdLine;

    struct command *cmd;

    int pid = vfork();

    //printf("Some instructions at beginning\n");
     if(strcmp(buffer, "exit") == 0){
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
      if(strcmp(buffer, "exit") != 0){
	printf("Your command: %s\n", buffer);
	parseInputRedir(buffer);
	execl("/bin/sh", "/bin/sh", "-c", buffer, 0);

	//exit(1);
      }
      //execl("/bin/sh", "/bin/sh", "-c", buffer, 0);
      //checkRedirection(buffer);
    }

	//fix if the user doesn't enter quit then the prompt still doesn't show up on the screen.
   }
  return 1;
}
