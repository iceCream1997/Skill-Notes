### C++关键字  
1. alignas和alignof(c++11)  
    alignas：用在struct关键字后面，用来指定结构体的对齐字节，但是不能小于结构体本身所需要的最小对齐字节，比如结构体中有int类型，alignas不能小于4，小于4的时候会无效，即使alignas(2),对齐字节也是4，alignas(0)会被忽略，按着默认计算    
    alignof：用来计算对齐字节  
    ```C++
    struct alignas(8) A{
        char a;
    };
    struct B{
        char a;
        int b;
    };
    sizeof(A) = 8;
    sizeof(B) = 8;
    alignof(A) = 8;
    alignof(B) = 4;
    ```    
2. and和and_eq(c++11)
    * and 即 &&,```(a == 1) && (b == 1)```等价于```(a == 1) and (b == 1)```  
    * and_eq 即 &=, ```b &= a; b = b&a; b and_eq a;```这三个是等价的，都是将b和a做与运算后赋值给b  
3. asm：用来嵌套汇编语言       
5. bitand:&, bitor:|, ```a&b; a bitand b;```等价  
6. compl(c++11) 等价 ~,按位取反，二进制0变1，1变0  
7. constexpr(c++11) 
    * 加在函数前，可以使函数在编译期展开执行，前提是函数已经确定     
    * 还可以防止类 类型的隐式转换
8. decltype(c++11) 获得表达式的返回值  
    ```C++
    int a = 10;
    decltype(a) b = a;  //和auto b = a;一样
    //还可以用来指定函数的返回值类型  
    template<typename T,typename U>
    auto add(T a,U b)->decltype(a+b){
        return a+b;  //把a+b的类型做为返回值类型  return (c),返回c的引用
    }
    ```
9. dynamic_cast(c++11) 
    * 将指向派生类的基类指针或引用，安全的转换为派生类的指针或引用，并用派生类的指针或引用调用非虚函数。如果是基类指针或引用，调用的是虚函数不需要转换，只需要用基类指针指向派生类即可,调用的虚函数要和基类的虚函数同名。  
    * 转换的前提是基类必须含有虚函数，如果转化指针失败会返回null,转换引用失败会抛出异常  
10. enum 枚举,和结构体里面的数组有些类似,弱类型   
    ```C++
    enum DAY{
        MON=1,TUE,WED,THU,FRI,SAT,SUN  //默认0为初识下标
    };

    DAY day;
    day = TUE;
    cout<<day<<endl;  // 2
    if(day == TUE){  //如果有另外一个枚举类型中含有TUE，会不知道是哪一个enum中的
        cout<<"ok"<<endl;  // ok
    }
    ```  
    enum class(C++11):强类型  
    ```C++
    enum class NewClassDay : long{//默认int
         MON=1,TUE,WED,THU,FRI,SAT,SUN 
    };
    NewClassDay day;
    day = NewClassDay::WED;
    if(day == NewClassDay::WED){
        cout<<"ok"<<endl;   // ok
    }
    ```
11. explicit,只允许显示的调用
    ```C++
    struct A {
        A(int) {}
        A(int,int) {}
        operator int () const{return 0;}
    };
    struct B {
        explicit B(int) {}
        explicit B(int,int) {}
        explicit operator int () const{return 0;}
    };
    A a1 = 1; //A a1 = A(1) ok
    B b1 = 1;//false
    A a2(2); // ok
    B b2(2); //ok
    int na1 = a1; //ok operator支持强转  
    int nb1 = b2;//false 隐式调用
    int na2 = static_cast<int> a1; //显示转换 ok
    int nb2 = static_cast<int> b2; //ok
    ```  
12. friend 友元
    * 在类中可以声明友元函数和友元类，友元函数和友元类可以调用该类的几乎所有成员(包括私有成员)
    ```C++
    class A{
        private:
        int data;
        public:
        friend void F(A a);
        friend class B;
    };
    void F(A a){
        cout<<a.data<<endl;
    }
    ```
    * 对于类来说，friend关系只是单向的，A并不是B的友元，所以A无法访问B的成员  
    * 友元关系不能继承  
13. namespace 命名空间,可以在代码中开辟出一块命名空间，也可以没有名字，不过没有名字的话，对其他的文件是匿名的，就是说其他的c++文件看不到这个空间    
    ```C++
    namespace GroupA{
        class A{
            int value;
        };
    }

    namespace GroupB{
        class A{
            int value;
        };
        class B{
            int value;
        };
    }
    GroupA::A a1;
    GroupB::A a2;
    using namespace GroupB;//省略前缀
    B a3; 
    ```  
13. noexpect(C++11)
    * 加在函数前面，用来告诉编译器，我这个函数绝对不会抛出异常，让编译器可以使用一些优化的手段，但是不建议使用，因为你很难保证你的函数不会出现异常。  
14. nullptr(C++11)  
    * NULL在C中是(void*)0,在C++中是0,C++对类型的要求更加严格  
    * nullptr在C++中是一个类型，具体的话，我也没弄的太懂，建议使用nullptr
    ```C++
    void test(int *a);
    test(NULL); //无法调用test
    test(nullptr);//可以调用test
    ```
15. static静态  
    * 全局的静态变量，在编译的时候进行初始化，而局部的静态变量，在第一次使用的时候进行初始化，在程序结束的时候才会销毁  
    * struct中的静态数据,是保存在静态空间的，所以不会算入struct的大小  
    ```C++
    struct S{
    static int s;
    };
    int S::s = 10;
    std::cout<<sizeof(S)<<std::endl;  // 1 
    std::cout<<S::s<<endl;   // 10
    ```
    * struct和class里面的静态变量都要在结构体外和类外进行初始化，同时可以直接使用类名调用类的静态成员而不用实例化    
16. static_assert(C++11)  
    * 编译时进行判断，如果发现条件不满足会中断编译并且报错,assert()是一个宏，在运行调试的时候进行判断
    ```C++
    static_assert(1 == 2); //报错，中断编译，只有在编译才能起作用，编译完成之后会优化掉的
    assert(1 == 2) //运行时判断，条件不成立直接中断程序
    ```
17. typedef 对类型命名，C++11以前用的很多  
    ```C++
    typedef unsigned ulong;
    typedef std::map<int,ulong> Group;
    Group a;
    std::map<int,ulong>::iterator iter = a.begin();
    Group::iterator iter = a.begin();
    auto iter = a.begin()  //c++11之后
    ``` 
18. using 
    ```C++
    typedef std::map<int,ulong> Group;
    using Group = std::map<int,ulong>; //这两个是一样的
    ```
19. volatile 告诉编译器不要进行任何优化  
