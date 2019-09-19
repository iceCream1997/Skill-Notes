### C++多线程编程  
1. 多进程和多线程  
    * Linux fork、windows CreateProcess、signal  
    * 多个进程之间时共享的代码段  
    * 多线程编程的两个问题，多线程计算和数据IO，一般的瓶颈会出现在IO上面，要在IO和计算之间找到平衡点  
    * 会导致的问题: 1)死锁 2)乱序 3)并发访问数据造成的问题 4)低效率   
    * C++11带来的新概念:
        1. 高阶接口：(async, future)
        2. 低阶接口: (thread, mutex)  
2. 资源共享  
    * 如果没有必要的话，线程之间不要共享资源  
    * 当线程需要共享非const资源的时候，原子操作      
3. 文件写入问题  
    * 当对文件写入的时候会先操作系统的缓存中，只有当删除文件流的时候才会真正的写入到磁盘文件里，所以在程序的运行期间有可能会出现缓存被覆盖的情况  
    * 在使用类对文件流进行操作的时候，写入时会先保存在缓存中，只有在类析构的时删除打开的文件流的时候才会把缓存写入到磁盘文件中  
4. 原子操作(compare and set)CAS atomic  
    * 最早是在java中实现的，C++11引入  
    * atomic  
    ```C++
    std::atomic<int> a; //定义一个原子的int 原子操作只能保证变量是线程安全的，不能保存多线程的时候代码逻辑是没有问题的  这个时候就需要用到mutex
    ```
5. 临界区 mutex 
    * 临界区的使用一定要十分的小心，如果lock()之后忘了unlock(),就会发生死锁的情况,连续两次调用lock()也会出现死锁的情况    
    * 如果调用接口，可能接口中会有lock(),导致死锁  
    * 在设计类的时候使用lock(),保证类的接口都是线程安全的  
    * 一般来说可以自定义一个模板mutex类，在构造函数中引用一个mutex,并上锁，在析构函数中解锁    
    ```C++
    template<typename T>
    class Lock{
      public:  
        Lock(T& mutex) : m_mutex(mutex) {
            m_mutex.lock();
        }
        ~Lock(){
            m_mutex.unlock();
        }
      private:
        T& m_mutex;
    };

    Lock<std::mutex> lock(m_mutex);
    ```
6. C++11中的lock模板  
    * lock_guard: ```std::lock_guard<std::mutex> lock(m_mutex);```  
    * lock 对许多锁进行加锁   ```std::lock(a.Mutex, b.Mutex)```,这个锁是会按着一定顺序进行加锁的  
    * lock_guard的优势：
        1. 灵活
        2. 可以配合实现按着一定顺序上锁，防止出现死锁的情况  
    ```C++
    std::lock(a.Mutex, b.Mutex /*.....*/)   // 这个标准的函数可以传入任意个锁，然后会按着一定的顺序是上锁，保证每一个调用的地方都是按着这个顺序上锁，但是不会主动解锁 
    /* 猜测一下实现，首先是去重，然后是排序，最后按排好的顺序加锁 */
    std::lock_guard<std::mutex> lockA(a.Mutex, std::adopt_lock);    //std::adopt_lock告诉构造函数，a.Mutex我已经锁上了，不用在构造函数中加锁了，只要在析构函数中解锁就行了
    std::lock_guard<std::mutex> lockB(b.Mutex, std::adopt_lock);    //释放锁  
    ```  
7. thread的两种死法
    * 线程创建之后，有两种管理方式，一种是有创建的程序管理，也就是程序员手动管理thread::join()。另一种就是交给操作系统管理，在线程运行结束之后自动释放资源thread::detach()  
    * thread::join(),用来管理线程，可以指定线程的执行顺序，当前线程会阻塞在这里等待join的线程完成，不会继续向下执行  
    * detach(),相当于把这个线程中进程控制块中踢出去，交给操作系统管理，后面的线程也不会再对这个线程进行什么操作了  
    * 实际上在调用join()函数之前，应该先进行一次判断```if(t.joinable()) t.join();```  
    * detach()的应用场景: 在做某件我不想管理的事情，很简单，不会出错，生命周期比整个程序的生命周期短很多，如果生命周期太短，在程序结束的时候会被杀掉，导致某些资源的析构函数会无法调用，资源直接被回收  
8. thread之间的交互,一些常用的函数  
    * std::this_thread::sleep_for(std::chrono::minutes(1)); 休眠sleep_for
    * std::this_thread::yield();    程序运行到这里时候会把CPU让出来，针对多核CPU  
    * 当cpu被长时间占用去做没什么意义的事的时候，比如开一个单独的线程跑一个循环去询问文件读取有没有完成，这样这个循环在读取完成之前一直在占用cpu，这里可以使用休眠函数，让这个线程每隔一段时间循环访问一次，这样用时间片的方式可以充分的利用CPU  
    * 锁空间不能开的太大，比如把sleep_for锁进去，就完全没有必要  
    * 不要频繁的加锁解锁,会占用大量的CPU和资源  

10. 多线程同步的四种方式  
    * 临界区，
    * 事件
    * 信号量
    * 互斥量

    
        
    
