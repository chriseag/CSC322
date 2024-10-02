//----SignalReceiver
//--------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

//--------------------------------------------------------------------------------------------------
//----Signal handler to handle signal coming from SignalSender
static void SIGUSR1Handler(int sig) {
  printf("SignalReceiver just got an SIGUSR1\n");
}

//--------------------------------------------------------------------------------------------------
//----Main method to tell program to wait for an incoming signal continuously
int main(void) {
  signal(SIGINT, SIG_IGN);
  signal(SIGUSR1, SIGUSR1Handler);

  while(1){
    pause();
  }

  return 0;
}
