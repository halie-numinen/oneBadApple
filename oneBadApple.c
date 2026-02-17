#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>

#define READ 0
#define WRITE 1

void sigHandler (int);

int main() {
    int fd[2];
    int pid;
    int pipeCreationResult;
    pipeCreationResult = pipe(fd);
    if (pipeCreationResult < 0) {
        perror("Failed pipe creation\n");
        exit(1);
    }
    pid = fork();
    if (pid < 0) {
        perror("Fork failed\n");
        exit(1);
    }

    while (1) { // user input
        printf("Enter command: ");
        fgets(string, n, stdin);
    }
    string[strcspn(string, "\n") = '\0'];
    signal (SIGINT, sigHandler);
    printf ("waiting...\n");
    pause();
    return 0;
}
void sigHandler (int sigNum) {
    printf (" received an interrupt.\n");
    // this is where shutdown code would be inserted
    sleep (1);
    printf ("time to exit\n");
    exit(0);
}

