    * new表达式与delete。
    new表达式(new operator)的工作一般分为三步.
    首先调用operator new分配一块内存足够大的空间来存储给定类型的对象，假如失败的话调用new_handler；
    然后编译器运行对应类型的构造函数构造对象；
    最后返回一个指向该对象的指针。
    delete函数首先执行指定对象的析构函数，然后释放内存。
    我们可以重载new，但实际上重载的不是new表达式，而是重载了operator new操作符。new表达式(new operator)是不可以重载的，也就是说，new表达式无论如何执行的都是上述三个步骤。
    可以定义自己的operator new(delete)版本，此时会覆盖标准库的operator new。标准库定义了几个不同版本的operator new函数,以new为例(数组版本类似)
    void* operator new(size_t size);
    void* operator new(size_t, nothrw_t&) noexcept;

    对于operator new函数，第一个形参必须是size_t格式，表示存储制定类型对象所需的字节数，返回类型必须是void*。
    对于operator delete函数，返回类型必须是void,第一个形参必须是void*，用来指向待释放的内存。
    重载时可以给函数新增实参，但是 void* operator new(size_t, void*);函数不允许被重载，该函数为标准库专用。如果重载了oprator new，则应该也重载operator delete。

    * malloc函数和free函数。
    malloc函数接受一个size_t类型的参数，表示待分配空间的字节数，返回一个void指针，分配失败时，返回0；free函数接受一个void*，将相关内存返回给系统，调用free(0)没有任何意义。

    * malloc和new的区别，如果malloc申请内存失败的话，不会调用分配内存失败处理程序，而new会。

    一个简单的重载new和delete：
    void* operator new(size_t size){
        cout << "newing..." << endl;
        if(void* men = malloc(size))
            return men;
        else
            throw bad_alloc();
    }
    void operator delete(void* men) noexcept{
        free(men);
    }

    * 定位new表达式(placement new)定义在头文件new中
    new (place_address) type
    new (place_address) type (initializers)
    new (place_address) type [size]
    new (place_address) type [size] {braced initializers list}
    如果使用这种方法，显式的调用构造函数在指定地址上构造了一个对象，则必须显示的调用析构函数。
    STL中alloctor使用的就是这种placement new
