//----ThreadFibServer
//--------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/resource.h>

#define MY_FIFO "FIBOPIPE"
#define TRUE 1
#define FALSE 0

//--------------------------------------------------------------------------------------------------

//----Global variables used by functions
int ChildPID;
int NumberOfThreads;
int FibonacciNumber;

//--------------------------------------------------------------------------------------------------
//----Function to compute the Fibonacci number for the given value
long Fibonacci(long WhichNumber) {

  if (WhichNumber <= 1) {
    return(WhichNumber);
  }
  else {
    return(Fibonacci(WhichNumber - 2) + Fibonacci(WhichNumber - 1));
  }
}

//--------------------------------------------------------------------------------------------------
//----Signal handler - when receiving SIGXCPU send a signal to interface to stop loop
void SIGXCPUHandler(int sig){

  extern int ChildPID;

  printf("S: Received a SIGXCPU, ignoring any more\n");
  printf("S: Received a SIGXCPU, sending SIGUSR1 to interface\n");
  if(signal(SIGXCPU, SIG_IGN) == SIG_ERR){
    perror("Unable to reset signal handler");
  }

  kill(ChildPID, SIGUSR1);
}

//--------------------------------------------------------------------------------------------------
//----Function to set the limit on resource usage
void SetCPUTimeLimit(int CPUTimeLimit) {

  struct rlimit ResourceLimits;

  printf("S: Setting CPU limit to %ds\n", CPUTimeLimit);
  if (getrlimit(RLIMIT_CPU,&ResourceLimits) == -1) {
    perror("CPULimitedRun - Getting resource limit:");
    exit(EXIT_FAILURE);
  }

  ResourceLimits.rlim_cur = CPUTimeLimit;
  if (setrlimit(RLIMIT_CPU,&ResourceLimits) == -1) {
    perror("CPULimitedRun - Setting resource limit:");
    exit(EXIT_FAILURE);
  }
}

//--------------------------------------------------------------------------------------------------
//----Function to run the Fibonacci function (in a different thread) and print out the result
void * FibonacciThread(void * Data){

  int num;
  extern int NumberOfThreads;

  num = *((int *)Data);
  printf("S: Fibonacci %d is %ld\n",num,Fibonacci(num));

  NumberOfThreads--;
  return(NULL);
}

//--------------------------------------------------------------------------------------------------
//----Function to report the CPU usage
void ReportCPU(void){

  struct rusage Usage;
  long TotalSec, TotalUsec;

  getrusage(RUSAGE_SELF,&Usage);
  TotalSec = Usage.ru_utime.tv_sec + Usage.ru_stime.tv_sec + (Usage.ru_utime.tv_usec +
  Usage.ru_stime.tv_usec)/1000000;
  TotalUsec = (Usage.ru_utime.tv_usec + Usage.ru_stime.tv_usec) % 1000000;
  printf("S: Server has used %lds %ldus\n",TotalSec,TotalUsec);
}

//--------------------------------------------------------------------------------------------------
//----Function to read from the pipe as well as create and detach the Fib thread
void MainHelper(FILE * FIFORead){

  pthread_t NewThread;
  extern int NumberOfThreads;

  while(fscanf(FIFORead," %d",&FibonacciNumber) == 1 && FibonacciNumber > 0){
    ReportCPU();
    printf("S: Received %d from interface\n", FibonacciNumber);
    if (pthread_create(&NewThread,NULL,FibonacciThread,&FibonacciNumber) != 0){
      perror("Creating thread");
      exit(EXIT_FAILURE);
    }
    if(pthread_detach(NewThread) != 0){
      perror("Detaching thread");
      exit(EXIT_FAILURE);
    }
    NumberOfThreads++;
    printf("S: Created and detached the thread for %d\n", FibonacciNumber);
  }
}

//--------------------------------------------------------------------------------------------------
//----Function to wait for all threads to finish before exiting the program
void WaitForThreads(void){

  extern int NumberOfThreads;

  while(NumberOfThreads > 0){
    printf("S: Waiting for %d threads\n", NumberOfThreads);
    sleep(1);
  }
}

//--------------------------------------------------------------------------------------------------
//----Function to clean up the user interface program zombie
void WaitForChild(int ChildPID){

  int DeadPID;
  int DeadStatus;

  DeadPID = waitpid(ChildPID, &DeadStatus, 0);
  printf("S: Child %d completed with status %d\n", DeadPID, DeadStatus);
}

//--------------------------------------------------------------------------------------------------
//----Main function to fork and exec user interface program and run all previous functions
int main(int argc, char *argv[]){

  FILE *FIFORead;
  extern int ChildPID;
  extern int NumberOfThreads;


  unlink(MY_FIFO);
  if(mkfifo(MY_FIFO, 0700) == -1){
    perror("Making FIFO");
    exit(EXIT_FAILURE);
  }


  if ((ChildPID = fork()) == -1){
    perror("Could not fork");
    exit(EXIT_FAILURE);
  }

  if (ChildPID == 0){
    execlp("./ThreadFibInterface", "ThreadFibInterface", MY_FIFO, NULL);
    perror("Unable to exec ThreadFibInterface:");
    exit(EXIT_FAILURE);
  }
  
  else{
    if(signal(SIGXCPU, SIGXCPUHandler) == SIG_ERR){
      perror("Unable to install SIGXCPU handler");
      exit(EXIT_FAILURE);
    }
    if(siginterrupt(SIGXCPU, TRUE) == -1){
      perror("Abandoning interrupted system calls");
      exit(EXIT_FAILURE);
    }

    SetCPUTimeLimit(atoi(argv[1]));

    if((FIFORead = fopen(MY_FIFO, "r")) == NULL){
      perror("Opening FIFO to read");
      exit(EXIT_FAILURE);
    }
    NumberOfThreads = 0;
    MainHelper(FIFORead);
    fclose(FIFORead);
    WaitForThreads();
    ReportCPU();
    WaitForChild(ChildPID);
    unlink(MY_FIFO);
   }

    return EXIT_SUCCESS;
}
