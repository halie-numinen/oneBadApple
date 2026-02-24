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
    int i = 0 //counting for the nodes
    int counter = 0 //while loop variable
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

    while (1) { // user input for number of nodes
        printf("Enter number of nodes: ");
        fgets(int, n, stdin);
    }

    while (counter < n){ // creating nodes from given input
        struct node i
        {
            struct node *next
        };
        n++
        i++
    }

    while (1) { // getting the message the user what to send and what node to send to
        printf("Enter message: ");
        fgets(char, message, stdin);
        printf("Enter desired node to receive message: "):
        fgets(int, nodenum, stdin);

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

