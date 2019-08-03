#include <iostream>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <errno.h>

using namespace std;

#define IPC_KEY 0X12345678
#define TYPE_C 1
#define TYPE_S 2

// struct msgbuf
// {
//     long mtype;
//     char mtext[1024];
// };  

int main(){
    int msqid = -1;
    msqid = msgget(IPC_KEY,IPC_CREAT|0664);
    if(msqid < 0){
        perror("msgget");
        exit(1);
    }

    while(1){
        struct msgbuf buff;
        memset(&buff,0,sizeof(struct msgbuf));
        buff.mtype = TYPE_C;
        cin>>buff.mtext;
        msgsnd(msqid,&buff,1024,0);

        //接受数据
      //ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp,int msgflg);
      msgrcv(msqid,&buff,1024,TYPE_S,0);
      cout<<buff.mtext<<endl;
    }

    msgctl(msqid,IPC_RMID,NULL);
    exit(0);
}