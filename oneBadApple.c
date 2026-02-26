#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>

#define READ 0
#define WRITE 1

struct messagingSystem{
    int destinationNode;
    char message[1000];
} apple;

void sigHandler (int);

int main() {
    char nodesString[20];
    int nodes;
    char* noNode;
    char *errorCheacking;
    while (1) { // user input for number of nodes
        printf("Enter number of nodes: ");
        noNode = fgets(nodesString, sizeof(nodesString), stdin);
        if (noNode != NULL && strlen(nodesString) > 1) {
            break;
        }
    }
    nodesString[strcspn(nodesString, "\n")] = '\0';
    nodes = (int)strtol(nodesString, &errorCheacking, 10);

    int fd[nodes][2];
    int pid;
    int inputPipe, outputPipe;
    char message[1000];
    char inputNode[20];
    int pipeCreationResult;
    for (int i = 0; i < nodes; i++) { // creating pipes
        pipeCreationResult = pipe(fd[i]);
        if (pipeCreationResult < 0) {
            perror("Failed pipe creation\n");
            exit(1);
        }
        printf("Parent created node %d with a pid of: %d\n", i, getpid());
    }
    int childId;
    for (int i = 1; i < nodes; i++) { 
        pid = fork();
        if (pid < 0) {
            perror("Fork failed\n");
            exit(1);
        }
        if (pid == 0) { // Child
            childId = i;
            inputPipe = fd[i][READ]; 
            outputPipe = fd[(i + 1) % nodes][WRITE];
        
            for (int j = 0; j < nodes; j++) { // closing unused ends
                if (i != j) {
                    close(fd[j][READ]); 
                }
                if (j != (i + 1) % nodes) {
                    close(fd[j][WRITE]);
                }
            }
            while (1) { 
                read(inputPipe, &apple, sizeof(apple));
                printf("Node %d: received the apple and is inspecting message\n", childId);
                if (apple.destinationNode == childId) {
                    printf("Node %d received the message and it is: %s\n", childId, apple.message);
                    printf("Node %d: clearing message header\n", childId);
                    strcpy(apple.message, "empty");
                }
                else { // write to the next node
                    printf("Node %d is forwarding massage to node %d\n", childId, (childId + 1) % nodes);
                }
                write(outputPipe, &apple, sizeof(apple));
            }
        }
    }
    // parent
    inputPipe = fd[0][READ]; 
    outputPipe = fd[1][WRITE];
    
    signal (SIGINT, sigHandler);
    for (int j = 0; j < nodes; j++) { // closing unused ends
        if (j != 0) {
            close(fd[j][READ]); 
        }
        if (j != 1) {
            close(fd[j][WRITE]);
        }
    }
    while (1) { // getting the message the user what to send and what node to send to (parent loop)
        printf("Enter message: ");
        fgets(message, 1000, stdin);
        printf("Enter desired node to receive message: ");
        fgets(inputNode, sizeof(inputNode), stdin);
        inputNode[strcspn(inputNode, "\n")] = '\0';
        message[strcspn(message, "\n")] = '\0';
        apple.destinationNode = strtol(inputNode, NULL, 10);
        strcpy(apple.message, message);
        
        write(outputPipe, &apple, sizeof(apple));
        read(inputPipe, &apple, sizeof(apple));
        printf("Parent: apple returned.\n");
    }

    return 0;
    }
    void sigHandler (int sigNum) {
        printf ("Parent is shuting down\n");
        if (sigNum == SIGINT) { 
            printf ("^C received.\n"); 
        }
        
    exit(0);
}
