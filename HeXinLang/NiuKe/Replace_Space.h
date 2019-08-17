/*请实现一个函数，将一个字符串中的每个空格替换成“%20”。
例如，当字符串为We Are Happy.则经过替换之后的字符串为We%20Are%20Happy。 */
#include "head.h"

using namespace std;
//思路：将空格转换为%20，该字符串长度会发生改变。
//先求出改变后的字符串的长度，然后从后向前依次替换
//从前往后的话，每次插入空格都要移动之后的字符，效率不高
//注意不能直接访问超过内存的数组位置，会发生越界错误
class solution{
public:
    void replaceSpace(char* str,int length)
    {
        int spacenum =  0;
        int len = 0;
        char* p = str;
        while(*p != '\0')
        {
            if(*p == ' ')
            {
                spacenum++;
                p++;
                len++;
            }
            else
            {
                p++;
                len++;
            }    
        }
        int nlen = len + spacenum * 2;
        if(nlen > length)
            return;
        while(len >= 0){
            if(str[len] != ' ')
            {
                str[nlen] = str[len];
                --len,--nlen;
            }else
            {
                str[nlen] = '0';
                str[nlen-1] = '2';
                str[nlen-2] = '%';
                --len;
                nlen-=3;
            }
            
        }
    }
};