#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

#define MAX_INPUT 1024
#define MAX_ARGS 100

void sigint_handler(int signo) {
    if (signo != SIGINT) {
        return;
    }
    char cwd[MAX_INPUT];
    if(getcwd(cwd, sizeof(cwd)) == NULL){
        printf("sudoshell: ");
    }else{
        printf("\nTo exit, use \"exit\" command.\n\n");  
        printf("sudoshell:%s ", cwd);
    }
    fflush(stdout);
}

void execute_cd(char *path){
    if(path==NULL){
        fprintf(stderr, "cd failed: Missing argument\n");
    }else{
        if (chdir(path) != 0) {
            perror("cd failed");
        }
    }
}

void loop(){
    char input[MAX_INPUT];
    pid_t child_pid;
    int quit=0;
    char cwd[MAX_INPUT];

    do{
        if (getcwd(cwd, sizeof(cwd)) == NULL) {
            perror("getcwd Failed");
            continue;
        }

        printf("\n[sudoshell] %s ➜  ", cwd); 

        // Handling Input
        if(fgets(input, sizeof(input), stdin) == NULL){
            printf("\nExiting sudoShell...\n");
            exit(0);
        }
        input[strcspn(input, "\n")] = '\0';  // Replace newline char with null
        
        if(strlen(input) == 0) continue; // Handle empty user input


        // Tokenize input into arguments
        char *args[MAX_ARGS];
        char *token = strtok(input, " "); // Get first command
        int i=0;
        while(token!=NULL && i<MAX_ARGS-1){
            args[i++] = token;
            token = strtok(NULL, " "); // I know its weird, check strtok definition -> subsequent calls should use null as argument
        }
        args[i] = NULL;

        // Built-In: cd command
        if (strcmp(args[0], "cd") == 0) {
            execute_cd(args[1]);
            continue;
        }

        // Built-In: exit command
        if(strcmp(args[0], "exit")==0){
            quit=1;
            continue;
        }
        
        child_pid = fork(); // Child process created
        
        if (child_pid < 0) {
            perror("fork failed");
            continue;
        }

        if(child_pid == 0) { 
            // Inside child process
            signal(SIGINT, SIG_DFL);
            execvp(args[0],args);

            // If execvp succeeds, it replaces program so below code wont run. Only runs when unsuccessfull
            fprintf(stderr, "sudoshell: command not found: %s\n", args[0]);
            exit(1);
            
        }else{
            // Inside parent process
            waitpid(child_pid,NULL,0);
        }

    }while(!quit);
}


int main(){
    printf("Welcome to sudoShell! \n");
    signal(SIGINT, sigint_handler);

    loop();
    return 0;
}
