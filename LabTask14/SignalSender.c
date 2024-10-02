//----SignalSender
//--------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

//--------------------------------------------------------------------------------------------------
//----Gloabl Variables
int counter;
pid_t child_pid;

//--------------------------------------------------------------------------------------------------
//----Signal Handler to handle the ^C signal
//----Also sends signal to the SignalReceiver program
static void SIGINTHandler(int sig) {
  printf("SignalSender just got an interrupt\n");
  alarm(5);
  kill(child_pid, SIGUSR1);
}

//--------------------------------------------------------------------------------------------------
//----Signal Handler to handle the alarm signal
static void SIGALRMHandler(int sig) {
  counter++;
  printf("SignalSender just got alarm %d\n", counter);
  alarm(5);
}

//--------------------------------------------------------------------------------------------------
//----Main method to fork and exec
//----Also cleans up zombie process and ends program
int main(void) {
  counter = 0;
  pid_t pid;

  signal(SIGINT, SIGINTHandler);
  signal(SIGALRM, SIGALRMHandler);

  pid = fork();
  if(pid < 0){
    perror("Could not fork");
    exit(EXIT_FAILURE);
  }
  else if(pid == 0){
    execl("/Users/chriseagar/Labs/LabTask14/SignalReceiver", "SignalReceiver", NULL);
    perror("Failed to exec");
    exit(EXIT_FAILURE);
  }

  child_pid = pid;

  alarm(5);
  while (counter < 3){
    pause();
  }

  alarm(0);  
  kill(child_pid, SIGKILL);  
  wait(NULL);
  return 0;
}

