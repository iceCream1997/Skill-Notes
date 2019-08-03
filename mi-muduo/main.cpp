#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <iostream>

using namespace std;

#define MAX_LINE 100
#define MAX_EVENT 500
#define MAX_LISTENFD 5

int CreatAndListen(){
    int on = 1;
    int listenfd = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in servaddr;
    fcntl(listenfd,F_SETFL,O_NONBLOCK); //设置文件描述符no-block io
    setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));//设置端口重用
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(11111);

    if(-1 == bind(listenfd, (struct sockaddr *)&servaddr,sizeof(servaddr) ) ){
        cout<<"bind error,error:"<<errno<<endl;
    }

    if(-1 == listen(listenfd, MAX_LISTENFD)){
        cout<<"listend erron,error:"<<errno<<endl;
    }

    return listenfd;
}

int main(){

    
}

