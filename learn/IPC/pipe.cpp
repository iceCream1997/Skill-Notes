#include <iostream>
#include <bits/errno.h>
#include <unistd.h>
#include <sys/types.h>

using namespace std;

int main(void){
    int fd[2];
    pid_t pid;
    char msg[1024];
    if(pipe(fd) < 0){
        perror("pipe");
        exit(1);
    }
    pid = fork();
    if(pid < 0){
        perror("fork");
        exit(1);
    }
    if(pid == 0){
        close(fd[0]);
        write(fd[1],"son,father love you!",100);
    }
    else if(pid > 0)
    {
        close(fd[1]);
        read(fd[0],msg,100);
        cout<<msg<<endl;
    }
    exit(0);
}