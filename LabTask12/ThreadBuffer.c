//----ThreadBuffer
//--------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <sched.h>

//--------------------------------------------------------------------------------------------------

//----global variables to communicate between threads
char globalString[100] = "";
int producerExit = 0;

//--------------------------------------------------------------------------------------------------

//----Function for the producer thread
//----Yields the CPU until global string is empty
//----Prompts the user for a string
//----Reads the user input into the global string
//----Terminates when user enters ^D
void* producer(void* arg) {
    while (producerExit == 0) {
        while (strlen(globalString) > 0) {
            sched_yield();
        }
        printf("Enter a string (press ^D to exit): ");
        if (fgets(globalString, sizeof(globalString), stdin) == NULL) {
            producerExit = 1;
        }
    }
    pthread_cancel(*(pthread_t*)arg);
    return NULL;
}

//--------------------------------------------------------------------------------------------------

//----Function for the consumer thread
//----Yields the CPU until the global string is non-empty
//----Prints global string to screen
//----Sets gloabl string to empty at the end
void* consumer(void* arg) {
    while (1) {
        // wait until the shared string is non-empty
        while (strlen(globalString) == 0) {
            sched_yield();
            if (producerExit == 1) {
                // exit the consumer thread if the producer thread has exited
                return NULL;
            }
        }
        // print the global string to the screen
        printf("Received: %s", globalString);
        // clear the shared string
        memset(globalString, 0, sizeof(globalString));
    }
}

//--------------------------------------------------------------------------------------------------

//----Main function
//----Sets common global string to empty
//----Starts threads
//----Detaches threads
//----Exits program
int main() {
    pthread_t producerThread, consumerThread;

    // set the shared string to empty
    memset(globalString, 0, sizeof(globalString));

    // create and start the threads
    pthread_create(&producerThread, NULL, producer, &consumerThread);
    pthread_create(&consumerThread, NULL, consumer, NULL);

    // detach the threads
    pthread_detach(producerThread);
    pthread_detach(consumerThread);

    // exit the main thread
    pthread_exit(NULL);
    return 0;
}
