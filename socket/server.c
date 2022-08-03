#include"server.h"
// Reader Function
void* reader(void* param)
{
    int *data=(int *)param;
    // Lock the semaphore
    sem_wait(&x);
    readercount++;
 
    if (readercount == 1)
        sem_wait(&y);
 
    // Unlock the semaphore
    sem_post(&x);
 
    printf("\n%d reader is inside",
           readercount);
    printf("\nCurrent counter %d",*data);
    sleep(5);
 
    // Lock the semaphore
    sem_wait(&x);
    readercount--;
 
    if (readercount == 0) {
        sem_post(&y);
    }
 
    // Lock the semaphore
    sem_post(&x);
 
    printf("\n%d Reader is leaving",
           readercount + 1);
    pthread_exit(NULL);
}
 
// Writer Function
void* writer(void* param)
{
    int *data=(int *)param;

    printf("\nWriter is trying to enter %d",*data);
 
    // Lock the semaphore
    sem_wait(&y);
 
    printf("\nWriter has entered");
    //Increment Counter
    *data=*data+1;
    // Unlock the semaphore
    sem_post(&y);
 
    printf("\nWriter is leaving");
    pthread_exit(NULL);
}
int main(void)
{
    struct sockaddr_in stSockAddr;
    struct sockaddr_storage serverStorage;
    sem_init(&x, 0, 1);
    sem_init(&y, 0, 1);
    int SocketFD = socket(AF_INET,
                            SOCK_STREAM, 0);
 
    if(-1 == SocketFD)
    {
        perror("can not create socket");
        exit(EXIT_FAILURE);
    }
 
    memset(&stSockAddr, 0, sizeof(struct sockaddr_in));
    stSockAddr.sin_family = AF_INET;
    stSockAddr.sin_port = htons(PORT);
    stSockAddr.sin_addr.s_addr = INADDR_ANY;

    if(-1 == bind(SocketFD,(const struct sockaddr *)&stSockAddr, sizeof(struct sockaddr_in)))
    {
        perror("error bind failed");
        close(SocketFD);
        exit(EXIT_FAILURE);
    }
 
    if(-1 == listen(SocketFD, 10))
    {
        perror("error listen failed");
        close(SocketFD);
        exit(EXIT_FAILURE);
    }
    int i=0;
    int counter=0;
    for(;;)
    {
        int addr_size = sizeof(serverStorage);
        int ConnectFD = accept(SocketFD, (struct sockaddr*)&serverStorage,
                           &addr_size);
        int choice = 0;
        
        if(0 > ConnectFD)
        {
            perror("error accept failed");
            close(SocketFD);
            exit(EXIT_FAILURE);
        }
        recv(ConnectFD,
             &choice, sizeof(choice), 0);

        if (choice == 1) {
            // Creater readers thread
            if (pthread_create(&readerthreads[i++], NULL,
                               reader, &counter)
                != 0)
 
                // Error in creating thread
                printf("Failed to create thread\n");
        }
        else if (choice == 2) {
            // Create writers thread
            if (pthread_create(&writerthreads[i++], NULL,
                               writer, &counter)
                != 0)
 
                // Error in creating thread
                printf("Failed to create thread\n");
        }
        if (i >= 50) {
            // Update i
            i = 0;
 
            while (i < 50) {
                // Suspend execution of
                // the calling thread
                // until the target
                // thread terminates
                pthread_join(writerthreads[i++],
                             NULL);
                pthread_join(readerthreads[i++],
                             NULL);
            }
 
            // Update i
            i = 0;
        }
        /* perform read write operations ... */
        shutdown(ConnectFD, SHUT_RDWR);
        close(ConnectFD);
    }
 
    close(SocketFD);
    return 0;
}
/* Client code in C */