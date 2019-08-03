#include <iostream>
#include <bits/types.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <errno.h>
#include <string.h>

using namespace std;

#define IPC_KEY 0x12345678
#define TYPE_C 1
#define TYPE_S 2

// struct msgbuf
// {
//     long mtype;
//     char mtext[1024];
// };

int main(){
    int msqid = -1;
    //int msgget(key_t key, int msgflg);
   //key :消息队列标识符，msgflg:IPC_CREAT :不存在消息队列则创建，存在则打开
   //创建消息队列
    msqid = msgget(IPC_KEY,IPC_CREAT|0664);
    if(msqid < 0){
        perror("msgget");
        exit(1);
    }
    
    while(1){
        //接受数据
      //ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtype,int msgflg);
      struct msgbuf buff;
      msgrcv(msqid,&buff,1024,TYPE_C,0);
      //msqid :消息队列操作句柄；
      //&buff 接受数据的结构体，需要自己定义
      //1024 接受数据的最大数据长度，不包含mtype
      //0 如果数据长度超过指定长度不截断，如果参数是MSG_NOERROR 将会截断数据
      cout<<buff.mtext<<endl;

       //发送数据
       memset(&buff,0,sizeof(struct msgbuf));
       buff.mtype = TYPE_S;
       scanf("%s",buff.mtext);

       msgsnd(msqid,&buff,1024,0);
    }

     //一般用ctrl+c使进程停止，没有运行到这里，也就意味着没有删除消息队列
   //删除消息队列:IPC_RMID  第三个参数是删除后获取消息队列属性信息，如果不想获取可以置NULL
   //int msgctl(int msqid, int cmd, struct msqid_ds *buf);
    msgctl(msqid,IPC_RMID,NULL);
    exit(0);
}