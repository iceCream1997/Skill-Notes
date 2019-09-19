### STL框架： 容器 迭代器 算法  
1. 序列式容器和关联型容器  
    序列型容器：array/vector/deque/list/forword_list  按着插入顺序，是连续的  
    关联型容器：set/map/multiset/multimap   自动排序的  
    无顺序容器：unorder_map,unorder_set,unorder_multimap,unorder_multiset  
2. STL(C++11新加入)
    * 正则表达式  
    * rand()随机算法的优化  
    * thread async future  time  
3. 容器中保存的是什么  
    * 元素需要满足的条件：可以被复制和搬移(在拷贝和搬移的过程中没有副作用)；元素必须可以被赋值  
    * 容器里面存的是元素的值，不是引用  
4. 容器的通用接口  
    * 一般通过模板对容器进行操作  
    ```C++
    template <typename T>
    void containerAllInterface(T& a, T& b){
        T c;
        T d(a);  //copy
        T e = a;    //copy
        T ee{a};   //C++11
        T f(std::move(a));  //把a的东西移交给f，a中没有元素  
        auto iterB = b.begin();
        auto iterE = b.end();
        T g(iterB, iterE);  //copy
        b.size();   //绝大多数容器,std::forward_list没有
        b.empty();  //
        b.max_size();   //返回容器的最大容量  
        if(b == c){}    //会先比较数量，然后迭代器遍历  
        if(b != c){}

        e = b;
        e = std::move(b);
        e.swap(g);  //std::array  线性的交换,其他是o(1)
        swap(e,g);  //O(1),出了array
        
        e.cbegin(); // ->const_iterator
        auto ea = e.cbegin()
        *ea; // const&
        e.cend();
        e.clear();  // std::array 没有
    }
    ```
5. std::array  
    * 实际上是对C/C++原有的数组进行的封装  
    * 在建立的时候内存就已经声明好了，内存分配在栈上，内存不会重新分配,随机访问元素，一段连续的空间，可以随机访问到任何元素   
    * 不是线程安全的  
    ```C++
    /*namespace std{
        template<typename T, size_t N>
        class array;
    }*/
    std::array<int, 100> a; //未初始化
    std::array<int, 100> b = {};    //array里元素全部初始化为0
    std::array<int, 5> obj = {1,2,3,4,5};
    std::array<int, 5> obj2 = {1};  //第一个是1，后面补0

    auto aa = a;
    aa.swap(a); //遍历交换
    //访问元素
    a[1];       //不会检查下标是否合法  
    a.at(1);    //检查下标是否合法,下标不合法的时候回返回异常的  
    a.front();  //返回引用  
    a.back();   //返回引用
    a.cbegin();
    a.cend();   //const&
    a.rbegin();
    a.rend();   //从尾部向头部遍历
    a.crbengin();
    a.crend();  //const 从尾部遍历到头部  

    //和C的接口互用  
    std::array<char,100> carr;
    strcpy(&carr[0],"hello world\n");

    //特殊的地方
    auto info = std::get<1>(carr);  //carr[1]
    carr.fill(0);       //对所有的元素进行赋值  

    //异常 exception
    c.at(pos);  copy() move() swap() //这些在使用的时候都有可能发生异常  
    ```  
6. std::vector  
    * C++98引入的动态数组(dynamic array)  
    * 随机访问元素，末端添加删除元素效率高。前端和中间添加删除元素效率低，因为需要遍历的移动,删除会导致迭代器失效  
    * 存在当前容器大小和容量的关系，超出之后会重新分配2倍大小的空间，然后把之前的元素复制过去,插入也有可能导致迭代器失效  
    * 使用vector的场景，接收到的数据包
    ```C++
    using Group = std::vector<float>;

    Group a;
    Group b = a;
    Group c(a);
    Group d(10);    //大小为10，默认0
    Group e(10,1.0f);
    Group f(e.begin(),e.end()); 
    Group g({1.0f, 2.0f, 3.0f});
    Group h = {1.0f, 2.0f, 3.0f};   //C++11

    d.capacity();    //不会重新分配内存时，能保存元素的最大数目  
    d.reserve(100); //预先分配空间
    d.shrink_to_fit();  //C++11 

    //赋值
    b = g;
    b.assign(3,1.0f);   // {1.0f, 1.0f, 1.0f}
    b.assign(g.begin(), g,end());    // b = g
    b.assign({1.0f, 2.0f, 3.0f});   //重新赋值  

    b[0];
    b.at(0);
    b.front();
    b.back();   //引用  
    b.pop_back();   //线程不安全  

    b.erase(b.begin());     //返回删除元素的下一个位置，没有的话返回end()
    b.rease(b.begin(), b.end());

    b.push_back(10.0f);
    b.pop_back();
    auto iter = b.insert(b.end(), 100.0f);  //返回插入位置的迭代器  
    
    b.emplace(b.end(), 10.0f);    //C++11 原位插入
    b.emplace_back();   //可以直接传参构造，不需要构造之后push_back  

    b.clear();  //释放元素，调用析构函数，不会释放vector的内存  
    b.shink_to_fit();   //C++11,让vector的内存和保存的元素相符合，一般会降内存  

    //不要使用
    std::vector<bool> obj // not use
    ```
7. std::deque   
    * C++98中引入的动态数组，用栈上的指针操作堆上的内存 
    * 首部和尾部添加删除的效率很高,中间添加和删除效率低  
    * 元素的访问和迭代比vector慢，迭代器不是普通的指针,内存不是完全连续的，而是一块块的内存，通过指针连接起来  
    * 使用deque的场景,处理数据之后，发送回去时的缓存  
    ```C++
    using Group = std::deque<float>; 
    Group a;
    Group b = a;
    Group c(a);
    Group d(10);    //大小为10，默认0
    Group e(10,1.0f);
    Group f(e.begin(),e.end()); 
    Group g({1.0f, 2.0f, 3.0f});
    Group h = {1.0f, 2.0f, 3.0f};   //C++11

    //和vector不同，deque不提供以下函数
    /*d.capacity();
    d.reserve(100);*/
    d.shrink_to_fit();  //C++11 

    //赋值
    b = g;
    b.assign(3,1.0f);   // {1.0f, 1.0f, 1.0f}
    b.assign(g.begin(), g,end());    // b = g
    b.assign({1.0f, 2.0f, 3.0f});   //重新赋值  

    b[0];
    b.at(0);
    b.front();
    b.back();   //引用  
    b.pop_back();   //线程不安全  
   

    b.erase(b.begin());     //返回删除元素的下一个位置，没有的话返回end()
    b.rease(b.begin(), b.end());
    
    b.push_back(10.0f);
    b.push_front(0.0f);
    b.pop_back();
    b.pop_front();
    ```
8. std::list  
    * List是C++98引入的双向串列  
    * 不支持随机访问元素，访问头部和尾部元素的速度快  
    * list任何位置插入和删除都很快，因为是直接对指针进行操作，常量的时间就能完成
    * 插入和删除不会造成迭代器的失效  
    * 对于异常支持的很好，出现异常对于list而言，要么成功，要么什么影响都没有,如果是vector的话，比如删除出现了异常，vector里面本身的东西也可能出现错误    
    ```C++
    using Group = std::list<float>; 
    Group a;
    Group b = a;
    Group c(a);
    Group d(10);    //大小为10，默认0
    Group e(10,1.0f);
    Group f(e.begin(),e.end()); 
    Group g({1.0f, 2.0f, 3.0f});
    Group h = {1.0f, 2.0f, 3.0f};   //C++11

    //和vector不同，deque不提供以下函数
    /*d.capacity();
    d.reserve(100);
    d.shrink_to_fit();*/ 

    //赋值
    b = g;
    b.assign(3,1.0f);   // {1.0f, 1.0f, 1.0f}
    b.assign(g.begin(), g,end());    // b = g
    b.assign({1.0f, 2.0f, 3.0f});   //重新赋值  

    //交换
    b.swap(a);
    std::swap(a,b);

    //元素访问，不能随机访问
    /*b[0];
    b.at(0);*/
    b.front();
    b.back();   //引用  
    

    //迭代器访问元素
    auto iterBegin = a.begin();
    //assert(a.size() >= 10);
    //for(int i = 0; i < 5; i++) ++iterBegin;
    std::advance(iterBegin,4);
   

    b.erase(b.begin());     //返回删除元素的下一个位置，没有的话返回end()
    b.rease(b.begin(), b.end());
    
    b.push_back(10.0f);
    b.push_front(0.0f);
    b.pop_back();
    b.pop_front();

    //算法  
    b.remove(1.0f); //删除所有的1.0
    b.remove_if([](auto v){ return v > 100.0f;});
    b.reverse();    //反转链表1 2 3 4 -> 4 3 2 1
    b.sort();   //自动排序 < 这个sort会比std::sort要快,其实好像并不能对list用std::sort，因为list的自带排序对链表进行了特殊的处理  
    g.sort();   
    b.merge(g);  //把两个排好序的链表合并到b中，合并之后，g里面就没有东西了  
    c.unique(); //对于排好序的list去重，没有排序的话就只是连续的去重1 1 2 2 1 1 3 -> 1 2 1 3
    c.splice(c.begin(), b); //把b整个插入到c中的某个位置

    ```
9. std::forword_list(单向列表)
    * 特点和list差不多，不支持随机访问，访问头部的元素比较快  
    * 和自己手写实现的单向链表是一样的，空间和时间效率上是一样的  
    * 任何位置的插入和删除都很快，常量的时间完成  
    * 插入和删除不会造成迭代器失效  
    * 对异常有很好的支持，对我forward_list而言，要么成功，要么失败不会对元素造成影响  
     ```C++
    using Group = std::forword_list<float>; 
    Group a;
    Group b = a;
    Group c(a);
    Group d(10);    //大小为10，默认0
    Group e(10,1.0f);
    Group f(e.begin(),e.end()); 
    Group g({1.0f, 2.0f, 3.0f});
    Group h = {1.0f, 2.0f, 3.0f};   //C++11

    //和vector不同，deque不提供以下函数
    /*d.capacity();
    d.reserve(100);
    d.shrink_to_fit();*/ 

    //赋值
    b = g;
    b.assign(3,1.0f);   // {1.0f, 1.0f, 1.0f}
    b.assign(g.begin(), g,end());    // b = g
    b.assign({1.0f, 2.0f, 3.0f});   //重新赋值  

    //交换
    b.swap(a);
    std::swap(a,b);

    //元素访问，不能随机访问
    /*b[0];
    b.at(0);*/
    b.front();
    //b.back();   //引用  
    

    //迭代器访问元素
    a.before_begin();   //第一个元素的前面一个位置
    auto iterBegin = a.begin();
    //assert(a.size() >= 10);
    //for(int i = 0; i < 5; i++) ++iterBegin;
    std::advance(iterBegin,4);
   

    b.erase_after(b.before_begin());     //删除所给元素的下一个位置
    b.rease(b.before_begin(), b.end());     //return void   
    
    //b.push_back(10.0f);
    b.push_front(0.0f);
    //b.pop_back();
    b.pop_front();
    b.inster_after()

    //算法  
    b.remove(1.0f); //删除所有的1.0
    b.remove_if([](auto v){ return v > 100.0f;});
    //b.reverse();    //反转链表1 2 3 4 -> 4 3 2 1
    b.sort();   //自动排序 < 这个sort会比std::sort要快,其实好像并不能对list用std::sort，因为list的自带排序对链表进行了特殊的处理  
    g.sort();   
    b.merge(g);  //把两个排好序的链表合并到b中，合并之后，g里面就没有东西了  
    c.unique(); //对于排好序的list去重，没有排序的话就只是连续的去重1 1 2 2 1 1 3 -> 1 2 1 3
    c.splice(c.begin(), b); //把b整个插入到c中的某个位置

    ```  
10. std::set和std::multiset  
    * C++98引入的二叉树数据结构  
    * 都会自动排序，但是set中不能有重复的值，multiset中可以有重复的值  
    * 插入、删除和查找都是log(n)的，1000个元素大概20次左右,所以如果有频繁的在中间插入、删除和查找，或者希望数据按序的话，可以使用，频繁的修改可以用vector   
    * 元素必须支持严格的弱排序，即 a < a == false, a == b, b == c --> a == c;  
    * 不能改变元素的值  
    * 数据是以红黑数节点的形式保存的，消耗的内存会很大，左右节点、父节点、前驱指针、后驱指针，至少都有五个指针了  
    ```C++
    using Group = std::set<float>; // std::set<int,cmp> 自定义排序函数  
    Group a;
    Group b = a;
    Group c(a);
    Group d(10);    //大小为10，默认0
    Group e(10,1.0f);
    Group f(e.begin(),e.end()); 
    Group g({1.0f, 4.0f, 3.0f});
    Group h = {1.0f, 2.0f, 3.0f};   //C++11

    auto keycomp = c.key_comp();

    b = g;
   
    //交换
    b.swap(a);
    std::swap(a,b);

    //算法函数
    auto num = a.count(1.0f);   //set 0||1  multiset >= 0
    auto findIter = a.find(1.0f);       //返回迭代器,没有就返回end()

    auto lower  = a.lower_bound(1.0f);  //返回可以插入的位置，有可能会插入失败，因为可能会返回end(),表示不能再迭代器上插入，返回的是 <= 1.0f的位置，没有就是end()  
    auto high = a.upper_bound(1.0f);    //返回最后一个可插入的点,返回的位置是 > 1.0f的位置  
    auto range = a.equal_range(1.0f); //返回一个pair<a.lower_bound(1.0f), a.equal_range(1.0f)> 代表可插入的范围  
    
    auto state = b.insert(10.0f);   //返回插入位置的迭代器  

    //对于class
    class Person;
    using Group2 = std::set<Person, CompareName>;
    Group2 g2;

    auto iter = ge.find(aa);  //对于类来说，是按着名字排序的，就会按着名字查找，只要找到了名字相同，虽然年龄可能会不相同，但是还是会返回yes，返回名字相同位置的迭代器
    
    using Group = std::set<Person,CompareAge>;
    Group g;
    auto ageIter = g.begin();  
    //(*ageIter).changeAge(40); 这样也是不行的，索引存进去就是const的了，不能随便改变  

    g2.find(aa);    //也是根据构造的时候确定的比较索引进行比较查找的   
    iter = std::find(aa);   //std::find()是根据你自定义的 operator== 进行比较的  
    ```
11. std::map 和 std::multimap  
    * C++98引入的二叉树结构
    * 大多属性都和set一样，set中存的是值，map中是键值对，键不能更改，底层红黑树  
    * map中键不能重复，值可以重复，multimap中键值都可以重复  
    * 对于map的解引，是个const的pair类型  
    ```C++
    using Group = std::map<int,std::string>
    Group a;
    Group b = a;

    auto keycomp = c.key_comp();
    auto valcopm = c.val_comp(); 

    b = g;
   
    //交换
    b.swap(a);
    std::swap(a,b);

    //算法函数
    auto num = a.count(1.0f);   //和set一样，按key查找

    auto findIter = a.find(1.0f);       //返回迭代器,没有就返回end()，返回的其实是一个pair<const int, std::string>&,是一个引用    

    auto lower  = a.lower_bound(1.0f);  //返回可以插入的位置，有可能会插入失败，因为可能会返回end(),表示不能再迭代器上插入，返回的是 <= 1.0f的位置，没有就是end()  
    auto high = a.upper_bound(1.0f);    //返回最后一个可插入的点,返回的位置是 > 1.0f的位置  
    auto range = a.equal_range(1.0f); //返回一个pair<a.lower_bound(1.0f), a.equal_range(1.0f)> 代表可插入的范围  
    
    auto state = b.insert();   //返回插入位置的迭代器,插入的应该是一个pair，单独的插入返回的也是一个pair

    b.emplace(std::make_pair(10,"good"));   //emplace是以move的方式放入的 
    b.emplace(11,std::string("again"));     //会根据一些函数推导等，得到这个结果  
    b.empclae(12,"thrid");   

    b[13];      //如果不存在13这个键，会默认的构造一个值，因此没有构造函数的话，是不能用[]进行访问的
    auto& findInfo = b.at(13);  //有的话返回引用，没有的话返回异常  
    //可以的话，尽量使用find来访问数据    
    ```  
12. unorder_set和unorder_map
    * C++11新引入的，插入删除和查询的效率更高，hash_table实现  
    * 不会自动排序，无序的  
    * 极端情况下，性能不稳定  
    * 实现时用了桶，空间上消耗会更多,大概1000W数据是个分水岭，超过1000W数据时，unorder_map的效率会下降，可能会不断的重构等，1000W之前效率很高  
    * 元素允许有重复的，注意解决hash冲突的方法  
