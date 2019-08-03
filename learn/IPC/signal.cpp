#include <unistd.h>
#include <signal.h>
#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <errno.h>

using namespace std;

int dis = 0;

void ouch(int sig){
    printf("I get a signal %d\n",sig);
    dis = 1;
}

int main(int argc,char *argv[]){
    pid_t pid;
    pid = fork();

    if(pid < 0){
        perror("fork");
    }
    if(pid == 0){
        sleep(5);
        kill(getppid(),SIGALRM);
    }
    if(pid > 0){
        signal(SIGALRM,ouch);
        while (!dis)
        {
            printf("\nwait signal\n");
            sleep(1);
        }
        

        if(dis){
            printf("\nexit!\n");
        }
    }
    exit(0);
}