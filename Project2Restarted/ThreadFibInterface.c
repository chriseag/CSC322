//----ThreadFibInterface
//--------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define MY_FIFO "FIBOPIPE"
#define TRUE 1
#define FALSE 0

//--------------------------------------------------------------------------------------------------

//----Extern variables from ThreadFibServer
extern int ChildPID;
extern int NumberOfThreads;

//----Global variable used in functions
int FibonacciNumber = 1;


//--------------------------------------------------------------------------------------------------
//----Signal handler - when receiving SIGUSR1 from ThreadFibServer FibonacciNumber is set to
//----0 in order to stop the loop
void SIGUSR1Handler(int sig){
  FibonacciNumber = 0;
  printf("I: Received a SIGUSR1, stopping loop\n");
}

//--------------------------------------------------------------------------------------------------
//----Function to take user input and write the input into the pipe
void MainHelper(FILE * FIFOWrite){

  extern int NumberOfThreads;
 
  while(FibonacciNumber != 0){
    printf("Which Fibonacci number do you want: ");
    scanf("%d", &FibonacciNumber);
    if(FibonacciNumber != 0){
      fprintf(FIFOWrite, "%d\n", FibonacciNumber);
      fflush(FIFOWrite);
    }
  }
}

//--------------------------------------------------------------------------------------------------
//----Main function to set up signal handlers and run other functions
int main(void){

  FILE *FIFOWrite;

  if(signal(SIGUSR1, SIGUSR1Handler) == SIG_ERR){
    perror("Could not install SIGUSR1 handler");
    exit(EXIT_FAILURE);
  }

  if(siginterrupt(SIGUSR1, TRUE) == -1){
    perror("Abandoning interrupted system calls");
    exit(EXIT_FAILURE);
  }

  if((FIFOWrite = fopen(MY_FIFO, "w")) == NULL){
    perror("Opening FIFO to write");
    exit(EXIT_FAILURE);
  }

  MainHelper(FIFOWrite);

  fclose(FIFOWrite);

  return EXIT_SUCCESS;
}
