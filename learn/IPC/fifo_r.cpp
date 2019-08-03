#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

using namespace std;

#define FIFO_NAME "testfifo"
#define BUF_SIZE 1024

int main(int argc,char *argv[]){
    int fd;
    char buf[BUF_SIZE];

    fd = open(FIFO_NAME,O_RDONLY);
    read(fd,buf,BUF_SIZE);

    cout<<buf<<endl;

    close(fd);

    exit(0);
}