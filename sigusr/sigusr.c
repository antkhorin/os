#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int sig, siginfo_t* info, void* vp) {
    printf("SIGUSR%d from %d\n",sig == SIGUSR1 ? 1 : 2, info->si_pid);
    exit(1);
}

int main(){
    struct sigaction action;
    action.sa_sigaction = handler;
    action.sa_flags=SA_SIGINFO;
    sigemptyset(&action.sa_mask);
    sigaddset(&action.sa_mask,SIGUSR1);
    sigaddset(&action.sa_mask,SIGUSR2);
    sigaction(SIGUSR1, &action, 0);
    sigaction(SIGUSR2, &action, 0);
    sleep(10);
    action.sa_handler = SIG_IGN;
    sigaction(SIGUSR1, &action, 0);
    sigaction(SIGUSR2, &action, 0);
    printf("No signals were caught\n");
    return 0;
}