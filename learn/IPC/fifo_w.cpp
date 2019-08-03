#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <iostream>
#include <string.h>

using namespace std;

#define FIFO_NAME "testfifo"

int main(int argc,char *argv[]){
    int fd;
    char buf[] = "hello friend!";
    mkfifo(FIFO_NAME,S_IFIFO|0666);
    fd = open(FIFO_NAME,O_WRONLY);
    if(fd < 0){
        perror("open fifo");
    }
    write(fd,buf,strlen(buf)+1);

    close(fd);

    unlink(FIFO_NAME);
    sleep(1);
    exit(0);
}