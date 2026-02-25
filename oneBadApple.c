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
    int nodes;
    long destinationNodeInteger;
    char* noNode;
    char *errorCheacking;
    while (1) { // user input for number of nodes
        printf("Enter number of nodes: ");
        fgets(nodesString, sizeof(nodesString), stdin);
        if (strlen(nodesString) > 0 || noNode == NULL) {
            break;
        }
    }
    nodesString[strcspn(nodesString, "\n")] = '\0';
    nodes = (int)strtol(nodesString, &errorCheacking, 10);

    int fd[nodes][2];
    int pid;
    int inputPipe, outputPipe;
    char message[1000];
    char destinationNode[20];
    int pipeCreationResult;
    for (int i = 0; i < nodes; i++) { // creating pipes
        pipeCreationResult = pipe(fd[i]);
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
            while (1) { //infinant loop
                // pause(); // the apple
                printf("Node %d: received the appel and is inspecting message\n", childId);
                if (destinationNodeInteger == childId) {
                    printf("Node %d received the message and it is: %s\n", childId, message);
                    read(inputPipe, &readMessage, sizeof(char));
                    printf("Node %d: clearing message header\n", childId);
                    strcpy(message, "empty");
                }
                else { // write to the next node (might need to move after else)
                    printf("Apple is moving from node %d to node %d\n", outputPipe, inputPipe);
                    write(outputPipe, message, strlen(message));
                    printf("Node %d: forwarding massage to node %d", outputPipe, inputPipe);
                }
            }
        }
    }
    // parent
    printf("Parent: apple returned, ready for another message.\n");
    printf("Enter the destination node as a number (0 ...): ");
    char* noDestination = fgets(destinationNode, sizeof(destinationNode), stdin);
    printf("Enter message: ");
    char* noMessage = fgets(message, 1000, stdin);
    for (int i = 0; i < nodes; i++) { // closing all pipes
        printf("Node %d is shutting down\n", nodes);
        close(fd[i][0]);
        close(fd[i][1]);
    }
    
    signal (SIGINT, sigHandler);
    // printf ("waiting...\n");
    while (1) {
        pause(); // the apple
    }
    // while (counter < n){ // creating nodes from given input
    //     struct node[i] {
    //         struct node *next;
    //     };
    //     n++;
    //     i++;
    // }
    return 0;
}
void sigHandler (int sigNum) {
    printf ("received an interrupt.\n");
    if (sigNum == SIGINT) { // To find Ctrl c
        printf ("^C received.  That's it, I'm shutting you down...\n"); 
    }
    exit(0);
}

