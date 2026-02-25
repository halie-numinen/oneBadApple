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
    // int i = 0; //counting for the nodes
    // int counter = 0; //while loop variable
    char nodesString[20];
    long nodes;
    long destinationNodeInteger;
    char* noNode;
    char *errorCheacking;
    while (1) { // user input for number of nodes
        printf("Enter number of nodes: ");
        fgets(nodesString, sizeof(nodesString) stdin);
        if (strlen(nodesString) > 0 || noNode == NULL) {
            break;
        }
    }
    nodesString[strcspn(nodesString, "\n")] = '\0';
    nodes = strtol(nodesString, &errorCheacking, 10);

    int fd[nodes][2];
    int pid;
    int inputPipe, outputPipe;
    char message[1000];
    char destinationNode[20];
    int pipeCreationResult;
    for (int i = 0; i < nodes; i++) { // creating pipes
        pipeCreationResult = pipe(fd);
        if (pipeCreationResult < 0) {
            perror("Failed pipe creation\n");
            exit(1);
        }
        printf("Parent created node %d with a pid of: %d\n", i, getpid());

    }
    while (1) { // getting the message the user what to send and what node to send to
        printf("Enter message: ");
        char* noDestination = fgets(destinationNode, sizeof(destinationNode), stdin);
        printf("Enter desired node to receive message: ");
        char* noMessage = fgets(message, 1000, stdin);
        if (noMessage == NULL || noDestination == NULL || strlen(destinationNode) > 0) {
            break;
        }
    }
    destinationNode[strcspn(destinationNode, "\n")] = '\0';
    destinationNodeInteger = strtol(destinationNode, &errorCheacking, 10);

    char readMessage[1000];
    int childId;
    message[strcspn(message, "\n")] = '\0';
    for (int i = 0; i < nodes - 1; i++) { 
        pid = fork();
        if (pid < 0) {
            perror("Fork failed\n");
            exit(1);
        }
        if (pid == 0) {
            childId = i;
            inputPipe = fd[(childId - 1 + nodes) % nodes][READ]; 
            outputPipe = fd[nodes][WRITE];
        
            for (int j = 0; j < nodes; j++) { // closing unuesd ends
                if (fd[j][READ] != inputPipe) {
                    close(fd[j][READ]); // what the child uses
                }
                if (fd[j][WRITE] != outputPipe) {
                    close(fd[j][WRITE]);
                }
        }
    
    }
    while (counter < n){ // creating nodes from given input
        struct node[i] {
            struct node *next;
        };
        n++;
        i++;
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

