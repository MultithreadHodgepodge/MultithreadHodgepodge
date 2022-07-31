#include "client.h"
void* clienthread(void* args)
{
 
    int client_request = *((int*)args);
    int network_socket;
 
    // Create a stream socket
    network_socket = socket(AF_INET,
                            SOCK_STREAM, 0);
 
    // Initialise port number and address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);
 
    // Initiate a socket connection
    int connection_status = connect(network_socket,
                                    (struct sockaddr*)&server_address,
                                    sizeof(server_address));
 
    // Check for connection error
    if (connection_status < 0) {
        puts("Error\n");
        return 0;
    }
 
    printf("Connection established\n");
 
    // Send data to the socket
    send(network_socket, &client_request,
         sizeof(client_request), 0);
 
    // Close the connection
    close(network_socket);
    pthread_exit(NULL);
 
    return 0;
}
 
int main(void)
{
    printf("1. Read\n");
    printf("2. Write\n");
 
    // Input
    int choice;
    scanf("%d", &choice);
    pthread_t tid;
 
    // Create connection
    // depending on the input
    switch (choice) {
    case 1: {
        int client_request = 1;
 
        // Create thread
        pthread_create(&tid, NULL,
                       clienthread,
                       &client_request);
        sleep(20);
        break;
    }
    case 2: {
        int client_request = 2;
 
        // Create thread
        pthread_create(&tid, NULL,
                       clienthread,
                       &client_request);
        sleep(20);
        break;
    }
    default:
        printf("Invalid Input\n");
        break;
    }
 
    // Suspend execution of
    // calling thread
    pthread_join(tid, NULL);
}