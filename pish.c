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
// int parse(const char *cmdline, struct command *cmd) {
//   static char = array[1024];
//   char *line = array;
//   char *token = strtok(cmdLine, " ");
//   int is_bg;

//   if(cmdline == NULL) {
//     perror("command line is NULL\n");
//   }
//   cmd->argc = 0;
//   int i = 0;

//   while(token != NULL) {
//     cmd->argv[i] = token;
//     token = strtok(NULL, " ");
//     ++i;
//   }
//   cmd->argc = i;
//   cmd->argv[cmd->argc] = NULL;

//   if(cmd->argc == 0) {
//     return 1;
//   }

//   if((is_bg = (*cmd->argv[cmd->argc-1] == '&')) != 0) {
//     cmd->argv[--cmd->argc] = NULL;
//   }
//   return is_bg;
// }

char* readline() {
  char *line = NULL;
  size_t buflen = 0;
  getline(&line, &buflen, stdin);
  return line;
}

// void eval(char *cmdLine) {
//   int bg;
//   struct command cmd;

//   bg = parse(cmdLine, &cmd);

//   if(bg == -1) {
//     return;
//   }

//   if(cmd.argv[0] == NULL) {
//     return;
//   }
//   runSystemCommand(&cmd, bg);
  
// }
// void runSystemCommand(struct command *cmd, int bg) {
//   pid_t childPid;
//   char* path = "./bin/";
//   char progpath[20];

//   strcpy(progpath, path);
//   strcat(progpath, cmd->argv[0]);

//   for(int i = 0; i < strlen(progpath); i++) {
//     if(progpath[i] == "\n") {
//       progpath[i] = "\0";
//     }
//   }
//   if((childPid =fork()) < 0) {
//     perror("fork() error");
//   }
//   else if(childPid == 0) {
//     if(execvp(cmd->argv[0], cmd->argv) < 0) {
//       printf("command not found\n");
//       exit(0);
//     }
//   }
// }
int main(int argc, char* argv[]) {
  while (1) {
    char* cmdLine;
    printf("%s", prompt);
    cmdLine = readline();
    if(strcmp(cmdLine, "quit") == 0){
      printf("You have quitted the process");
      exit(1);
    }
    // cmdLine(strlen(cmdLine) - 1) = "\0";
    // eval(cmdLine);
  }
  return 1;
}
