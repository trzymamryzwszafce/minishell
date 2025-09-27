#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    pid_t pid;
    char *argv[] = {"/bin/ls", "-l", NULL}; // command and arguments
    char *envp[] = {NULL}; // environment (empty for now)

    pid = fork();
    if (pid == 0)
    {
        // Child process: run the command
        execve(argv[0], argv, envp);
        perror("execve failed"); // only runs if execve fails
        exit(1);
    }
    else if (pid > 0)
    {
        // Parent process: wait for child
        wait(NULL);
    }
    else
    {
        perror("fork failed");
        exit(1);
    }
    return 0;
}

