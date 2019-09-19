### C++类相关知识
1. 尽量使用前置声明   
    ```C++
      class Parent;
      class Child{
      public:
          explicit Child(Parent p):m_parent(&p){}//这里编译时会报错，因为编译器不知道p局部变量的大小，无法正确的分配内存，改成指针就可以了，因为指针占用的内存是固定的(4/8字节)  
      private:                                    //函数在编译的时候要知道参数的类型，表现为要知道参数的大小，这样才能进行参数检查
          Parent* m_parent;
      };
      ```
    * 可以解决两个类相互调用，解决先有鸡还是先有蛋的问题  
    * 如果对类的操作全部都是通过指针和引用的方式来调用类的接口，可以使用前置声明的方式来代替直接使用头文件，头文件过多会导致编译的很慢      
    * 前置声明是一个不完全的类型，如果不引入类的完整声明的话，在需要完整类型的时候会报错(assert运行时)，可以做为返回值的类型，但是不能做为返回值  
    * 不能用前置类代替include的类型:继承(做为基类)、做为类成员

2. 类的三个原则  
    1. 如果有需要自己管理的资源，要在构造函数中申请资源，在析构函数中释放资源。(会默认的生成析构函数，默认的析构函数不会释放自己申请的资源，造成内存泄漏)  
    2. 如果类能够被拷贝，一定要明确的写出拷贝构造函数。(没有写明拷贝构造函数的话，会自动生成拷贝构造函数，默认浅拷贝，会造成资源的重复释放等问题，野指针)   
    3. 如果有自己需要管理的资源，等号拷贝也一定要自己重载。(会默认生成，浅拷贝)  
    * 如果类设计为singlton，需要自己声明拷贝构造函数和等号拷贝(不需要实现)，并且声明为私有函数,这样做是为了不让构造器生成默认的拷贝构造函数和重载=运算符。
    ```C++
      //C++11之后可以这么写:  
      class A{
      private:
        A () = delete;
        A operator=() = delete;  
      };  
      //或者引入第三方的boost库  
      #include<boost/noncopyble.hpp>
      class A : boost::noncopyble {
        //这样也可以不用写拷贝构造函数和重载=运算符  
      };
    ```  

3. C++11之后变成了五个原则(新加了两个)   
      4. std::move(),可以将左值变成右值,针对右值引用进行拷贝构造函数重载  
      5. std::move(),要对=运算符的重载   
      * 不需要进行进行右值操作时也要声明这两个函数=delete
      ```C++
      class A {
      public:
        A(const A& rhs): m_val(new int(*(rhs.m_val) )){}
        A(A&& rhs){
          m_val = rhs.m_val;
          rhs.m_val = nullptr;
        }
        A& operator=(A&& rhs){    //这样写是有错误的，如果是自引用，即自己引用自己就会有错误  
          if(&rhs == this) return this; //不写这个就会发生自引用错误
          delete m_val;  //删除自己所拥有的内存，防止内存泄漏
          m_val = rhs.m_val;
          rhs.m_val = nullptr;
          return *this;
        }  
      private:
        int *m_val;
      } 
      A a;
      //调用右值引用拷贝构造函数
      A&& b = std::move(a);  //对a的资源右值化，用b去右值引用a的资源，引用之后a不建议继续使用，因为不知道a的资源发生了什么
      A c;
      A d;
      c = std::move(d); //调用=运算符赋值
      ```
  
3. 左值和右值  
    * 有名字，有类型，有值，是左值，有值，有类型，没有名字是右值。右值是不能取地址，左值可以取地址。
    * 因为右值不能被引用，且只会使用一次，会浪费资源，为了节省这一部分资源，所以引入了右值引用。
    ```C++
    int getNum(){
      int a = 10;
      return a; //是一个临时变量，在函数内可以取地址，在函数外不能取地址，所以在函数体外是一个右值
    }
    int&& a = getNum();//右值引用
    int a = 10;
    int&& b = std::move(a);  //可以将a的资源右值化，然后b引用这个右值，但是a还在，任然是左值，move只是将a的资源右值化并不做任何移动
    cout<<"a:"<<a<<"b:"<<b<<endl;//a:10 b:10
    b = 5;
    cout<<"a:"<<a<<"b:"<<b<<endl;//a:5  b:5
    return 0;
    ```  

4. 不要在析构函数中抛出异常  
    * 类在构造的时候，先调用基类的构造函数，再调用派生类的构造函数，在析构时，先调用派生类的析构函数去析构成员，再调用基类的析构函数  
    * 析构函数默认是noexcept,如果析构函数里抛出异常，在编译阶段就会出现错误  
    * 如果强行用noexcept(false)在析构函数里抛出异常，用try{}catch{}去捕获，会出现抛出多个异常的情况，一个try{}catch{}只能处理一个异常  
    * 强行用noexcept(false)在析构函数中抛出异常，可能会导致资源释放失败  

5. 构造函数失败应该抛出异常  
    * 类的构造中出了错误，应该抛出异常，告诉使用者哪里出了异常  
    * swap()也不能抛出异常  

6. 虚函数遇见构造函数和析构函数会退化  
    * 类中在重载函数的时候可以加上override关键字，编译器在编译的时候回进行检查，如果没有对应的虚函数时会报错  
    ```C++
    class Base{
    public:
      virtual void f(){ std::cout << "Base\n";}
      virtual ~Base(){}
    };
    class Derived : Base {
        void f () override{
          Base::f();    //调用基类的虚函数
          std::cout << "Derived\n";
        }
    }
    ```
    * 类如果在构造和析构函数中调用自己的虚函数，调用的是类自己的虚函数，这个就是退化，因为是利用this指针进行的调用  
    * 如果类的成员函数中有虚函数，且析构函数是public的，这时候需要把析构函数声明为虚函数  

7. 重新审视auto  
    * 在函数中使用，会覆盖掉外来的同名变量  
    * auto指向常量字符串时，是常量的字符指针  
    ```C++
    void autoValue(bool age){//外来age，会被覆盖掉
      auto age = 10;
      auto height = 160.0f;  //float
      auto weight = 50.0;     //double

      auto name = std::string("Yt");   //string
      auto name = "Yt";     //const char*
    }
    ```

8. 左值引用和右值引用  
    * 老版本中，对左值的引用可以是普通引用和const引用，但是对右值的引用必须是const引用
    * 新版本后可以用&&对右值进行普通引用

9. 智能指针  
    * 为了解决内存泄漏的问题```#include<memeory>```,auto_ptr(老版本),shared_ptr(C++11,常用)，unique_ptr(C++11)  
    * shared_ptr,通过引用，每使用一次引用计数加一，没析构一次引用计数减一，用来共享指针    
    * unique_ptr,这个指针，只能有一个使用者  
    * weak_ptr,和share_ptr一起使用  
    ```C++
    typedef std::shared_ptr<int> intPtr; 
    intPtr num1(new int(1));
    std::cout << num1.use_count() << std::endl;  //打印出指针的使用者   1
    intPtr null;
    std::cout << null.use_count() << std::endl;   // 0
    intPtr num2(num1);                            //共享同一个指针
    std::cout << num1.use_count() << std::endl;   // 2
    std::cout << num2.use_count() << std::endl;   // 2
    num2.reset();                                 // 不需要使用后释放指针
    num2 = nullptr;
    std::cout << num1.use_count() << std::endl;   // 1

    intPtr num3;
    num1.swap(num3);        //交换资源
    auto p = num3.get();    //返回普通的指针
    
    if(num3){....}    //还原了很多指针的操作，比如,重载了 -> 和 *

    num3.unique()     //判断智能指针是不是唯一的,效率可能会比if(num3.use_count() )要高，多线程的情况下
    ```   
    * shared_ptr 用weak_ptr打破循环引用，在原本使用shared_ptr的地方使用weak_ptr可以打破循环引用带来的问题，shared_ptr循环引用会导致资源释放不掉，内存泄漏  
    ```C++
    typedef std::shared_ptr<Object> ObjPtr;
    typedef std::weak_ptr<Object> weakObjPtr;
    Objptr obj(new Object(1));
    weakObjPtr weakObj(obj);
    std::cout << obj.use_count() << std::endl;    //1
    {
      auto p = weakObj.lock();    // auto === ObjPtr  weak指向的shared_ptr如果引用计数不为0，有效，返回shared_ptr,如果为0，返回shared_ptr的空指针  
      if(p){
        std::cout << p.unique() << std::endl;   //false  p.use_count() >= 2,原本至少为1，加上p，所以是至少为2  
      }
    }
    obj.reset();
    auto p = weakObj.lock();    //返回为空的指针，因为obj不在指向任何资源了，所以返回为空,weak_ptr,判断shared_ptr指向的资源是否为空  

    weakObj.expired()     //可以不会返回shared_ptr判断资源是不是被引用      
    ```   
    * 在使用类中使用指针时不要用this指针构造shared_ptr,因为类的成员函数出了作用域之后可能会析构shared_ptr,如果想从this指针获得shared_ptr，需要公有继承一个模版类，enable_shared_from_this<>  
    ```C++
    class Child : public std::enable_shared_form_this<Chlid>{     //当使用了enable_shared_form_this，就表明我要用只能指针来管理这个类，就不要当成一个普通的类来使用  
    public:
      test(){
        shared_from_this()  //函数，当需用从this指针得到shared_ptr时调用，保存了一个weak_ptr,通过把weak_ptr转换成shared_ptr  
      }
    }
    ```  
    * unique_ptr,一份资源只能有一个使用者，保证析构函数一定会调用,用来处理指针，释放资源,建议能使用nuiuqe_ptr就不要用shared_ptr    
    ```C++
    typedef std::unique_ptr<Object> UniqueObjectPtr;
    typedef std::shared_ptr<Object> ObjectPtr;  

    UniqueObjectPtr obj(new Object(1));

    auto p = obj.get();         //获得原生指针 
    if(p){}
    if(obj){}      // bool 操作
    obj->print();   // -> * 普通指针的使用方法

    p = obj.release();   //不需要管理资源，取消对资源的管理并把资源交给一个普通的指针  
    delete p;

    obj.reset();   //释放管理的资源，没有就什么都不做
    obj.reset(new Object(2));   //释放已有的，指向新管理的  

    std::move(obj); //转换成右值，资源交出去之后就不再拥有资源，一份资源只能有一个使用者

    //在使用中发现不只一个使用者需要使用这份资源，需要转化为shared_ptr
    ObjectPtr sharedObj(std::move(obj));
    assert(obj == nullptr); //资源转移之后就为空  
    return 0;
    ```
    * 智能指针需要注意的点:
     1. 前提:绝对不要自己管理资源  
     2. 一个裸的指针不要用两个shared_ptr管理,unique_ptr也是  
     ```C++
      auto pObj = new Object(1);
      ObjectPtr obj(pObj);
      ObjectPtr obj2(pObj); //会调用两次析构函数

      ObjectPtr obj2(obj);  //应该这么使用  
     ```
     3. weak_ptr打破循环引用,parent,child
     4. 在类的内部接口中，需要将this指针做为智能指针来使用，需要用该类派生自enable_shared_form_this()  
     5. 使用shared_ptr做为函数接口时，如果有可能有const shared_ptr& 的形式  
     6. shared_ptr 和 weak_ptr 和裸指针在效率上会大很多，尤其是在多线程下。  
        空间上:裸指针在64位下8字节，64位，一般使用48位(英特尔处理器),剩下12位没有使用。shared_ptr,首先是指针8字节，一个引用计数，配合weak_ptr，要保存weak_ptr的数目,即两个引用计数和一个指针，至少3个裸指针大小，32字节  
        时间上: 两个引用计数拷贝，其中一个还要+1,还有一个指针拷贝，多线程下为了保证原子操作，要更复杂。时间主要是在调用new上，，多次new，地址空间不连续，导致调用的时间会增加    
        ```C++
        ObjectPtr obj(new Object(1));
        ObjectPtr obj = std::make_shared<Object>(3);  //功能上一样，但是只会调用一次new，包括Object,智能指针所需的引用计数，指针位，地址连续,还能节省空间         
        ```
     7. 在构造和析构函数中，不能使用enable_shared_form_this 和 shared_form_this, 构造函数中，类还没有构造好，无法使用，析构时，马上就要进行析构了，使用也没有意义  
     8. 某些情况下，使用智能指针会出现内存不会降的情况，比如weak_ptr处理循环引用的时候，虽然已经没有使用这份资源了，但是weak_ptr仍然指向这份资源，导致资源无法释放  
     9. 可能的话，尽量使用类的实例，类的实例不行的时候必须要使用指针，可以先用std::unique_ptr，最后万不得已再使用shared_ptr  
     10. 智能指针的性能损耗在于，解引用，瓶颈点,因此不要用weak_ptr存数据，有一个解引的过程，十分损耗性能，weak_ptr还是还是用来解决shared_ptr的循环引用的      


