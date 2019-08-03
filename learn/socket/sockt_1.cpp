#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <error.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>
#include <netinet/in.h>

#define MYPORT 5000
#define MAXBUF 100

using namespace std;

int main(){
    int socketfd = socket(AF_INET,SOCK_STREAM,0);
    if(socketfd == -1){
        perror("socket");
        exit(1);
    }
    struct sockaddr_in my_addr;
    struct sockaddr_in their_addr;
    int addr_len,numbytes;
    char buf[MAXBUF];
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(MYPORT);
    my_addr.sin_addr = INADDR_ANY;
    

}
