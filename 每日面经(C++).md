## 每天刷一篇面经(C++后台方向) 日志打卡   
### 2019-8-8-white-来源网络  
1. C++是不是类型安全的？
  * 不是。两个不同类型的指针之间可以强制转换（用reinterpret_cast)。C#是类型安全的。  
2. main 函数执行以前，还会执行什么代码？  
 * 全局对象的构造函数会在main 函数之前执行。

### 2019-8-17-white-腾讯云现场面  
1. 大量的短连接会导致服务端大量连接出于time-wait状态，导致通道被占用。通过修改什么参数可以修改time-wait的时间
  * 修改/etc/sysctl.conf文件中的参数  
  * 
2. 如何判断对端关闭 
  * 使用read返回值，如果返回0，并且errno=EAGAIN，则说明连接被对方关闭  
  * 使用心跳包，长时间没有接到心跳包时，说明连接断开  
  * getsockopt判断连接状态，若是TCP_ESTABLISHED，则说明连接未断开，否则说明连接断开  
3. 大量连接处于close-wait状态是因为什么？怎么解决  
  * 对端关闭是程序没有检测到，或者程序忘了需要关闭连接，检测对端有没有关闭，对端关闭主动断开连接    
4. 如何优雅的关闭连接  
  * 使用shutdown函数，close会关闭套接字，如果套接字是共享的，不会进行四次挥手关闭连接，而shutdown会根据传进的参数会切断套接字的共享功能，使用shutdown之后也要调用close；    
  ```C++
  int shutdown(int s,int how);
   /*shut_re(0) 另一端不许再发送数据,数据读取完之后自动会关闭  
   shut_wr(1) 另一端不许再接收数据
   shut_rdwr(2) 另一端不许发送和接受 */
   close(s);
   ```
  * 使用so_linger:  
  ```C++
  struct linger{
    int l_onoff;
    int l_linger;
  };

  struct linger ling;
  ling.l_onoff = 1;
  ling.l_linger = 0;
  setsockopt(fd, SOL_SOCKET, SO_LINGER, (char*)&ling, sizeof(ling));
  close(fd);
  ```
    1. l_onoff为0，则l_linger忽略，此种情况相当于SO_LINGER没有使用一样，即等于内核默认情况，close调用会立即返回，可能会也可能不会传输未发送的数据  
    2. l_onoff为非0，l_linger为0，则close关闭时tcp将丢弃保留在发送缓冲区中的任何数据并发送一个RST给对方，不会再有四次挥手  
    3. l_onoff为非0，l_linger为非0，此时close关闭时内核将会拖延一段时间，如果发送缓冲区中还有数据，进程将处于阻塞状态，直到缓冲区中所有数据发送完成并被对方确认，之后再进行正常的四次挥手。此种情况下，检查close的返回值是很重要的，因为如果数据发送完成前超时，close将返回EWOULDBLOCK错误并且套接口发送缓冲区中数据都会丢失。close如果成功返回，则说明对方已对发送的数据进行了确认，但却并不知道应用程序是否已读取了数据。并且如果套接口是非阻塞的，它将不等待close完成  


