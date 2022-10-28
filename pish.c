#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#define PATH

int MAXLINE = 1024;
char prompt[] = "pish%";
extern char **environ;

struct command {
  int argc; //number of arguments passed in
  char *argv[128]; //list of arguments
};

//signal handling
void cntrlZ(int sig) {
   printf("You have now exited the shell\n");
   exit(1);
}

void coreDump(int sig) {
   printf("Quitted the process by core dumping\n");
   exit(1);
}


void cntrlC(int sig) {
   printf("Copied\n");
   exit(1);
}

//output redirecting
void outputRedir(char *found) {
    //printf("File redirection successful\n");
    //redirecting file using dup2. FIX
    int redirect_fd = open(found, O_CREAT | O_TRUNC | O_WRONLY);
    dup2(redirect_fd, STDOUT_FILENO);
    close(redirect_fd);
}

//appending output to a file
void appendRedir(char *found) {
    //printf("File redirection successful\n");
    //redirecting file using dup2. FIX
    int redirect_fd = open(found, O_CREAT | O_TRUNC | O_WRONLY);
    dup2(redirect_fd, STDOUT_FILENO);
    close(redirect_fd);
}

//parsing the command entered based on a space
char* parseSpace(char* buffer) {
	execl("/bin/sh", "/bin/sh", "-c", buffer, 0);

    	//char str[] = "strtok needs to be called several times to split a string";
	int init_size = strlen(buffer);
	char delim[] = " ";

	char *ptr = strtok(buffer, delim);

	while(ptr != NULL)
	{
		//printf("'%s'\n", ptr);
		ptr = strtok(NULL, delim);
	}
	return ptr;
	//printf("\n");
	
}

//parsing output for redirection
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

void underCons(char *p) {
    int fileRedirect;
    fileRedirect = open(&p[1], O_RDWR | O_CREAT | O_APPEND);
    dup2(fileRedirect,1);
}

//check for input redir with strchr
void checkInputRedir(char* buffer) {
    char *p;
    p = strchr(buffer, '<');

    int fd;
    int ret;
    fd = open("testing.txt", O_CREAT | O_APPEND | O_WRONLY);

    if(fd < 0) {
	perror("error in opening file");
    }
    ret = dup2(fd, 1);

    if(ret < 0) {
	perror("error in dup2");
	exit(1);
    }

    
    //underCons(p);
    //gets the filename
    printf("filename: %s\n", &p[1]);
    close(fd);
}

void commandExec(char* buffer) {
    char *p;
    p = strchr(buffer, '/');
    printf("Pathname you entered: %s\n");
 
}


//writing input for redirection
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

	close(fd);
	//return;
}

//parsing output for redirection
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

void changeDir(char* buffer) {
	FILE *fp;
    	//char str[] = "strtok needs to be called several times to split a string";
	int init_size = strlen(buffer);
	char delim[] = "cd";

	char *ptr = strtok(buffer, delim);
	int i = 0;
	while(ptr != NULL)
	{
		//i++;
		ptr = strtok(NULL, delim);
		printf("New directory'%s'\n", ptr);

		//printf("'%s'\n", ptr);
	}
	printf("\n");

}


void pipeProgram(char *buffer) {
	int fd[2];
	if(pipe(fd) == -1) {
		printf("An error occured creating pipe\n");
	}
	int pid = fork();
	if(pid == 0) {
		close(fd[0]);
		int x;
		printf("Input a number: ");
		scanf("%d", &x);
		if(write(fd[1], &x, sizeof(int)) == -1) {
			printf("error occured with writing to pipe");
			exit(1);
		}
		close(fd[1]);
	}
	else {
		close(fd[1]);
		int y; 
		if(read(fd[0], &y, sizeof(int)) == -1) {
			printf("error occured with reading from pipe");
			exit(1);
		}
		close(fd[0]);
	}
	
}

int main(int argc, char* argv[], char **envp) {
  printf("This is the beginning of the pish shell terminal\n");
  //ctrl z
  struct sigaction sa;
  sa.sa_handler = &cntrlZ;
  sa.sa_flags = SA_RESTART;
  sigaction(SIGTSTP, &sa, NULL);

  //core dump
  struct sigaction ta;
  ta.sa_handler = &coreDump;
  ta.sa_flags = SA_RESTART;
  sigaction(SIGQUIT, &ta, NULL);

  //ctrl c
  struct sigaction ba;
  ba.sa_handler = &cntrlC;
  ba.sa_flags = SA_RESTART;
  sigaction(SIGINT, &ba, NULL);


  int ret;
  ret = setenv("PATH", "os/pish/", 0);
  if(ret == -1) {
    perror("PATH not created");
  }

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
     if(strcmp(buffer, "cd") == 0){	
	printf("Entering the directory with the shell. The shell's home directory\n");
	chdir("/home");        
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
	char *pathname;
   	pathname = strchr(buffer, '/');
	char* ptr = parseSpace(buffer);
	printf("ptr: %s\n", &ptr[1]);
	printf("environ: %p\n", environ);
		

	execl("/bin/sh", "/bin/sh", "-c", buffer, 0);
	//setenv[PATH];


	//exit(1);
      }
      //execl("/bin/sh", "/bin/sh", "-c", buffer, 0);
      //checkRedirection(buffer);
    }

   }
  return 1;
}
